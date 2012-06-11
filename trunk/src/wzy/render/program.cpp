#include <wzy/render/program.hpp>

#include <algorithm>

#include <wzy/render/glew.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {
namespace render {


// ---------------------------------------
Program::Program() :
    mName(glCreateProgram()),
    mShaders() {

    if (!mName)
        throw Exception("Program creation failed.");

    setDefault();
}

Program::~Program() {
    glDeleteProgram(mName);
}


// ----------------------------------------------
bool Program::attached(const std::shared_ptr<BasicShader>& shader) const {
    auto it = std::find(mShaders.begin(), mShaders.end(), shader);
    return it != mShaders.end();
}

void Program::link() const {
    glLinkProgram(mName);
    if (!linked())
        throw Exception("Unable to link program. Log:\n" + infoLog());
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
    if (!linked())
        link();
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

void Program::setDefault() {
    shader<BasicShader::Type::Vertex>()->setSource(fileToString("shaders/default/vertex.glsl"));
    shader<BasicShader::Type::Fragment>()->setSource(fileToString("shaders/default/fragment.glsl"));
    link();
}

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

void Program::uniform(const std::string& name, int v) {
    validate();

    auto loc = glGetUniformLocation(mName, name.c_str());
    if (loc == -1)
        throw Exception("Invalid uniform location for " + name + ".");

    glUniform1i(loc, v);
}

void Program::uniform(const std::string& name, const std::vector<int>& v) {
    validate();

    auto loc = glGetUniformLocation(mName, name.c_str());
    if (loc == -1)
        throw Exception("Invalid uniform location for " + name + ".");

    glUniform1iv(loc, v.size(), v.data());
}


// -------------------------------------------
void Program::uniform(int cols, int rows, const float* val, const std::string& name) {
    validate();

    void (*func)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) = nullptr;

    switch (cols) {
    case 2:
        switch (rows) {
        case 2: func = glUniformMatrix2fv; break;
        case 3: func = glUniformMatrix2x3fv; break;
        case 4: func = glUniformMatrix2x4fv; break;
        default: throw Exception("Invalid matrix row number in uniform.");
        }
        break;

    case 3:
        switch (rows) {
        case 2: func = glUniformMatrix3x2fv; break;
        case 3: func = glUniformMatrix3fv; break;
        case 4: func = glUniformMatrix3x4fv; break;
        default: throw Exception("Invalid matrix row number in uniform.");
        }
        break;

    case 4:
        switch (rows) {
        case 2: func = glUniformMatrix4x2fv; break;
        case 3: func = glUniformMatrix4x3fv; break;
        case 4: func = glUniformMatrix4fv; break;
        default: throw Exception("Invalid matrix row number in uniform.");
        }
        break;

    default: throw Exception("Invalid matrix coloumn number in uniform.");
    }

    GLint loc = glGetUniformLocation(mName, name.c_str());

    if (loc == -1)
        throw Exception("Matrix uniform " + name + " not found in program.");

    func(loc, 1, GL_FALSE, val);
}

}
}
