#include <wzy/render/texture.hpp>

#include <map>

#include <wzy/render/glew.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

namespace {

struct TexInfo {
    GLenum target;
    GLenum binding;
};

const TexInfo getTexInfo(BasicTexture::Type t) {
    static std::map<BasicTexture::Type, TexInfo> typeMap = {
        { BasicTexture::Type::Tex1D, { GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D } },
        { BasicTexture::Type::Tex2D, { GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D } },
        { BasicTexture::Type::Tex3D, { GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D } }
    };

    auto it = typeMap.find(t);
    if (it == typeMap.end())
        throw Exception("Unable to find texture info.");
    return it->second;
}

GLenum getInternalFormat(BasicTexture::BaseInternalFormat intf) {
    static std::map<BasicTexture::BaseInternalFormat, GLenum> intfMap = {
        { BasicTexture::BaseInternalFormat::R, GL_RED },
        { BasicTexture::BaseInternalFormat::RG, GL_RG },
        { BasicTexture::BaseInternalFormat::RGB, GL_RGB },
        { BasicTexture::BaseInternalFormat::RGBA, GL_RGBA }
    };

    auto it = intfMap.find(intf);
    if (it == intfMap.end())
        throw Exception("Unable to convert internal format to GL.");
    return it->second;
}

GLenum getInternalFormat(BasicTexture::SizedInternalFormat intf) {
    static std::map<BasicTexture::SizedInternalFormat, GLenum> intfMap = {
        { BasicTexture::SizedInternalFormat::RGBA8, GL_RGBA8 }
    };

    auto it = intfMap.find(intf);
    if (it == intfMap.end())
        throw Exception("Unable to convert internal format to GL.");
    return it->second;
}

GLenum getFormat(BasicTexture::Format f) {
    static std::map<BasicTexture::Format, GLenum> formatMap = {
        { BasicTexture::Format::R, GL_RED },
        { BasicTexture::Format::RG, GL_RG },
        { BasicTexture::Format::RGB, GL_RGB },
        { BasicTexture::Format::BGR, GL_BGR },
        { BasicTexture::Format::RGBA, GL_RGBA },
        { BasicTexture::Format::BGRA, GL_BGRA }
    };

    auto it = formatMap.find(f);
    if (it == formatMap.end())
        throw Exception("Unable to convert format to GL.");
    return it->second;
}

GLenum getDataType(BasicTexture::DataType d) {
    static std::map<BasicTexture::DataType, GLenum> dataTypeMap = {
        { BasicTexture::DataType::Byte, GL_BYTE },
        { BasicTexture::DataType::UByte, GL_UNSIGNED_BYTE }
    };

    auto it = dataTypeMap.find(d);
    if (it == dataTypeMap.end())
        throw Exception("Unable to convert data type to GL.");
    return it->second;
}

GLenum get2DTarget(BasicTexture::Target2D t) {
    static std::map<BasicTexture::Target2D, GLenum> targetMap = {
        { BasicTexture::Target2D::Tex2D, GL_TEXTURE_2D }
    };

    auto it = targetMap.find(t);
    if (it == targetMap.end())
        throw Exception("Unable to convert 2D texture target to GL.");
    return it->second;
}

GLenum getMinFilter(const BasicTexture::MinFilter& filter) {
    static std::map<BasicTexture::MinFilter, GLenum> filterMap = {
        { BasicTexture::MinFilter::Linear, GL_LINEAR },
        { BasicTexture::MinFilter::LinearMipmapLinear, GL_LINEAR_MIPMAP_LINEAR }
    };

    auto it = filterMap.find(filter);
    if (it == filterMap.end())
        throw Exception("Unable to convert min filter to GL.");
    return it->second;
}

GLenum getMagFilter(const BasicTexture::MagFilter& filter) {
    static std::map<BasicTexture::MagFilter, GLenum> filterMap = {
        { BasicTexture::MagFilter::Linear, GL_LINEAR }
    };

    auto it = filterMap.find(filter);
    if (it == filterMap.end())
        throw Exception("Unable to convert mag filter to GL.");
    return it->second;
}

GLenum getWrap(const BasicTexture::Wrap& wrap) {
    static std::map<BasicTexture::Wrap, GLenum> wrapMap = {
        { BasicTexture::Wrap::ClampToEdge, GL_CLAMP_TO_EDGE },
        { BasicTexture::Wrap::Repeat, GL_REPEAT }
    };

    auto it = wrapMap.find(wrap);
    if (it == wrapMap.end())
        throw Exception("Unable to convert texture wrap to GL.");
    return it->second;
}

}


