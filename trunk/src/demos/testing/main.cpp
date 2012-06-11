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
    {0.8, 0.8, 0.0, 1.0},
    {0.8, -0.8, 0.0, 1.0},

    {-0.8, 0.8, 0.0, 1.0},
    {0.8, -0.8, 0.0, 1.0},
    {-0.8, -0.8, 0.0, 1.0}
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

const std::shared_ptr<wzy::Model> createModel() {
    auto verts = std::make_shared<std::vector<wzy::Vector4f> >(vertices);
    auto cols = std::make_shared<std::vector<wzy::Vector4f> >(colours);
    auto texCs = std::make_shared<std::vector<wzy::Vector2f> >(texCoords);

    auto tex = std::make_shared<wzy::render::Texture2D>();

    unsigned char* data = new unsigned char[512 * 512 * 3];

    memset(data, 255, 512 * 512 * 3);

    tex->setImage(wzy::render::Texture2D::BaseInternalFormat::RGB, wzy::Vector2i(512, 512),
                  wzy::render::Texture2D::Format::RGB, wzy::render::Texture2D::DataType::UByte,
                  data);

    auto mdl = std::make_shared<wzy::Model>(verts, cols, texCs);
    mdl->material()->textures()->push_back(tex);

    return mdl;
}

class TestingState : public wzy::State {
public:
    TestingState() :
        mModel(createModel()),
        mEnt(std::make_shared<wzy::Entity>(mModel)) {
        wzy::Engine::singleton().rootNode()->attach(mEnt);

        mEnt->setPosition(wzy::Vector3f(0.0, 0.0, -1.0));

        auto view = std::make_shared<wzy::gui::View>(wzy::gui::UDim({ 0.0, 0.0 }, { 0, 0 }),
                                                     wzy::gui::UDim({ 0.5, 0.5 }, { 0, 0 }));
        wzy::Engine::singleton().rootGUIObject()->attach(view);
    }

    void update() {
        // -------------------------------------------------------------
        auto view = wzy::Engine::singleton().rootView();
        view->scale(wzy::Vector2f(0.1, 0.1));
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

} catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
}
