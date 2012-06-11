#include <wzy/core/engine.hpp>

#include <wzy/render/render.hpp>
#include <wzy/scene/model.hpp>


namespace wzy {

Engine::Engine() :
    Singleton<Engine>(),
    Window(),
    mStates(),
    mRootNode(new SceneNode),
    mRootGUIObject(new gui::Object(gui::UDim({ 0.0, 0.0 }, { 0, 0 }),
                                   gui::UDim({ 0.0, 0.0 }, { 0, 0 }))),
    mRootView() {

    render::init();

    mRootView.reset(new gui::View(gui::UDim({ 0.0, 0.0 }, { 0, 0 }),
                                  gui::UDim({ 1.0, 1.0 }, { 0, 0 })));
    mRootGUIObject->attach(mRootView);
}

Engine::~Engine() {
}


// -----------------------------------------------
void Engine::frame() {
    for (std::shared_ptr<State>& state : mStates)
        state->update();
    draw();
}


// ---------------------------------------
const Engine::ConstStateStack Engine::states() const {
    ConstStateStack ret(mStates.begin(), mStates.end());
    return ret;
}


// --------------------------------------
void Engine::draw() {
    render::FrameBuffer::useDefault();
    render::clear();
    mRootGUIObject->draw(gui::UDim({ 0.0, 0.0 }, { 0, 0 }), { 1.0, 1.0 });
}

}
