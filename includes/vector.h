#pragma once
#include <cstring>
#include <exception>
#include <stdexcept>
#include <iostream>
#include "exceptions.h"

namespace MySTL {
    template<typename T>
    class vector
    {
    private:
        T* _data{ nullptr };
        size_t capacity_num;
        size_t elements_num;
        void resize();
    public:
        using iterator = T*;  // Random Iterator
        using const_iterator = const T*; // Constant Iterator
    public:
        vector();
        vector(T* arr, size_t n);
        vector(T* _begin, T* _end);
        vector(size_t _elem_num, T value);
        vector(size_t n);
        vector(vector<T>&& vec) noexcept;
        vector(std::initializer_list<T> l);
        vector(const vector<T>& sec);
        ~vector();

        void resize(size_t new_elem_num);
        void resize(size_t new_elem_num, T value);
        void reserve(size_t new_capacity);

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        void push_back(T elem);
        void pop_back();
        void clear();
        void erase(vector<T>::iterator pos_begin, vector<T>::iterator pos_end);
        
        void insert(vector<T>::iterator pos, T value);
        void insert(vector<T>::iterator pos, size_t ins_elem_num, T value);
        void insert(vector<T>::iterator pos, 
            vector<T>::iterator other_pos_begin, vector<T>::iterator other_pos_end);

        bool empty() const noexcept;
        size_t capacity() const noexcept;
        size_t size() const noexcept;
        T* data();

        constexpr void swap(vector<T>& _Right);

        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        constexpr void operator=(const vector<T>& vec);
        constexpr void operator=(vector<T>&& vec) noexcept;
        bool operator==(const vector<T>& vec);
        bool operator!=(const vector<T>& vec);

        constexpr void view();
    };

    template<typename T>
    void vector<T>::resize()
    {
        /* The mode of vector resize:
         * if v.elements_num == capacity, new capacity = capacity + 512;
         */
        if (elements_num == capacity_num) {
            try {
                T* temp = new T[capacity_num + 512];
                for (size_t i = 0; i < elements_num; i++) {
                    temp[i] = _data[i];
                }
                delete[] _data;
                _data = temp;
                capacity_num += 512;
                temp = nullptr;
            }
            catch (std::bad_alloc& e) {
                throw e;
            }
        }
    }

