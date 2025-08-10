set(MODULE_NAME utils)

################################################################################

set(CPP_FILES
    Atmosphere.cpp
    Cuboid.cpp
    FirstMomentOfMass.cpp
    InertiaMatrix.cpp
    ParallelAxisInertia.cpp
    PositionVector.cpp
    XmlUtils.cpp
)

################################################################################

add_library(${MODULE_NAME} STATIC ${CPP_FILES})

qt5_use_modules(${MODULE_NAME} Xml)
