#include <wzy/scene/material.hpp>

#include <wzy/render/program.hpp>


namespace wzy {

Material::Material() :
    mProgram(new render::Program),
    mTextures(new std::vector<std::shared_ptr<render::Texture2D> >) {
}


// -----------------------------------------
void Material::use() {
    mProgram->use();

    if (mProgram->hasUniform("wzyTexture2D")) {
        static std::vector<int> iv = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        };

        for (std::size_t i = 0; i < mTextures->size(); ++i) {
            auto tex = (*mTextures)[i];
            tex->activateSlot(i);
            tex->bind();
        }

        mProgram->uniform("wzyTexture2D", 0);
    }
}

}
