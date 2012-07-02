#ifndef WZY_SCENE_ENTITY_HPP
#define WZY_SCENE_ENTITY_HPP

#include <memory>
#include <type_traits>

#include <wzy/render/material.hpp>
#include <wzy/scene/node.hpp>


namespace wzy {

class Model;

namespace detail {
class BaseEntity { };
}

template <class T>
struct IsEntity : public std::is_base_of<detail::BaseEntity, T> { };


class AbstractEntity : public detail::BaseEntity, public AbstractSceneNode {
public:
    AbstractEntity(const std::shared_ptr<Model>& model);
    virtual ~AbstractEntity() = 0;

    const std::shared_ptr<const Model> model() const
    { return mModel; }

    void setModel(const std::shared_ptr<Model>& mdl)
    { mModel = validate(mdl); }

    const std::shared_ptr<render::Material> material()
    { return mMaterial; }

    void setMaterial(const std::shared_ptr<render::Material>& mat)
    { mMaterial = mat; }

    void draw(const Matrix4f& projection, const Matrix4f& transform) override;

private:
    std::shared_ptr<Model> mModel;
    std::shared_ptr<render::Material> mMaterial;
};

class Entity final : public AbstractEntity {
public:
    template <class... Args>
    Entity(Args&&... args) :
        AbstractEntity(std::forward<Args>(args)...) { }
};

}

#endif
