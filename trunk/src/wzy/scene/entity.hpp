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


class Entity : public detail::BaseEntity, public Movable {
public:
    Entity(const std::shared_ptr<Model>& model);

    void draw() const;

private:
    std::shared_ptr<Model> mModel;
};

}

#endif
