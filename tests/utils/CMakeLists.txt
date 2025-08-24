set(MODULE_NAME mc-mass-tests-utils)

################################################################################

set(SOURCES
    TestCheck.cpp
    TestStringUtils.cpp
    TestXmlDoc.cpp
    TestXmlNode.cpp
)

################################################################################

add_library(${MODULE_NAME} OBJECT ${SOURCES})
