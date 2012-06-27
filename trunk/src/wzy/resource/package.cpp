#include <wzy/resource/package.hpp>

#include <array>
#include <fstream>

#include <wzy/utilities/exception.hpp>


namespace wzy {

const std::shared_ptr<Package> Package::load(const std::string& name) {
    std::ifstream inf("packages/" + name + ".wzypkg");

    if (!inf.good())
        throw Exception("Unable to load package " + name + ".");

    std::array<char, 6> id;
    inf.read(id.data(), 6);

    if (!(std::string(id.data()) == "WZYPKG"))
        throw Exception("Package " + name + " is not a valid package.");

    size_t nameLen = 0;
    inf >> nameLen;

    std::string pkgname(nameLen, ' ');
    inf.read(&pkgname[0], nameLen);

    if (pkgname != name)
        throw Exception("Package loading name " + name + " doesn't match to package's name " + pkgname + ".");

    Version vers(1, 0, 0);
    inf.read(reinterpret_cast<char*>(&vers), sizeof(Version));

    auto pkg = std::make_shared<Package>(name, vers);

    return pkg;
}

void Package::write(const std::shared_ptr<const Package>& pkg) {
    std::ofstream ouf("packages/" + pkg->name() + ".wzypkg", std::ofstream::out | std::ofstream::trunc);

    if (!ouf.good())
        throw Exception("Unable to write package " + pkg->name() + ".");

    ouf << "WZYPKG" << pkg->name().length() << pkg->name();

    auto vers = pkg->version();
    ouf.write(reinterpret_cast<char*>(&vers), sizeof(Version));
}


// -------------------------------------------------------
Package::Item::~Item() {
}


// ---------------------------------------------
Package::Package(const std::string& name, const Version& version) :
    mName(name),
    mVersion(version) {
}

Package::~Package() {
}

}
