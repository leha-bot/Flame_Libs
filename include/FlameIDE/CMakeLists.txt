cmake_minimum_required(VERSION 3.14)

set(INSTALL_HEADER_SUBPATH "include/FlameIDE")

set(HEADER_MODULES
	${FLAME_INCLUDE_SUBMODLUES_PATH}/About
	${FLAME_INCLUDE_SUBMODLUES_PATH}/Bus
	${FLAME_INCLUDE_SUBMODLUES_PATH}/Common
	${FLAME_INCLUDE_SUBMODLUES_PATH}/Constants
	${FLAME_INCLUDE_SUBMODLUES_PATH}/Crypto
	${FLAME_INCLUDE_SUBMODLUES_PATH}/Os
	${FLAME_INCLUDE_SUBMODLUES_PATH}/Others
	${FLAME_INCLUDE_SUBMODLUES_PATH}/Streams
	${FLAME_INCLUDE_SUBMODLUES_PATH}/Templates
	${FLAME_INCLUDE_SUBMODLUES_PATH}/Ubjson
)
foreach(module ${HEADER_MODULES})
	add_subdirectory(${module})
endforeach()

flame_resolve_targets()
