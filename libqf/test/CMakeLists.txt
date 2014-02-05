find_package(PkgConfig REQUIRED)
pkg_check_modules(FARSTREAM REQUIRED farstream-0.2)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${FARSTREAM_INCLUDE_DIRS}
)

macro(qfs_test target)
  automoc4_add_executable(${target} "${target}.cpp")
  target_link_libraries(${target} qf
                                  QtCore
                                  ${QT_QTTEST_LIBRARY}
                                  ${QTGSTREAMER_LIBRARIES}
                                  ${FARSTREAM_LIBRARIES})
  add_test(NAME ${target} COMMAND ${target})
endmacro(qfs_test)

qfs_test(sessiontest)
