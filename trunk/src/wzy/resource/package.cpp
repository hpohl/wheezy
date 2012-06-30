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
    std::size_t nameLen = 0;
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
    std::size_t numItems = 0;
    inf.read(reinterpret_cast<char*>(&numItems), sizeof(numItems));

    // Read item locations
    std::vector<std::size_t> begins(numItems);
    inf.read(reinterpret_cast<char*>(&begins[0]), numItems * sizeof(std::size_t));

    // Create package
    auto pkg = std::make_shared<Package>(name, vers);

    // Read items
    for (auto begin : begins) {

        // Seek to location
        inf.seekg(begin);

        // Read item ID
        int id = 0;
        inf.read(reinterpret_cast<char*>(&id), sizeof(id));

        // Read item name length & name
        std::size_t itmNameLen = 0;
        inf.read(reinterpret_cast<char*>(&itmNameLen), sizeof(itmNameLen));

        std::string itmName(itmNameLen, 0);
        inf.read(&itmName[0], itmNameLen);

        // Read item size
        std::size_t size = 0;
        inf.read(reinterpret_cast<char*>(&size), sizeof(size));

        // Read item content
        std::string data(size, 0);
        inf.read(&data[0], size);

        // Add item to package
        pkg->addItem(Item::create(id, itmName, data));
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
    std::size_t len = pkg->name().length();
    ouf.write(reinterpret_cast<char*>(&len), sizeof(len));
    ouf << pkg->name();

    // Write package version
    auto vers = pkg->version();
    ouf.write(reinterpret_cast<char*>(&vers), sizeof(Version));

    // Write item count
    std::size_t count = pkg->mItems.size();
    ouf.write(reinterpret_cast<char*>(&count), sizeof(count));

    // Write item locations
    auto items = pkg->mItems;
    std::size_t begin = ouf.tellp() + static_cast<decltype(ouf.tellp())>(items.size() * sizeof(begin));

    for (auto itm : items) {
        ouf.write(reinterpret_cast<char*>(&begin), sizeof(begin));
        begin += sizeof(int) + sizeof(std::size_t) + itm->name().length() + sizeof(std::size_t) + itm->size();
    }


    // Write packages
    for (auto itm : items) {
        // Write item id
        int id = itm->id();
        ouf.write(reinterpret_cast<char*>(&id), sizeof(id));

        // Write item name length & name
        std::size_t nameLen = itm->name().length();
        ouf.write(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        ouf << itm->name();

        // Write item size
        std::size_t size = itm->size();
        ouf.write(reinterpret_cast<char*>(&size), sizeof(size));

        // Write item content
        ouf << itm->content();
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
void Package::addItem(const std::shared_ptr<Item>& item) {
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
    auto pred = [&](const std::shared_ptr<Item>& itm) -> bool { return itm->name() == name; };
    auto it = std::find_if(mItems.begin(), mItems.end(), pred);
    return it != mItems.end();
}

const std::shared_ptr<Item> Package::getItem(const std::string& name) {
    auto pred = [&](const std::shared_ptr<Item>& itm) -> bool { return itm->name() == name; };
    auto it = std::find_if(mItems.begin(), mItems.end(), pred);
    if (it == mItems.end())
        throw Exception("Unable to find item " + name + " in package " + mName + ".");
    return *it;
}

}
