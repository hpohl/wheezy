#ifndef WZY_CORE_ENGINE_HPP
#define WZY_CORE_ENGINE_HPP

#include <chrono>
#include <memory>
#include <stack>
#include <typeindex>

#include <wzy/core/state.hpp>
#include <wzy/core/window.hpp>
#include <wzy/utilities/singleton.hpp>


namespace wzy {

class SceneNode;

namespace gui {
class Object;
class View;
}

class Engine final : public Singleton<Engine>,
                     public Window {
public:
    typedef std::stack<std::shared_ptr<State> > StateStack;


    // ------------------------------------------------
    Engine();
    ~Engine();


    // ---------------------------------------------------
    void frame();


    // ---------------------------------------------------
    const std::chrono::time_point<std::chrono::high_resolution_clock> timeStarted() const
    { return mEngineStarted; }

    const std::chrono::milliseconds timeSinceStart() const
    { return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeStarted()); }

    const std::chrono::time_point<std::chrono::high_resolution_clock> lastFrameTime() const
    { return mLastFrameTime; }

    const std::chrono::milliseconds lastFrameDuration() const
    { return mLastFrameDuration; }

    float fps() const
    { return 1000.0 / static_cast<float>(mLastFrameDuration.count()); }

    float timeRatio() const
    { return static_cast<float>(mLastFrameDuration.count() / 1000.0); }


    // --------------------------------------------------
    const StateStack states()
    { return mStates; }

    const StateStack::value_type current()
    { return mStates.top(); }

    template <class StateType, class... Args>
    void pushState(Args&&... args) {
        static_assert(IsState<StateType>::value, "You can only push states.");
        mStates.push(std::shared_ptr<State>(new StateType(std::forward<Args>(args)...)));
    }

    void popState()
    { mStates.pop(); }

    template <class StateType, class... Args>
    void popAllAndPush(Args&&... args) {
        while (!mStates.empty())
            mStates.pop();
        pushState<StateType>(std::forward<Args>(args)...);
    }


    // -----------------------------------
    const std::shared_ptr<SceneNode> rootNode()
    { return mRootNode; }

    const std::shared_ptr<gui::Object> rootGUIObject()
    { return mRootGUIObject; }

    const std::shared_ptr<gui::View> rootView()
    { return mRootView; }


private:
    std::chrono::time_point<std::chrono::high_resolution_clock> mEngineStarted;
    std::chrono::time_point<std::chrono::high_resolution_clock> mLastFrameTime;
    std::chrono::milliseconds mLastFrameDuration;
    StateStack mStates;
    std::shared_ptr<SceneNode> mRootNode;
    std::shared_ptr<gui::Object> mRootGUIObject;
    std::shared_ptr<gui::View> mRootView;

    void resized() override;

    void draw();
};


}


#endif
