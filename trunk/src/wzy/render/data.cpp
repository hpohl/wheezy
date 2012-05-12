#include <wzy/render/data.hpp>

#include <wzy/render/glew.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

Data::Data() :
    mName(0),
    mVertexBuffer(),
    mTexCoordBuffer() {

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
    } if (mColorBuffer) {
        mColorBuffer->bind();
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
