#ifndef WZY_RESOURCE_ITEM_HPP
#define WZY_RESOURCE_ITEM_HPP

#include <functional>
#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <vector>


namespace wzy {

class ResourceManager;

class BasicItem {
public:
    typedef std::function<const std::shared_ptr<BasicItem>()> Creator;

    class Depency {
    public:
        Depency(const std::string& package,
                const std::string& name) :
            mPackage(package),
            mName(name) { }

        explicit Depency(std::istream& is) :
            mPackage(),
            mName()
        { read(is); }

        const std::string package() const
        { return mPackage; }

        void setPackage(const std::string& package)
        { mPackage = package; }

        const std::string name() const
        { return mName; }

        void setName(const std::string& name)
        { mName = name; }

        void read(std::istream& is) {
            std::int32_t pkgNameLen = 0;
            is.read(reinterpret_cast<char*>(&pkgNameLen), sizeof(pkgNameLen));
            mPackage.resize(pkgNameLen);
            is.read(&mPackage[0], pkgNameLen);

            std::int32_t nameLen = 0;
            is.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
            mPackage.resize(nameLen);
            is.read(&mPackage[0], nameLen);
        }

        void write(std::ostream& os) const {
            std::int32_t pkgNameLen = mPackage.size();
            os.write(reinterpret_cast<const char*>(&pkgNameLen), sizeof(pkgNameLen));
            os.write(mPackage.data(), pkgNameLen);

            std::int32_t nameLen = mName.size();
            os.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
            os.write(mName.data(), nameLen);
        }

    private:
        std::string mPackage;
        std::string mName;
    };

    class DepencyGroup {
    public:
        explicit DepencyGroup(const std::string& name) :
            mName(name),
            mDepencies() { }

        explicit DepencyGroup(std::istream& is) :
            mName(),
            mDepencies()
        { read(is); }

        const std::string name() const
        { return mName; }

        void setName(const std::string& name)
        { mName = name; }

        const std::vector<Depency> getDepencies() const
        { return mDepencies; }

        void addDepency(const Depency& depency)
        { mDepencies.push_back(depency); }

        void read(std::istream& is) {
            std::int32_t nameLen = 0;
            is.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
            mName.resize(nameLen);
            is.read(&mName[0], nameLen);

            std::int32_t depSize = 0;
            is.read(reinterpret_cast<char*>(&depSize), sizeof(depSize));

            mDepencies.clear();
            for (int i = 0; i < depSize; ++i)
                mDepencies.push_back(Depency(is));
        }

        void write(std::ostream& os) const {
            std::int32_t nameLen = mName.size();
            os.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
            os.write(mName.data(), nameLen);

            std::int32_t depSize = mDepencies.size();
            os.write(reinterpret_cast<const char*>(&depSize), sizeof(depSize));

            for (auto dep : mDepencies)
                dep.write(os);
        }

    private:
        std::string mName;
        std::vector<Depency> mDepencies;
    };


    // --------------------------------------------------------------------
    static const std::shared_ptr<BasicItem> create(int id);

    static void registerCreator(int id, const Creator& creator)
    { creators().insert(std::make_pair(id, creator)); }

    static void removeCreator(int id)
    { creators().erase(id); }


    // ---------------------------------------------------------
    BasicItem(int id, const std::string& name = "") :
        mId(id),
        mName(name),
        mDepencyGroups() {
    }

    virtual ~BasicItem() = 0;


    int id() const
    { return mId; }

    const std::string name() const
    { return mName; }


    const std::vector<DepencyGroup> depencyGroups() const
    { return mDepencyGroups; }

    const DepencyGroup getDepencyGroup(const std::string& name) const;

    void addDepencyGroup(const DepencyGroup& group)
    { mDepencyGroups.push_back(group); }

    void addItemToDepencyGroup(const std::string& group,
                               const std::string& package,
                               const std::string& name);

    void write(std::ostream& os) const;
    void read(std::istream& is);

private:
    static std::map<int, Creator>& creators()
    { static std::map<int, Creator> m; return m; }

    int mId;
    std::string mName;
    std::vector<DepencyGroup> mDepencyGroups;

    virtual void doRead(std::istream& is) = 0;
    virtual void doWrite(std::ostream& os) const = 0;
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
    static const std::shared_ptr<BasicItem> create()
    { return std::make_shared<Derived>(); }

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
