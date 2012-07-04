#ifndef WZY_RESOURCE_ITEM_HPP
#define WZY_RESOURCE_ITEM_HPP

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>


namespace wzy {

class ResourceManager;

class BasicItem {
public:
    typedef std::function<const std::shared_ptr<BasicItem>(const std::string&,
                                                           const std::string&)> Creator;

    class Depency {
    public:
        Depency(const std::string& package,
                const std::string& name) :
            mPackage(package),
            mName(name) { }

        const std::string package() const
        { return mPackage; }

        void setPackage(const std::string& package)
        { mPackage = package; }

        const std::string name() const
        { return mName; }

        void setName(const std::string& name)
        { mName = name; }

    private:
        std::string mPackage;
        std::string mName;
    };

    class DepencyGroup {
    public:
        DepencyGroup(const std::string& name) :
            mName(name),
            mDepencies() { }

        const std::string name() const
        { return mName; }

        void setName(const std::string& name)
        { mName = name; }

        const std::vector<Depency> getDepencies() const
        { return mDepencies; }

        void addDepency(const Depency& depency)
        { mDepencies.push_back(depency); }

    private:
        std::string mName;
        std::vector<Depency> mDepencies;
    };


    static const std::shared_ptr<BasicItem> create(int id,
                                                   const std::string& name,
                                                   const std::string& content);

    static void registerCreator(int id, const Creator& creator)
    { creators().insert(std::make_pair(id, creator)); }

    static void removeCreator(int id)
    { creators().erase(id); }


    BasicItem(int id, const std::string& name) :
        mId(id),
        mName(name),
        mDepencyGroups() {
    }

    virtual ~BasicItem() = 0;


    int id() const
    { return mId; }

    const std::string name() const
    { return mName; }


    virtual const std::string content() const = 0;


    const std::vector<DepencyGroup> depencyGroups() const
    { return mDepencyGroups; }

    const DepencyGroup getDepencyGroup(const std::string& name) const;

    void addDepencyGroup(const DepencyGroup& group)
    { mDepencyGroups.push_back(group); }

    void addItemToDepencyGroup(const std::string& group,
                               const std::string& package,
                               const std::string& name);

    ///virtual void read(const std::string& data) = 0;

    //void write(std::ostream& os) const;
    //void read(const ResourceManager& rm, std::istream& is);

private:
    static std::map<int, Creator>& creators()
    { static std::map<int, Creator> m; return m; }

    int mId;
    std::string mName;
    std::vector<DepencyGroup> mDepencyGroups;
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
