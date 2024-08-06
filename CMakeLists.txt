cmake_minimum_required(VERSION 3.10)

# Set the project name
project(creatingacompiler C)

# Add all C source files in the current directory to the executable
file(GLOB SOURCES
    "main.c"
    "memory.c"
    "vm.c"
    "object.c"
    "compiler.c"
    "scanner.c"
    "value.c"
    "chunk.c"
    "debug.c"
    # Add more files here in the desired order
)

# Create the executable from the source files
add_executable(TurboCompiler ${SOURCES})

# Include directories if needed
# include_directories(${CMAKE_SOURCE_DIR}/include)

# Link libraries if needed
# target_link_libraries(MyExecutable some_library)

# Add a custom target to run the executable
add_custom_target(Run
    COMMAND TurboCompiler
    DEPENDS TurboCompiler
    WORKING_DIRECTORY ${CMAKE_PROJEeCT_DIR}
    COMMENT "Running Compiler"
)