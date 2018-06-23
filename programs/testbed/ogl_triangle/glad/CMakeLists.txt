set(glad_SOURCES gl.c)
set(glad_HEADERS gl.h khrplatform.h)
add_library(glad ${glad_SOURCES} ${glad_HEADERS})
target_link_libraries(glad ${CMAKE_DL_LIBS})
