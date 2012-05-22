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

    Matrix4f m;
    perspective(m, 60, 1, 0.1, 100.0);

    mMaterial->use();
    mMaterial->program()->uniform("wzyModelViewMatrix", this->transformation());
    mMaterial->program()->uniform("wzyProjectionMatrix", m);
    mModel->renderData()->draw();
}

}
