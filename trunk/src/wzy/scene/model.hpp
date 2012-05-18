#ifndef WZY_SCENE_MODEL_HPP
#define WZY_SCENE_MODEL_HPP

#include <memory>
#include <vector>

#include <wzy/render/data.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {

class Model final {
public:
    struct Index {
        size_t vertex;
        size_t colour;
    };

    Model();
    Model(const std::vector<Vector4f>& vertices,
          const std::vector<Vector4f>& colours);

    const std::shared_ptr<const render::Data> renderData() const
    { return mRenderData; }

private:
    std::shared_ptr<std::vector<Vector4f> > mVertices;
    std::shared_ptr<std::vector<Vector4f> > mColours;
    std::shared_ptr<std::vector<Index> > mIndices;
    std::shared_ptr<render::Data> mRenderData;

    void update();
};

}

#endif