// ------------------------------------------
void BasicTexture::activateSlot(unsigned int i) {
    glActiveTexture(GL_TEXTURE0 + i);
}


// ---------------------------------------
BasicTexture::BasicTexture(Type t) :
    mType(t),
    mMinFilter(MinFilter::Linear),
    mMagFilter(MagFilter::Linear),
    mSWrap(Wrap::Repeat),
    mTWrap(Wrap::Repeat),
    mName(0) {

    glGenTextures(1, &mName);
    if (!mName)
        throw Exception("Unable to create texture.");

    setMinFilter(MinFilter::Linear);
    setMagFilter(MagFilter::Linear);
    setSWrap(Wrap::Repeat);
    setTWrap(Wrap::Repeat);
}

BasicTexture::~BasicTexture() {
    glDeleteTextures(1, &mName);
}


// -------------------------------------
void BasicTexture::bind() const {
    glBindTexture(getTexInfo(mType).target, mName);
    if (!bound())
        throw Exception("Unable to bind texture.");
}

bool BasicTexture::bound() const {
    GLint name = 0;
    glGetIntegerv(getTexInfo(mType).binding, &name);
    return static_cast<GLuint>(name) == mName;
}

void BasicTexture::reserve(SizedInternalFormat internalFormat, const Vector2i& size,
                           Target2D target) {
    bind();
    glTexStorage2D(get2DTarget(target), 1, getInternalFormat(internalFormat),
                   size.x(), size.y());
}

void BasicTexture::setImage(BaseInternalFormat internalFormat, const Vector2i& size,
                            Format format, DataType dt, const void* data, Target2D target) {
    bind();
    glTexImage2D(get2DTarget(target), 0, getInternalFormat(internalFormat),
                 size.x(), size.y(), 0, getFormat(format), getDataType(dt), data);
}

void BasicTexture::setMinFilter(const MinFilter& filter) {
    bind();
    glTexParameteri(getTexInfo(mType).target, GL_TEXTURE_MIN_FILTER, getMinFilter(filter));
    mMinFilter = filter;
}

void BasicTexture::setMagFilter(const MagFilter& filter) {
    bind();
    glTexParameteri(getTexInfo(mType).target, GL_TEXTURE_MAG_FILTER, getMagFilter(filter));
    mMagFilter = filter;
}

void BasicTexture::setSWrap(const Wrap& wrap) {
    bind();
    glTexParameteri(getTexInfo(mType).target, GL_TEXTURE_WRAP_S, getWrap(wrap));
    mSWrap = wrap;
}

void BasicTexture::setTWrap(const Wrap& wrap) {
    bind();
    glTexParameteri(getTexInfo(mType).target, GL_TEXTURE_WRAP_T, getWrap(wrap));
    mTWrap = wrap;
}


// -----------------------------------------------------
const std::shared_ptr<Texture2D> textureFromImage(const RGBAImage& img) {
    std::shared_ptr<Texture2D> ret(new Texture2D);
    ret->setImage(BasicTexture::BaseInternalFormat::RGBA,
                  img.size(),
                  BasicTexture::Format::RGBA,
                  BasicTexture::DataType::UByte,
                  img.data()->data());
    return ret;
}


// -----------------------------------------------------
const Vector2i Texture<BasicTexture::Type::Tex2D>::size() const {
    bind();
    GLint width = 0, height = 0;

    glGetTexLevelParameteriv(getTexInfo(type()).target, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(getTexInfo(type()).target, 0, GL_TEXTURE_WIDTH, &height);

    return Vector2i(width, height);
}


}
}
