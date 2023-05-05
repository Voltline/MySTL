#pragma once

namespace MySTL
{
	template<typename T>
	class Node
	{
	public:
		T value;
		Node* next{ nullptr };
		Node* last{ nullptr };
	public:
		Node() = default;
		Node(T value);
		~Node();
	};

	template<typename T>
	inline Node<T>::Node(T value)
	{
		this->value = value;
	}

	template<typename T>
	inline Node<T>::~Node()
	{
		if (this->last != nullptr && this->next != nullptr) {
			this->last->next = this->next;
		}
	}

	template<typename T>
	class Iterator
	{
	private:
		Node<T>* node_ptr{ nullptr };
	public:
		Iterator() = delete;
		Iterator(Node<T>& _node);
		Iterator(Node<T>* _node_ptr);
		~Iterator() = default;

		T& operator*();
		T* operator->();
		Iterator<T> operator+(size_t _Off);
		Iterator<T> operator-(size_t _Off);
		Iterator<T> operator++();
		Iterator<T> operator++(int n);
		Iterator<T> operator--();
		Iterator<T> operator--(int n);
		
		bool operator==(Iterator<T> _Right);
		bool operator!=(Iterator<T> _Right);

		void operator=(const Iterator<T>& _Right);
		void operator+=(size_t _Off);
		void operator-=(size_t _Off);
	};

	template<typename T>
	inline Iterator<T>::Iterator(Node<T>& _node)
	{
		this->node_ptr = &(_node);
	}

	template<typename T>
	inline Iterator<T>::Iterator(Node<T>* _node_ptr)
	{
		this->node_ptr = _node_ptr;
	}

	template<typename T>
	inline T& Iterator<T>::operator*()
	{
		return this->node_ptr->value;
	}

