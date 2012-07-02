#include <wzy/resource/manager.hpp>

#include <algorithm>

#include <wzy/utilities/exception.hpp>


namespace wzy {

ResourceManager::ResourceManager() :
    mPackages() {
}


// ------------------------------------------
const std::shared_ptr<Package> ResourceManager::getPackage(const std::string& package) {
    auto pred = [&](const std::shared_ptr<Package>& pkg) -> bool { return pkg->name() == package; };
    auto it = std::find_if(mPackages.begin(), mPackages.end(), pred);

    if (it == mPackages.end()) {
        auto pkg = Package::load(package);
        mPackages.insert(pkg);
        return pkg;
    }

    return *it;
}

const std::shared_ptr<BasicItem> ResourceManager::getItem(const std::string& package,
                                                     const std::string& name) {
    auto pkg = getPackage(package);
    return pkg->getItem(name);
}

}
