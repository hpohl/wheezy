#ifndef WZY_RENDER_PROGRAM_HPP
#define WZY_RENDER_PROGRAM_HPP

#include <memory>
#include <string>
#include <vector>

#include <GL/glew.h>

#include <wzy/render/shader.hpp>
#include <wzy/utilities/exception.hpp>
#include <wzy/utilities/general.hpp>
#include <wzy/utilities/mat.hpp>
#include <wzy/utilities/noncopyable.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {
namespace render {

class Program final : public NonCopyable {
public:
    Program();
    ~Program();


    unsigned int name() const
    { return mName; }

    template <BasicShader::Type type>
    const std::shared_ptr<Shader<type> > shader();

    template <BasicShader::Type type>
    void setShader(const std::shared_ptr<Shader<type> >& shader);


    bool attached(const std::shared_ptr<BasicShader>& shader) const;

    void link() const;

    bool linked() const;

    bool valid() const;
    void validate() const;

    void use() const;

    const std::string infoLog() const;

    void setDefault();
    void setColourDefault();

    bool hasUniform(const std::string& name) const;

    void uniform(const std::string& name, int v);
    void uniform(const std::string& name, const std::vector<int>& v);

    template <int cols, int rows>
    void uniform(const std::string& name, const Matrix<cols, rows, float>& m)
    { uniform(cols, rows, m.data(), name); }

private:
    const unsigned int mName;
    std::vector<std::shared_ptr<BasicShader> > mShaders;

    void attach(const std::shared_ptr<BasicShader>& shader);
    void detach(const std::shared_ptr<BasicShader>& shader);

    bool attachedGL(const std::shared_ptr<BasicShader>& shader) const;

    void uniform(int cols, int rows, const float* val, const std::string& name);
};

template <BasicShader::Type type>
const std::shared_ptr<Shader<type> > Program::shader() {
    for (std::shared_ptr<BasicShader>& shader : mShaders)
        if (shader->type() == type)
            return std::static_pointer_cast<Shader<type> >(shader);
    auto newShader = std::make_shared<Shader<type>>();
    setShader(newShader);
    return newShader;
}

template <BasicShader::Type type>
void Program::setShader(const std::shared_ptr<Shader<type> >& shader) {
    wzy::validate(shader);

    for (auto it = mShaders.begin(); it != mShaders.end(); ++it) {
        if ((*it)->type() == type) {
            detach(shader);
            if (attachedGL(shader))
                throw Exception("Unable to detach previous shader.");
            mShaders.erase(it);
            break;
        }
    }

    attach(shader);
    mShaders.push_back(shader);
}

}
}

#endif
