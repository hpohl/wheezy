#ifndef WZY_SCENE_MATERIAL_HPP
#define WZY_SCENE_MATERIAL_HPP

#include <memory>
#include <sstream>
#include <vector>

#include <wzy/render/texture.hpp>
#include <wzy/resource/item.hpp>
#include <wzy/utilities/general.hpp>


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

    void setProgram(const std::shared_ptr<render::Program>& prog)
    { mProgram = validate(prog); }

    const TexturesPtr textures()
    { return mTextures; }

private:
    std::shared_ptr<render::Program> mProgram;
    TexturesPtr mTextures;
};


class MaterialItem : public Item {
public:
    constexpr static int constId = -3;

    template <class... Args>
    MaterialItem(const std::string& name, const std::string& content, Args&&... args);

    const std::string content() const override
    { return ""; }

    const std::shared_ptr<Material> material()
    { return mMaterial; }

private:
    static bool mReg;

    static const std::shared_ptr<Item> create(const std::string& name,
                                              const std::string& content)
    { return std::make_shared<MaterialItem>(name, content); }

    std::shared_ptr<Material> mMaterial;
};

template <class... Args>
MaterialItem::MaterialItem(const std::string& name, const std::string& content, Args&&... args) :
    Item(constId, name, std::forward<Args>(args)...),
    mMaterial(new Material) {

    std::istringstream ss(content);

    // Read textures
    std::size_t numTextures = 0;
    ss.read(reinterpret_cast<char*>(numTextures), sizeof(numTextures));


}

}

#endif
