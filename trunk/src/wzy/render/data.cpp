#include <wzy/render/data.hpp>

#include <wzy/render/glew.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

const std::shared_ptr<Data> Data::quad(const Vector2f& size) {
    Vector2f halfSize = size / 2.0;

    std::vector<Vector4f> vertices = {
        { -halfSize.x(), halfSize.y(), 0.0, 1.0 },
        { halfSize.x(), -halfSize.y(), 0.0, 1.0 },
        { halfSize.x(), halfSize.y(), 0.0, 1.0 },

        { -halfSize.x(), halfSize.y(), 0.0, 1.0 },
        { -halfSize.x(), -halfSize.y(), 0.0, 1.0 },
        { halfSize.x(), -halfSize.y(), 0.0, 1.0 }
    };

    std::vector<Vector2f> texCoords = {
        { 0.0, 1.0 },
        { 1.0, 0.0 },
        { 1.0, 1.0 },

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
    mVertexBuffer(new VertexBuffer),
    mColourBuffer(new ColourBuffer),
    mTexCoordBuffer(new TexCoordBuffer) {

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
    mTexCoordBuffer(texCoords) {

    glGenVertexArrays(1, &mName);
    if (!mName)
        throw Exception("Unable to create vertex array.");
}

Data::~Data() {
    glDeleteVertexArrays(1, &mName);
}

// -----------------------------------------
void Data::bind() const {
    glBindVertexArray(mName);
}

void Data::set() const {
    bind();

    if (mVertexBuffer->count() > 0) {
        mVertexBuffer->bind();
        glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(10);
    } if (mColourBuffer->count() >= mVertexBuffer->count()) {
        mColourBuffer->bind();
        glVertexAttribPointer(11, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(11);
    } if (mTexCoordBuffer->count() >= mVertexBuffer->count()) {
        mTexCoordBuffer->bind();
        glVertexAttribPointer(12, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(12);
    }
}

void Data::draw() const {
    set();
    glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer->count());
}

}
}
