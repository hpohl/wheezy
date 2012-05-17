#include <wzy/core/engine.hpp>

#include <wzy/render/render.hpp>


namespace wzy {

Engine::Engine() :
    Singleton<Engine>(),
    Window(),
    mStates(),
    mSceneManager(new SceneManager) {
    render::init();
}

Engine::~Engine() {
}


// -----------------------------------------------
void Engine::frame() {
    for (std::shared_ptr<State>& state : mStates)
        state->update();

    update();
}


// ---------------------------------------
const Engine::ConstStateStack Engine::states() const {
    ConstStateStack ret(mStates.begin(), mStates.end());
    return ret;
}


// --------------------------------------
void Engine::draw() {
    for (const std::shared_ptr<AbstractEntity>& ent : mSceneManager->entities()) {

    }
}

}
