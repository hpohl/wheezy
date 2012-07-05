#include <wzy/resource/items/material.hpp>

#include <GL/glew.h>

#include <wzy/render/program.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {

MaterialItem::MaterialItem() :
    Item(),
    mMaterial() {
}


// -----------------------------------------------------
void MaterialItem::doRead(std::istream& is) {
    std::int32_t vsSize = 0;
    is.read(reinterpret_cast<char*>(&vsSize), sizeof(vsSize));

    std::string vsSource(vsSize, 0);
    is.read(&vsSource[0], vsSize);

    std::int32_t fsSize = 0;
    is.read(reinterpret_cast<char*>(&fsSize), sizeof(fsSize));

    std::string fsSource(fsSize, 0);
    is.read(&fsSource[0], fsSize);

    mMaterial.reset(new render::Material);

    auto prog = mMaterial->program();
    auto vs = prog->shader<render::BasicShader::Type::Vertex>();
    auto fs = prog->shader<render::BasicShader::Type::Fragment>();

    vs->setSource(vsSource);
    fs->setSource(fsSource);

    vs->compile();
    fs->compile();

    prog->link();
}

void MaterialItem::doWrite(std::ostream& os) const {
    auto prog = mMaterial->program();

    auto vsSource = prog->shader<render::BasicShader::Type::Vertex>()->source();
    std::int32_t vsSize = vsSource.size();
    os.write(reinterpret_cast<const char*>(&vsSize), sizeof(vsSize));
    os.write(&vsSource[0], vsSource.size());

    auto fsSource = prog->shader<render::BasicShader::Type::Fragment>()->source();
    std::int32_t fsSize = fsSource.size();
    os.write(reinterpret_cast<const char*>(&fsSize), sizeof(fsSize));
    os.write(&fsSource[0], fsSource.size());
}

}
