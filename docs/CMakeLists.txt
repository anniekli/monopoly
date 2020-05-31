set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)

file(GLOB SOURCE_LIST CONFIGURE_DEPENDS
    "${Monopoly_SOURCE_DIR}/include/**/*.h"
    "${Monopoly_SOURCE_DIR}/include/**/*.hpp"
    "${Monopoly_SOURCE_DIR}/include/**/*.cc"
    "${Monopoly_SOURCE_DIR}/include/**/*.cpp")

doxygen_add_docs(docs
    ${SOURCE_LIST}
    "${CMAKE_CURRENT_SOURCE_DIR}/README.md"
    WORKING_DIRECTORY
    "${PROJECT_SOURCE_DIR}/include"
)
