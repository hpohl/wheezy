#ifndef WZY_SCENE_NODE_HPP
#define WZY_SCENE_NODE_HPP

#include <memory>
#include <set>

#include <wzy/scene/movable.hpp>
#include <wzy/utilities/noncopyable.hpp>


namespace wzy {

class SceneNode : public Movable, public NonCopyable {
public:
    const std::set<std::shared_ptr<SceneNode> > children()
    { return mChildren; }

    const std::shared_ptr<SceneNode> createChild();

private:
    std::set<std::shared_ptr<SceneNode> > mChildren;
};

}

#endif
