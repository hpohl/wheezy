add_executable(dtesting
main.cpp
)

target_link_libraries(dtesting
wzycore wzymedia wzyrender wzyresource wzyscene
GL GLU
)
