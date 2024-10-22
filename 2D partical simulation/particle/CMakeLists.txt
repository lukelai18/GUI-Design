
add_executable(particle
  App.hpp
  App.cpp
  MainWindow.hpp
  MainWindow.cpp
  CanvasGL.hpp
  CanvasGL.cpp
  ControlPanel.hpp
  ControlPanel.cpp
  Simulation.hpp
  Simulation.cpp
  Vector2d.hpp
)
target_link_libraries(particle wx::core wx::gl)


