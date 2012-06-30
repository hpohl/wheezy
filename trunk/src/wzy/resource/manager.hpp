#ifndef WZY_RESOURCE_MANAGER_HPP
#define WZY_RESOURCE_MANAGER_HPP

#include <set>

#include <wzy/resource/package.hpp>
#include <wzy/utilities/singleton.hpp>


namespace wzy {

class ResourceManager : public Singleton<ResourceManager> {
public:
    ResourceManager();

    const std::shared_ptr<Package> getPackage(const std::string& package);
    const std::shared_ptr<Item> getItem(const std::string& package, const std::string& name);

    template <class ItemT>
    const std::shared_ptr<ItemT> getItem(const std::string& package, const std::string& name)
    { return getPackage(package)->getItem<ItemT>(name); }

private:
    std::set<std::shared_ptr<Package> > mPackages;
};

}

#endif