	template<typename T>
	inline T* Iterator<T>::operator->()
	{
		return &(this->node_ptr->value);
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator+(size_t _Off)
	{
		Node<T>* _target_node_ptr{ this };
		for (size_t i = 0; i < _Off; i++) {
			if (_target_node_ptr->next != nullptr) {
				_target_node_ptr = _target_node_ptr->next;
			}
			else {
				_target_node_ptr = nullptr;
				break;
			}
		}
		return Iterator<T>(_target_node_ptr);
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator-(size_t _Off)
	{
		Node<T>* _target_node_ptr{ this };
		for (size_t i = 0; i < _Off; i++) {
			if (_target_node_ptr->last != nullptr) {
				_target_node_ptr = _target_node_ptr->last;
			}
			else {
				_target_node_ptr = nullptr;
				break;
			}
		}
		return Iterator<T>(_target_node_ptr);
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator++() // ++a
	{
		*this += 1;
		return *this;
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator++(int n) // a++
	{
		Node<T>* temp_ptr{ this->node_ptr };
		*this += 1;
		return Iterator<T>(temp_ptr);
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator--() // --a
	{
		*this -= 1;
		return this;
	}

	template<typename T>
	inline Iterator<T> Iterator<T>::operator--(int n) // a--
	{
		Node<T>* temp_ptr{ this->node_ptr };
		*this -= 1;
		return Iterator<T>(temp_ptr);
	}

	template<typename T>
	inline bool Iterator<T>::operator==(Iterator<T> _Right)
	{
		if (this->node_ptr == _Right.node_ptr) return true;
		else return false;
	}
	template<typename T>
	inline bool Iterator<T>::operator!=(Iterator<T> _Right)
	{
		return !(*this == _Right);
	}

	template<typename T>
	inline void Iterator<T>::operator=(const Iterator<T>& _Right)
	{
		this->node_ptr = _Right.node_ptr;
	}

	template<typename T>
	inline void Iterator<T>::operator+=(size_t _Off)
	{
		for (size_t i = 0; i < _Off; i++) {
			if (this->node_ptr->next != nullptr) {
				this->node_ptr = this->node_ptr->next;
			}
			else {
				this->node_ptr = nullptr;
				break;
			}
		}
	}

	template<typename T>
	inline void Iterator<T>::operator-=(size_t _Off)
	{
		for (size_t i = 0; i < _Off; i++) {
			if (this->node_ptr->last != nullptr) {
				this->node_ptr = this->node_ptr->last;
			}
			else {
				this->node_ptr = nullptr;
				break;
			}
		}
	}

	template<typename T>
	class List
	{
	private:
		Node<T>* _head{ nullptr };
		Node<T>* _tail{ nullptr };
		Node<T>* _end{ nullptr };
		size_t _size{ 0 };
	public:
		using iterator = Iterator<T>;
		using const_iterator = const Iterator<T>;
	public:
		List() = default;
		List(std::initializer_list<T> l);
		List(const List<T>& _Right);
		List(List<T>&& _mv_Right) noexcept;
		~List();

		iterator begin()
		{
			return Iterator<T>(this->_head);
		}

		iterator end()
		{
			return Iterator<T>(this->_end);
		}

		const_iterator begin() const
		{
			return Iterator(this->_head);
		}

		const_iterator end() const
		{
			return Iterator(this->_end);
		}

		void insert();

		void push_back(T value);
		void push_front(T value);
		void pop_back();
		void pop_front();
		void clear();

		void erase(List<T>::const_iterator _Where);
		void erase(List<T>::const_iterator _First, List<T>::const_iterator _Last);

		T& front();
		T& back();

		void operator=(const List<T>& _Right);
		void view();
		const size_t size();
	};

	template<typename T>
	inline List<T>::List(std::initializer_list<T> l)
	{
		size_t length{ l.size() };
		if (length == 1) {
			this->_head = new Node<T>{ *l.begin() };
			this->_tail = this->_head;
			this->_size++;
		}
		else {
			size_t i = 0;
			for (auto& val : l) {
				if (i == 0) {
					this->_head = new Node<T>{ val };
					this->_tail = this->_head;
				}
				else if (i < length) {
					Node<T>* temp = new Node<T>{ val };
					temp->last = this->_tail;
					this->_tail->next = temp;
					this->_tail = temp;
				}
				i++;
				this->_size++;
			}
		}
		this->_end = new Node<T>{};
		this->_end->last = this->_tail;
		this->_tail->next = this->_end;
	}

	template<typename T>
	inline List<T>::List(const List<T>& _Right)
	{
		size_t length = _Right._size;
		if (_Right._size == 1) {
			this->_head = new Node<T>{ *_Right._head };
			this->_end = this->_head;
			this->_size++;
		}
		else {
			size_t i = 0;
			for (auto& val : _Right) {
				if (i == 0) {
					this->_head = new Node<T>{ val };
					this->_tail = this->_head;
				}
				else if (i < length) {
					Node<T>* temp = new Node<T>{ val };
					temp->last = this->_tail;
					this->_tail->next = temp;
					this->_tail = temp;
				}
				i++;
				this->_size++;
			}
		}
		this->_end = new Node<T>{};
		this->_end->last = this->_tail;
		this->_tail->next = this->_end;
	}
	
	template<typename T>
	inline List<T>::List(List<T>&& _mv_Right) noexcept
	{
		this->_head = _mv_Right._head;
		this->_tail = _mv_Right._tail;
		this->_end = _mv_Right._end;
		this->_size = _mv_Right._size;

		_mv_Right._head = nullptr;
		_mv_Right._tail = nullptr;
		_mv_Right._end = nullptr;
		_mv_Right._size = 0;
	}

	template<typename T>
	inline List<T>::~List()
	{
		Node<T>* _node_ptr{ this->_head }, * _temp_ptr{ nullptr };
		while (_node_ptr != this->_end) {
			_temp_ptr = _node_ptr;
			_node_ptr = _node_ptr->next;
			delete _temp_ptr;
		}
		delete this->_end;
		this->_head = nullptr;
		this->_tail = nullptr;
		this->_end = nullptr;
		this->_size = 0;
	}

	template<typename T>
	inline void List<T>::push_back(T value)
	{
		if (this->_size == 1) {
			this->_tail = new Node<T>{ value };
			this->_head->next = this->_tail;
			this->_tail->last = this->_head;

			this->_tail->next = this->_end;
			this->_end->last = this->_tail;
			this->_size++;
		}
		else {
			Node<T>* temp_node_ptr = new Node<T>{ value };
			this->_tail->next = temp_node_ptr;
			temp_node_ptr->last = this->_tail;
			
			this->_tail = temp_node_ptr;
			this->_tail->next = this->_end;
			this->_end->last = this->_tail;

			this->_size++;
		}
	}
	
	template<typename T>
	inline void List<T>::push_front(T value)
	{
		Node<T>* temp_node_ptr = new Node<T>{ value };
		if (this->_size == 1) {
			this->_head = temp_node_ptr;
			this->_head->next = this->_tail;
			this->_tail->last = this->_head;
			this->_head->last = nullptr;
			this->_size++;
		}
		else {
			temp_node_ptr->next = this->_head;
			this->_head->last = temp_node_ptr;
			this->_head = temp_node_ptr;
			this->_size++;
		}
	}
	
	template<typename T>
	void List<T>::pop_back()
	{
		/*
		if (this->_size != 1) {
			Node<T>* temp = this->_tail;
			this->_tail = this->_tail->last;
			this->_tail->next = this->_end;
			this->_end->last = this->_tail;
			temp->~Node();
		}
		else {
			Node<T>* temp = this->_tail;
			this->_
		}

		this->_size--;*/
	}
	
	template<typename T>
	inline void List<T>::pop_front()
	{

	}
	
	template<typename T>
	inline void List<T>::clear()
	{

	}

	template<typename T>
	inline T& List<T>::front()
	{
		return this->_head->value;
	}

	template<typename T>
	inline T& List<T>::back()
	{
		return this->_tail->value;
	}

	template<typename T>
	inline void List<T>::operator=(const List<T>& _Right)
	{
		this->_head = _Right._head;
		this->_tail = _Right._tail;
	}

	template<typename T>
	inline void List<T>::view()
	{
		for (auto& i : *this) {
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}

	template<typename T>
	inline const size_t List<T>::size()
	{
		return this->_size;
	}
}
