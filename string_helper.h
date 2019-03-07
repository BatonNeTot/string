#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include "string.h"
#include "numb_helper.h"

#include <cstring>

namespace str{
    namespace cmpr {
        struct less
        {
            bool operator()(char const *a, char const *b)
            {
                return std::strcmp(a, b) < 0;
            }
        };

        struct equal
        {
            bool operator()(char const *a, char const *b)
            {
                return std::strcmp(a, b) == 0;
            }
        };
    };

    inline bool less(char const *a, char const *b) {
        return std::strcmp(a, b) < 0;
    }

    inline bool equal(char const *a, char const *b) {
        return std::strcmp(a, b) == 0;
    }

    inline int cmp(const char *a, const char *b) {
        return util::sign(std::strcmp(a,b));
    }

    util::string frmt(const char *, ...);

    util::string to_utf8(unsigned int code);

    util::string concat(size_t count, util::string* strings);

    util::string concat(size_t count, util::string* strings, size_t sum_size);
};

#endif //STRING_HELPER_H