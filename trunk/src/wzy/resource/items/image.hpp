#ifndef WZY_RESOURCE_ITEMS_IMAGE_HPP
#define WZY_RESOURCE_ITEMS_IMAGE_HPP

#include <wzy/media/image.hpp>
#include <wzy/resource/item.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {

#define WZY_RESOURCE_ITEMS_IMAGE_DEFINE_ITEM(name, p, id) \
class name##ImageItem : public Item<name##ImageItem, id> { \
public: \
    name##ImageItem() : \
        Item(), \
        mImage(new Image<p>) { \
    } \
    \
    name##ImageItem(const std::string& name, const std::shared_ptr<Image<p> >& img) : \
        Item(name), \
        mImage(validate(img)) { \
    } \
    \
    const std::shared_ptr<Image<p> > image() \
    { return mImage; } \
    \
private: \
    std::shared_ptr<Image<p> > mImage; \
    \
    void doRead(std::istream& is) override \
    { mImage->load(is); } \
    \
    void doWrite(std::ostream& os) const override \
    { mImage->save(os); } \
};

WZY_RESOURCE_ITEMS_IMAGE_DEFINE_ITEM(RGBA, RGBAImagePixel, -10)

}

#endif
