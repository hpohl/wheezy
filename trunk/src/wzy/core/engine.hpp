#ifndef WZY_CORE_ENGINE_HPP
#define WZY_CORE_ENGINE_HPP

#include <memory>
#include <typeindex>
#include <vector>

#include <wzy/core/state.hpp>
#include <wzy/core/window.hpp>
#include <wzy/gui/view.hpp>
#include <wzy/scene/node.hpp>
#include <wzy/utilities/singleton.hpp>


namespace wzy {

class Engine final : public Singleton<Engine>,
                     public Window {
public:
    typedef std::vector<std::shared_ptr<State> > StateStack;
    typedef std::vector<std::shared_ptr<const State> > ConstStateStack;


    // ------------------------------------------------
    Engine();
    ~Engine();


    // ---------------------------------------------------
    void frame();


    // --------------------------------------------------
    const StateStack states()
    { return mStates; }

    const ConstStateStack states() const;

    const StateStack::value_type current()
    { return mStates.back(); }

    template <class StateType>
    bool stateInStack() const;

    template <class StateType, class... Args>
    void pushState(Args&&... args) {
        static_assert(IsState<StateType>::value, "You can only push states.");
        mStates.push_back(std::shared_ptr<State>(new StateType(std::forward<Args>(args)...)));
    }

    void popState()
    { mStates.erase(mStates.end()); }

    template <class StateType, class... Args>
    void popAllAndPush(Args&&... args) {
        mStates.clear();
        pushState<StateType>(std::forward<Args>(args)...);
    }


    // -----------------------------------
    std::shared_ptr<SceneNode> rootNode()
    { return mRootNode; }

    std::shared_ptr<gui::Object> rootGUIObject()
    { return mRootGUIObject; }

    std::shared_ptr<gui::View> rootView()
    { return mRootView; }


private:
    StateStack mStates;
    std::shared_ptr<SceneNode> mRootNode;
    std::shared_ptr<gui::Object> mRootGUIObject;
    std::shared_ptr<gui::View> mRootView;

    void draw();
};


template <class StateType>
bool Engine::stateInStack() const {
    for (auto val : mStates)
        if (typeid(*val) == typeid(*val))
            return true;
    return false;
}

}


#endif
