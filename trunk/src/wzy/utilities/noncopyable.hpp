#ifndef WZY_UTILITES_NONCOPYABLE_HPP
#define WZY_UTILITES_NONCOPYABLE_HPP

namespace wzy {

struct NonCopyable {
    NonCopyable() = default;
    NonCopyable(const NonCopyable& other) = delete;
    NonCopyable(const NonCopyable&& other) = delete;
    NonCopyable& operator=(const NonCopyable& rhs) = delete;
};

}

#endif
