add_library(wzymedia SHARED
image.cpp image.hpp
)

target_link_libraries(wzymedia
wzyrender
${FREEIMAGE_LIBRARY}
)
