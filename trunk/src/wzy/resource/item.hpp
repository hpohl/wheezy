#ifndef WZY_RESOURCE_ITEM_HPP
#define WZY_RESOURCE_ITEM_HPP

#include <functional>
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

    static void registerCreator(int id, const Creator& creator)
    { creators().insert(std::make_pair(id, creator)); }

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

private:
    static std::map<int, Creator>& creators()
    { static std::map<int, Creator> m; return m; }

    int mId;
    std::string mName;
};

template <class T>
struct IsItem : public std::is_base_of<BasicItem, T> { };

namespace detail {
template <class T, T> struct Val { };
}

template <class Derived, int tid>
class Item : public BasicItem {
public:
    constexpr static int constId = tid;

    template <class... Args>
    Item(Args&&... args) :
        BasicItem(tid, std::forward<Args>(args)...) { }

    virtual ~Item() = 0;

private:
    static const std::shared_ptr<BasicItem> create(const std::string& name,
                                                   const std::string& content)
    { return std::make_shared<Derived>(name, content); }

    struct Initialiser {
        Initialiser()
        { registerCreator(tid, Item<Derived, tid>::create); }

        ~Initialiser()
        { removeCreator(tid); }
    };

    static Initialiser mInitialiser;

    typedef detail::Val<Initialiser&, mInitialiser> User;
};

template <class Derived, int tid>
typename Item<Derived, tid>::Initialiser Item<Derived, tid>::mInitialiser;

template <class Derived, int tid>
Item<Derived, tid>::~Item() { }

}

#endif
