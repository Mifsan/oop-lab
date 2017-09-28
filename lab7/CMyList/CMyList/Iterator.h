#pragma once
#include "Node.h"

template <typename ValueType>
class CIterator : public std::iterator<std::bidirectional_iterator_tag, ValueType>
{

public:
	using NodeType = Node<std::decay_t<ValueType>>;

	CIterator() = default;

	CIterator(NodeType * node)
		: m_node(node)
	{
	}

	typename reference operator*() const
	{
		if (m_node != nullptr && m_node->next != nullptr && m_node->prev != nullptr)
		{
			return m_node->data;
		}
		else
		{
			throw runtime_error("CMyList iterator not dereferencable");
		}
	}

	bool operator==(CIterator<ValueType> const& other) const
	{
		return m_node == other.m_node;
	}

	bool operator!=(CIterator<ValueType> const& other) const
	{
		return m_node != other.m_node;
	}

	CIterator<ValueType> & operator++()
	{
		if (m_node->next != nullptr)
		{
			m_node = m_node->next.get();
		}
		else
		{
			throw out_of_range("CMyList iterator not incrementable");
		}
		return *this;
	}

	CIterator<ValueType> & operator--()
	{
		if (m_node->prev != nullptr && m_node->prev->prev != nullptr)
		{
			m_node = m_node->prev;
		}
		else
		{
			throw out_of_range("CMyList iterator not decrementable");
		}
		return *this;
	}

	pointer operator->()const
	{
		return pointer_traits<pointer>::pointer_to(**this);
	}

	CIterator<ValueType> operator++(int)
	{
		CIterator<ValueType> tmp = *this;
		++*this;
		return tmp;
	}

	CIterator<ValueType> operator--(int)
	{
		if (m_node->prev != nullptr && m_node->prev->prev != nullptr)
		{
			CIterator<ValueType> tmp = *this;
			--*this;
			return tmp;
		}
		else
		{
			throw out_of_range("CMyList iterator not decrementable");
		}
	}
private:
	NodeType * m_node = nullptr;
	template <class T>
	friend class CMyList;
};