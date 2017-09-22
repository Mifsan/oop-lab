#include "stdafx.h"
#include "StringList.h"

using namespace std;

CStringList::CStringList()
{
	m_firstNode = make_unique<Node>("", nullptr, nullptr);
	m_firstNode->next = make_unique<Node>("", m_firstNode.get(), nullptr);
	m_lastNode = m_firstNode->next.get();
}

CStringList::CStringList(const CStringList & other)
	: CStringList()
{
	for (auto const & data : other)
	{
		AppendBack(data);
	}
}

CStringList::CStringList(CStringList && other)
	: CStringList()
{
	swap(m_firstNode, other.m_firstNode);
	swap(m_lastNode, other.m_lastNode);
	swap(m_size, other.m_size);
}

CStringList & CStringList::operator=(CStringList const & other)
{
	if (this != addressof(other))
	{
		CStringList tmp(other);
		swap(m_firstNode, tmp.m_firstNode);
		swap(m_lastNode, tmp.m_lastNode);
		swap(m_size, tmp.m_size);
	}
	return *this;
}

CStringList & CStringList::operator=(CStringList && other)
{
	if (this != addressof(other))
	{
		CStringList tmp(move(other));
		swap(m_firstNode, tmp.m_firstNode);
		swap(m_lastNode, tmp.m_lastNode);
		swap(m_size, tmp.m_size);
	}
	return *this;
}

CStringList::~CStringList()
{
	Clear();
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

void CStringList::AppendBack(const string & data)
{
	Insert(end(), data);
}

void CStringList::AppendFront(const string & data)
{
	Insert(begin(), data);
}

void CStringList::Insert(const CIterator & it, const string & data)
{
	auto newNode = make_unique<Node>(data, it.m_node->prev, move(it.m_node->prev->next));
	it.m_node->prev = newNode.get();
	newNode->prev->next = move(newNode);
	++m_size;
}

void CStringList::Erase(const CIterator & it)
{
	if (m_size == 0)
	{
		throw out_of_range("Erase() called on empty CStringList");
	}
	else if (it == end())
	{
		throw out_of_range("CStringList erase iterator outside range");
	}
	it.m_node->next->prev = it.m_node->prev;
	it.m_node->prev->next = move(it.m_node->next);
	--m_size;
}

void CStringList::Clear()
{
	while (m_size != 0)
	{
		Erase(begin());
	}
}

CStringList::CIterator CStringList::begin()
{
	return m_firstNode->next.get();
}

CStringList::CIterator CStringList::begin() const
{
	return m_firstNode->next.get();
}

CStringList::CIterator CStringList::end()
{
	return m_lastNode;
}

CStringList::CIterator CStringList::end() const
{
	return m_lastNode;
}

CStringList::CIterator CStringList::cbegin() const
{
	return begin();
}

CStringList::CIterator CStringList::cend() const
{
	return end();
}

reverse_iterator<CStringList::CIterator> CStringList::rbegin()
{
	return reverse_iterator<CStringList::CIterator>(end());
}

reverse_iterator<CStringList::CIterator> CStringList::rbegin() const
{
	return reverse_iterator<CStringList::CIterator>(end());
}

reverse_iterator<CStringList::CIterator> CStringList::rend()
{
	return reverse_iterator<CStringList::CIterator>(begin());
}

reverse_iterator<CStringList::CIterator> CStringList::rend() const
{
	return reverse_iterator<CStringList::CIterator>(begin());
}

reverse_iterator<CStringList::CIterator> CStringList::crbegin() const
{
	return rbegin();
}

reverse_iterator<CStringList::CIterator> CStringList::crend() const
{
	return rend();
}

CStringList::CIterator::CIterator(Node * node)
	:m_node(node)
{
}

string & CStringList::CIterator::operator*() const
{
	if (m_node != nullptr && m_node->next != nullptr && m_node->prev != nullptr)
	{
		return m_node->data;
	}
	else
	{
		throw runtime_error("CStringList iterator not dereferencable");
	}
}

bool CStringList::CIterator::operator==(CIterator const& other) const
{
	return m_node == other.m_node;
}

bool CStringList::CIterator::operator!=(CIterator const& other) const
{
	return m_node != other.m_node;
}

CStringList::CIterator & CStringList::CIterator::operator++()
{
	if (m_node->next != nullptr)
	{
		m_node = m_node->next.get();
	}
	else
	{
		throw out_of_range("CStringList iterator not incrementable");
	}
	return *this;
}

CStringList::CIterator & CStringList::CIterator::operator--()
{
	if (m_node->prev != nullptr)
	{
		m_node = m_node->prev;
	}
	else
	{
		throw out_of_range("CStringList iterator not decrementable");
	}
	return *this;
}

CStringList::CIterator::pointer CStringList::CIterator::operator->()const
{
	return pointer_traits<pointer>::pointer_to(**this);
}

CStringList::CIterator CStringList::CIterator::operator++(int)
{
	CIterator tmp = *this;
	++*this;
	return tmp;
}

CStringList::CIterator CStringList::CIterator::operator--(int)
{
	CIterator tmp = *this;
	--*this;
	return tmp;
}