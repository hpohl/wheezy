#ifndef WZY_RENDER_SHADER_HPP
#define WZY_RENDER_SHADER_HPP

#include <map>
#include <string>
#include <tuple>

#include <wzy/utilities/noncopyable.hpp>


namespace wzy {
namespace render {

class BasicShader : public NonCopyable {
public:
    enum class Type {
        Fragment,
        Vertex
    };

    struct BuiltIn {
        std::string layout;
        std::string storage;
        std::string type;
    };

    typedef std::map<std::string, BuiltIn> BuiltIns;


    static const BuiltIns builtIns();
    static const BuiltIn findBuiltIn(const std::string& name);
    static void parseSource(std::string& src);

    BasicShader(BasicShader::Type t);
    virtual ~BasicShader() = 0;

    unsigned int name() const
    { return mName; }

    Type type() const;

    const std::string source() const;
    void setSource(const std::string& source);

    void compile();
    bool compiled() const;

    const std::string infoLog() const;

private:
    static BuiltIns mBuiltIns;

    const unsigned int mName;
};

template <BasicShader::Type ttype>
class Shader final : public BasicShader {
public:
    template <class... Args>
    Shader(Args&&... args) :
        BasicShader(ttype, std::forward<Args>(args)...) { }
};

typedef Shader<BasicShader::Type::Fragment> FragmentShader;
typedef Shader<BasicShader::Type::Vertex> VertexShader;

}
}

#endif
