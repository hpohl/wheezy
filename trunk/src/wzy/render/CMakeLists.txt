add_library(wzyrender SHARED
buffer.cpp buffer.hpp
data.cpp data.hpp
framebuffer.cpp framebuffer.hpp
program.cpp program.hpp
render.cpp render.hpp
shader.cpp shader.hpp
texture.cpp texture.hpp
glew.hpp
)

target_link_libraries(wzyrender
wzyutilities
${GLEW_LIBRARY}
)
