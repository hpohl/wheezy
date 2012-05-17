#ifndef WZY_RESOURCE_MANAGER_HPP
#define WZY_RESOURCE_MANAGER_HPP

#include <map>
#include <memory>
#include <string>

#include <wzy/utilities/singleton.hpp>


namespace wzy {

class Model;

class ResourceManager : public Singleton<ResourceManager> {
public:

    void addModel(const std::string& name, const std::shared_ptr<Model>& mdl);

    bool containsModel(const std::string& name) const
    { return mModels.find(name) != mModels.end(); }

    const std::shared_ptr<const Model> getModel(const std::string& name) const;

    const std::shared_ptr<Model> getModel(const std::string& name)
    { return std::const_pointer_cast<Model>(static_cast<const ResourceManager*>(this)->getModel(name)); }

private:
    std::map<std::string, std::shared_ptr<Model> > mModels;
};

}

#endif
