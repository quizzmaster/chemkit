find_package(Chemkit)
include_directories(${CHEMKIT_INCLUDE_DIRS})

if(NOT ${CHEMKIT_WITH_GUI})
  return()
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

set(HEADERS
  atomcolormap.h
  gui.h
  periodictabledialog.h
  periodictablewidget.h
)

set(SOURCES
  atomcolormap.cpp
  gui.cpp
  periodictabledialog.cpp
  periodictablewidget.cpp
)

set(MOC_HEADERS
  periodictabledialog.h
  periodictablewidget.h
)

set(UI_FORMS
  periodictabledialog.ui
  periodictablewidget.ui
)

qt5_wrap_ui(UI_SOURCES ${UI_FORMS})
qt5_wrap_cpp(MOC_SOURCES ${MOC_HEADERS})

add_definitions(
  -DCHEMKIT_GUI_LIBRARY
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_chemkit_library(chemkit-gui ${SOURCES} ${UI_SOURCES} ${MOC_SOURCES})
target_link_libraries(chemkit-gui Qt5::Widgets ${CHEMKIT_LIBRARIES})

# install header files
install(FILES ${HEADERS} DESTINATION include/chemkit/)
