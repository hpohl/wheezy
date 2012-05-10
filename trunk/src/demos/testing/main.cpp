#include <iostream>

#include <GL/freeglut.h>

#include <wzy/core/engine.hpp>
#include <wzy/media/image.hpp>
#include <wzy/render/data.hpp>
#include <wzy/render/program.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/utilities/vec.hpp>


const char* vertexShader =
{
    "#version 400\n"\

    "layout(location=10) in vec4 wzyPosition;\n"\

    "void main(void)\n"\
    "{\n"\
    "   gl_Position = wzyPosition;\n"\
    "}\n"
};

const char* fragmentShader =
{
    "#version 400\n"\

    "out vec4 out_Color;\n"\

    "void main(void)\n"\
    "{\n"\
    "   out_Color = vec4(0.0, 0.0, 1.0, 1.0);\n"\
    "}\n"
};

std::vector<wzy::Vector4f> vertices = {
    {-1.0, 0.0, -1.0, 1.0},
    {0.0, 1.0, -1.0, 1.0},
    {1.0, 0.0, -1.0, 1.0}
};

class TestingState : public wzy::State {
public:
    void update() {
        wzy::render::Program prog;

        prog.setShader(std::make_shared<wzy::render::VertexShader>());
        prog.setShader(std::make_shared<wzy::render::FragmentShader>());

        prog.getShader<wzy::render::BasicShader::Type::Vertex>()->setSource(vertexShader);
        prog.getShader<wzy::render::BasicShader::Type::Vertex>()->compile();

        prog.getShader<wzy::render::BasicShader::Type::Fragment>()->setSource(fragmentShader);
        prog.getShader<wzy::render::BasicShader::Type::Fragment>()->compile();

        prog.link();

        prog.use();


        auto vbo = std::make_shared<wzy::render::Data::VertexBuffer>();

        vbo->setData(vertices);


        wzy::render::Data data;

        data.setVertices(vbo);


        data.draw();


        // -------------------------------------------------------------
        wzy::Image img("images/bruce.png");
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
