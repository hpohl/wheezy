#include <wzy/scene/model.hpp>

#include <algorithm>

#include <wzy/utilities/exception.hpp>


namespace wzy {

Model::Model() :
    mName(),
    mChildren(new std::vector<std::shared_ptr<Model> >),
    mVertices(new std::vector<Vector4f>),
    mColours(new std::vector<Vector4f>),
    mTexCoords(new std::vector<Vector2f>),
    mMaterial(new Material),
    mRenderData(new render::Data) {
}

Model::Model(const VerticesPtr& vertices,
             const ColoursPtr& colours,
             const TexCoordsPtr& texCoords) :
    mName(),
    mChildren(new std::vector<std::shared_ptr<Model> >),
    mVertices(vertices),
    mColours(colours),
    mTexCoords(texCoords),
    mMaterial(new Material),
    mRenderData(new render::Data) {

    update();
}


// ----------------------------------------
void Model::update() {
    auto vbo = std::make_shared<render::Data::VertexBuffer>();
    vbo->setData(*mVertices);
    mRenderData->setVertices(vbo);

    if (!mColours->empty()) {
        auto cbo = std::make_shared<render::Data::ColourBuffer>();
        cbo->setData(*mColours);
        mRenderData->setColours(cbo);
    }

    if (!mTexCoords->empty()) {
        auto tcbo = std::make_shared<render::Data::TexCoordBuffer>();
        tcbo->setData(*mTexCoords);
        mRenderData->setTexCoords(tcbo);
    }
}

}
