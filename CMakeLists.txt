# CMakeList.txt: проект CMake для CalmWaters; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
project ("CalmWaters")
# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()



add_executable (CalmWaters "CalmWaters.cpp" "CalmWaters.h" "Player.cpp" "Player.h" "InputHandler.h" "InputHandler.cpp" "GameTimer.h" "GameTimer.cpp")

target_include_directories(CalmWaters PRIVATE "C:/SDL3/SDL3-3.4.8/include")

target_link_directories(CalmWaters PRIVATE "C:/SDL3/SDL3-3.4.8/lib/x64")
target_link_libraries(CalmWaters PRIVATE "SDL3.lib")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CalmWaters PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
