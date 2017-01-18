include_directories(
   ./..
   /home/ioanna/proj/googletest/googletest/include/
   /home/ioanna/proj/googletest/googlemock/include/

)
link_directories (
    /home/ioanna/proj/googletest/googletest/gtest/
    /home/ioanna/proj/googletest/googlemock/gtest/
    /home/ioanna/proj/googletest/googlemock/
)

set(SOURCES
    test.cc
)

find_package (Threads)


add_executable(proj_test  ${SOURCES})
set (LIBRARIES
    gtest
    gtest_main
    gmock
)

target_link_libraries(proj_test ${LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
