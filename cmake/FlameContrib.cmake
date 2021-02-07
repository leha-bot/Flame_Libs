cmake_minimum_required(VERSION 3.14)

find_package(Git REQUIRED)
if(NOT Git_FOUND)
	message(FATAL "Git not found")
endif()

function(download_resolver)
	set(RESOLVER_NAME CMakeFlameResolver)
	set(RESOLVER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${RESOLVER_NAME})
	set(RESOLVER_VERSION v1.0)
	if(NOT (EXISTS "${RESOLVER_PATH}" AND IS_DIRECTORY "${RESOLVER_PATH}"))
		message(STATUS "Clone ${RESOLVER_NAME}")
		execute_process(COMMAND
			${GIT_EXECUTABLE}
			clone https://github.com/kachsheev/${RESOLVER_NAME}.git
			--branch ${RESOLVER_VERSION}
			${RESOLVER_PATH}
		)
	else()
		message(STATUS "Not need to clone ${RESOLVER_NAME} version=${RESOLVER_VERSION}")
	endif()
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${RESOLVER_PATH}/cmake" PARENT_SCOPE)
endfunction()

download_resolver()