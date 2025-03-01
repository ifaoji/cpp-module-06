#pragma once

#ifndef ASSERT_HPP_
#    define ASSERT_HPP_

#    include <cstdlib>
#    define ASSERT(condition, message)                                         \
        if (!(condition)) {                                                    \
            std::cerr << "Failed assertion at " << __FILE__ << ":" << __LINE__ \
                      << ": " << message << std::endl;                         \
            std::abort();                                                      \
        }

#    define ASSERT_EQ(left, right, message)                                    \
        if ((left) != (right)) {                                               \
            std::cerr << "Failed assertion at " << __FILE__ << ":" << __LINE__ \
                      << ":\n"                                                 \
                      << "`left == right` failed: " << message                 \
                      << "\nleft: " << #left << "\nright: " << #right          \
                      << std::endl;                                            \
            std::abort();                                                      \
        }

#    define ASSERT_NE(left, right, message)                                    \
        if ((left) == (right)) {                                               \
            std::cerr << "Failed assertion at " << __FILE__ << ":" << __LINE__ \
                      << ":\n"                                                 \
                      << "`left != right` failed: " << message                 \
                      << "\nleft: " << #left << "\nright: " << #right          \
                      << std::endl;                                            \
            std::abort();                                                      \
        }

#endif
