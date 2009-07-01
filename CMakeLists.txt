PROJECT(genetifex)

FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})

SET(GenetifexSources main.cpp genetifex.cpp view.cpp scene.cpp)

QT4_AUTOMOC(${GenetifexSources})

ADD_EXECUTABLE(genetifex ${GenetifexSources})

TARGET_LINK_LIBRARIES(genetifex ${QT_LIBRARIES})
