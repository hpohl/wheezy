#include <wzy/core/engine.hpp>

#include <wzy/render/render.hpp>


namespace wzy {

Engine::Engine() {
    render::init();
}

Engine::~Engine() {
}


// -----------------------------------------------
void Engine::frame() {
    for (std::shared_ptr<State>& state : mStates) {
        state->update();
    }
}


// ---------------------------------------
const Engine::ConstStateStack Engine::states() const {
    ConstStateStack ret(mStates.begin(), mStates.end());
    return ret;
}

}
