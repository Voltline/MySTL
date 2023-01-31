#pragma once
#include <cstring>
#include <exception>
#include <stdexcept>
#include <iostream>
#include "exceptions.h"

using size_t = unsigned long long;

namespace MySTL {
    template<typename T>
    class Vector
    {
    private:
        T* _data{ nullptr };
        size_t capacity_num{0};
        size_t elements_num{0};
        void resize();
    public:
        using iterator = T*;  // Random Iterator
    public:
        Vector();
        Vector(T* arr, size_t n);
        Vector(size_t _elem_num, T value);
        Vector(size_t n);
        Vector(Vector<T>&& vec) noexcept;
        Vector(std::initializer_list<T> l);
        Vector(Vector<T>& sec);
        ~Vector();

        void resize(size_t new_elem_num);
        void resize(size_t new_elem_num, T value);
        void reserve(size_t new_capacity);

        Vector<T>::iterator begin();
        Vector<T>::iterator end();

        void push_back(T elem);
        void pop_back();
        void clear();
        void erase(Vector<T>::iterator pos_begin, Vector<T>::iterator pos_end);
        
        void insert(Vector<T>::iterator pos, T value);
        void insert(Vector<T>::iterator pos, size_t ins_elem_num, T value);
        void insert(Vector<T>::iterator pos, 
            Vector<T>::iterator other_pos_begin, Vector<T>::iterator other_pos_end);

        bool empty();
        size_t capacity();
        size_t size();
        T* data();

        constexpr void swap(Vector<T>& _Right);

        T& operator[](size_t index);
        bool operator==(const Vector<T>& vec);
        bool operator!=(const Vector<T>& vec);

        constexpr void view();
    };

    template<typename T>
    void Vector<T>::resize()
    {
        /* The mode of vector resize:
         * if v.elements_num == capacity, new capacity = capacity + 128;
         */
        if (this->elements_num == this->capacity()) {
            try {
                T* temp = new T[this->capacity() + 128];
                memcpy(temp, this->_data, this->elements_num * sizeof(T));
                delete[] this->_data;
                this->_data = temp;
                this->capacity_num = this->capacity() + 128;
                temp = nullptr;
            }
            catch (std::bad_alloc& e) {
                throw e;
            }
        }
    }

