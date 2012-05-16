#include <wzy/render/data.hpp>

#include <wzy/render/glew.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

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
        auto loc = BasicShader::findBuiltIn("wzyPosition").location;
        glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(loc);
    } if (mTexCoordBuffer) {
        mTexCoordBuffer->bind();
        auto loc = BasicShader::findBuiltIn("wzyTexCoord").location;
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(loc);
    } if (mColourBuffer) {
        mColourBuffer->bind();
        auto loc = BasicShader::findBuiltIn("wzyColor").location;
        glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(loc);
    }
}

void Data::draw() const {
    set();
    glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer->size());
}

}
}
