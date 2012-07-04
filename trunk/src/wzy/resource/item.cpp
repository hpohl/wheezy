#include <wzy/resource/item.hpp>

#include <algorithm>

#include <wzy/resource/manager.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {


const std::shared_ptr<BasicItem> BasicItem::create(int id,
                                                   const std::string& name,
                                                   const std::string& content) {
    auto it = creators().find(id);

    if (it == creators().end())
        throw Exception("Unable to create item from id " + toString(id) + ".");

    return it->second(name, content);
}


// ----------------------------------------------
BasicItem::~BasicItem() {
}


// --------------------------------------
/*void BasicItem::write(std::ostream& os) const {
    std::int32_t nDepencies = mDepencies.size();
    os.write(reinterpret_cast<const char*>(&nDepencies), sizeof(nDepencies));

    for (auto dep : mDepencies) {
        std::int32_t sizePkgName = dep.first.size();
        os.write(reinterpret_cast<const char*>(&sizePkgName), sizeof(sizePkgName));
        os.write(dep.first.data(), sizePkgName);

        std::int32_t sizeItmName = dep.second.size();
        os.write(reinterpret_cast<const char*>(&sizeItmName), sizeof(sizeItmName));
        os.write(dep.second.data(), sizeItmName);
    }

    auto con = content();
    std::int32_t conLen = content.size();

    os.write(reinterpret_cast<const char*>(&conLen), sizeof(conLen));
    os.write(con.data(), conLen);
}

void BasicItem::read(ResourceManager& rm, std::istream& is) {
    std::int32_t nDepencies = 0;
    is.read(reinterpret_cast<char*>(&nDepencies), sizeof(nDepencies));

    for (int i = 0; i < nDepencies; ++i) {
        std::int32_t sizePkgName = 0;
        is.read(reinterpret_cast<char*>(&sizePkgName), sizeof(sizePkgName));
        std::string pkgName(sizePkgName, 0);
        is.read(reinterpret_cast<char*>(&pkgName[0]), sizePkgName);

        std::int32_t sizeItmName = 0;
        is.read(reinterpret_cast<char*>(&sizeItmName), sizeof(sizeItmName));
        std::string itmName(sizeItmName, 0);
        is.read(reinterpret_cast<char*>(&itmName[0]), sizeItmName);

        rm.getItem()
    }
}*/

const BasicItem::DepencyGroup BasicItem::getDepencyGroup(const std::string& name) const {
    auto pred = [&](const DepencyGroup& group) -> bool { return group.name() == name; };
    auto it = std::find_if(mDepencyGroups.begin(), mDepencyGroups.end(), pred);
    if (it == mDepencyGroups.end())
        throw Exception("Unable to find depency group " + name + " in item " + mName);
    return *it;
}

void BasicItem::addItemToDepencyGroup(const std::string& group,
                                      const std::string& package,
                                      const std::string& name) {
    auto pred = [&](const DepencyGroup& g) -> bool { return g.name() == group; };
    auto it = std::find_if(mDepencyGroups.begin(), mDepencyGroups.end(), pred);
    if (it == mDepencyGroups.end())
        throw Exception("Unable to find depency group " + name + " in item " + mName);
    it->addDepency(Depency(package, name));
}


}
