#pragma once

namespace Somn {
	template<class T>
	struct ListNode {
		ListNode* _next;
		ListNode* _pre;
		T _data;

	public:
		ListNode(const T& val);
	};

	template<class T>
	class list {
		typedef ListNode<T> Node;

	public:
		list();

		void push_back(const T& val);

	private:
		Node* _head;

	};

	template<class T>
	inline list<T>::list()
	{
		_head = new Node;
		_head->_next = _head;
		_head->_pre = _head;
	}

	template<class T>
	inline void list<T>::push_back(const T& val)
	{
		Node* newNode = new Node;
		Node* tail = _head->_pre;
		tail->_next = newNode;
		newNode->_pre = tail;
		_head->_pre = newNode;
		newNode->_next = _head;

	}

	template<class T>
	inline ListNode<T>::ListNode(const T& val)
	{
		_next = _pre = nullptr;
		_data = val;
	}

}
