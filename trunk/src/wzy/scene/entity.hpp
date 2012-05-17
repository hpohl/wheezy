#ifndef WZY_SCENE_ENTITY_HPP
#define WZY_SCENE_ENTITY_HPP

#include <memory>
#include <type_traits>

#include <wzy/scene/movable.hpp>


namespace wzy {

class Model;

namespace detail {

class BaseEntity { };

}

template <class T>
struct IsEntity : public std::is_base_of<detail::BaseEntity, T> { };


class AbstractEntity : public detail::BaseEntity, public Movable {
public:
    AbstractEntity(const std::shared_ptr<Model>& model);
    virtual ~AbstractEntity() = 0;

private:
    std::shared_ptr<Model> mModel;
};

class Entity : public AbstractEntity {
public:
    template <class... Args>
    Entity(Args&&... args) :
        AbstractEntity(std::forward<Args>(args)...) { }
};

}

#endif
