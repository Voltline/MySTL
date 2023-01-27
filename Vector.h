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
        T* data;
        size_t capacity{};
        size_t elements_num{};
        void resize();
    public:
        Vector();
        Vector(T* arr, int n);
        Vector(size_t n);
        Vector(Vector<T>&& vec) noexcept;
        Vector(std::initializer_list<T> l);
        Vector(Vector<T>& sec);
        ~Vector();

        void resize(size_t new_elem_num);
        void resize(size_t new_elem_num, T value);
        void reserve(size_t new_size);

        T* begin();
        T* end();

        void push_back(T elem);
        void pop_back();
        void clear();
        void erase(T* pos_begin, T* pos_end);
        
        void insert(T* pos, T value);
        void insert(T* pos, size_t ins_elem_num, T value);
        void insert(T* pos, T* other_pos_begin, T* other_pos_end);

        bool empty();
        size_t capacity_num();
        size_t elem_num();
        T* get_data();

        T& operator[](size_t index);
        bool operator==(Vector vec);

        template<typename U>
        friend std::ostream& operator<<(std::ostream& output, Vector<U> vec);
    };

    template<typename T>
    void Vector<T>::resize()
    {
        /* The mode of vector resize:
         * if v.elements_num == capacity, new capacity = capacity + 128;
         */
        if (this->elements_num == this->capacity) {
            try {
                T* temp = new T[this->capacity + 128];
                memcpy(temp, this->data, this->elements_num * sizeof(T));
                delete[] this->data;
                this->data = temp;
                temp = nullptr;
            }
            catch (std::bad_alloc& e) {
                throw e;
            }
        }
    }

    template<typename T>
    T& Vector<T>::operator[](size_t index) 
    {
        if (index < this->elements_num) {
            return this->data[index];
        }
        else {
            throw std::out_of_range("Out of Range!");
        }
    }

    template<typename T>
    Vector<T>::Vector() 
    {
        this->data = new T[128];
        this->capacity = 128;
        this->elements_num = 0;
    }

    template<typename T>
    Vector<T>::Vector(size_t n) 
    {
        try {
            this->data = new T[n];
            this->capacity = n;
            this->elements_num = 0;
        }
        catch (std::bad_alloc& e) {
            this->data = new T[128];
            this->capacity = 128;
            this->elements_num = 0;
        }
    }

    template<typename T>
    Vector<T>::Vector(T* arr, int n) 
    {
        this->data = arr;
        this->capacity = n;
        this->elements_num = n;
        this->resize();
    }

    template<typename T>
    Vector<T>::Vector(Vector<T>&& vec) noexcept 
    {
        this->data = vec.get_data();
        this->capacity = vec.capacity_num();
        this->elements_num = vec.elem_num();
        this->resize();

        vec.~Vector();
    }

    template<typename T>
    Vector<T>::Vector(std::initializer_list<T> l) 
    {
        try {
            this->data = new T[l.size() + 128];
            this->elements_num = 0;
            this->capacity = l.size() + 128;
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
        this->capacity = sec.capacity_num();
        this->elements_num = sec.elem_num();
        try {
            this->data = new T[this->capacity];
            for (int i = 0; i < this->elements_num; i++) {
                this->data[i] = sec[i];
            }
        }
        catch (std::bad_alloc& e) {
            throw e;
        }
    }

    template<typename T>
    Vector<T>::~Vector() 
    {
        delete[] this->data;
        this->data = nullptr;
        this->capacity = 0;
        this->elements_num = 0;
    }

    template<typename T>
    inline void Vector<T>::resize(size_t new_elem_num)
    {
        if (new_elem_num <= this->capacity) {
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
        if (new_elem_num <= this->capacity) {
            if (new_elem_num <= this->elements_num) {
                this->elements_num = new_elem_num;
            }
            else {
                for (; this->elements_num < new_elem_num; this->elements_num++) {
                    this->data[this->elements_num] = value;
                }
            }
        }
        else {
            this->reserve(new_elem_num + 128);
            for (; this->elements_num < new_elem_num; this->elements_num++) {
                this->data[this->elements_num] = value;
            }
        }
        this->resize();
    }

    template<typename T>
    bool Vector<T>::empty() 
    {
        if (this->elements_num == 0) return true;
        else return false;
    }

    template<typename T>
    size_t Vector<T>::capacity_num()
    {
        return this->capacity;
    }

    template<typename T>
    size_t Vector<T>::elem_num() 
    {
        return this->elements_num;
    }

    template<typename T>
    T* Vector<T>::get_data()
    {
        return this->data;
    }

    template<typename U>
    std::ostream& operator<<(std::ostream& output, Vector<U> vec) 
    {
        for (int i = 0; i < vec.elem_num(); i++) {
            output << vec[i] << " ";
        }
        return output;
    }

    template<typename T>
    inline void Vector<T>::reserve(size_t new_size)
    {
        if (new_size != this->capacity) {
            try {
                T* temp = new T[new_size];
                size_t min_size{ (new_size > this->elements_num) ? this->elements_num : new_size };
                memcpy(temp, this->data, min_size * sizeof(T));
                delete[] this->data;
                this->data = temp;
                temp = nullptr;
                this->capacity = new_size;
            }
            catch (std::bad_alloc& e) {
                throw e;
            }
        }
    }

    template<typename T>
    inline T* Vector<T>::begin()
    {
        return this->data;
    }

    template<typename T>
    inline T* Vector<T>::end()
    {
        return this->data + this->elements_num;
    }

    template<typename T>
    inline void Vector<T>::push_back(T elem)
    {
        this->resize();
        if (this->elements_num < this->capacity) {
            this->data[this->elements_num] = elem;
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
    inline void Vector<T>::erase(T* pos_begin, T* pos_end)
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
}