    template<typename T>
    bool operator==(const Vector<T>& _Left, const Vector<T>& _Right) 
    {
        if (_Left.size() != _Right.size()) {
            return false;
        }
        else {
            for (size_t i = 0; i < _Left.size(); i++) {
                if (_Left[i] != _Right[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    template<typename T>
    bool operator!=(const Vector<T>& _Left, const Vector<T>& _Right)
    {
        return !(_Left == _Right);
    }

    template<typename T>
    T& Vector<T>::operator[](size_t index) 
    {
        if (index < this->size()) {
            return this->_data[index];
        }
        else {
            throw std::out_of_range("Out of Range!");
        }
    }

    template<typename T>
    inline bool Vector<T>::operator==(const Vector<T>& vec)
    {
        return (*this == vec);
    }

    template<typename T>
    inline bool Vector<T>::operator!=(const Vector<T>& vec)
    {
        return !(*this == vec);
    }

    template<typename T>
    inline constexpr void Vector<T>::view()
    {
        for (int i = 0; i < this->size(); i++) {
            std::cout << this->_data[i] << " ";
        }
        std::cout << std::endl;
    }

    template<typename T>
    Vector<T>::Vector() 
    {
        this->capacity_num = 0;
        this->elements_num = 0;
    }

    template<typename T>
    Vector<T>::Vector(size_t n) 
    {
        try {
            this->_data = new T[n];
            this->capacity_num = n;
            this->elements_num = 0;
        }
        catch (std::bad_alloc& e) {
            this->_data = new T[128];
            this->capacity_num = 128;
            this->elements_num = 0;
        }
    }

    template<typename T>
    Vector<T>::Vector(T* arr, size_t n)
    {
        this->_data = arr;
        this->capacity_num = n;
        this->elements_num = n;
        this->resize();
    }

    template<typename T>
    inline Vector<T>::Vector(size_t _elem_num, T value)
    {
        this->capacity_num = _elem_num + 128;
        this->_data = new T[this->capacity_num];

        for (; this->elements_num < _elem_num; this->elements_num++) {
            this->_data[this->elements_num] = value;
        }
    }

    template<typename T>
    Vector<T>::Vector(Vector<T>&& vec) noexcept 
    {
        this->_data = vec.data();
        this->capacity_num = vec.capacity();
        this->elements_num = vec.size();
        this->resize();

        vec.~Vector();
    }

    template<typename T>
    Vector<T>::Vector(std::initializer_list<T> l) 
    {
        try {
            this->_data = new T[l.size() + 128];
            this->elements_num = 0;
            this->capacity_num = l.size() + 128;
            for (auto it = l.begin(); it != l.end(); it++) {
                this->push_back(*it);
            }
        }
        catch (std::bad_alloc& e) {
            throw e;
        }
    }

    template<typename T>
    Vector<T>::Vector(Vector<T>& sec) 
    {
        this->capacity_num = sec.capacity();
        this->elements_num = sec.size();
        try {
            this->_data = new T[this->capacity()];
            for (int i = 0; i < this->size(); i++) {
                this->_data[i] = sec[i];
            }
        }
        catch (std::bad_alloc& e) {
            throw e;
        }
    }

    template<typename T>
    Vector<T>::~Vector() 
    {
        delete[] this->_data;
        this->_data = nullptr;
        this->capacity_num = 0;
        this->elements_num = 0;
    }

    template<typename T>
    inline void Vector<T>::resize(size_t new_elem_num)
    {
        if (new_elem_num <= this->capacity()) {
            this->elements_num = new_elem_num;
        }
        else {
            this->reserve(new_elem_num + 128);
            this->elements_num = new_elem_num;
        }
        this->resize();
    }

    template<typename T>
    inline void Vector<T>::resize(size_t new_elem_num, T value)
    {
        if (new_elem_num <= this->capacity()) {
            if (new_elem_num <= this->elements_num) {
                this->elements_num = new_elem_num;
            }
            else {
                for (; this->elements_num < new_elem_num; this->elements_num++) {
                    this->_data[this->elements_num] = value;
                }
            }
        }
        else {
            this->reserve(new_elem_num + 128);
            for (; this->elements_num < new_elem_num; this->elements_num++) {
                this->_data[this->elements_num] = value;
            }
        }
        this->resize();
    }

    template<typename T>
    inline bool Vector<T>::empty() 
    {
        if (this->elements_num == 0) return true;
        else return false;
    }

    template<typename T>
    inline size_t Vector<T>::capacity()
    {
        return this->capacity_num;
    }

    template<typename T>
    inline size_t Vector<T>::size()
    {
        return this->elements_num;
    }

    template<typename T>
    inline T* Vector<T>::data()
    {
        return this->_data;
    }

    template<typename T>
    inline constexpr void Vector<T>::swap(Vector<T>& _Right)
    {
        size_t temp_size{ _Right.size() }, temp_capacity{ _Right.capacity() };
        T* temp_data_ptr{ _Right.data() };
        _Right.elements_num = this->size();
        _Right.capacity_num = this->capacity();
        _Right._data = this->data();

        this->elements_num = temp_size;
        this->capacity_num = temp_capacity;
        this->_data = temp_data_ptr;
        
        temp_data_ptr = nullptr;
    }

    template<typename T>
    inline void Vector<T>::reserve(size_t new_capacity)
    {
        if (new_capacity != this->capacity()) {
            try {
                T* temp = new T[new_capacity];
                size_t min_capacity{ (new_capacity > this->elements_num) ? this->elements_num : new_capacity };
                memcpy(temp, this->_data, min_capacity * sizeof(T));
                delete[] this->_data;
                this->_data = temp;
                temp = nullptr;
                this->capacity_num = new_capacity;
                if (this->elements_num > this->capacity()) {
                    this->elements_num = this->capacity();
                    this->resize();
                }
            }
            catch (std::bad_alloc& e) {
                throw e;
            }
        }
    }

    template<typename T>
    inline Vector<T>::iterator Vector<T>::begin()
    {
        return this->_data;
    }

    template<typename T>
    inline Vector<T>::iterator Vector<T>::end()
    {
        return this->_data + this->elements_num;
    }

    template<typename T>
    inline void Vector<T>::push_back(T elem)
    {
        this->resize();
        if (this->size() < this->capacity()) {
            this->_data[this->size()] = elem;
            this->elements_num++;
            this->resize();
        }
        else {
            throw std::out_of_range("Out of Range!");
        }
    }

    template<typename T>
    inline void Vector<T>::pop_back()
    {
        this->elements_num--;
    }

    template<typename T>
    inline void Vector<T>::clear()
    {
        this->elements_num = 0;
    }

    template<typename T>
    inline void Vector<T>::erase(Vector<T>::iterator pos_begin, Vector<T>::iterator pos_end)
    {
        if (pos_begin <= pos_end) {
            if (pos_begin >= this->begin() && pos_begin <= this->end()) {
                if (this->end() < pos_end) {
                    pos_end = this->end();
                }
                memcpy(pos_begin, pos_end, (this->end() - pos_end) * sizeof(T));
                this->elements_num -= pos_end - pos_begin;
            }
            else {
                throw IteratorErrorException{};
            }
        }
        else {
            throw IteratorErrorException{};
        }
    }

    template<typename T>
    inline void Vector<T>::insert(Vector<T>::iterator pos, T value)
    {
        if (pos >= this->begin() && pos <= this->end()) {
            size_t ins_pos_index = pos - this->begin();
            size_t elem_after_insert_num = this->end() - pos;
            if (this->capacity() - this->elements_num >= 1) {
                memcpy(pos + 1, pos, elem_after_insert_num * sizeof(T));
                *pos = value;
            }
            else {
                this->reserve(this->capacity() + 1);
                pos = this->begin() + ins_pos_index;
                memcpy(pos + 1, pos, elem_after_insert_num * sizeof(T));
                *pos = value;
            }
            this->elements_num++;
        }
        else {
            throw IteratorOutOfRangeException{};
        }
    }

    template<typename T>
    inline void Vector<T>::insert(Vector<T>::iterator pos, size_t ins_elem_num, T value)
    {
        if (pos >= this->begin() && pos <= this->end()) {
            size_t ins_pos_index = pos - this->begin();
            size_t copy_num = this->end() - pos;
            if (ins_elem_num + this->size() > this->capacity()) {
                this->reserve(ins_elem_num + this->size() + 128);
                pos = this->begin() + ins_pos_index;
            }
            memcpy(pos + ins_elem_num, pos, copy_num * sizeof(T));
            size_t index = pos - this->begin();
            for (size_t i = 0; i < ins_elem_num; i++) {
                this->_data[index + i] = value;
            }
            this->elements_num += ins_elem_num;
        }
        else {
            throw IteratorOutOfRangeException{};
        }
    }

    template<typename T>
    inline void Vector<T>::insert(Vector<T>::iterator pos,
        Vector<T>::iterator other_pos_begin, Vector<T>::iterator other_pos_end)
    {
        if (pos >= this->begin() && pos <= this->end()) {
            size_t ins_pos_index = pos - this->begin();
            size_t copy_num = this->end() - pos, ins_elem_num = other_pos_end - other_pos_begin;
            if (ins_elem_num + this->size() > this->capacity()) {
                this->reserve(ins_elem_num + this->size() + 128);
                pos = this->begin() + ins_pos_index;
            }
            memcpy(pos + ins_elem_num, pos, copy_num * sizeof(T));
            size_t index = pos - this->begin();
            for (size_t i = 0; i < ins_elem_num; i++) {
                this->_data[index + i] = *(other_pos_begin + i);
            }
            this->elements_num += ins_elem_num;
        }
        else {
            throw IteratorOutOfRangeException{};
        }
    }

}
