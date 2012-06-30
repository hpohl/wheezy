#ifndef WZY_RESOURCE_ITEM_HPP
#define WZY_RESOURCE_ITEM_HPP

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>


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

private:
    static std::map<int, Creator>& creators()
    { static std::map<int, Creator> m; return m; }

    int mId;
    std::string mName;
};


template <class T>
struct IsItem : public std::is_base_of<Item, T> { };


class UniversalItem : public Item {
public:
    constexpr static int constId = -1;

    template <class... Args>
    UniversalItem(const std::string& name, const std::string& content, Args&&... args) :
        Item(constId, name, std::forward<Args>(args)...),
        mContent(content) {
    }

    const std::string content() const override
    { return mContent; }

    void setContent(const std::string& content)
    { mContent = content; }

private:
    static bool mReg;

    static const std::shared_ptr<Item> create(const std::string& name,
                                              const std::string& content)
    { return std::make_shared<UniversalItem>(name, content); }

    std::string mContent;
};

}

#endif
