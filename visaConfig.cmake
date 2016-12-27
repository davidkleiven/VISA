
get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
include(${SELF_DIR}/visa-target.cmake)
get_filename_component(visa_INCLUDE_DIRS "${SELF_DIR}/include/visa" ABSOLUTE)
