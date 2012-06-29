#ifndef WZY_RESOURCE_ITEM_HPP
#define WZY_RESOURCE_ITEM_HPP

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <wzy/media/image.hpp>


namespace wzy {

class Item {
public:
    typedef std::function<const std::shared_ptr<Item>(const std::string&,
                                                           const std::string&)> Creator;

    static const std::shared_ptr<Item> create(int id,
                                              const std::string& name,
                                              const std::string& content);

    static bool registerCreator(int id, const Creator& creator)
    { creators().insert(std::make_pair(id, creator)); return true; }

    static void removeCreator(int id)
    { creators().erase(id); }


    Item(int id, const std::string& name) :
        mId(id),
        mName(name) {
    }

    virtual ~Item() = 0;


    int id() const
    { return mId; }

    const std::string name() const
    { return mName; }

    virtual const std::string content() const = 0;
    virtual std::size_t size() const = 0;

private:
    static std::map<int, Creator>& creators()
    { static std::map<int, Creator> m; return m; }

    int mId;
    std::string mName;
};


class UniversalItem : public Item {
public:
    template <class... Args>
    UniversalItem(const std::string& name, const std::string& content, Args&&... args) :
        Item(-1, name, std::forward<Args>(args)...),
        mContent(content) {
    }

    const std::string content() const override
    { return mContent; }

    std::size_t size() const override
    { return mContent.size(); }

    void setContent(const std::string& content)
    { mContent = content; }

private:
    static bool mReg;

    static const std::shared_ptr<Item> create(const std::string& name,
                                              const std::string& content)
    { return std::make_shared<UniversalItem>(name, content); }

    std::string mContent;
};


/*class ImageItem : public Item {
private:
    static const std::string genContent(const Image& image) {

    }

public:
    template <class... Args>
    ImageItem(const std::string& name, const std::string& content, Args&&... args) :
        Item(-2, name, std::forward<Args>(args)...),
        mImage(std::stringstream(content), Image::Format::PNG, content.size()),
        mContent(genContent(mImage)) {
    }

    const std::string content() const override
    { return mContent; }

    std::size_t size() const override
    { return mContent.size(); }

private:
    static bool mReg;

    static const std::shared_ptr<Item> create(const std::string& name,
                                              const std::string& content)
    { return std::make_shared<UniversalItem>(name, content); }

    Image mImage;
    std::string mContent;
};*/

}

#endif
