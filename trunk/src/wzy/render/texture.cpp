#include <wzy/render/texture.hpp>

#include <wzy/render/glew.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

namespace {

GLenum typeToGL(BasicTexture::Type t) {
    switch (t) {
    case BasicTexture::Type::TwoD: return GL_TEXTURE_2D;
    default: throw Exception("Unknown texture type.");
    }
}

GLenum typeToBinding(BasicTexture::Type t) {
    switch (t) {
    case BasicTexture::Type::TwoD: return GL_TEXTURE_BINDING_2D;
    default: throw Exception("Unknown texture type.");
    }
}

}


// ------------------------------------------
void BasicTexture::setSlot(Slot s) {
    glActiveTexture(GL_TEXTURE0 + s);
}


// --------------------------------------
BasicTexture::BasicTexture(Type t) :
    mName(0),
    mType(t) {

    glGenTextures(1, &mName);
    if (!mName)
        throw Exception("Unable to create texture.");
}

BasicTexture::~BasicTexture() {
    glDeleteTextures(1, &mName);
}


// -------------------------------------------
void BasicTexture::bind() const {
    glBindTexture(typeToGL(mType), mName);
    if (!bound())
        throw Exception("Failed to bind texture.");
}

bool BasicTexture::bound() const {
    GLint name;
    glGetIntegerv(typeToBinding(mType), &name);
    return name == mName;
}

}
}
