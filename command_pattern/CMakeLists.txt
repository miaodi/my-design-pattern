project(command_pattern)

add_executable(${PROJECT_NAME} exec.cpp)

set_target_properties(command_pattern PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                 "${CMAKE_BINARY_DIR}/bin")
