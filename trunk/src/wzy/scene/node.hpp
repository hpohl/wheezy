#ifndef WZY_SCENE_NODE_HPP
#define WZY_SCENE_NODE_HPP

#include <memory>
#include <set>

#include <wzy/scene/movable.hpp>
#include <wzy/utilities/mat.hpp>
#include <wzy/utilities/noncopyable.hpp>


namespace wzy {

class AbstractSceneNode : public Movable, public NonCopyable {
public:
    virtual ~AbstractSceneNode() = 0;

    const std::set<std::shared_ptr<AbstractSceneNode> > children()
    { return mChildren; }

    void attach(const std::shared_ptr<AbstractSceneNode>& node);
    void detach(const std::shared_ptr<AbstractSceneNode>& node);

    virtual void draw(const Matrix4f& transform);

private:
    std::set<std::shared_ptr<AbstractSceneNode> > mChildren;
};

class SceneNode final : public AbstractSceneNode {
public:
    template <class... Args>
    SceneNode(Args&&... args) :
        AbstractSceneNode(std::forward<Args>(args)...) { }
};

}

#endif
