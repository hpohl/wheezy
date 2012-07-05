#ifndef WZY_RESOURCE_ITEMS_MATERIAL_HPP
#define WZY_RESOURCE_ITEMS_MATERIAL_HPP

#include <wzy/render/material.hpp>
#include <wzy/resource/item.hpp>


namespace wzy {

class MaterialItem : public Item<MaterialItem, -20> {
public:
    MaterialItem();

    const std::shared_ptr<render::Material> material()
    { return mMaterial; }

private:
    std::shared_ptr<render::Material> mMaterial;

    void doRead(std::istream& is) override;
    void doWrite(std::ostream& os) const override;
};

}

#endif