    template<typename T>
    bool operator==(const vector<T>& _Left, const vector<T>& _Right) 
    {
        if (_Left.elements_num != _Right.elements_num) {
            return false;
        }
        else {
            for (size_t i = 0; i < _Left.elements_num; i++) {
                if (_Left[i] != _Right[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    template<typename T>
    bool operator!=(const vector<T>& _Left, const vector<T>& _Right)
    {
        return !(_Left == _Right);
    }

    template<typename T>
    T& vector<T>::operator[](size_t index) 
    {
        if (index < elements_num) {
            return _data[index];
        }
        else {
            throw std::out_of_range("Out of Range!");
        }
    }

    template<typename T>
    const T& vector<T>::operator[](size_t index) const
    {
        if (index < elements_num) {
            return _data[index];
        }
        else {
            throw std::out_of_range("Out of Range!");
        }
    }

    template<typename T>
    inline constexpr void vector<T>::operator=(const vector<T>& vec)
    {
        elements_num = vec.elements_num;
        capacity_num = vec.capacity_num;
        delete[] _data;
        _data = new T[capacity_num];
        for (size_t i = 0; i < elements_num; i++) {
            _data[i] = vec._data[i];
        }
    }

    template<typename T>
    inline constexpr void vector<T>::operator=(vector<T>&& vec) noexcept
    {
        _data = vec._data;
        elements_num = vec.elements_num;
        capacity_num = vec.capacity_num;
        vec._data = nullptr;
    }

    template<typename T>
    inline bool vector<T>::operator==(const vector<T>& vec)
    {
        return (*this == vec);
    }

    template<typename T>
    inline bool vector<T>::operator!=(const vector<T>& vec)
    {
        return !(*this == vec);
    }

    template<typename T>
    inline constexpr void vector<T>::view()
    {
        for (int i = 0; i < elements_num; i++) {
            std::cout << _data[i] << " ";
        }
        std::cout << std::endl;
    }

    template<typename T>
    vector<T>::vector()
        : capacity_num(0), elements_num(0) {}

    template<typename T>
    vector<T>::vector(size_t n) 
        : _data(new T[n]), capacity_num(n), elements_num(0) {}

    template<typename T>
    vector<T>::vector(T* arr, size_t n)
        : _data(new T[n]), capacity_num(n), elements_num(n)
    {
        for (size_t i = 0; i < n; i++) {
            _data[i] = arr[i];
        }
        resize();
    }

    template<typename T>
    inline vector<T>::vector(T* _begin, T* _end)
    {
        if (_end >= _begin) {
            size_t length = _end - _begin + 1;
            _data = new T[length];
            elements_num = length;
            capacity_num = length;
            for (size_t i = 0; i < length; i++) {
                _data[i] = *(_begin + i);
            }
            resize();
        }
        else {
            throw std::logic_error("Iterator Range Error!");
        }
    }

    template<typename T>
    inline vector<T>::vector(size_t _elem_num, T value)
        : _data(new T[_elem_num])
        , capacity_num(_elem_num)
        , elements_num(0)
    {
        for (; elements_num < _elem_num; elements_num++) {
            _data[elements_num] = value;
        }
    }

    template<typename T>
    vector<T>::vector(vector<T>&& vec) noexcept 
        : _data(vec._data)
        , capacity_num(vec.capacity_num)
        , elements_num(vec.elements_num)
    {
        resize();
        vec._data = nullptr;
    }

    template<typename T>
    vector<T>::vector(std::initializer_list<T> l) 
        : _data(new T[l.size()])
        , elements_num(0)
        , capacity_num(l.size())
    {
        for (auto it = l.begin(); it != l.end(); it++) {
            push_back(*it);
        }
    }

    template<typename T>
    vector<T>::vector(const vector<T>& sec) 
        : _data(new T[sec.capacity_num])
        , capacity_num(sec.capacity_num)
        , elements_num(sec.elements_num)
    {
        for (int i = 0; i < elements_num; i++) {
            _data[i] = sec[i];
        }
    }

    template<typename T>
    vector<T>::~vector() 
    {
        delete[] _data;
        _data = nullptr;
    }

    template<typename T>
    inline void vector<T>::resize(size_t new_elem_num)
    {
        if (new_elem_num <= capacity_num) {
            elements_num = new_elem_num;
        }
        else {
            reserve(new_elem_num + 128);
            elements_num = new_elem_num;
        }
        resize();
    }

    template<typename T>
    inline void vector<T>::resize(size_t new_elem_num, T value)
    {
        if (new_elem_num <= capacity()) {
            if (new_elem_num <= elements_num) {
                elements_num = new_elem_num;
            }
            else {
                for (; elements_num < new_elem_num; elements_num++) {
                    _data[elements_num] = value;
                }
            }
        }
        else {
            reserve(new_elem_num + 128);
            for (; elements_num < new_elem_num; elements_num++) {
                _data[elements_num] = value;
            }
        }
        resize();
    }

    template<typename T>
    inline bool vector<T>::empty() const noexcept
    {
        if (elements_num == 0) return true;
        else return false;
    }

    template<typename T>
    inline size_t vector<T>::capacity() const noexcept
    {
        return capacity_num;
    }

    template<typename T>
    inline size_t vector<T>::size() const noexcept
    {
        return elements_num;
    }

    template<typename T>
    inline T* vector<T>::data()
    {
        return _data;
    }

    template<typename T>
    inline constexpr void vector<T>::swap(vector<T>& _Right)
    {
        size_t temp_size{ _Right.elements_num }, temp_capacity{ _Right.capacity_num };
        T* temp_data_ptr{ _Right._data };
        _Right.elements_num = elements_num;
        _Right.capacity_num = capacity_num;
        _Right._data = _data;

        elements_num = temp_size;
        capacity_num = temp_capacity;
        _data = temp_data_ptr;
        
        temp_data_ptr = nullptr;
    }

    template<typename T>
    inline void vector<T>::reserve(size_t new_capacity)
    {
        if (new_capacity != capacity_num) {
            try {
                T* temp = new T[new_capacity];
                size_t min_capacity{ (new_capacity > elements_num) ? elements_num : new_capacity };
                memmove(temp, _data, min_capacity * sizeof(T));
                delete[] _data;
                _data = temp;
                temp = nullptr;
                capacity_num = new_capacity;
                if (elements_num > capacity_num) {
                    elements_num = capacity_num;
                    resize();
                }
            }
            catch (std::bad_alloc& e) {
                throw e;
            }
        }
    }

    template<typename T>
    inline vector<T>::iterator vector<T>::begin()
    {
        return _data;
    }

    template<typename T>
    inline vector<T>::iterator vector<T>::end()
    {
        return _data + elements_num;
    }

    template<typename T>
    inline vector<T>::const_iterator vector<T>::begin() const
    {
        return _data;
    }

    template<typename T>
    inline vector<T>::const_iterator vector<T>::end() const
    {
        return _data + elements_num;
    }

    template<typename T>
    inline void vector<T>::push_back(T elem)
    {
        resize();
        if (elements_num < capacity_num) {
            _data[elements_num] = elem;
            elements_num++;
            resize();
        }
        else {
            throw std::out_of_range("Out of Range!");
        }
    }

    template<typename T>
    inline void vector<T>::pop_back()
    {
        elements_num--;
    }

    template<typename T>
    inline void vector<T>::clear()
    {
        elements_num = 0;
    }

    template<typename T>
    inline void vector<T>::erase(vector<T>::iterator pos_begin, vector<T>::iterator pos_end)
    {
        if (pos_begin <= pos_end) {
            if (pos_begin >= begin() && pos_begin <= end()) {
                if (end() < pos_end) {
                    pos_end = end();
                }
                for (auto it = pos_begin; it != pos_end + 1; it++) { // TODO: check if it's right!
                    *it = *(it + (pos_end - pos_begin));
                }
                elements_num -= pos_end - pos_begin;
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
    inline void vector<T>::insert(vector<T>::iterator pos, T value)
    {
        if (pos >= begin() && pos <= end()) {
            size_t ins_pos_index = pos - begin();
            size_t elem_after_insert_num = end() - pos;

            if (capacity_num < elements_num + 1) {
                reserve(capacity_num + 10);
            }
            pos = begin() + ins_pos_index;
            size_t element_to_be_mv_length = end() - pos;
            auto mv_ptr_pos{ end() - 1 };
            for (size_t i = 0; i < element_to_be_mv_length; i++) {
                *(mv_ptr_pos - i + 1) = *(mv_ptr_pos - i);
            }
            *pos = value;
            elements_num++;
        }
        else {
            throw IteratorOutOfRangeException{};
        }
    }

    template<typename T>
    inline void vector<T>::insert(vector<T>::iterator pos, size_t ins_elem_num, T value)
    {
        if (pos >= begin() && pos <= end()) {
            size_t ins_pos_index = pos - begin();
            size_t copy_num = end() - pos;
            if (ins_elem_num + elements_num > capacity_num) {
                reserve(ins_elem_num + elements_num + 128);
                pos = begin() + ins_pos_index;
            }

            size_t element_to_be_mv_length = end() - pos;

            auto mv_ptr_pos{ end() - 1 };
            for (size_t i = 0; i < element_to_be_mv_length; i++) {
                *(mv_ptr_pos - i + ins_elem_num) = *(mv_ptr_pos - i);
            }
            elements_num += ins_elem_num;
            size_t index = pos - begin();
            for (size_t i = 0; i < ins_elem_num; i++) {
                _data[index + i] = value;
            }
        }
        else {
            throw IteratorOutOfRangeException{};
        }
    }

    template<typename T>
    inline void vector<T>::insert(vector<T>::iterator pos,
        vector<T>::iterator other_pos_begin, vector<T>::iterator other_pos_end)
    {
        if (pos >= begin() && pos <= end()) {
            size_t ins_pos_index = pos - begin();
            size_t copy_num = end() - pos, ins_elem_num = other_pos_end - other_pos_begin;
            if (ins_elem_num + elements_num > capacity_num) {
                reserve(ins_elem_num + elements_num + 128);
                pos = begin() + ins_pos_index;
            }

            size_t element_to_be_mv_length = end() - pos;

            auto mv_ptr_pos{ end() - 1 };
            for (size_t i = 0; i < element_to_be_mv_length; i++) {
                *(mv_ptr_pos - i + ins_elem_num) = *(mv_ptr_pos - i);
            }
            elements_num += ins_elem_num;

            size_t index = pos - begin();
            for (size_t i = 0; i < ins_elem_num; i++) {
                _data[index + i] = *(other_pos_begin + i);
            }
        }
        else {
            throw IteratorOutOfRangeException{};
        }
    }
}
