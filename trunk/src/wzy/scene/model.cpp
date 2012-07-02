#include <wzy/scene/model.hpp>

#include <algorithm>
#include <fstream>
#include <sstream>

#include <wzy/utilities/exception.hpp>


namespace wzy {

Model::Model() :
    mName(),
    mChildren(new std::vector<std::shared_ptr<Model> >),
    mVertices(new std::vector<Vector4f>),
    mColours(new std::vector<Vector4f>),
    mTexCoords(new std::vector<Vector2f>),
    mMaterial(new render::Material),
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
    mMaterial(new render::Material),
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


// -----------------------------------
const std::shared_ptr<Model> loadFromOBJ(const std::string& fileName) {
    std::ifstream inf(fileName);

    Model::VerticesPtr vertices(new std::vector<Vector4f>);
    Model::TexCoordsPtr texCoords(new std::vector<Vector2f>);

    std::vector<Vector4f> unorderedVertices;
    std::vector<Vector2f> unorderedTexCoords;

    while (inf.good()) {
        std::string line;
        std::getline(inf, line);

        if (line.empty())
            continue;

        auto pos = line.find_first_of(' ');
        std::string cmd(line, 0, pos);

        if (cmd == "v") {
            Vector3f vertex;
            std::stringstream ss(std::string(line, pos));

            ss >> vertex[0] >> vertex[1] >> vertex[2];

            unorderedVertices.push_back(Vector4f(vertex, 1.0));

        } else if (cmd == "f") {
            std::stringstream ss(std::string(line, pos));

            std::vector<int> indices;

            while (!ss.eof()) {
                int idx = 0;
                ss >> idx;
                indices.push_back(idx);
            }

            if (indices.size() == 4) {
                indices.insert(indices.begin() + 3, indices[0]);
                indices.insert(indices.begin() + 5, indices[2]);
            }

            for (auto idx : indices)
                vertices->push_back(unorderedVertices.at(idx - 1));
        } else if (cmd == "vt") {
            Vector2f texCoord;
            std::stringstream ss(std::string(line, pos));

            int count = 0;
            while (!ss.eof()) {
                if (count == 2)
                    break;

                ss >> texCoord[count];
                ++count;
            }

            unorderedTexCoords.push_back(texCoord);
        }
    }

    //for (auto vert : *vertices)
    //    print(vert);

    auto mdl = std::make_shared<Model>();

    mdl->setVertices(vertices);
    mdl->setTexCoords(texCoords);

    mdl->update();

    return mdl;
}

}
