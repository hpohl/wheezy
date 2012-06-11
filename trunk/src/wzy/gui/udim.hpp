#ifndef WZY_GUI_UDIM_HPP
#define WZY_GUI_UDIM_HPP

#include <wzy/utilities/vec.hpp>

#include <wzy/render/framebuffer.hpp>


namespace wzy {
namespace gui {

class UDim {
public:
    UDim(const Vector2f& rel,
         const Vector2i& abs) :
        mRel(rel), mAbs(abs) { }

    const Vector2f rel() const
    { return mRel; }

    const Vector2i abs() const
    { return mAbs; }

    void setRel(const Vector2f& rel)
    { mRel = rel; }

    void setAbs(const Vector2i& abs)
    { mAbs = abs; }

    const Vector2i current() const
    { return render::FrameBuffer::currentSize() * mRel + mAbs; }

private:
    Vector2f mRel;
    Vector2i mAbs;
};

#define WZY_GUI_UDIM_OPERATOR(op) \
inline const UDim operator op(const UDim& lhs, const UDim& rhs) \
{ return UDim(lhs.rel() op rhs.rel(), lhs.abs() op rhs.abs()); }

WZY_GUI_UDIM_OPERATOR(+)
WZY_GUI_UDIM_OPERATOR(-)
WZY_GUI_UDIM_OPERATOR(*)
WZY_GUI_UDIM_OPERATOR(/)

}
}

#endif
