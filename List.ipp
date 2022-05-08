#pragma once
#include "List.h"

template<typename T>
inline void NodeList<T>::append(T* data)
{
	Node* node = new Node(data);
	if (this->head == nullptr) {
		node->index = 0;
		this->head = node;
		this->tail = node;
	}
	else
	{
		this->tail->next = node;
		node->index = this->tail->index + 1;
		tail = node;
	}
}

template<typename T>
inline bool NodeList<T>::insert(u_int64 index, T* data)
{
	Node* node = new Node(data);

	Node* prev;
	Node* i = this->head;
	while (i->next != nullptr)
	{
		if (i->index == index)
		{
			node->next = i;
			prev->next = node;
			node->index = i->index;

			Node* i = node;
			while (i != nullptr)
			{
				i->index += 1;
				i = i->next;
			}
			return true;
		}
		prev = i;
		i = i->next;
	}
	return false;
}

template<typename T>
inline T& NodeList<T>::get(u_int64 index)
{
	Node* i = this->head;
	while (i != nullptr)
	{
		if (i->index == index)
			return i->data;
		i = i->next;
	}
	return nullptr;
}

template<typename T>
inline bool NodeList<T>::remove(u_int64 index)
{
	Node* i = this->head;
	Node* prev;
	while (i != nullptr)
	{
		if (i->index == index)
		{
			if (i == head)
				head = head->next;
			else
				if (i == tail)
					tail = prev;

			for (Node* cur = i; cur != nullptr; cur = cur->next)
				cur->index -= 1;

			delete i;
			return true;
		}
		prev = i;
		i = i->next;
	}
	return false;
}

template<typename T>
inline u_int64 NodeList<T>::size()
{
	return this->tail->index + 1;
}

template<typename T>
inline T& NodeList<T>::operator[](u_int64 index)
{
	Node* i = this->head;
	while (i != nullptr)
	{
		if (i->index == index)
			return *(i->data);
		i = i->next;
	}
	return *(new T);
}

template<typename T>
inline bool NodeList<T>::includes(T* data)
{
	Node* i = this->head;
	while (i != nullptr)
	{
		if (*(i->data) == *data)
			return true;
		i = i->next;
	}
	return false;
}