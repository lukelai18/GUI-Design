
include(FetchContent)

FetchContent_Declare(
  wxWidgets
  GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
  GIT_TAG        v3.2.1
)

# Check if population has already been performed
FetchContent_GetProperties(wxWidgets)
string(TOLOWER "wxWidgets" lcName)
if(NOT ${lcName}_POPULATED)
  message(STATUS "wxWidgets download and configure requested")

  # Fetch the content using previously declared details
  FetchContent_Populate(wxWidgets)

  # Set custom variables, policies, etc.
  set(wxBUILD_SHARED OFF CACHE BOOL "Build wxWidgets as shared lib" FORCE)
  add_definitions(-D__STDC_WANT_LIB_EXT1__)

  # Bring the populated content into the build
  add_subdirectory(${${lcName}_SOURCE_DIR} ${${lcName}_BINARY_DIR})
  
  message(STATUS "wxWidgets source folder: ${${lcName}_SOURCE_DIR}")
endif()
