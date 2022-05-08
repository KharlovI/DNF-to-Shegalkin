#pragma once
typedef unsigned long long u_int64;

template<typename T>
class NodeList
{
protected:
	struct Node
	{
		u_int64 index;
		T* data;
		Node* next;

		Node(T* data)
			: data(data), next(nullptr) {}

	};
	Node* head, * tail;

public:
	NodeList()
		: head(nullptr), tail(nullptr) {}
	void append(T* data);
	bool insert(u_int64 index, T* data);
	T& get(u_int64 index);
	bool remove(u_int64 index);
	u_int64 size();
	bool includes(T* data);
	T& operator[](u_int64 index);
};

#include "List.ipp"