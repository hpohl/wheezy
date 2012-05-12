#ifndef WZY_RENDER_TEXTURE_HPP
#define WZY_RENDER_TEXTURE_HPP

#include <utility>

#include <wzy/utilities/noncopyable.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {
namespace render {

class BasicTexture : NonCopyable {
public:
    enum class Type {
        OneD,
        TwoD,
        ThreeD
    };

    template <Type ttype>
    friend class Texture;


    static void activateSlot(int s);

    BasicTexture(Type t);
    virtual ~BasicTexture() = 0;

    unsigned int name() const
    { return mName; }

    Type type() const
    { return mType; }

    void bind() const;
    bool bound() const;

    void setData(const Vector2i& size, int bpp, const unsigned char* data);

private:
    unsigned int mName;
    const Type mType;
};

template <BasicTexture::Type ttype>
class Texture : public BasicTexture {
public:
    template <class... Args>
    Texture(Args&&... args) :
        BasicTexture(ttype, std::forward<Args>(args)...) { }
};

typedef Texture<BasicTexture::Type::TwoD> Texture2D;


}
}

#endif
