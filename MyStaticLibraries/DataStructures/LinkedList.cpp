#include "pch.h"
#include "LinkedList.h"

namespace datastructures
{

	template <typename T>
	LinkedList<T> operator+(LinkedList<T> l1, LinkedList<T>& l2)
	{
		l1 += l2;
		return l1;
	}

	template<typename T>
	void LinkedList<T>::operator+=(const LinkedList l)
	{
		Node* n = l.begin;
		int correctSize = 0;
		if (size == 0 && l.size > 0)
		{
			veryFirst(l.begin->value);
			n = n->next;
			correctSize++;
		}
		if (size == 1 && l.size > 1)
		{
			verySecond(l.begin->next->value);
			n = n->next;
			correctSize++;
		}

		while (n != nullptr)
		{
			Node* newN = new Node(*n);
			end->next = newN;
			newN->previous = end;
			end = newN;
			n = n->next;

		}

		size += l.size-correctSize;

	}

	template <typename T>
	int LinkedList<T>::Size()
	{
		return size;
	}

	template<typename T>
	void LinkedList<T>::clear()
	{
		if (size == 0)
			return;

		Node* n = begin;
		while (n != nullptr)
		{
			Node* d = n;
			n = n->next;
			delete d;
		}

		begin = nullptr;
		end = nullptr;
		size = 0;
	}

	template<typename T>
	void LinkedList<T>::addFirst(T value)
	{
		if (size == 0)
			return veryFirst(value);

		if (size == 1)
			return verySecond(value);

		Node* n = new Node(value);
		n->next = begin;
		begin->previous = n;
		begin = n;

		size++;
	}

	template<typename T>
	void LinkedList<T>::addAt(int index, T value)
	{
		if (index < 0 || index > size)
			throw std::runtime_error("invalid index: " + index);

		if (index == 0)
			return addFirst(value);

		if (index == size)
			return addLast(value);

		Node* n;
		if (index < size / 2)
		{
			n = begin;
			for (int i = 0; i < index; i++)
			{
				n = n->next;
			}
		}
		else
		{
			n = end;
			for (int i = 0; i < size - index - 1; i++)
			{
				n = n->previous;
			}
		}

		Node* newN = new Node(value);
		newN->next = n;
		newN->previous = n->previous;
		n->previous->next = newN;
		n->previous = newN;

		size++;
	}

	template<typename T>
	void LinkedList<T>::addLast(T value)
	{
		if (size == 0)
			return veryFirst(value);

		if (size == 1)
			return verySecond(value);

		Node* n = new Node(value);
		n->previous = end;
		end->next = n;
		end = n;

		size++;
	}

	template<typename T>
	T LinkedList<T>::getFirst()
	{
		if (size == 0)
			throw std::runtime_error("cannot retrieve from emtpy list");

		return begin->value;
	}

	template<typename T>
	inline T LinkedList<T>::getAt(int index)
	{
		if (index < 0 || index > size)
			throw std::runtime_error("invalid index: " + index);

		if (index == 0)
			return getFirst();

		if (index == size)
			return getLast();

		Node* n;
		if (index < size / 2)
		{
			n = begin;
			for (int i = 0; i < index; i++)
			{
				n = n->next;
			}
		}
		else
		{
			n = end;
			for (int i = 0; i < size - index - 1; i++)
			{
				n = n->previous;
			}
		}

		return n->value;
	}

	template<typename T>
	inline T LinkedList<T>::getLast()
	{
		if (size == 0)
			throw std::runtime_error("cannot retrieve from emtpy list");

		return end->value;
	}

	template<typename T>
	T LinkedList<T>::popFirst()
	{
		if (size == 0)
			throw std::runtime_error("cannot remove from empty list!");
		T element = begin->value;
		removeAt(0);
		return element;
	}

	template <typename T>
	T LinkedList<T>::pop(int index)
	{
		T element = getAt(index);
		removeAt(0);
		return element;
	}

	template <typename T>
	T LinkedList<T>::popLast()
	{
		if (size == 0)
			throw std::runtime_error("cannot remove from empty list!");
		T element = end->value;
		removeAt(size - 1);
		return element;
	}

	template<typename T>
	void LinkedList<T>::eraseFirst()
	{
		removeAt(0);
		return;
	}

	template<typename T>
	void LinkedList<T>::erase(int index)
	{
		removeAt(index);
		return;
	}

	template<typename T>
	void LinkedList<T>::eraseLast()
	{
		removeAt(size - 1);
		return;
	}

	template<typename T>
	void LinkedList<T>::remove(T element)
	{
		if (size == 0)
			throw std::runtime_error("cannot remove from empty list!");

		Node* n = begin;
		while (n != nullptr)
		{
			if (n->value == element)
			{
				n->previous->next = n->next;
				n->next->previous = n->previous;
				delete n;
				size--;
				return;
			}
			n = n->next;
		}

		throw std::runtime_error("cannot remove: the element was not in the list!");
	}

	template<typename T>
	void LinkedList<T>::veryFirst(T value)
	{
		begin = new Node(value);

		size++;

		return;
	}

	template<typename T>
	void LinkedList<T>::verySecond(T value)
	{
		end = new Node(value);
		begin->next = end;
		end->previous = begin;

		size++;

		return;
	}

	template<typename T>
	void LinkedList<T>::removeVeryFirst()
	{
		delete begin;
		begin = nullptr;
		size = 0;
	}

	template<typename T>
	void LinkedList<T>::removeFirstOfTwo()
	{
		end->previous = nullptr;
		delete begin;
		begin = end;
		end = nullptr;

		size = 1;
	}

	template<typename T>
	void LinkedList<T>::removeSecondOfTwo()
	{
		begin->next = nullptr;
		delete end;
		end = nullptr;

		size = 1;
	}

	template<typename T>
	void LinkedList<T>::removeAt(int index)
	{
		if (size == 0)
			throw std::runtime_error("cannot remove from empty list!");

		if (index < 0 || index >= size)
			throw std::runtime_error("invalid index: " + index);

		if (size == 1)
		{
			removeVeryFirst();
			return;
		}

		if (size == 2)
		{
			if (index == 0)
			{
				removeFirstOfTwo();
				return;
			}
			else
			{
				removeSecondOfTwo();
				return;
			}
		}

		if (index == 0)
		{
			Node* n = begin;
			begin->next->previous = nullptr;
			begin = begin->next;
			delete n;

			size--;
			return;
		}

		if (index == size - 1)
		{
			Node* n = end;
			end->previous->next = nullptr;
			end = end->previous;
			delete n;

			size--;
			return;
		}

		Node* n;
		if (index < size / 2)
		{
			n = begin;
			for (int i = 0; i < index; i++)
			{
				n = n->next;
			}
		}
		else
		{
			n = end;
			for (int i = 0; i < size - index - 1; i++)
			{
				n = n->previous;
			}
		}

		n->previous->next = n->next;
		n->next->previous = n->previous;
		delete n;

		size--;
	}

	

}// namespace datastructures