
add_executable(calc 
  App.hpp
  App.cpp
  MainWindow.hpp
  MainWindow.cpp
)
target_link_libraries(calc wx::core)


