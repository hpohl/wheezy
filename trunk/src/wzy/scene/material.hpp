#ifndef WZY_SCENE_MATERIAL_HPP
#define WZY_SCENE_MATERIAL_HPP

#include <memory>
#include <vector>

#include <wzy/render/texture.hpp>


namespace wzy {

namespace render {
class Program;
}

class Material {
public:
    typedef std::shared_ptr<std::vector<std::shared_ptr<render::Texture2D> > > TexturesPtr;


    Material();

    void use();

    const std::shared_ptr<render::Program> program()
    { return mProgram; }

    const TexturesPtr textures()
    { return mTextures; }

private:
    std::shared_ptr<render::Program> mProgram;
    TexturesPtr mTextures;
};

}

#endif
