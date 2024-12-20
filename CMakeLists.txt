# CMakeList.txt : CMake project for cpp-router, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("cpp-router")

file(GLOB_RECURSE sources Sources/*.cpp Sources/*.h ThirdParty/libeslcpp/src/*.c ThirdParty/libeslcpp/src/esl_oop.cpp)

# Remove the comment bellow to enable BoostCPP in your project
# set(BOOST_INCLUDEDIR ${CMAKE_SOURCE_DIR}/ThirdParty/boost/include)
# set(BOOST_LIBRARYDIR ${CMAKE_SOURCE_DIR}/ThirdParty/boost/lib)
# end boost include
set(BOOST_INCLUDEDIR "")
set(BOOST_LIBRARYDIR "")
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Remove the comment bellow to enable BoostCPP in your project
# find_package(Boost COMPONENTS system filesystem thread REQUIRED)
# end boost include
include_directories(${BOOST_INCLUDEDIR} ${CMAKE_SOURCE_DIR}/ThirdParty/libeslcpp/src/include)
link_directories(${BOOST_LIBRARYDIR})
# Add source to this project's executable.
add_executable (cpp-router "cpp-router.cpp" "cpp-router.h" ${sources})
target_link_libraries(
	cpp-router 
	# Add the individual Boost Libs here, bellow has some samples
	# ${BOOST_LIBRARYDIR}/libboost_atomic.so
	# ${BOOST_LIBRARYDIR}/libboost_container.so
	# ${BOOST_LIBRARYDIR}/libboost_filesystem.so
	# ${BOOST_LIBRARYDIR}/libboost_json.so
	# ${BOOST_LIBRARYDIR}/libboost_thread.so
	# ${BOOST_LIBRARYDIR}/libboost_system.so
)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cpp-router PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
