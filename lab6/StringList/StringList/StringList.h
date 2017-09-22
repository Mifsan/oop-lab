#pragma once

class CStringList
{
	struct Node
	{
		Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node *prev;
		std::unique_ptr<Node> next;
	};
public:

	CStringList();
	CStringList(const CStringList & other);
	~CStringList();
	CStringList(CStringList && other);

	CStringList & operator = (CStringList const & other);
	CStringList & operator = (CStringList && other);

	size_t GetSize() const;
	bool IsEmpty() const;

	class CIterator: public std::iterator<std::bidirectional_iterator_tag, std::string>
	{
		friend CStringList;
		CIterator(Node *node);
	public:
		CIterator() = default;
		std::string & operator*()const;
		CIterator & operator++();
		CIterator & operator--();
		CIterator operator++(int);
		CIterator operator--(int);
		pointer operator->()const;
		bool operator==(CIterator const & other)const;
		bool operator!=(CIterator const & other)const;
	private:
		Node *m_node = nullptr;
	};

	void AppendBack(const std::string & data);
	void AppendFront(const std::string & data);
	void Insert(const CIterator & it, const std::string& data);

	void Erase(const CIterator & it);
	void Clear();

	CIterator begin();
	CIterator end();
	CIterator begin() const;
	CIterator end() const;
	CIterator cbegin() const;
	CIterator cend() const;

	std::reverse_iterator<CIterator> rbegin();
	std::reverse_iterator<CIterator> rend();
	std::reverse_iterator<CIterator> rbegin() const;
	std::reverse_iterator<CIterator> rend() const;
	std::reverse_iterator<CIterator> crbegin() const;
	std::reverse_iterator<CIterator> crend() const;

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode = nullptr;
	Node * m_lastNode = nullptr;
};