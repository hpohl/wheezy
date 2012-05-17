#include <wzy/scene/entity.hpp>

#include <wzy/scene/model.hpp>


namespace wzy {

AbstractEntity::AbstractEntity(const std::shared_ptr<Model>& model) :
    mModel(model) {
}

AbstractEntity::~AbstractEntity() {
}

}
