#ifndef WZY_RESOURCE_PACKAGE_HPP
#define WZY_RESOURCE_PACKAGE_HPP

#include <memory>
#include <string>
#include <vector>

#include <wzy/resource/item.hpp>
#include <wzy/resource/version.hpp>


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

    void addItem(const std::shared_ptr<Item>& item)
    { mItems.push_back(item); }
    void removeItem(const std::string& name);

    const std::vector<std::shared_ptr<Item> > items()
    { return mItems; }

private:
    std::string mName;
    Version mVersion;
    std::vector<std::shared_ptr<Item> > mItems;
};

}

#endif
