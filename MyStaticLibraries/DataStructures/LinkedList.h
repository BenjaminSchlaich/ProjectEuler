#pragma once

#include <stdexcept>
#include <iostream> // to override operator<<

namespace datastructures
{
	template <typename T>
	class LinkedList;

	template <typename T>
	class LinkedList
	{
		class Node;

	public:
		inline LinkedList()
		{
			size = 0;
			begin = nullptr;
			end = nullptr;
		}

		friend std::ostream& operator<<(std::ostream& os, LinkedList& l)
		{
			std::cout << '{';

			Node* n = l.begin;
			while (n != nullptr)
			{
				std::cout << n->value;
				if (n->next != nullptr)
					std::cout << ", ";
				else
					std::cout << " }";
				n = n->next;
			}
			return os;
		}

		//LinkedList(LinkedList& l);

		void operator+=(const LinkedList l);

		int Size();

		void clear();

		void addFirst(T value);

		void addAt(int index, T value);

		void addLast(T value);

		T getFirst();

		T getAt(int index);

		T getLast();

		T popFirst();

		T pop(int index);

		T popLast();

		void eraseFirst();
		
		void erase(int index);

		void eraseLast();

		void remove(T element);

	private:

		class Node
		{
		public:
			Node()
			{
				previous = nullptr;
				next = nullptr;
			}

			Node(T value)
			{
				previous = nullptr;
				this->value = value;
				next = nullptr;
			}

			Node(Node &n)
			{
				previous = nullptr;
				value = n.value;
				next = nullptr;
			}

			Node* previous;
			T value;
			Node* next;
		};

		int size;

		Node* begin;
		Node* end;

		void veryFirst(T value);

		void verySecond(T value);

		void removeVeryFirst();

		void removeFirstOfTwo();
		
		void removeSecondOfTwo();

		void removeAt(int index);
	};



}// namespace datastructures