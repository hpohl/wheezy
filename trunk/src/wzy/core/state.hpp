#ifndef WZY_CORE_STATE_HPP
#define WZY_CORE_STATE_HPP

#include <type_traits>


namespace wzy {

class State {
public:
    State();
    virtual ~State() = 0;

    virtual void update();
};

template <class T>
struct IsState : public std::is_base_of<State, T> { };

}

#endif
