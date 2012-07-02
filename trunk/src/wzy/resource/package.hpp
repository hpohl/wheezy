#ifndef WZY_RESOURCE_PACKAGE_HPP
#define WZY_RESOURCE_PACKAGE_HPP

#include <memory>
#include <set>
#include <string>

#include <wzy/resource/item.hpp>
#include <wzy/resource/version.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {

class Package {
public:
    static const std::shared_ptr<Package> load(const std::string& name);
    static void write(const std::shared_ptr<const Package>& pkg);

    Package(const std::string& name, const Version& version);
    ~Package();

    const std::string name() const
    { return mName; }

    const Version version() const
    { return mVersion; }

    void addItem(const std::shared_ptr<BasicItem>& item);
    void removeItem(const std::string& name);

    bool hasItem(const std::string& name);
    const std::shared_ptr<BasicItem> getItem(const std::string& name);

    template <class ItemT>
    const std::shared_ptr<ItemT> getItem(const std::string& name) {
        static_assert(IsItem<ItemT>::value, "Trying to get non-item.");
        auto itm = getItem(name);

        if (itm->id() != ItemT::constId)
            throw Exception("Item " + name + " has incorrect id.");
        return std::static_pointer_cast<ItemT>(itm);
    }

    const std::set<std::shared_ptr<BasicItem> > items()
    { return mItems; }

private:
    std::string mName;
    Version mVersion;
    std::set<std::shared_ptr<BasicItem> > mItems;
};

}

#endif
