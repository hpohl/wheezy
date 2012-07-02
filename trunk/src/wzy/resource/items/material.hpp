#ifndef WZY_RESOURCE_ITEMS_MATERIAL_HPP
#define WZY_RESOURCE_ITEMS_MATERIAL_HPP

#include <wzy/render/material.hpp>
#include <wzy/resource/item.hpp>


namespace wzy {

class MaterialItem : public Item<MaterialItem, -20> {
public:
    MaterialItem(const std::string& name, const std::string& content);
    MaterialItem(const std::string& name, const std::shared_ptr<render::Material>& material);

    const std::string content() const override;

    const std::shared_ptr<render::Material> material()
    { return mMaterial; }

private:
    std::shared_ptr<render::Material> mMaterial;
};

}

#endif
