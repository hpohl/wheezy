#include <iostream>

#include <cstring>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <wzy/core/engine.hpp>
#include <wzy/media/image.hpp>
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

std::vector<wzy::Vector4f> colors = {
    {1.0, 0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 0.0, 1.0, 1.0},

    {1.0, 0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 0.0, 1.0, 1.0}
};

class TestingState : public wzy::State {
public:
    void update() {
        // -------------------------------------------------------------
        wzy::Image img("images/bruce.png");
        wzy::render::Texture2D tex;

        tex.setData(img.size(), img.bpp(), img.data());
        tex.activateSlot(0);
        tex.bind();


        // ------------------------------------------------
        wzy::render::Program prog;
        prog.use();


        auto vbo = std::make_shared<wzy::render::Data::VertexBuffer>();
        vbo->setData(vertices);

        auto tcbo = std::make_shared<wzy::render::Data::TexCoordBuffer>();
        tcbo->setData(texCoords);

        auto cbo = std::make_shared<wzy::render::Data::ColourBuffer>();
        cbo->setData(colors);


        wzy::render::Data data;

        data.setVertices(vbo);
        data.setColors(cbo);


        data.draw();
    }
};

int main()
try {
    wzy::Engine& eng = wzy::Engine::singleton();
    eng.pushState<TestingState>();

    eng.execute();

} catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
}
