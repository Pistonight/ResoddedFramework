# CmakeLists.txt
project(LawnProject)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/Lawn/*.c"
    "${CMAKE_SOURCE_DIR}/src/Lawn/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/Lawn/*.h"
)

foreach(EXCLUDED_FILE IN LISTS EXCLUDE_FILES)
    list(REMOVE_ITEM SOURCES "${EXCLUDED_FILE}")
endforeach()

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PUBLIC
    WIN32
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    _LIB
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}../ImageLib"
    "${CMAKE_CURRENT_SOURCE_DIR}../PakLib"
    "${CMAKE_CURRENT_SOURCE_DIR}../Sexy.TodLib"
    "${CMAKE_CURRENT_SOURCE_DIR}../SexyAppFramework"
)

foreach(FILE_PATH IN LISTS SOURCES)
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}/src/Lawn" "${FILE_PATH}")
    get_filename_component(FOLDER_PATH "${REL_PATH}" PATH)
    string(REPLACE "/" "\\" FILTER_PATH "${FOLDER_PATH}")
    source_group("${FILTER_PATH}" FILES "${FILE_PATH}")
endforeach()
