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

    explicit UniversalItem() :
        Item(),
        mContent() {
    }

    void setContent(const std::string& content)
    { mContent = content; }

    const std::string content() const
    { return mContent; }

private:
    std::string mContent;

    void doRead(std::istream& is) override {
        std::int32_t size = 0;
        is.read(reinterpret_cast<char*>(&size), sizeof(size));
        mContent.resize(size);
        is.read(&mContent[0], size);
    }

    void doWrite(std::ostream& os) const override {
        std::int32_t size = mContent.size();
        os.write(reinterpret_cast<const char*>(&size), sizeof(size));
        os.write(&mContent[0], size);
    }
};

}

#endif
