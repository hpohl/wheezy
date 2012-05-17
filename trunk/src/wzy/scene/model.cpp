#include <wzy/scene/model.hpp>

#include <algorithm>

#include <wzy/utilities/exception.hpp>


namespace wzy {

Model::Model() :
    mVertices(new std::vector<Vector4f>),
    mColours(new std::vector<Vector4f>),
    mIndices(new std::vector<Index>) {
}

Model::Model(const std::vector<Vector4f>& vertices,
             const std::vector<Vector4f>& colours) :
    mVertices(new std::vector<Vector4f>),
    mColours(new std::vector<Vector4f>),
    mIndices(new std::vector<Index>) {

    if (vertices.size() != colours.size())
        throw Exception("Vertices and colours must have the same size in model creation.");

    auto size = vertices.size();

    for (size_t i = 0; i < size; ++i) {
        Index idx;

        auto vit = std::find(mVertices->begin(), mVertices->end(), vertices[i]);
        if (vit == mVertices->end()) {
            mVertices->push_back(vertices[i]);
            idx.vertex = mVertices->size() - 1;
        } else
            idx.vertex = vit - mVertices->begin();

        auto cit = std::find(mColours->begin(), mColours->end(), colours[i]);
        if (cit == mColours->end()) {
            mColours->push_back(colours[i]);
            idx.colour = mColours->size() - 1;
        } else
            idx.colour = cit - mColours->begin();

        mIndices->push_back(idx);
    }

    update();
}


// ----------------------------------------
void Model::update() {
    /*std::vector<Vector4f> vertices;
    std::vector<Vector4f> colours;

    for (const Index& i : *mIndices) {
        assert(i.vertex < mVertices->size());
        vertices.push_back((*mVertices)[i.vertex]);

        assert(i.colour < mVertices->size());
        colours.push_back((*mColours)[i.colour]);
    }

    auto vbo = std::make_shared<render::Data::VertexBuffer>();
    vbo->setData(vertices);
    mRenderData->setVertices(vbo);

    auto cbo = std::make_shared<render::Data::ColourBuffer>();
    cbo->setData(colours);
    mRenderData->setColours(cbo);*/
}

}
