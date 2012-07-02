#ifndef WZY_RESOURCE_ITEMS_UNIVERSAL_HPP
#define WZY_RESOURCE_ITEMS_UNIVERSAL_HPP

#include <wzy/resource/item.hpp>


namespace wzy {

class UniversalItem : public Item<UniversalItem, -1> {
public:
    UniversalItem(const std::string& name, const std::string& content) :
        Item(name),
        mContent(content) {
    }

    const std::string content() const override
    { return mContent; }

    void setContent(const std::string& content)
    { mContent = content; }

private:
    std::string mContent;
};

}

#endif
