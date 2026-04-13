#pragma once
#include <iostream>

template <typename T>
struct Node {
	T data;
	std::shared_ptr<Node<T>> next;
	std::weak_ptr<Node<T>> prev; //двозв'язні списки

	Node(T value) : data(value), next(nullptr) {}
};