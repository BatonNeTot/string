//
// Created by KILLdon on 07.03.2019.
//

#ifndef STRING_STRING_H
#define STRING_STRING_H

#include "smart_pool.h"

#include <sstream>

namespace util {
    class string {
    private:

        static smart_pool<char> _valuePool;

        char *_value;
        size_t _size;

        void _init(const char *);

        void _check_index(int index) const;

    public:

        string(const string &sourse);
        string(const string &&sourse);
        string(const char *source);
        string(const std::string &source);
        string(const std::string &&source);

        explicit string(size_t size = 0);

        ~string();

        inline const char *c_str() const { return _value; };

        inline const size_t size() const { return _size; };

        operator char*() const;
        operator const char*() const;

        char &operator[](int index);
        const char &operator[](int index) const;

        friend std::ostream& operator<<(std::ostream& os, const string& str);
        friend std::istream& operator>>(std::istream& is, const string& str);

        friend bool operator==(const string& lhs, const string& rhs);
        friend inline bool operator!=(const string& lhs, const string& rhs) { return !(lhs==rhs); };

        friend bool operator<(const string& lhs, const string& rhs);
        friend inline bool operator>(const string& lhs, const string& rhs) { return rhs < lhs; };
        friend inline bool operator<=(const string& lhs, const string& rhs) { return !(rhs < lhs); };
        friend inline bool operator>=(const string& lhs, const string& rhs) { return !(lhs < rhs); };

        friend string operator+(const string& lhs, const string& rhs);

    };
}

#endif //STRING_STRING_H
