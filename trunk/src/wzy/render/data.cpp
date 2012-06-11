#include <wzy/render/data.hpp>

#include <wzy/render/glew.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

const std::shared_ptr<Data> Data::quad() {
    static std::vector<Vector4f> vertices = {
        { -0.5, 0.5, 0.0, 1.0 },
        { 0.5, 0.5, 0.0, 1.0 },
        { 0.5, -0.5, 0.0, 1.0 },

        { -0.5, 0.5, 0.0, 1.0 },
        { -0.5, -0.5, 0.0, 1.0 },
        { 0.5, -0.5, 0.0, 1.0 }
    };

    static std::vector<Vector2f> texCoords = {
        { 0.0, 1.0 },
        { 1.0, 1.0 },
        { 1.0, 0.0 },

        { 0.0, 1.0 },
        { 0.0, 0.0 },
        { 1.0, 0.0 }
    };

    auto data = std::make_shared<Data>();

    auto vertexBuffer = std::make_shared<VertexBuffer>();
    vertexBuffer->setData(vertices);

    auto texCoordBuffer = std::make_shared<TexCoordBuffer>();
    texCoordBuffer->setData(texCoords);

    data->setVertices(vertexBuffer);
    data->setTexCoords(texCoordBuffer);

    return data;
}


// ------------------------------------------
Data::Data() :
    mName(0),
    mVertexBuffer(),
    mColourBuffer(),
    mTexCoordBuffer() {

    glGenVertexArrays(1, &mName);
    if (!mName)
        throw Exception("Unable to create vertex array.");
}

Data::Data(const std::shared_ptr<const VertexBuffer>& vertices,
           const std::shared_ptr<const ColourBuffer>& colours,
           const std::shared_ptr<const TexCoordBuffer>& texCoords) :
    mName(0),
    mVertexBuffer(vertices),
    mColourBuffer(colours),
    mTexCoordBuffer(texCoords) { }

Data::~Data() {
    glDeleteVertexArrays(1, &mName);
}

// -----------------------------------------
void Data::bind() const {
    glBindVertexArray(mName);
}

void Data::set() const {
    bind();

    if (mVertexBuffer) {
        mVertexBuffer->bind();
        glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(10);
    } if (mColourBuffer) {
        mColourBuffer->bind();
        glVertexAttribPointer(11, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(11);
    } if (mTexCoordBuffer) {
        mTexCoordBuffer->bind();
        glVertexAttribPointer(12, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(12);
    }
}

void Data::draw() const {
    set();
    glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer->size());
}

}
}
