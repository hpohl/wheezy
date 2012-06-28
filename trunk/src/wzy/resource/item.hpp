#ifndef WZY_RESOURCE_ITEM_HPP
#define WZY_RESOURCE_ITEM_HPP

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>


namespace wzy {

class BasicItem {
public:
    typedef std::function<const std::shared_ptr<BasicItem>(const std::string&,
                                                           const std::string&)> Creator;

    static const std::shared_ptr<BasicItem> create(int id,
                                                   const std::string& name,
                                                   const std::string& content);

    static bool registerCreator(int id, const Creator& creator)
    { creators().insert(std::make_pair(id, creator)); return true; }

    static void removeCreator(int id)
    { creators().erase(id); }


    BasicItem(int id, const std::string& name) :
        mId(id),
        mName(name) {
    }

    virtual ~BasicItem() = 0;


    int id() const
    { return mId; }

    const std::string name() const
    { return mName; }

    virtual const std::string content() const = 0;
    virtual size_t size() const = 0;

private:
    static std::map<int, Creator>& creators()
    { static std::map<int, Creator> m; return m; }

    int mId;
    std::string mName;
};


template <class Derived, int tid>
class Item : public BasicItem {
public:
    static const std::shared_ptr<BasicItem> create(const std::string& name,
                                                   const std::string& content)
    { return std::make_shared<Derived>(name, content); }

    template <class... Args>
    Item(Args&&... args) :
        BasicItem(tid, std::forward<Args>(args)...) {
    }

    static constexpr int constId = tid;
};


class UniversalItem : public Item<UniversalItem, -1> {
public:
    template <class... Args>
    UniversalItem(const std::string& name, const std::string& content, Args&&... args) :
        Item(name, std::forward<Args>(args)...),
        mContent(content) {
    }

    const std::string content() const override
    { return mContent; }

    size_t size() const override
    { return mContent.size(); }

    void setContent(const std::string& content)
    { mContent = content; }

private:
    std::string mContent;
};

static const bool mReg = BasicItem::registerCreator(-1, UniversalItem::create);

}

#endif
