set(MODULE_NAME mc-mass-utils)

################################################################################

set(CPP_FILES
    Atmosphere.cpp
    StringUtils.cpp
    XmlDoc.cpp
    XmlNode.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${CPP_FILES})
