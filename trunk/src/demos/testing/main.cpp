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
    {-0.8, 0.8, 0.0, 1.0},
    {0.8, -0.8, 0.0, 1.0},
    {0.8, 0.8, 0.0, 1.0},

    {-0.8, 0.8, 0.0, 1.0},
    {-0.8, -0.8, 0.0, 1.0},
    {0.8, -0.8, 0.0, 1.0},
};

std::vector<wzy::Vector2f> texCoords = {
    {0.0, 1.0},
    {1.0, 0.0},
    {1.0, 1.0},

    {0.0, 1.0},
    {0.0, 0.0},
    {1.0, 0.0},
};

std::vector<wzy::Vector4f> colours = {
    {1.0, 0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 0.0, 1.0, 1.0},

    {1.0, 0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 0.0, 1.0, 1.0}
};

const std::shared_ptr<wzy::Model> createModel() {
    /*auto verts = std::make_shared<std::vector<wzy::Vector4f> >(vertices);
    auto cols = std::make_shared<std::vector<wzy::Vector4f> >(colours);
    auto texCs = std::make_shared<std::vector<wzy::Vector2f> >(texCoords);

    auto mdl = std::make_shared<wzy::Model>(verts, cols, texCs);
    auto prog = std::make_shared<wzy::render::Program>();
    prog->setColourDefault();
    mdl->material()->setProgram(prog);
    //mdl->material()->textures()->push_back(wzy::render::textureFromImage(wzy::Image("images/landscape.jpg")));*/

    auto mdl = wzy::loadFromOBJ("models/altair.obj");

    std::vector<wzy::Vector4f> colours(mdl->vertices()->size(), wzy::Vector4f(1.0, 0.0, 0.0, 1.0));

    mdl->setColours(std::make_shared<decltype(colours)>(colours));

    mdl->update();

    auto prog = std::make_shared<wzy::render::Program>();
    prog->setColourDefault();
    mdl->material()->setProgram(prog);

    return mdl;
}

class TestingState : public wzy::State {
public:
    TestingState() :
        mModel(createModel()),
        mEnt(std::make_shared<wzy::Entity>(mModel)) {
        wzy::Engine::singleton().rootNode()->attach(mEnt);

        mEnt->setPosition(wzy::Vector3f(0.0, 0.0, -5.0));
    }

    void update() {
        wzy::Engine& eng = wzy::Engine::singleton();
        auto cam = wzy::Engine::singleton().rootView()->camera();

        if (wzy::Engine::singleton().isPressed(wzy::Window::Key::w))
            cam->setPosition(cam->position() + wzy::Vector3f(-0.1, 0.0, 0.0));
        if (wzy::Engine::singleton().isPressed(wzy::Window::Key::e))
            cam->setPosition(cam->position() + wzy::Vector3f(0.0, 0.0, -0.1));
        if (wzy::Engine::singleton().isPressed(wzy::Window::Key::r))
            cam->setPosition(cam->position() + wzy::Vector3f(0.1, 0.0, 0.0));
        if (wzy::Engine::singleton().isPressed(wzy::Window::Key::d))
            cam->setPosition(cam->position() + wzy::Vector3f(0.0, 0.0, 0.1));

        constexpr float sensitivity = 30.0;
        auto rot = cam->rotation();

        std::cout << "Camera rotation: Roll: " << wzy::Degree(rot.roll()).v() << ", Pitch: " << wzy::Degree(rot.pitch()).v() << ", Yaw: " << wzy::Degree(rot.yaw()).v() << std::endl;

        cam->setRotation(cam->rotation() * wzy::Quaternionf(wzy::Degree(0.0),
                                                            wzy::Degree(sensitivity) * eng.timeRatio() * eng.mouseForce().x(),
                                                            wzy::Degree(sensitivity) * eng.timeRatio() * eng.mouseForce().y()));
    }

private:
    std::shared_ptr<wzy::Model> mModel;
    std::shared_ptr<wzy::AbstractEntity> mEnt;
};

int main()
try {
    wzy::Engine& eng = wzy::Engine::singleton();
    eng.pushState<TestingState>();

    eng.execute();

} /*catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
}*/
catch (int i) { }
