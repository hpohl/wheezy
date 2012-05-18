#ifndef WZY_SCENE_MATERIAL_HPP
#define WZY_SCENE_MATERIAL_HPP

#include <memory>


namespace wzy {

namespace render {
class Program;
}

class Material {
public:
    Material();

    void use();

    const std::shared_ptr<render::Program> program()
    { return mProgram; }

private:
    std::shared_ptr<render::Program> mProgram;
};

}

#endif
