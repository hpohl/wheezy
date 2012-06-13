#ifndef WZY_RENDER_TEXTURE_HPP
#define WZY_RENDER_TEXTURE_HPP

#include <utility>

#include <wzy/media/image.hpp>
#include <wzy/utilities/noncopyable.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {
namespace render {

class BasicTexture : public NonCopyable {
public:
    enum class Type {
        Tex1D,
        Tex2D,
        Tex3D,
        Array1D,
        Array2D,
        Array3D,
        Rectangle,
        CubeMap,
        Multisample,
        MutlisampleArray
    };

    enum class BaseInternalFormat {
        R,
        RG,
        RGB,
        RGBA
    };

    enum class SizedInternalFormat {
        RGBA8
    };

    enum class Format {
        R,
        RG,
        RGB,
        BGR,
        RGBA,
        BGRA
    };

    enum class DataType {
        Byte,
        UByte
    };

    enum class Target2D {
        Tex2D
    };

    enum class MinFilter {
        Nearest,
        Linear,
        LinearMipmapLinear
    };

    enum class MagFilter {
        Nearest,
        Linear
    };

    enum class Wrap {
        ClampToEdge,
        ClampToBorder,
        MirroredRepeat,
        Repeat
    };


    static void activateSlot(unsigned int i);

    BasicTexture(Type t);
    virtual ~BasicTexture() = 0;

    Type type() const
    { return mType; }

    unsigned int name() const
    { return mName; }

    void bind() const;
    bool bound() const;

    void reserve(SizedInternalFormat internalFormat, const Vector2i& size, Target2D target = Target2D::Tex2D);

    void setImage(BaseInternalFormat internalFormat, const Vector2i& size,
                  Format format, DataType dt, const void* data, Target2D target = Target2D::Tex2D);

    void setMinFilter(const MinFilter& filter);
    void setMagFilter(const MagFilter& filter);

    void setSWrap(const Wrap& wrap);
    void setTWrap(const Wrap& wrap);

    const MinFilter minFilter() const
    { return mMinFilter; }

    const MagFilter magFilter() const
    { return mMagFilter; }

    const Wrap sWrap() const
    { return mSWrap; }

    const Wrap tWrap() const
    { return mTWrap; }

private:
    const Type mType;
    MinFilter mMinFilter;
    MagFilter mMagFilter;
    Wrap mSWrap;
    Wrap mTWrap;
    unsigned int mName;
};


// --------------------------------------------------
template <BasicTexture::Type ttype>
class Texture : public BasicTexture {
public:
    template <class... Args>
    Texture(Args&&... args) :
        BasicTexture(ttype, std::forward<Args>(args)...) { }
};

typedef Texture<BasicTexture::Type::Tex2D> Texture2D;


// ---------------------------------------------------
const std::shared_ptr<Texture2D> textureFromImage(const Image& img);

}
}


#endif
