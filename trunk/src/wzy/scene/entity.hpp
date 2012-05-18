#ifndef WZY_SCENE_ENTITY_HPP
#define WZY_SCENE_ENTITY_HPP

#include <memory>
#include <type_traits>

#include <wzy/scene/node.hpp>


namespace wzy {

class Material;
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

    void draw(const Matrix4f& transform) override;

private:
    std::shared_ptr<Model> mModel;
    std::shared_ptr<Material> mMaterial;
};

class Entity final : public AbstractEntity {
public:
    template <class... Args>
    Entity(Args&&... args) :
        AbstractEntity(std::forward<Args>(args)...) { }
};

}

#endif