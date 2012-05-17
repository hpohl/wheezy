#ifndef WZY_SCENE_MODEL_HPP
#define WZY_SCENE_MODEL_HPP

#include <memory>
#include <vector>

#include <wzy/utilities/vec.hpp>


namespace wzy {

class Model {
public:
    struct Index {
        size_t vertex;
        size_t colour;
    };

    Model();
    Model(const std::vector<Vector4f>& vertices,
          const std::vector<Vector4f>& colours);

private:
    std::shared_ptr<std::vector<Vector4f> > mVertices;
    std::shared_ptr<std::vector<Vector4f> > mColours;
    std::shared_ptr<std::vector<Index> > mIndices;

    void update();
};

}

#endif
