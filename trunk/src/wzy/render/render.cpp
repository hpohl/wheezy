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

        glEnable(GL_TEXTURE_2D);

        initialised = true;
    }
}

}
}
