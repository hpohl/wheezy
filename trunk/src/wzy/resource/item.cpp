#include <wzy/resource/item.hpp>

#include <wzy/utilities/general.hpp>


namespace wzy {


const std::shared_ptr<Item> Item::create(int id,
                                         const std::string& name,
                                         const std::string& content) {
    auto it = creators().find(id);

    if (it == creators().end())
        throw Exception("Unable to create item from id " + toString(id) + ".");

    return it->second(name, content);
}


// ----------------------------------------------
Item::~Item() {
}


// ---------------------------------------------
bool UniversalItem::mReg = Item::registerCreator(constId, create);


// ----------------------------------------------------------
bool ImageItem::mReg = Item::registerCreator(constId, create);


}
