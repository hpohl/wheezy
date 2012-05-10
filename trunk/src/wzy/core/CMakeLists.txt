add_library(wzycore SHARED
engine.cpp engine.hpp
state.cpp state.hpp
window.cpp window.hpp
)

target_link_libraries(wzycore
wzyrender wzyutil
${GLUT_LIBRARIES}
)
