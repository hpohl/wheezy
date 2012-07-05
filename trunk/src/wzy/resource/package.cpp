#include <wzy/resource/package.hpp>

#include <algorithm>
#include <array>
#include <fstream>

#include <wzy/utilities/exception.hpp>


namespace wzy {

const std::shared_ptr<Package> Package::load(const std::string& name) {
    // Open file
    std::ifstream inf("packages/" + name + ".wzypkg");

    if (!inf.good())
        throw Exception("Unable to load package " + name + ".");

    // Read ID
    std::string id(6, 0);
    inf.read(&id[0], 6);

    if (!(std::string(id.data()) == "WZYPKG"))
        throw Exception("Package " + name + " is not a valid package.");

    // Read name length & name
    std::int32_t nameLen = 0;
    inf.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));

    std::string pkgname(nameLen, 0);
    inf.read(&pkgname[0], nameLen);

    auto pos = name.find_last_of('/');
    if (pos == std::string::npos)
        pos = 0;

    std::string str(name.begin() + pos, name.end());

    if (pkgname != str)
        throw Exception("Package loading name " + str + " doesn't match to package's name " + pkgname + ".");


    // Read version
    Version vers(1, 0, 0);
    inf.read(reinterpret_cast<char*>(&vers), sizeof(Version));

    // Read the number of items
    std::int32_t numItems = 0;
    inf.read(reinterpret_cast<char*>(&numItems), sizeof(numItems));

    // Create package
    auto pkg = std::make_shared<Package>(name, vers);

    // Read items
    for (int i = 0; i < numItems; ++i) {
        // Read item ID
        int id = 0;
        inf.read(reinterpret_cast<char*>(&id), sizeof(id));

        // Add item to package
        auto itm = BasicItem::create(id);
        itm->read(inf);
        pkg->addItem(itm);
    }

    return pkg;
}

void Package::write(const std::shared_ptr<const Package>& pkg) {
    // Open the file
    std::ofstream ouf("packages/" + pkg->name() + ".wzypkg", std::ofstream::out | std::ofstream::trunc);

    if (!ouf.good())
        throw Exception("Unable to write package " + pkg->name() + ".");

    // Write WZYPKG identifier
    ouf << "WZYPKG";

    // Write package name length and name
    std::int32_t len = pkg->name().length();
    ouf.write(reinterpret_cast<char*>(&len), sizeof(len));
    ouf << pkg->name();

    // Write package version
    auto vers = pkg->version();
    ouf.write(reinterpret_cast<char*>(&vers), sizeof(Version));

    // Write item count
    std::int32_t count = pkg->mItems.size();
    ouf.write(reinterpret_cast<char*>(&count), sizeof(count));

    // Write packages
    for (const std::shared_ptr<BasicItem>& itm : pkg->mItems) {
        // Write item id
        int id = itm->id();
        ouf.write(reinterpret_cast<char*>(&id), sizeof(id));

        // Write item
        itm->write(ouf);
    }
}


// ---------------------------------------------
Package::Package(const std::string& name, const Version& version) :
    mName(name),
    mVersion(version) {
}

Package::~Package() {
}


// ---------------------------------------------
void Package::addItem(const std::shared_ptr<BasicItem>& item) {
    if (hasItem(item->name()))
        throw Exception("An item named " + item->name() + " already exists in package " + mName + ".");
    auto res = mItems.insert(item);
    if (!res.second)
        throw Exception("Failed to add item " + item->name() + " to package " + " mName " + ".");
}

void Package::removeItem(const std::string& name) {
    mItems.erase(getItem(name));
}

bool Package::hasItem(const std::string& name) {
    auto pred = [&](const std::shared_ptr<BasicItem>& itm) -> bool { return itm->name() == name; };
    auto it = std::find_if(mItems.begin(), mItems.end(), pred);
    return it != mItems.end();
}

const std::shared_ptr<BasicItem> Package::getItem(const std::string& name) {
    auto pred = [&](const std::shared_ptr<BasicItem>& itm) -> bool { return itm->name() == name; };
    auto it = std::find_if(mItems.begin(), mItems.end(), pred);
    if (it == mItems.end())
        throw Exception("Unable to find item " + name + " in package " + mName + ".");
    return *it;
}

}
