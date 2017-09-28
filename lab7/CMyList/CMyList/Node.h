#pragma once
#include "stdafx.h"

template <typename T>
class Node
{
public:
	Node(const boost::optional<T> & data, Node<T> * prev, std::unique_ptr<Node<T>> && next)
		: data(data), prev(prev), next(std::move(next))
	{
	}
	boost::optional<T> data;
	Node<T> * prev;
	std::unique_ptr<Node<T>> next;
};