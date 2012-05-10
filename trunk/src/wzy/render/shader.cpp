#include <wzy/render/shader.hpp>

#include <memory>

#include <wzy/render/glew.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {


namespace {

GLenum typeToGL(BasicShader::Type t) {
    switch (t) {
    case BasicShader::Type::Fragment:
        return GL_FRAGMENT_SHADER;
    case BasicShader::Type::Vertex:
        return GL_VERTEX_SHADER;
    default:
        throw Exception("Unknown shader type.");
    }
}

}


// -------------------------------------
BasicShader::BasicShader(Type t) :
    mName(glCreateShader(typeToGL(t))) {

    if (!mName)
        throw Exception("Shader creation failed.");
}

BasicShader::~BasicShader() {
    glDeleteShader(mName);
}


// ---------------------------------
BasicShader::Type BasicShader::type() const {
    GLint t = 0;
    glGetShaderiv(mName, GL_SHADER_TYPE, &t);

    switch (t) {
    case GL_FRAGMENT_SHADER: return Type::Fragment;
    case GL_VERTEX_SHADER: return Type::Vertex;
    default: throw Exception("Unknown shader type.");
    }
}

const std::string BasicShader::source() const {
    GLint len = 0;
    glGetShaderiv(mName, GL_SHADER_SOURCE_LENGTH, &len);
    std::unique_ptr<GLchar[]> data(new GLchar[len]);
    glGetShaderSource(mName, len, nullptr, data.get());
    return std::string(data.get());
}

void BasicShader::setSource(const std::string& source) {
    const GLchar* csource = source.c_str();
    const GLint len = source.length();
    glShaderSource(mName, 1, &csource, &len);
}

void BasicShader::compile() {
    glCompileShader(mName);
    if (!compiled())
        throw Exception("Failed to compile shader.");
}

bool BasicShader::compiled() const {
    GLint status = 0;
    glGetShaderiv(mName, GL_COMPILE_STATUS, &status);
    return status;
}

const std::string BasicShader::infoLog() const {
    GLint len = 0;
    glGetShaderiv(mName, GL_INFO_LOG_LENGTH, &len);
    std::unique_ptr<GLchar[]> data(new GLchar[len]);
    glGetShaderInfoLog(mName, len, nullptr, data.get());
    return std::string(data.get());
}

}
}
