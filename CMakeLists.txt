# CMakeList.txt: проект CMake для CMakeProject1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required(VERSION 3.10)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CMakeProject1")



# Добавьте источник в исполняемый файл этого проекта.
add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

#set(CMAKE_CXX_STANDARD 20)
#
#    include(FetchContent)
#
#     FetchContent_AddRepeatingUse(
#        "https://github.com/sebsjames/mathplot.git"
#        GIT_TAG "main" 
#        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/mathplot
#    )
#
#    FetchContent_MakeDependent(mathplot)
#
# Set the build output location to a common directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
 
find_package( OpenGL REQUIRED )
#find_package(glfw3 3.4 REQUIRED)
 
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE external/glfw-3.4/include/GLFW)
target_link_directories("${CMAKE_PROJECT_NAME}" PRIVATE external/glfw-3.4/lib-vc2022)
target_link_libraries("CMakeProject1" PRIVATE glfw3)


set(MPLOT_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/external/mathplot-main" CACHE PATH "The path to mathplot")
#include_directories(BEFORE ${MPLOT_INCLUDE_PATH})         # Allows mplot/Header.h to be found
target_include_directories(CMakeProject1 PRIVATE ${MPLOT_INCLUDE_PATH})
#include_directories(BEFORE ${MPLOT_INCLUDE_PATH}/maths)   # Allows sm/Header.h to be found
target_include_directories(CMakeProject1 PRIVATE ${MPLOT_INCLUDE_PATH}/maths)

# If you want to add another directory to your include path, you can add an extra include_directories call:
# include_directories(BEFORE ${PROJECT_SOURCE_DIR}/my_includes)
#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/external/glfw-3.4/include)
target_include_directories(CMakeProject1 PRIVATE ${PROJECT_SOURCE_DIR}/external/glfw-3.4/include)

#find_package(Freetype REQUIRED)
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE external/freetype)
target_link_directories("${CMAKE_PROJECT_NAME}" PRIVATE external/freetype)
target_link_libraries("CMakeProject1" PRIVATE freetype)
#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/external/freetype/include)
#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/external)
 
target_include_directories(CMakeProject1 PRIVATE ${PROJECT_SOURCE_DIR}/external/freetype/include)
target_include_directories(CMakeProject1 BEFORE PRIVATE ${PROJECT_SOURCE_DIR}/external)

#Примеры замены
#Старый вариант с  :
#Код
#include_directories(
#    ${CMAKE_CURRENT_SOURCE_DIR}/include
#)
#add_executable(my_app main.cpp)
#Новый вариант с target_include_directories:
#Код
#add_executable(my_app main.cpp)
#target_include_directories(my_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)







#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/imgui)            # Imgui
#include_directories(BEFORE ${PROJECT_SOURCE_DIR}/imgui/backends)   #
    
#add_subdirectory(external/mathplot-main) 
#target_link_libraries(CMakeProject1 mathplot-main::mathplot-main)
#target_link_libraries(CMakeProject1 OpenGL::GL Freetype::Freetype glfw)
#target_link_libraries(${PROJECT_NAME} mathplot-main::mathplot-main)

# Tell the program where the mathplot fonts are, to compile them into the binary
##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMPLOT_FONTS_DIR=\"\\\"${PROJECT_SOURCE_DIR}/mathplot/fonts\\\"\"")
##
### Find the libraries which will be needed by mathplot
##set(OpenGL_GL_PREFERENCE "GLVND") # Following `cmake --help-policy CMP0072`
##find_package(OpenGL REQUIRED)
##find_package(glfw3 3.4 REQUIRED)
##find_package(Freetype REQUIRED)
##find_package(nlohmann_json REQUIRED)
##
##
### Assuming that you installed mathplot in-tree (i.e. 'next to' yourprog.cpp).
##set(MPLOT_INCLUDE_PATH "${PROJECT_SOURCE_DIR}/mathplot" CACHE PATH "The path to mathplot")
##include_directories(BEFORE ${MPLOT_INCLUDE_PATH})         # Allows mplot/Header.h to be found
##include_directories(BEFORE ${MPLOT_INCLUDE_PATH}/maths)   # Allows sm/Header.h to be found

# If you want to add another directory to your include path, you can add an extra include_directories call:
# include_directories(BEFORE ${PROJECT_SOURCE_DIR}/my_includes)

#
# All the library finding is now done. It's time to compile the program.
#


# Mathplot code requires a number of libraries, these are the ones required for graphics
###target_link_libraries(CMakeProject1 OpenGL::GL Freetype::Freetype glfw)
# If you change prog1 to use sm::hdfdata or sm::bezcurve, you may need to link these too:
# set(MPLOT_LIBS_EXTRA ${ARMADILLO_LIBRARY} ${ARMADILLO_LIBRARIES} ${HDF5_C_LIBRARIES})

#
# All done!
#

# This is just a useful stanza for debugging of cmake variables:
 option(DEBUG_VARIABLES OFF)
 if(DEBUG_VARIABLES)
   get_cmake_property(_variableNames VARIABLES)
   foreach (_variableName ${_variableNames})
     message(STATUS "${_variableName}=${${_variableName}}")
   endforeach()
 endif(DEBUG_VARIABLES)