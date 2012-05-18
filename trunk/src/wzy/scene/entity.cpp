#include <wzy/scene/entity.hpp>

#include <wzy/scene/material.hpp>
#include <wzy/scene/model.hpp>


namespace wzy {

AbstractEntity::AbstractEntity(const std::shared_ptr<Model>& model) :
    detail::BaseEntity(),
    AbstractSceneNode(),
    mModel(model),
    mMaterial(new Material) {
}

AbstractEntity::~AbstractEntity() {
}


// -------------------------------------------------
void AbstractEntity::draw(const Matrix4f& transform) {

    AbstractSceneNode::draw(transform);
    mMaterial->use();
    mMaterial->program()->uniform(this->transform(), "wzyModelViewMatrix");
    mModel->renderData()->draw();
}

}
