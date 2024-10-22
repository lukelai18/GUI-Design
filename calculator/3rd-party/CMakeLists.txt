
# wxWidgets
include(${CMAKE_CURRENT_LIST_DIR}/wxWidgets.cmake)

# dummy executable depending on wxWidgets
set(CMAKE_FOLDER "Utilities")
add_executable(wxApp EXCLUDE_FROM_ALL wxApp.cpp)
target_link_libraries(wxApp wx::core wx::gl)

