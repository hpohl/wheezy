#include <wzy/render/shader.hpp>

#include <iostream>
#include <memory>
#include <sstream>

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


// ---------------------------------------
BasicShader::BuiltIns BasicShader::mBuiltIns = {
    // Vector data
    {"wzyPosition", {"layout(location = 10)", "in", "vec4"}},
    {"wzyColour", {"layout(location = 11)", "in", "vec4"}},
    {"wzyTexCoord", {"layout(location = 12)", "in", "vec2"}},

    // Uniforms
    {"wzyModelViewMatrix", {"", "uniform", "mat4"}},
    {"wzyProjectionMatrix", {"", "uniform", "mat4"}},
    {"wzyTexture2D", {"", "uniform", "sampler2D"}}
};


// ---------------------------------------
const BasicShader::BuiltIns BasicShader::builtIns() {
    return mBuiltIns;
}

const BasicShader::BuiltIn BasicShader::findBuiltIn(const std::string& name) {
    auto it = mBuiltIns.find(name);
    if (it == mBuiltIns.end())
        throw Exception("Unable to find shader builtin named " + name + ".");
    return it->second;
}

void BasicShader::parseSource(std::string& src) {
    if (src.find("//WZYSHADER") == std::string::npos) {
        for (BuiltIns::value_type& p : mBuiltIns) {
            auto name = p.first;
            auto builtin = p.second;

            if (src.find(name) != std::string::npos) {
                auto addition = builtin.layout + " " + builtin.storage +
                        " " + builtin.type + " " + name + ";\n";
                src.insert(src.begin(), addition.begin(), addition.end());
            }
        }

        src.insert(0, "layout(row_major) uniform;\n");
        src.insert(0, "#extension GL_ARB_shading_language_420pack: enable\n");
        src.insert(0, "#version 420\n");
        src.insert(0, "//WZYSHADER\n");
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
    std::string parsedSource(source);
    parseSource(parsedSource);

    const GLchar* csource = parsedSource.c_str();
    const GLint len = parsedSource.length();
    glShaderSource(mName, 1, &csource, &len);
}

void BasicShader::compile() {
    glCompileShader(mName);
    if (!compiled())
        throw Exception("Failed to compile shader. Log: \n" + infoLog());
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
