#ifndef WZY_SCENE_MATERIAL_HPP
#define WZY_SCENE_MATERIAL_HPP

#include <memory>
#include <sstream>
#include <vector>

#include <wzy/render/texture.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {
namespace render {

class Program;

class Material {
public:
    typedef std::shared_ptr<std::vector<std::shared_ptr<render::Texture2D> > > TexturesPtr;


    Material();

    void use();

    const std::shared_ptr<Program> program()
    { return mProgram; }

    const std::shared_ptr<const Program> program() const
    { return mProgram; }

    void setProgram(const std::shared_ptr<Program>& prog)
    { mProgram = validate(prog); }

    const TexturesPtr textures()
    { return mTextures; }

private:
    std::shared_ptr<Program> mProgram;
    TexturesPtr mTextures;
};

}
}

#endif
