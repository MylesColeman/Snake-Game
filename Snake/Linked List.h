#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

template <typename T>
class Node
{
public:
	Node(T newData) : data{ newData } {}

	T data;

	Node* next{ nullptr };
};

template <typename T>
class LinkedList
{
public:
	Node<T>* head{ nullptr };

	// Calls the first item in the list
	T front() const
	{
		if (head == nullptr)
		{
			std::cerr << "Error -  Accessing From Empty List!" << std::endl;
			return T();
		}

		return head->data;
	}

	// Calls the last item in the list
	T back() const
	{
		if (head == nullptr)
		{
			std::cerr << "Error -  Accessing From Empty List!" << std::endl;
			return T();
		}
		else
		{
			Node<T>* tempPtr{ head };

			while (tempPtr->next != nullptr)
				tempPtr = tempPtr->next;

			return tempPtr->data;
		}
	}

	// Calls the size of the list
	int size() const
	{
		Node<T>* tempPtr{ head };
		int itemCounter{ 0 };

		while (tempPtr != nullptr)
		{
			tempPtr = tempPtr->next;
			itemCounter++;
		}

		return itemCounter;
	}

	// Inserts an item to the list at a specific point
	void Insert(size_t pos, T value)
	{
		if (pos > size())
		{
			std::cerr << "Error - Invalid position for insertion!" << std::endl;
			return;
		}

		Node<T>* newNode = new Node<T>(value);

		if (pos == 0)
		{
			newNode->next = head;
			head = newNode;
		}
		else
		{
			Node<T>* current = head;
			for (size_t i = 0; i < pos - 1; ++i)
			{
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}
	}

	// Adds an item to the front of the list
	void push_front(T newData)
	{
		Node<T>* newNode = new Node<T>(newData);

		if (head == nullptr)
			head = newNode;
		else
		{
			newNode->next = head;
			head = newNode;
		}
	}

	// Adds an item to the back of the list
	void push_back(T newData)
	{
		Node<T>* newNode = new Node<T>(newData);

		if (head == nullptr)
			head = newNode;
		else
		{
			Node<T>* tempPtr{ head };

			while (tempPtr->next != nullptr)
				tempPtr = tempPtr->next;

			tempPtr->next = newNode;
		}
	}

	// Removes the item at the front of the list
	void pop_front()
	{
		if (head == nullptr)
		{
			std::cerr << "Error -  Accessing From Empty List!" << std::endl;
			return;
		}

		Node<T>* tempPtr{ head };

		head = tempPtr->next;

		delete tempPtr;
	}

	// Removes the item at the back of the list
	void pop_back()
	{
		if (head == nullptr)
		{
			std::cerr << "Error -  Accessing From Empty List!" << std::endl;
			return;
		}
		else if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
		}
		else
		{
			Node<T>* current{ head };
			Node<T>* previous{ nullptr };

			while (current->next != nullptr)
			{
				previous = current;
				current = current->next;
			}

			previous->next = nullptr;
			delete current;
		}
	}

	// Removes an item from a specific point in the list
	void Erase(size_t pos)
	{
		if (head == nullptr || pos >= size())
		{
			std::cerr << "Error - Invalid position for erasure!" << std::endl;
			return;
		}

		Node<T>* temp = head;

		if (pos == 0)
		{
			head = head->next;
			delete temp;
		}
		else
		{
			Node<T>* previous = nullptr;
			for (size_t i = 0; i < pos; ++i)
			{
				previous = temp;
				temp = temp->next;
			}
			previous->next = temp->next;
			delete temp;
		}
	}

	// Removes all items from the lits
	void Clear()
	{
		Node<T>* tempPtr{ head };

		while (tempPtr != nullptr)
		{
			Node<T>* next{ tempPtr->next };
			delete tempPtr;
			tempPtr = next;
		}
		head = nullptr;
	}

	// Checks whether the list is empty
	bool empty() const
	{
		if (head == nullptr)
		{
			return true;
		}
		else
			return false;
	}
};