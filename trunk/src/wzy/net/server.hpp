#ifndef WZY_NET_SERVER_HPP
#define WZY_NET_SERVER_HPP

#include <memory>

#include <wzy/scene/manager.hpp>
#include <wzy/utilities/singleton.hpp>


namespace wzy {

class Server : public Singleton<Server> {
public:

private:
    const std::shared_ptr<SceneManager> mSceneManager;
};

}

#endif
