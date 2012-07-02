add_library(wzyresource SHARED
item.cpp item.hpp
manager.cpp manager.hpp
package.cpp package.hpp
version.hpp
)

add_subdirectory(items)

target_link_libraries(wzyresource
wzyresource_items
)
