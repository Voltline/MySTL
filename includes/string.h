#pragma once
#include <iostream>
#include <cstring>
#include "vector.h"

namespace MySTL 
{
    template <typename T>
    class basic_string
    {
    private:
        vector<T> container;
        size_t _size;
    public:
        using iterator = T*;
        using const_iterator = const T*;
        inline static size_t npos = -1;
    public:
        basic_string();
        basic_string(const char* _c_str);
        basic_string(const char* _c_str, size_t _size);
        basic_string(const char* _c_str, size_t _begin, size_t _size);
        basic_string(size_t _size, char c);
        basic_string(const basic_string<T>& _str);
        basic_string(basic_string<T>&& _mv_str) noexcept;
        basic_string(std::initializer_list<T> l);
        ~basic_string();

        basic_string<T>& operator=(const basic_string<T>& _Right);
        basic_string<T>& operator=(basic_string<T>&& _Right) noexcept;
        basic_string<T>& operator=(const char* _str);
        basic_string<T>& operator=(char c);

        basic_string<T> operator+(const basic_string<T>& _Right);
        basic_string<T> operator+(const char* _str);
        basic_string<T> operator+(char c);

        basic_string<T>& operator+=(const basic_string<T>& _Right);
        basic_string<T>& operator+=(const char* _str);
        basic_string<T>& operator+=(char c);

        T& operator[](size_t _index);
        const T& operator[](size_t _index) const;
        T& at(size_t _index);

        bool operator==(const basic_string<T>& _Right);
        bool operator!=(const basic_string<T>& _Right);
        bool operator>(const basic_string<T>& _Right);
        bool operator<(const basic_string<T>& _Right);
        bool operator>=(const basic_string<T>& _Right);
        bool operator<=(const basic_string<T>& _Right);

        bool operator==(const char* _c_Right);
        bool operator!=(const char* _c_Right);
        bool operator>(const char* _c_Right);
        bool operator<(const char* _c_Right);
        bool operator>=(const char* _c_Right);
        bool operator<=(const char* _c_Right);

        size_t size() const noexcept;
        size_t capacity() const noexcept;
        bool empty() const noexcept;
        const T* data();
        const T* c_str();
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        void reserve(size_t new_capacity_size);
        void resize(size_t new_elem_size);
        void clear();
        void erase(const size_t _Where);
        void erase(const size_t _Off, const size_t _Count);
        void erase(iterator _begin, iterator _end);
        void erase(iterator _pos);

        void append(size_t _Count, char c);
        void append(const basic_string<T>& _str);
        void append(const basic_string<T>& _str, size_t _Begin = 0);
        void append(const basic_string<T>& _str, size_t _Begin, size_t _Count);
        void append(const char* _str);
        void append(const char* _str, size_t _Begin);
        void append(const char* _str, size_t _Begin, size_t _Count);
        void append(std::initializer_list<char> l);
        void push_back(char c);

        size_t find(char c, size_t _begin_pos = 0);
        size_t find(const char* _str, size_t _begin_pos = 0);
        size_t find(const basic_string<T>& _str, size_t _begin_pos = 0);

        void swap(basic_string<T>& _Right);

        template<typename U>
        friend std::ostream& operator<<(std::ostream& output, const basic_string<U>& _str)
        {
            for (auto& i : _str) {
                output << i;
            }
            return output;
        }

        template<typename U>
        friend std::istream& operator>>(std::istream& input, basic_string<U>& _str)
        {
            _str.clear();
            U c = input.get();
            while (c != ' ' && c != '\n' && c != '\t') {
                _str.push_back(c);
                c = input.get();
            }
            return input;
        }
    };

    template<typename T>
    basic_string<T>::basic_string()
    {
        container = vector<unsigned char>{};
    }

    template<typename T>
    basic_string<T>::basic_string(const char* _c_str)
    {
        size_t length{ strlen(_c_str) };
        _size = length;
        container = vector<T>();
        for (size_t i = 0; i < length; i++) {
            container.push_back(*(_c_str + i));
        }
        container.push_back('\0');
    }

