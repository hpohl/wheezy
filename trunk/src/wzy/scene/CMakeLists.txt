add_library(wzyscene SHARED
camera.cpp camera.hpp
entity.cpp entity.hpp
light.cpp light.hpp
model.cpp model.hpp
movable.cpp movable.hpp
node.cpp node.hpp
)

target_link_libraries(wzyscene
wzyrender
)
