add_library(wzynet SHARED
server.cpp server.hpp
)

target_link_libraries(wzynet
wzyscene
)
