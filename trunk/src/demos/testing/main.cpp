#include <iostream>

#include <cstring>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <wzy/core/engine.hpp>
#include <wzy/media/image.hpp>
#include <wzy/scene/entity.hpp>
#include <wzy/scene/model.hpp>
#include <wzy/render/data.hpp>
#include <wzy/render/program.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/render/texture.hpp>
#include <wzy/utilities/general.hpp>
#include <wzy/utilities/vec.hpp>

std::vector<wzy::Vector4f> vertices = {
    {-0.8, 0.8, -0.8, 1.0},
    {0.8, 0.8, -0.8, 1.0},
    {0.8, -0.8, -0.8, 1.0},

    {-0.8, 0.8, -0.8, 1.0},
    {0.8, -0.8, -0.8, 1.0},
    {-0.8, -0.8, -0.8, 1.0}
};

std::vector<wzy::Vector2f> texCoords = {
    {0.0, 0.0},
    {1.0, 0.0},
    {1.0, 1.0},

    {0.0, 0.0},
    {1.0, 1.0},
    {0.0, 1.0}
};

std::vector<wzy::Vector4f> colours = {
    {1.0, 0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 0.0, 1.0, 1.0},

    {1.0, 0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 0.0, 1.0, 1.0}
};

class TestingState : public wzy::State {
public:
    TestingState() :
        mProg(),
        mEnt(wzy::Engine::singleton().sceneManager()->addEntity<wzy::Entity>(std::make_shared<wzy::Model>(vertices, colours))) {

        mProg.use();
    }

    void update() {
        // -------------------------------------------------------------
        wzy::Image img("images/bruce.png");
        wzy::render::Texture2D tex;

        tex.setData(img.size(), img.bpp(), img.data());
        tex.activateSlot(0);
        tex.bind();
    }

private:
    wzy::render::Program mProg;
    std::shared_ptr<wzy::AbstractEntity> mEnt;
};

int main()
try {
    wzy::Engine& eng = wzy::Engine::singleton();
    eng.pushState<TestingState>();

    eng.execute();

} catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
}
