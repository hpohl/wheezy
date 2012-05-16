#include <wzy/scene/entity.hpp>

#include <wzy/scene/model.hpp>


namespace wzy {

Entity::Entity(const std::shared_ptr<Model>& model) :
    mModel(model) {
}


// ----------------------------------------------
void Entity::draw() const {
    mModel->renderData()->draw();
}

}
