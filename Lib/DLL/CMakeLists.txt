cmake_minimum_required(VERSION 2.6)
project(RakNetDLL)

FILE(GLOB ALL_HEADER_SRCS ${RakNet_SOURCE_DIR}/Source/*.h)
FILE(GLOB ALL_CPP_SRCS ${RakNet_SOURCE_DIR}/Source/*.cpp)


message("Using system lua...")
set(ENV{LUA_DIR} ~/.luaenv/versions/5.1.5) # hints for find lua in luaenv.
find_package(Lua REQUIRED)

include_directories( ${RAKNET_INTERNAL_INCLUDE_DIRS} )

add_library(RakNetDLL MODULE ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} readme.txt)

IF(WIN32 AND NOT UNIX)
	SET( CMAKE_CXX_FLAGS "/D WIN32 /D _RAKNET_DLL /D _CRT_NONSTDC_NO_DEPRECATE /D _CRT_SECURE_NO_DEPRECATE /GS- /GR- ")
ENDIF(WIN32 AND NOT UNIX)

IF(WIN32 AND NOT UNIX)
	target_link_libraries (RakNetDLL ${RAKNET_LIBRARY_LIBS} ${LUA_LIBRARIES})
	set_target_properties(RakNetDLL PROPERTIES OUTPUT_NAME "raknet" PREFIX "")
ELSE(WIN32 AND NOT UNIX)
	target_link_libraries (RakNetDLL ${RAKNET_LIBRARY_LIBS} ${LUA_LIBRARIES})
	set_target_properties(RakNetDLL PROPERTIES OUTPUT_NAME "raknet" PREFIX "")
	INSTALL(TARGETS RakNetDLL DESTINATION ${RakNet_SOURCE_DIR}/Lib/DLL)
	INSTALL(TARGETS RakNetDLL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF(WIN32 AND NOT UNIX)
