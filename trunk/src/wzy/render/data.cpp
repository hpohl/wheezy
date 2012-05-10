#include <wzy/render/data.hpp>

#include <wzy/render/glew.hpp>
#include <wzy/render/shader.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

Data::Data() :
    mName(0) {

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
        glVertexAttribPointer(BasicShader::vertexLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(BasicShader::vertexLoc);
    }
}

void Data::draw() const {
    set();
    glDrawArrays(GL_TRIANGLES, 0, mVertexBuffer->size());
}

}
}
