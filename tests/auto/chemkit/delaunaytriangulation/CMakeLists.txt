qt4_wrap_cpp(MOC_SOURCES delaunaytriangulationtest.h)
add_executable(delaunaytriangulationtest delaunaytriangulationtest.cpp ${MOC_SOURCES})
target_link_libraries(delaunaytriangulationtest chemkit ${QT_LIBRARIES})
add_chemkit_test(chemkit.DelaunayTriangulation delaunaytriangulationtest)
