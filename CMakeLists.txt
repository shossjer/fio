cmake_minimum_required(VERSION 3.5)

include(CMakeDependentOption)
include(dep/dep.cmake)

project(fio CXX)

# project setup

if(DEFINED CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Detected multi configuration build: ${CMAKE_CONFIGURATION_TYPES}")

	if(DEFINED CMAKE_BUILD_TYPE)
		message(WARNING "Both CMAKE_CONFIGURATION_TYPES and CMAKE_BUILD_TYPE are set! Please unset CMAKE_BUILD_TYPE to avoid confusion.")
	endif()
elseif(DEFINED CMAKE_BUILD_TYPE)
	if(CMAKE_BUILD_TYPE STREQUAL "")
		message(STATUS "Detected single configuration build")
	else()
		message(STATUS "Detected single configuration build: ${CMAKE_BUILD_TYPE}")
	endif()
else()
	message(FATAL_ERROR "Neither CMAKE_CONFIGURATION_TYPES or CMAKE_BUILD_TYPE are set!")
endif()

if(NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 11)
	message(STATUS "C++ standard ${CMAKE_CXX_STANDARD} (default)")
elseif(CMAKE_CXX_STANDARD LESS 11)
	message(FATAL_ERROR "Require C++ standard >= 11")
else()
	message(STATUS "C++ standard ${CMAKE_CXX_STANDARD}")
endif()
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_property(_dep_directory_set DIRECTORY PROPERTY "DEP_DIRECTORY" SET)
if(NOT _dep_directory_set)
	set_property(DIRECTORY PROPERTY "DEP_DIRECTORY" "${CMAKE_SOURCE_DIR}/dep/${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}")
endif()

# project information

message(STATUS "Using C++ compiler ${CMAKE_CXX_COMPILER}")
message(STATUS "System is ${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}")

# build dependencies

macro(_package_catch)
	dep_package(catch-2-12-1 fio_catch
		${ARGV}

		FILES
		catch2/catch.hpp
		)
endmacro()

option(FIO_BUILD_CATCH "Build catch" ON)
if(FIO_BUILD_CATCH)
	_package_catch(IGNORE_SYSTEM)

	dep_build(catch-2-12-1
		DOWNLOAD_STEP
		GIT_REPOSITORY "https://github.com/philsquared/Catch.git"
		GIT_TAG "v2.12.1"
		GIT_SHALLOW True

		CMAKE_OPTIONS
		-DCATCH_BUILD_TESTING=OFF
		-DCATCH_INSTALL_DOCS=OFF
		-DCATCH_INSTALL_HELPERS=OFF
		)
endif()

_package_catch()

# project options

cmake_dependent_option(FIO_BUILD_BENCHMARKS "Build benchmarks" OFF "TARGET fio_catch" OFF)

# build features

if(FIO_BUILD_BENCHMARKS)
	add_library(fiobnc_features INTERFACE)

	# https://www.agner.org/optimize/#asmlib
	macro(_package_asmlib)
		dep_package(asmlib fio_asmlib
			${ARGV}

			FILES
			asmlib.h

			LIBS
			Linux_x86_64 libaelf64.a
			Windows_AMD64 libacof64.lib
			)
	endmacro()

	option(FIO_BUILD_ASMLIB "Build asmlib" ON)
	if(FIO_BUILD_ASMLIB)
		_package_asmlib(IGNORE_SYSTEM)

		dep_build(asmlib
			DOWNLOAD_STEP
			URL "https://www.agner.org/optimize/asmlib.zip"
			TIMEOUT 10

			INSTALL_STEP
			INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_if_different "\$\{_source_dir\}/asmlib.h" "\$\{_install_prefix\}/include"
			Linux_x86_64
			COMMAND ${CMAKE_COMMAND} -E copy_if_different "\$\{_source_dir\}/libaelf64.a" "\$\{_install_prefix\}/lib"
			Windows_AMD64
			COMMAND ${CMAKE_COMMAND} -E copy_if_different "\$\{_source_dir\}/libacof64.lib" "\$\{_install_prefix\}/lib"
			)
	endif()

	_package_asmlib()
	if(TARGET fio_asmlib)
		target_link_libraries(fiobnc_features INTERFACE fio_asmlib)
		target_compile_definitions(fiobnc_features INTERFACE HAVE_ASMLIB)
	endif()

	# https://github.com/electronicarts/EAStdC
	macro(_package_eastdc)
		dep_package(eastdc-latest fio_eastdc
			SUPPORTS_DEBUG
			${ARGV}

			FILES
			EAStdC/EASprintf.h

			LIBS
			EAStdC
			)
	endmacro()

	cmake_dependent_option(FIO_BUILD_EASTDC "Build eastdc" ON "POLICY CMP0097" OFF)
	if(FIO_BUILD_EASTDC)
		_package_eastdc(IGNORE_SYSTEM)

		# note eastdc has a nasty recursive dependency between its submodules
		# so we have to hack around it by not fetching the submodules when
		# cloning but instead postpone it and make an explicit request to
		# fetch the submodules later; this is why we require POLICY CMP0097
		# (available since version 3.14)
		#
		# https://gitlab.kitware.com/cmake/cmake/-/issues/19832
		#
		# furthermore, the latest version of the library is missing an
		# install target and recursive calls to its dependencies, so we use
		# this DIY version of the library instead
		dep_build(eastdc-unknown
			POLICY_CMP0097
			FIND_GIT
			SUPPORTS_DEBUG

			DOWNLOAD_STEP
			GIT_REPOSITORY "https://github.com/shossjer/EAStdC.git"
			GIT_TAG "install"
			GIT_SUBMODULES ""
			GIT_SHALLOW True

			UPDATE_STEP
			UPDATE_COMMAND "${CMAKE_COMMAND}" -E chdir "\$\{_source_dir\}" "\$\{GIT_EXECUTABLE\}" submodule update --init "test/packages/EABase" "test/packages/EAAssert" "test/packages/EAThread"
			COMMAND "${CMAKE_COMMAND}" -E touch "\$\{_source_dir\}/CommonCppFlags"
			COMMAND "${CMAKE_COMMAND}" -E touch "\$\{_source_dir\}/test/packages/EAAssert/CommonCppFlags"
			COMMAND "${CMAKE_COMMAND}" -E touch "\$\{_source_dir\}/test/packages/EAThread/CommonCppFlags"

			CMAKE_OPTIONS
			-DEASTDC_BUILD_TESTS=OFF
			)
	endif()

	_package_eastdc()
	if(TARGET fio_eastdc)
		target_link_libraries(fiobnc_features INTERFACE fio_eastdc)
		target_compile_definitions(fiobnc_features INTERFACE HAVE_EASTDC)
	endif()

	# https://github.com/fmtlib/fmt
	macro(_package_fmt)
		dep_package(fmt-8.0.1 fio_fmt
			SUPPORTS_DEBUG
			${ARGV}

			FILES
			fmt/core.h

			LIBS
			optimized fmt
			debug fmtd
			)
	endmacro()

	option(FIO_BUILD_FMT "Build fmt" ON)
	if(FIO_BUILD_FMT)
		_package_fmt(IGNORE_SYSTEM)

		dep_build(fmt-8.0.1
			SUPPORTS_DEBUG

			DOWNLOAD_STEP
			URL "https://github.com/fmtlib/fmt/archive/refs/tags/8.0.1.tar.gz"
			TIMEOUT 10

			CMAKE_OPTIONS
			-DFMT_TEST=OFF
			-DBUILD_SHARED_LIBS=OFF
			)
	endif()

	_package_fmt()
	if(TARGET fio_fmt)
		target_link_libraries(fiobnc_features INTERFACE fio_fmt)
		target_compile_definitions(fiobnc_features INTERFACE HAVE_FMT)
	endif()
endif()

# remove dumb compiler options

if(MSVC)
	add_library(msvc_ignored_options INTERFACE)

	# default options we do NOT want in fiolib, but do want in fiobnc
	set(_ignored_options "/EH[ascr]*" "/RTC[su1]" "/M[TD]d?" "/GR")

	foreach(_option IN LISTS _ignored_options)
		string(REGEX MATCHALL "${_option}" _matches "${CMAKE_CXX_FLAGS}")
		if(_matches)
			string(REGEX REPLACE "${_option}" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
			target_compile_options(msvc_ignored_options INTERFACE ${_matches})
		endif()
	endforeach()

	foreach(_config IN LISTS CMAKE_CONFIGURATION_TYPES)
		string(TOUPPER "${_config}" _big_config)

		foreach(_option IN LISTS _ignored_options)
			string(REGEX MATCHALL "${_option}" _matches "${CMAKE_CXX_FLAGS_${_big_config}}")
			if(_matches)
				string(REGEX REPLACE "${_option}" "" CMAKE_CXX_FLAGS_${_big_config} "${CMAKE_CXX_FLAGS_${_big_config}}")
				target_compile_options(msvc_ignored_options INTERFACE
					$<$<CONFIG:${_config}>:${_matches}>)
			endif()
		endforeach()
	endforeach()
endif()

# subdirectory setup

add_subdirectory(code)
