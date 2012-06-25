#ifndef WZY_RENDER_RENDER_HPP
#define WZY_RENDER_RENDER_HPP

#include <wzy/utilities/vec.hpp>


namespace wzy {
namespace render {

void init();

void flush();
void finish();

void setViewport(const Vector2i& pos,
                 const Vector2i& size);

void clear();

}
}

#endif
