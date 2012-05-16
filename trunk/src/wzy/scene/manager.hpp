#ifndef WZY_SCENE_MANAGER_HPP
#define WZY_SCENE_MANAGER_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include <wzy/scene/entity.hpp>


namespace wzy {

class SceneManager {
public:
    SceneManager();

    const std::vector<std::shared_ptr<wzy::Entity> > entities() const
    { return mEntities; }

    template <class EntityT, class... Args>
    const std::shared_ptr<EntityT> addEntity(Args&&... args);

    void removeEntity(const std::shared_ptr<Entity>& ent)
    { std::remove(mEntities.begin(), mEntities.end(), ent); }

private:
    std::vector<std::shared_ptr<wzy::Entity> > mEntities;
};


// ----------------------------------------------
template <class EntityT, class... Args>
const std::shared_ptr<EntityT> SceneManager::addEntity(Args&&... args) {
    static_assert(IsEntity<EntityT>::value, "Can only push entities.");
    auto ent = std::make_shared<EntityT>(std::forward<Args>(args)...);
    mEntities.push_back(ent);
    return ent;
}

}

#endif
