#include <wzy/scene/material.hpp>

#include <wzy/render/program.hpp>


namespace wzy {

Material::Material() :
    mProgram(new render::Program) {
}


// -----------------------------------------
void Material::use() {
    mProgram->use();
}

}
