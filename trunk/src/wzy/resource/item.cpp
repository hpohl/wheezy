#include <wzy/resource/item.hpp>

#include <algorithm>

#include <wzy/resource/manager.hpp>
#include <wzy/utilities/general.hpp>


namespace wzy {


const std::shared_ptr<BasicItem> BasicItem::create(int id) {
    auto it = creators().find(id);

    if (it == creators().end())
        throw Exception("Unable to create item from id " + toString(id) + ".");

    return it->second();
}


// ----------------------------------------------
BasicItem::~BasicItem() {
}


// --------------------------------------
void BasicItem::write(std::ostream& os) const {
    std::int32_t nameLen = mName.size();
    os.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    os.write(mName.data(), nameLen);

    std::int32_t depSize = mDepencyGroups.size();
    os.write(reinterpret_cast<const char*>(&depSize), sizeof(depSize));

    for (auto depGroup : mDepencyGroups)
        depGroup.write(os);

    doWrite(os);
}

void BasicItem::read(std::istream& is) {
    std::int32_t nameLen = 0;
    is.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    mName.resize(nameLen);
    is.read(&mName[0], nameLen);

    std::int32_t depSize = 0;
    is.read(reinterpret_cast<char*>(&depSize), sizeof(depSize));

    mDepencyGroups.clear();
    for (int i = 0; i < depSize; ++i)
        mDepencyGroups.push_back(DepencyGroup(is));

    doRead(is);
}

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
