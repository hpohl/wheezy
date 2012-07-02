#include <wzy/resource/items/material.hpp>

#include <GL/glew.h>

#include <wzy/render/program.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {

MaterialItem::MaterialItem(const std::string& name, const std::string& content) :
    Item(name),
    mMaterial(new render::Material) {

    std::stringstream ss(content);

    std::int32_t vsSize = 0;
    ss.read(reinterpret_cast<char*>(&vsSize), sizeof(vsSize));

    std::string vsSource(vsSize, 0);
    ss.read(&vsSource[0], vsSize);

    std::int32_t fsSize = 0;
    ss.read(reinterpret_cast<char*>(&fsSize), sizeof(fsSize));

    std::string fsSource(fsSize, 0);
    ss.read(&fsSource[0], fsSize);

    auto prog = mMaterial->program();
    auto vs = prog->shader<render::BasicShader::Type::Vertex>();
    auto fs = prog->shader<render::BasicShader::Type::Fragment>();

    vs->setSource(vsSource);
    fs->setSource(fsSource);

    vs->compile();
    fs->compile();

    prog->link();
}

MaterialItem::MaterialItem(const std::string& name, const std::shared_ptr<render::Material>& material) :
    Item(name),
    mMaterial(validate(material)) {
}


// -------------------------------------------------
const std::string MaterialItem::content() const {
    std::stringstream ss;
    auto prog = mMaterial->program();

    auto vsSource = prog->shader<render::BasicShader::Type::Vertex>()->source();
    std::int32_t vsSize = vsSource.size();
    ss.write(reinterpret_cast<const char*>(&vsSize), sizeof(vsSize));
    ss.write(&vsSource[0], vsSource.size());

    auto fsSource = prog->shader<render::BasicShader::Type::Fragment>()->source();
    std::int32_t fsSize = fsSource.size();
    ss.write(reinterpret_cast<const char*>(&fsSize), sizeof(fsSize));
    ss.write(&fsSource[0], fsSource.size());

    return ss.str();
}

}
