#pragma once

#include <new>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <cassert>

template <typename T>
class CMyArray
{
public:

	CMyArray() = default;

	CMyArray(const CMyArray& arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

	CMyArray(CMyArray&& arr)
		: m_begin(std::move(arr.m_begin))
		, m_end(std::move(arr.m_end))
		, m_endOfCapacity(std::move(arr.m_endOfCapacity))
	{
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	void Append(const T & value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T *newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				// Конструируем копию value по адресу newItemLocation
				new (newEnd)T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			// Переключаемся на использование нового хранилища элементов
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else // has free space
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	T & GetBack()
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	const T & GetBack()const
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	size_t GetSize()const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity()const
	{
		return m_endOfCapacity - m_begin;
	}

	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}

	void Clear()
	{
		if (GetSize() > 0)
		{
			DestroyItems(m_begin, m_end);
			m_end = m_begin;
			m_endOfCapacity = m_end;
		}
	}

	void Resize(const size_t newSize)
	{
		for (;currSize > newSize; currSize--)
		{
			m_end->~T();
			m_end--;
		}

	}

	CMyArray & operator = (const CMyArray & arr)
	{
		if (this != &arr)
		{
			Clear();
			CopyFrom(arr);
		}
		return *this;
	}

	CMyArray & operator = (CMyArray && arr)
	{
		if (this != &arr)
		{
			Clear();

			m_begin = arr.m_begin;
			m_end = arr.m_end;
			m_endOfCapacity = arr.m_endOfCapacity;

			arr.m_begin = nullptr;
			arr.m_end = nullptr;
			arr.m_endOfCapacity = nullptr;
		}

		return *this;
	}

	T & operator[](const size_t index)
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("Index out of range");
		}

		return m_begin[index];
	}

	T & operator[](const size_t index)const
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("Index out of range");
		}

		return m_begin[index] const;
	}

	typedef T* iterator;
	typedef const T* const_iterator;
	iterator begin()
	{
		return m_begin;
	}
	const_iterator begin() const
	{
		return m_end;
	}
	iterator end()
	{
		return m_end;
	}
	const_iterator end() const
	{
		return m_end;
	}
	const_iterator cbegin() const
	{
		return begin();
	}
	const_iterator cend() const
	{
		return end();
	}

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}
	const_reverse_iterator crbegin() const
	{
		return rbegin();
	}
	const_reverse_iterator crend() const
	{
		return rend();
	}

private:

	static void DestroyItems(T *from, T *to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
			to->~T();
		}
	}

	static void DeleteItems(T *begin, T *end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T *srcBegin, T *srcEnd, T * const dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd)T(*srcBegin);
		}
	}

	static T *RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T *p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T *p)
	{
		free(p);
	}

	void CopyFrom(const CMyArray& arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);  /// <==== (1)
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}
private:
	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;
};