    template<typename T>
    basic_string<T>::basic_string(const char* _c_str, size_t _size)
    {
        size_t length{ _size };
        if (_size > strlen(_c_str)) {
            length = strlen(_c_str);
        }

        _size = length;
        container = vector<T>();
        for (size_t i = 0; i < length; i++) {
            container.push_back(*(_c_str + i));
        }
        container.push_back('\0');
    }

    template<typename T>
    basic_string<T>::basic_string(const char* _c_str, size_t _begin, size_t _size)
    {
        size_t c_str_len{ strlen(_c_str) };
        container = vector<T>();
        if (_begin > c_str_len) {
            _size = 0;
        }
        else {
            size_t length{ _size };
            if (_size > strlen(_c_str + _begin)) {
                length = strlen(_c_str + _begin);
            }

            _size = length;
            for (size_t i = _begin; i < length; i++) {
                container.push_back(*(_c_str + i));
            }
            container.push_back('\0');
        }
    }

    template<typename T>
    basic_string<T>::basic_string(size_t _size, char c)
    {
        container = vector<T>(_size, c);
        _size = _size;
    }

    template<typename T>
    basic_string<T>::basic_string(const basic_string<T>& _str)
    {
        container = vector<T>(_str.container);
        _size = _str._size;
    }

    template<typename T>
    basic_string<T>::basic_string(basic_string<T>&& _mv_str) noexcept
    {
        container = std::move(_mv_str.container);
        _size = _mv_str._size;
        _mv_str.container = vector<T>{};
    }

    template<typename T>
    basic_string<T>::basic_string(std::initializer_list<T> l)
    {
        container = vector<T>(l.size() + 128);
        _size = l.size();
        for (auto it = l.begin(); it != l.end(); it++) {
            container.push_back(static_cast<T>(*it));
        }
        container.push_back('\0');
    }

