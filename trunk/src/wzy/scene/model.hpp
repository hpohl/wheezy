#ifndef WZY_SCENE_MODEL_HPP
#define WZY_SCENE_MODEL_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include <wzy/render/data.hpp>
#include <wzy/scene/material.hpp>
#include <wzy/utilities/vec.hpp>


namespace wzy {

class Model final {
public:
    typedef std::shared_ptr<std::vector<std::shared_ptr<Model> > > ModelsPtr;
    typedef std::shared_ptr<std::vector<Vector4f> > VerticesPtr;
    typedef std::shared_ptr<std::vector<Vector4f> > ColoursPtr;
    typedef std::shared_ptr<std::vector<Vector2f> > TexCoordsPtr;


    Model();
    Model(const VerticesPtr& vertices,
          const ColoursPtr& colours = std::make_shared<std::vector<Vector4f> >(),
          const TexCoordsPtr& texCoords = std::make_shared<std::vector<Vector2f> >());

    const std::string name() const
    { return mName; }

    void setName(const std::string& name)
    { mName = name; }

    void attach(const std::shared_ptr<Model>& mdl)
    { mChildren->push_back(mdl); }

    void detach(const std::shared_ptr<Model>& mdl)
    { std::remove(mChildren->begin(), mChildren->end(), mdl); }

    const ModelsPtr children()
    { return mChildren; }

    const std::shared_ptr<const render::Data> renderData() const
    { return mRenderData; }

    const std::shared_ptr<Material> material()
    { return mMaterial; }

    void setMaterial(const std::shared_ptr<Material>& mtl)
    { mMaterial = mtl; }

private:
    std::string mName;
    ModelsPtr mChildren;
    VerticesPtr mVertices;
    ColoursPtr mColours;
    TexCoordsPtr mTexCoords;
    std::shared_ptr<Material> mMaterial;
    std::shared_ptr<render::Data> mRenderData;

    void update();
};

}

#endif
