#ifndef WZY_RENDER_TEXTURE_HPP
#define WZY_RENDER_TEXTURE_HPP

#include <wzy/utilities/noncopyable.hpp>


namespace wzy {
namespace render {

class BasicTexture : NonCopyable {
public:
    enum class Type {
        TwoD
    };

    enum Slot : unsigned int {
        First = 0,
        Second,
        Third
    };

    static void setSlot(Slot s);

    BasicTexture(Type t);
    virtual ~BasicTexture() = 0;

    unsigned int name() const
    { return mName; }

    Type type() const
    { return mType; }

    void bind() const;
    bool bound() const;

private:
    unsigned int mName;
    const Type mType;
};

}
}

#endif
