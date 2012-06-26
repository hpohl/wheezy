#include <wzy/scene/entity.hpp>

#include <wzy/scene/material.hpp>
#include <wzy/scene/model.hpp>


namespace wzy {

AbstractEntity::AbstractEntity(const std::shared_ptr<Model>& model) :
    detail::BaseEntity(),
    AbstractSceneNode(),
    mModel(model),
    mMaterial(model->material()) {
}

AbstractEntity::~AbstractEntity() {
}


// -------------------------------------------------
void AbstractEntity::draw(const Matrix4f& projection, const Matrix4f& transform) {
    AbstractSceneNode::draw(projection, transform);

    mMaterial->use();
    mMaterial->program()->uniform("wzyModelViewMatrix", transformation() * transform);
    mMaterial->program()->uniform("wzyProjectionMatrix", projection);
    mModel->renderData()->draw();
}

}
