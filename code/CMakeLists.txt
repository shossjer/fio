include (bnc/CMakeLists.txt)
include (lib/CMakeLists.txt)

add_library(fiolib STATIC)
target_sources(fiolib PRIVATE ${FIOLIB_SOURCES} ${FIOLIB_HEADERS} ${FIOLIB_SECRETS})
target_include_directories(fiolib PUBLIC "lib")
target_compile_options(fiolib PRIVATE
	$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
		-Wall -Wextra -Wconversion -Werror -nostdlib -fno-exceptions -fno-rtti>
	$<$<CXX_COMPILER_ID:MSVC>:
		/W4 /WX /Zl /GS- /GR- /Zc:rvalueCast>
	)
if(MSVC)
	set_target_properties(fiolib PROPERTIES
		STATIC_LIBRARY_FLAGS "/NODEFAULTLIB"
		)
endif()
install(TARGETS fiolib DESTINATION lib)
install(FILES ${FIOLIB_HEADERS} DESTINATION include/fio)

if(FIO_BUILD_BENCHMARKS)
	add_executable(fiobnc "")
	target_sources(fiobnc PRIVATE ${FIOBNC_SOURCES} ${FIOBNC_HEADERS})
	target_include_directories(fiobnc PRIVATE "bnc")
	target_link_libraries(fiobnc PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:msvc_ignored_options>
		fiolib fio_catch fiobnc_features
		)
	target_compile_options(fiobnc PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
			-Wall -Wextra -Wconversion -Werror -march=native>
		$<$<CXX_COMPILER_ID:MSVC>:
			/W4 /WX /Zc:rvalueCast>
		)
	target_compile_definitions(fiobnc PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:
			_CRT_SECURE_NO_WARNINGS>
		CATCH_CONFIG_ENABLE_BENCHMARKING
		)

	if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} VERSION_GREATER 3.7)
		set_target_properties(fiobnc PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_HOME_DIRECTORY}")
	endif()

	set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT fiobnc)
endif()
