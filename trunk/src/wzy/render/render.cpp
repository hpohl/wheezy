#include <wzy/render/render.hpp>

#include <wzy/render/glew.hpp>
#include <wzy/utilities/exception.hpp>


namespace wzy {
namespace render {

void init() {
    static bool initialised = false;
    if (!initialised) {
        if (glewInit() != GLEW_NO_ERROR)
            throw Exception("Unable to initialise renderer.");

        //glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

        glDepthFunc(GL_LESS);
        //glCullFace(GL_BACK);

        initialised = true;
    }
}

void flush()
{ glFlush(); }

void finish()
{ glFinish(); }

void setViewport(const Vector2i& pos, const Vector2i& size)
{ glViewport(pos.x(), pos.y(), size.x(), size.y()); }

void clear()
{ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

}
}
