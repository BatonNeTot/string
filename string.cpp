//
// Created by KILLdon on 07.03.2019.
//

#include "string.h"

namespace util {

    smart_pool<char> string::_valuePool;

    string::string(const string &sourse): _size(sourse._size) {
        _init(sourse);
    }

    string::string(const string &&sourse): _size(sourse._size) {
        _init(sourse);
    }

    string::string(const char *source): _size(0) {
        for (auto *iter = const_cast<char *>(source); *iter != '\0'; iter++, _size++);
        _init(source);
    }

    string::string(const std::string &source): _size(source.size()) {
        _init(source.c_str());
    }

    string::string(const std::string &&source): _size(source.size()) {
        _init(source.c_str());
    }

    void string::_init(const char *source) {
        const size_t full = _size + 1;
        _value = static_cast<char *>(_valuePool.alloc(full));
        std::copy(source, source + full, _value);
    }

    string::string(size_t size): _size(size) {
        if (_size < 0) {
            std::stringstream str;
            str << "size is negative: " << size;
            throw std::invalid_argument(str.str());
        }
        const size_t full = _size + 1;
        _value = static_cast<char *>(_valuePool.alloc(full));
        std::fill(_value, _value + full, '\0');
    }

    string::~string() {
        _valuePool.free((void *) _value);
    }

    void string::_check_index(int index) const {
        if (index < 0){
            std::stringstream str;
            str << "index is negative: " << index;
            throw std::out_of_range(str.str());
        }
        if (index >= _size) {
            std::stringstream str;
            str << "index is too big: " << index;
            throw std::out_of_range(str.str());
        }
    }

    string::operator char*() const {
        return _value;
    }

    string::operator const char*() const {
        return _value;
    }

    char &string::operator[](int index) {
        _check_index(index);
        return _value[index];
    }

    const char &string::operator[](int index) const {
        _check_index(index);
        return _value[index];
    }

    std::ostream &operator<<(std::ostream &os, const string &str) {
        char *buffer = str._value;
        size_t buffer_size = 0;
        for (size_t i = 0; i < str._size; i++ ) {
            if (str._value[i] != '\0') {
                buffer_size++;
            } else {
                if (buffer_size != 0)
                    os.write(buffer, buffer_size);

                buffer = str._value + i;
                buffer_size = 0;
            }
        }
        if (buffer_size != 0)
            os.write(buffer, buffer_size);
        return os;
    }

    std::istream &operator>>(std::istream &is, const string &str) {
        is >> str._value;
        return is;
    }

    bool operator==(const string& lhs, const string &rhs) {
        if (lhs._size != rhs._size)
            return false;
        for (size_t i = 0; i < lhs._size; i++) {
            if (lhs[i] != rhs[i])
                return false;
        }
        return true;
    }

    bool operator<(const string& lhs, const string &rhs) {
        size_t min = std::min(lhs._size, rhs._size);

        for (size_t i = 0; i < min; i++) {
            if (lhs[i] != rhs[i])
                return lhs[i] < rhs[i];
        }

        return rhs._size < lhs._size;
    }

    string operator+(const string& lhs, const string &rhs) {
        string result(lhs._size + rhs._size);

        std::copy(lhs._value, lhs._value + lhs._size, result._value);
        std::copy(rhs._value, rhs._value + rhs._size, result._value + lhs._size);

        return result;
    }
}