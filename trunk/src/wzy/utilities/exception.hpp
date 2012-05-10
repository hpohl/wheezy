#ifndef WZY_UTILITIES_EXCEPTION_HPP
#define WZY_UTILITIES_EXCEPTION_HPP

#include <stdexcept>


namespace wzy {

class AbstractException : public std::runtime_error {
public:
    template <typename... Args>
    AbstractException(Args&&... args) noexcept :
        std::runtime_error(std::forward<Args>(args)...) { }
    virtual ~AbstractException() noexcept = 0;
};


class Exception : public AbstractException {
public:
    template <typename... Args>
    Exception(Args&&... args) :
        AbstractException(std::forward<Args>(args)...) { }
};

}

#endif
