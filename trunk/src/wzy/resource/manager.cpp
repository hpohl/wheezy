#include <wzy/resource/manager.hpp>

#include <wzy/utilities/exception.hpp>


namespace wzy {

void ResourceManager::addModel(const std::string& name, const std::shared_ptr<Model>& mdl) {
    auto it = mModels.insert(std::make_pair(name, mdl));
    if (!it.second)
        throw Exception("Model named " + name + " already existed in resource database.");
}

const std::shared_ptr<const Model> ResourceManager::getModel(const std::string& name) const {
    auto it = mModels.find(name);
    if (it == mModels.end())
        throw Exception("Model named " + name + " not in resource database.");
    return it->second;
}

}
