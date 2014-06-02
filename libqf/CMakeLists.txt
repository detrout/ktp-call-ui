# This is *A LOT* of dependencies to find one by one,
# since gnome people like to include as many headers as possible
# in their public headers instead of doing forward declarations.
find_package(PkgConfig REQUIRED)
pkg_check_modules(FARSTREAM REQUIRED farstream-0.2)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${TP_FARSTREAM_INCLUDE_DIRS}
    ${FARSTREAM_INCLUDE_DIRS}
)

# Macro to run codegen from the subdirs
set(CODEGEN "/home/diane/kde/src/kde-telepathy/collabora/libqtgstreamer/x86_64-linux-gnu/codegen/codegen")
macro(run_codegen _dir_name _includes _headers)
    if (CODEGEN)
        set(_prefixed_headers "")
        foreach(_header ${_headers})
            list(APPEND _prefixed_headers ${_dir_name}/${_header})
        endforeach()

        add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/gen.cpp
                           COMMAND ${CODEGEN}
                           ARGS ${_includes} ${_prefixed_headers}
                                > ${CMAKE_CURRENT_SOURCE_DIR}/gen.cpp
                           DEPENDS ${CODEGEN} ${_headers}
                           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
    endif()

#     add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen.cpp
#                        COMMAND ${CMAKE_COMMAND}
#                        ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/gen.cpp
#                             ${CMAKE_CURRENT_BINARY_DIR}/gen.cpp
#                        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/gen.cpp
#                        COMMENT "Copying gen.cpp to the build directory")
endmacro()
set(CODEGEN_INCLUDES
        -Ifarstream/fs-candidate.h
        -Ifarstream/fs-codec.h
        -Ifarstream/fs-conference.h
        -Ifarstream/fs-participant.h
        -Ifarstream/fs-session.h
        -Ifarstream/fs-stream.h
)
set(CODEGEN_HEADERS
        candidate.h
        codec.h
        conference.h
        participant.h
        session.h
        stream.h
        enums.h
)
#run_codegen("." "${CODEGEN_INCLUDES}" "${CODEGEN_HEADERS}")


add_definitions(
    # These prevent gstreamer from including libxml2 headers
    -DGST_DISABLE_XML
    -DGST_DISABLE_LOADSAVE
)

kde4_add_library(qf STATIC
                    qf.cpp
                    gen.cpp
                    codec.cpp
                    conference.cpp
                    session.cpp
                )

target_link_libraries(qf
    ${QTGSTREAMER_LIBRARIES}
    ${TP_FARSTREAM_LDFLAGS}
    ${FARSTREAM_LDFLAGS}
    ${TELEPATHY_QT4_FARSTREAM_LIBRARIES}
)

add_subdirectory(test)

# /home/diane/kde/src/kde-telepathy/collabora/libqtgstreamer/x86_64-linux-gnu/codegen/codegen -I/usr/include/farstream-0.2/farstream/fs-candidate.h -I/usr/include/farstream-0.2/farstream/fs-codec.h -I/usr/include/farstream-0.2/farstream/fs-conference.h -I/usr/include/farstream-0.2/farstream/fs-participant.h -I/usr/include/farstream-0.2/farstream/fs-session.h -I/usr/include/farstream-0.2/farstream/fs-stream.h candidate.h codec.h conference.h participant.h session.h stream.h enums.h > gen.cpp
