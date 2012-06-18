add_executable(dtesting
main.cpp
)

target_link_libraries(dtesting
wzycore wzymedia wzyrender wzyscene
GL GLU
)
