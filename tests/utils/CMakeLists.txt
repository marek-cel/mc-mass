set(MODULE_NAME mc-mass-tests-utils)

################################################################################

set(SOURCES
    TestCheck.cpp
    TestMatrix3x3.cpp
    TestStringUtils.cpp
    TestVector3.cpp
    TestXmlDoc.cpp
    TestXmlNode.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