    template<typename T>
    basic_string<T>::~basic_string()
    {
        _size = 0;
        container.~vector();
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator=(const basic_string<T>& _Right)
    {
        container.~vector();
        container = _Right.container;
        _size = _Right._size;
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator=(basic_string<T>&& _Right) noexcept
    {
        container.~vector();
        container = std::move(_Right.container);
        _size = _Right._size;
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator=(const char* _str)
    {
        container.~vector();
        size_t length{ strlen(_str) };
        container = vector<T>(length + 128);
        _size = 0;
        for (size_t i = 0; i < length; i++) {
            container.push_back(_str[i]);
            _size++;
        }
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator=(char c)
    {
        clear();
        push_back(c);
        return *this;
    }

    template<typename T>
    basic_string<T> basic_string<T>::operator+(const basic_string<T>& _Right)
    {
        basic_string<T> temp{ *this };
        for (auto& i : _Right) {
            temp.push_back(i);
        }
        return temp;
    }

    template<typename T>
    basic_string<T> basic_string<T>::operator+(const char* _str)
    {
        basic_string<T> temp{ *this };
        size_t length{ strlen(_str) };
        for (size_t i = 0; i < length; i++) {
            temp.push_back(_str[i]);
        }
        return temp;
    }

    template<typename T>
    basic_string<T> basic_string<T>::operator+(char c)
    {
        basic_string<T> temp{ *this };
        temp.push_back(c);
        return temp;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator+=(const basic_string<T>& _Right)
    {
        for (auto& i : _Right) {
            push_back(i);
        }
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator+=(const char* _str)
    {
        size_t length{ strlen(_str) };
        for (size_t i = 0; i < length; i++) {
            push_back(_str[i]);
        }
        return *this;
    }

    template<typename T>
    basic_string<T>& basic_string<T>::operator+=(char c)
    {
        push_back(c);
        return *this;
    }

    template<typename T>
    T& basic_string<T>::operator[](size_t _index)
    {
        return container[_index];
    }

    template<typename T>
    const T& basic_string<T>::operator[](size_t _index) const
    {
        return container[_index];
    }

    template<typename T>
    T& basic_string<T>::at(size_t _index)
    {
        if (_index <= _size) {
            return container[_index];
        }
        else {
            throw std::out_of_range("Index Out of Range");
        }
    }

    template<typename T>
    bool basic_string<T>::operator==(const basic_string<T>& _Right)
    {
        if (_size != _Right._size) {
            return false;
        }
        else {
            for (size_t i = 0; i < _size; i++) {
                if (container[i] != _Right[i]) return false;
            }
            return true;
        }
    }

    template<typename T>
    bool basic_string<T>::operator!=(const basic_string<T>& _Right)
    {
        return !(*this == _Right);
    }

    template<typename T>
    bool basic_string<T>::operator>(const basic_string<T>& _Right)
    {
        size_t min_size{ _size < _Right.size() ? _size : _Right.size() };
        for (size_t i = 0; i < min_size; i++) {
            if (container[i] > _Right[i]) return true;
            else if (container[i] < _Right[i]) {
                return false;
            }
        }
        return _size > _Right.size();
    }

    template<typename T>
    bool basic_string<T>::operator<(const basic_string<T>& _Right)
    {
        return (*this <= _Right) && (*this != _Right);
    }

    template<typename T>
    bool basic_string<T>::operator>=(const basic_string<T>& _Right)
    {
        return (*this > _Right) || (*this == _Right);
    }

    template<typename T>
    bool basic_string<T>::operator<=(const basic_string<T>& _Right)
    {
        return !(*this > _Right);
    }

    template<typename T>
    bool basic_string<T>::operator==(const char* _c_Right)
    {
        if (strlen(_c_Right) != _size) return false;
        else {
            for (size_t i = 0; i < _size; i++) {
                if (container[i] != _c_Right[i])
                    return false;
            }
            return true;
        }
    }

    template<typename T>
    bool basic_string<T>::operator!=(const char* _c_Right)
    {
        return !(*this == _c_Right);
    }

    template<typename T>
    bool basic_string<T>::operator>(const char* _c_Right)
    {
        size_t length{ strlen(_c_Right) };
        size_t min_size{ _size < length ? _size : length };
        for (size_t i = 0; i < min_size; i++) {
            if (container[i] > _c_Right[i]) return true;
            else if (container[i] < _c_Right[i]) {
                return false;
            }
        }
        return _size > length;
    }

    template<typename T>
    bool basic_string<T>::operator<(const char* _c_Right)
    {
        return (*this <= _c_Right) && (*this != _c_Right);
    }

    template<typename T>
    bool basic_string<T>::operator>=(const char* _c_Right)
    {
        return (*this > _c_Right) || (*this == _c_Right);
    }

    template<typename T>
    bool basic_string<T>::operator<=(const char* _c_Right)
    {
        return !(*this > _c_Right);
    }

    template<typename T>
    size_t basic_string<T>::size() const noexcept
    {
        return _size;
    }

    template<typename T>
    size_t basic_string<T>::capacity() const noexcept
    {
        return container.capacity();
    }

    template<typename T>
    bool basic_string<T>::empty() const noexcept
    {
        if (_size != 0) return false;
        else return true;
    }

    template<typename T>
    const T* basic_string<T>::data()
    {
        return container.data();
    }

    template<typename T>
    const T* basic_string<T>::c_str()
    {
        return container.data();
    }

    template<typename T>
    typename basic_string<T>::iterator basic_string<T>::begin()
    {
        return container.begin();
    }

    template<typename T>
    typename basic_string<T>::iterator basic_string<T>::end()
    {
        return container.begin() + _size;
    }

    template<typename T>
    typename basic_string<T>::const_iterator basic_string<T>::begin() const
    {
        return container.begin();
    }

    template<typename T>
    typename basic_string<T>::const_iterator basic_string<T>::end() const
    {
        return container.begin() + _size;
    }

    template<typename T>
    void basic_string<T>::reserve(size_t new_capacity_size)
    {
        container.reserve(new_capacity_size);
    }

    template<typename T>
    void basic_string<T>::resize(size_t new_elem_size)
    {
        container.resize(new_elem_size);
        _size = new_elem_size;
    }

    template<typename T>
    void basic_string<T>::clear()
    {
        _size = 0;
        container.clear();
    }

    template<typename T>
    void basic_string<T>::erase(const size_t _Where)
    {
        if (_Where <= _size) {
            _size = _Where;
            container.erase(container.begin() + _Where, container.end());
            container.push_back('\0');
        }
    }

    template<typename T>
    void basic_string<T>::erase(const size_t _Off, const size_t _Count)
    {
        if (_Off <= _size) {
            if (_size - _Off > _Count) {
                _size -= _Count;
                container.erase(container.begin() + _Off, container.begin() + _Off + _Count);
                container[_size] = '\0';
            }
            else {
                erase(_Off);
            }
        }
    }

    template<typename T>
    void basic_string<T>::erase(basic_string<T>::iterator _begin, basic_string<T>::iterator _end)
    {
        if (_end >= _begin) {
            if (_begin >= begin()) {
                size_t _Off = _begin - begin();
                size_t _Count = _end - _begin;
                if (_Off <= _size) {
                    if (_size - _Off > _Count) {
                        _size -= _Count;
                        container.erase(container.begin() + _Off, container.begin() + _Off + _Count);
                        container[_size] = '\0';
                    }
                    else {
                        erase(_Off);
                    }
                }
            }
            else {
                throw IteratorOutOfRangeException{};
            }
        }
        else {
            throw IteratorErrorException{};
        }
    }

    template<typename T>
    void basic_string<T>::erase(basic_string<T>::iterator _pos)
    {
        if (_pos >= begin()) {
            if (_pos < end()) {
                size_t _Where = _pos - begin();
                if (_Where <= _size) {
                    _size--;
                    container.erase(_pos, _pos + 1);
                    container[_size] = '\0';
                }
            }
        }
        else {
            throw IteratorErrorException{};
        }
    }

    template<typename T>
    void basic_string<T>::append(size_t _Count, char c)
    {
        for (size_t i = 0; i < _Count; i++) {
            push_back(c);
        }
    }

    template<typename T>
    void basic_string<T>::append(const basic_string<T>& _str)
    {
        *this += _str;
    }

    template<typename T>
    void basic_string<T>::append(const basic_string<T>& _str, size_t _Begin)
    {
        if (_Begin <= _str.size()) {
            if (_Begin == 0) {
                *this += _str;
            }
            else {
                for (auto it = _str.begin() + _Begin; it != _str.end(); it++) {
                    push_back(*it);
                }
            }
        }
        else {
            throw std::out_of_range("Begin index out of range!");
        }
    }

    template<typename T>
    void basic_string<T>::append(const basic_string<T>& _str, size_t _Begin, size_t _Count)
    {
        if (_Begin <= _str.size()) {
            if (_Begin + _Count > _str.size()) {
                _Count = _str.size() - _Begin;
            }
            for (size_t i = 0; i < _Count; i++) {
                push_back(_str[_Begin + i]);
            }
        }
        else {
            throw std::out_of_range("Begin index out of range!");
        }
    }

    template<typename T>
    void basic_string<T>::append(const char* _str)
    {
        *this += _str;
    }

    template<typename T>
    void basic_string<T>::append(const char* _str, size_t _Begin)
    {
        if (_Begin <= strlen(_str)) {
            *this += (_str + _Begin);
        }
        else {
            throw std::out_of_range("Begin index out of range!");
        }
    }

    template<typename T>
    void basic_string<T>::append(const char* _str, size_t _Begin, size_t _Count)
    {
        if (_Begin <= strlen(_str)) {
            if (strlen(_str) - _Begin < _Count) {
                _Count = strlen(_str) - _Begin;
            }
            if (_Count != 0) {
                for (size_t i = 0; i < _Count; i++) {
                    push_back(_str[_Begin + i]);
                }
            }
        }
        else {
            throw std::out_of_range("Begin index out of range!");
        }
    }

    template<typename T>
    void basic_string<T>::append(std::initializer_list<char> l)
    {
        for (auto& i : l) {
            push_back(i);
        }
    }

    template<typename T>
    void basic_string<T>::push_back(char c)
    {
        if (_size == container.size()) {
            container.push_back(c);
        }
        else {
            container[_size] = c;
        }
        container.push_back('\0');
        _size++;
    }

    template<typename T>
    size_t basic_string<T>::find(char c, size_t _begin_pos)
    {
        for (size_t i = _begin_pos; i < _size; i++) {
            if (container[i] == c) {
                return i;
            }
        }
        return npos;
    }

    template<typename T>
    size_t basic_string<T>::find(const char* _str, size_t _begin_pos)
    {
        size_t length{ strlen(_str) };
        bool isFind{ true };
        if (_size < length) return npos;
        else {
            for (size_t i = _begin_pos; i < _size; i++) {
                if (_size - i >= length) {
                    if (container[i] == _str[0]) {
                        isFind = true;
                        for (size_t j = 1; j < length; j++) {
                            if (container[i + j] != _str[j]) {
                                i = i + j - 1;
                                isFind = false;
                                break;
                            }
                        }
                        if (isFind) return i;
                    }
                }
                else {
                    return npos;
                }
            }
            return npos;
        }
    }

    template<typename T>
    size_t basic_string<T>::find(const basic_string<T>& _str, size_t _begin_pos)
    {
        size_t length{ _str.size() };
        bool isFind{ true };
        if (_size < length) return npos;
        else {
            for (size_t i = _begin_pos; i < _size; i++) {
                if (_size - i >= length) {
                    if (container[i] == _str[0]) {
                        isFind = true;
                        for (size_t j = 1; j < length; j++) {
                            if (container[i + j] != _str[j]) {
                                i = i + j - 1;
                                isFind = false;
                                break;
                            }
                        }
                        if (isFind) return i;
                    }
                }
                else {
                    return npos;
                }
            }
            return npos;
        }
    }

    template<typename T>
    void basic_string<T>::swap(basic_string<T>& _Right)
    {
        basic_string<T> temp{ _Right };
        _Right.clear();
        for (auto& c : *this) {
            _Right.push_back(c);
        }
        clear();
        for (auto& c : temp) {
            push_back(c);
        }
    }

    template<typename T>
    bool operator==(const char* _Left, const basic_string<T>& _Right)
    {
        return _Right == _Left;
    }

    template<typename T>
    bool operator!=(const char* _Left, const basic_string<T>& _Right)
    {
        return _Right != _Left;
    }

    template<typename T>
    bool operator>(const char* _Left, const basic_string<T>& _Right)
    {
        return _Right < _Left;
    }

    template<typename T>
    bool operator<(const char* _Left, const basic_string<T>& _Right)
    {
        return _Right > _Left;
    }

    template<typename T>
    bool operator>=(const char* _Left, const basic_string<T>& _Right)
    {
        return _Right <= _Left;
    }

    template<typename T>
    bool operator<=(const char* _Left, const basic_string<T>& _Right)
    {
        return _Right >= _Left;
    }

    template<typename T>
    std::istream& getline(std::istream& input, basic_string<T>& _Target, const char _End = '\n')
    {
        _Target.clear();
        T c = input.get();
        while (c != '\n') {
            _Target.push_back(c);
            c = input.get();
        }
        return input;
    }

    using string = basic_string<char>;
    using wstring = basic_string<wchar_t>;
#ifdef __cpp_lib_char8_t
    using u8string = basic_string<char8_t>;
#endif // __cpp_lib_char8_t
    using u16string = basic_string<char16_t>;
    using u32string = basic_string<char32_t>;
}
