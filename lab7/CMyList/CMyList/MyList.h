#pragma once
#include "Iterator.h"


template <typename T>
class CMyList
{
public:
	CMyList();
	CMyList(const CMyList<T> & other);
	~CMyList();
	CMyList(CMyList<T> && other);

	CMyList<T> & operator = (CMyList<T> const & other);
	CMyList<T> & operator = (CMyList<T> && other);

	size_t GetSize() const;
	bool IsEmpty() const;

	void AppendBack(const T & data);
	void AppendFront(const T & data);
	void Insert(const CIterator<T> & it, T const & data);

	void Erase(const CIterator<T> & it);
	void Clear();

	CIterator<T> begin();
	CIterator<T> end();
	CIterator<const T> begin() const;
	CIterator<const T> end() const;
	CIterator<const T> cbegin() const;
	CIterator<const T> cend() const;

	std::reverse_iterator<CIterator<T>> rbegin();
	std::reverse_iterator<CIterator<T>> rend();
	std::reverse_iterator<CIterator<const T>> rbegin() const;
	std::reverse_iterator<CIterator<const T>> rend() const;
	std::reverse_iterator<CIterator<const T>> crbegin() const;
	std::reverse_iterator<CIterator<const T>> crend() const;

private:
	size_t m_size = 0;
	std::unique_ptr<Node<T>> m_firstNode = nullptr;
	Node<T> * m_lastNode = nullptr;
};


using namespace std;

template <typename T>
CMyList<T>::CMyList()
{
	m_firstNode = make_unique<Node<T>>(nullopt, nullptr, nullptr);
	m_firstNode->next = make_unique<Node<T>>(nullopt, m_firstNode.get(), nullptr);
	m_lastNode = m_firstNode->next.get();
}

template <typename T>
CMyList<T>::CMyList(const CMyList<T> & other)
	: CMyList<T>()
{
	try
	{
		for (auto const & data : other)
		{
			AppendBack(data);
		}
	}
	catch (...)
	{
		Clear();
		throw;
	}

}

template <typename T>
CMyList<T>::CMyList(CMyList<T> && other)
	: CMyList<T>()
{
	swap(m_firstNode, other.m_firstNode);
	swap(m_lastNode, other.m_lastNode);
	swap(m_size, other.m_size);
}

template <typename T>
CMyList<T> & CMyList<T>::operator=(CMyList<T> const & other)
{
	if (this != addressof(other))
	{
		CMyList<T> tmp(other);
		swap(m_firstNode, tmp.m_firstNode);
		swap(m_lastNode, tmp.m_lastNode);
		swap(m_size, tmp.m_size);
	}
	return *this;
}

template <typename T>
CMyList<T> & CMyList<T>::operator=(CMyList<T> && other)
{
	if (this != addressof(other))
	{
		CMyList<T> tmp(move(other));
		swap(m_firstNode, tmp.m_firstNode);
		swap(m_lastNode, tmp.m_lastNode);
		swap(m_size, tmp.m_size);
	}
	return *this;
}

template <typename T>
CMyList<T>::~CMyList()
{
	Clear();
}

template <typename T>
size_t CMyList<T>::GetSize() const
{
	return m_size;
}

template <typename T>
bool CMyList<T>::IsEmpty() const
{
	return m_size == 0;
}

template <typename T>
void CMyList<T>::AppendBack(const T & data)
{
	Insert(end(), data);
}

template <typename T>
void CMyList<T>::AppendFront(const T & data)
{
	Insert(begin(), data);
}

template <typename T>
void CMyList<T>::Insert(const CIterator<T> & it, const T & data)
{
	unique_ptr<Node<T>> newNode = make_unique<Node<T>>(make_optional(data), it.m_node->prev, move(it.m_node->prev->next));
	it.m_node->prev = newNode.get();
	newNode->prev->next = move(newNode);
	++m_size;
}

template <typename T>
void CMyList<T>::Erase(const CIterator<T> & it)
{
	if (m_size == 0)
	{
		throw out_of_range("Erase() called on empty CMyList");
	}
	else if (it == end())
	{
		throw out_of_range("CMyList erase iterator outside range");
	}
	it.m_node->next->prev = it.m_node->prev;
	it.m_node->prev->next = move(it.m_node->next);
	--m_size;
}

template <typename T>
void CMyList<T>::Clear()
{
	while (m_size != 0)
	{
		Erase(begin());
	}
}

template <typename T>
CIterator<T> CMyList<T>::begin()
{
	return m_firstNode->next.get();
}

template <typename T>
CIterator<const T> CMyList<T>::begin() const
{
	return m_firstNode->next.get();
}

template <typename T>
CIterator<T> CMyList<T>::end()
{
	return m_lastNode;
}

template <typename T>
CIterator<const T> CMyList<T>::end() const
{
	return m_lastNode;
}

template <typename T>
CIterator<const T> CMyList<T>::cbegin() const
{
	return begin();
}

template <typename T>
CIterator<const T> CMyList<T>::cend() const
{
	return end();
}

template <typename T>
reverse_iterator<CIterator<T>> CMyList<T>::rbegin()
{
	return reverse_iterator<CIterator<T>>(end());
}

template <typename T>
reverse_iterator<CIterator<const T>> CMyList<T>::rbegin() const
{
	return reverse_iterator<CIterator<const T>>(end());
}

template <typename T>
reverse_iterator<CIterator<T>> CMyList<T>::rend()
{
	return reverse_iterator<CIterator<T>>(begin());
}

template <typename T>
reverse_iterator<CIterator<const T>> CMyList<T>::rend() const
{
	return reverse_iterator<CIterator<const T>>(begin());
}

template <typename T>
reverse_iterator<CIterator<const T>> CMyList<T>::crbegin() const
{
	return rbegin();
}

template <typename T>
reverse_iterator<CIterator<const T>> CMyList<T>::crend() const
{
	return rend();
}
