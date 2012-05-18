#include <wzy/scene/node.hpp>

#include <wzy/utilities/exception.hpp>


namespace wzy {

AbstractSceneNode::~AbstractSceneNode() {
}


// -------------------------------------------
void AbstractSceneNode::attach(const std::shared_ptr<AbstractSceneNode>& node) {
    if (!mChildren.insert(node).second)
        throw Exception("SceneNode already exists, cannot attach.");
}

void AbstractSceneNode::detach(const std::shared_ptr<AbstractSceneNode>& node) {
    if (!mChildren.erase(node))
        throw Exception("Unable to detach scene node.");
}

void AbstractSceneNode::draw(const Matrix4f& transform) {
    for (auto node : mChildren)
        node->draw(transform);
}

}
