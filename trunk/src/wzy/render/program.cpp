#include <wzy/render/program.hpp>

#include <algorithm>

#include <wzy/render/glew.hpp>


namespace wzy {
namespace render {

Program::Program() :
    mName(glCreateProgram()),
    mShaders() {

    if (!mName)
        throw Exception("Program creation failed.");
}

Program::~Program() {
    glDeleteProgram(mName);
}


// ----------------------------------------------
bool Program::attached(const std::shared_ptr<BasicShader>& shader) const {
    auto it = std::find(mShaders.begin(), mShaders.end(), shader);
    return it != mShaders.end();
}

void Program::link() {
    glLinkProgram(mName);
    if (!linked())
        throw Exception("Unable to link program.");
}

bool Program::linked() const {
    GLint status = 0;
    glGetProgramiv(mName, GL_LINK_STATUS, &status);
    return status;
}

bool Program::valid() const {
    GLint status = 0;
    glGetProgramiv(mName, GL_VALIDATE_STATUS, &status);
    return status;
}

void Program::validate() const {
    if (!valid())
        throw Exception("Program is not valid.");
}

void Program::use() const {
    validate();
    glUseProgram(mName);
}

const std::string Program::infoLog() const {
    GLint len = 0;
    glGetProgramiv(mName, GL_INFO_LOG_LENGTH, &len);
    std::unique_ptr<GLchar[]> data(new GLchar[len]);
    glGetProgramInfoLog(mName, len, nullptr, data.get());
    return std::string(data.get());
}


// ---------------------------------------------------
void Program::attach(const std::shared_ptr<BasicShader>& shader) {
    glAttachShader(mName, shader->name());
}

void Program::detach(const std::shared_ptr<BasicShader>& shader) {
    glDetachShader(mName, shader->name());
}

bool Program::attachedGL(const std::shared_ptr<BasicShader>& shader) const {
    GLint num = 0;
    glGetProgramiv(GL_ATTACHED_SHADERS, shader->name(), &num);
    std::unique_ptr<GLuint[]> names(new GLuint[num]);
    glGetAttachedShaders(mName, num, nullptr, names.get());

    for (int i = 0; i < num; ++i)
        if (shader->name() == names[i])
            return true;

    return false;
}

}
}
