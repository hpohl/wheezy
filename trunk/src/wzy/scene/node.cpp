#include <wzy/scene/node.hpp>

namespace wzy {

const std::shared_ptr<SceneNode> SceneNode::createChild() {
    auto ret = std::make_shared<SceneNode>();
    mChildren.insert(ret);
    return ret;
}

}
