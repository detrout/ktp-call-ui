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

add_definitions(
    # These prevent gstreamer from including libxml2 headers
    -DGST_DISABLE_XML
    -DGST_DISABLE_LOADSAVE
)

kde4_add_library(qf STATIC
                    qf.cpp
                    gen.cpp
                    session.cpp
                    conference.cpp
                )

target_link_libraries(qf
    ${QTGSTREAMER_LIBRARIES}
    ${TP_FARSTREAM_LDFLAGS}
    ${FARSTREAM_LDFLAGS}
    ${TELEPATHY_QT4_FARSTREAM_LIBRARIES}
)

add_subdirectory(test)

# /home/diane/kde/src/kde-telepathy/collabora/libqtgstreamer/x86_64-linux-gnu/codegen/codegen -I/usr/include/farstream-0.2/farstream/fs-candidate.h -I/usr/include/farstream-0.2/farstream/fs-codec.h -I/usr/include/farstream-0.2/farstream/fs-conference.h -I/usr/include/farstream-0.2/farstream/fs-participant.h -I/usr/include/farstream-0.2/farstream/fs-session.h -I/usr/include/farstream-0.2/farstream/fs-stream.h candidate.h codec.h conference.h participant.h session.h stream.h enums.h > gen.cpp
