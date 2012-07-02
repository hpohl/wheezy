#ifndef WZY_RESOURCE_ITEMS_IMAGE_HPP
#define WZY_RESOURCE_ITEMS_IMAGE_HPP

#include <wzy/media/image.hpp>
#include <wzy/resource/item.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {

#define WZY_RESOURCE_ITEMS_IMAGE_DEFINE_ITEM(name, p, id) \
class name##ImageItem : public Item<name##ImageItem, id> { \
public: \
    name##ImageItem(const std::string& name, const std::string& content) : \
        Item(name), \
        mImage(new Image<p>(content)) { \
    } \
    \
    name##ImageItem(const std::string& name, const std::shared_ptr<Image<p> >& img) : \
        Item(name), \
        mImage(validate(img)) { \
    } \
    \
    const std::string content() const override \
    { return mImage->saveToString(); } \
    \
private: \
    std::shared_ptr<Image<p> > mImage; \
};

WZY_RESOURCE_ITEMS_IMAGE_DEFINE_ITEM(RGBA, RGBAImagePixel, -10)

}

#endif
