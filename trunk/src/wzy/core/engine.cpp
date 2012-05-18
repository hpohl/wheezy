#include <wzy/core/engine.hpp>

#include <wzy/render/render.hpp>
#include <wzy/scene/model.hpp>


namespace wzy {

Engine::Engine() :
    Singleton<Engine>(),
    Window(),
    mStates(),
    mRootNode(new SceneNode) {

    render::init();
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
    auto nodes = mRootNode->children();

    for (const std::shared_ptr<AbstractSceneNode>& node : nodes) {
        node->draw(mRootNode->transform());
    }
}

}
