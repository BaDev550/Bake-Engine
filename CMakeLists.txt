cmake_minimum_required(VERSION 3.20)

project("BakeEngine")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h") 
add_executable (BakeEngine ${ENGINE_SOURCES})

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)

target_include_directories(BakeEngine PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/Source
)

if (WIN32)
	target_compile_definitions(BakeEngine PRIVATE 
		_CRT_SECURE_NO_WARNINGS 
		_BAKE_PLATFORM_WINDOWS
	)
	target_link_libraries(BakeEngine PRIVATE
		glfw
		glm::glm-header-only
		Vulkan::Vulkan
		GPUOpen::VulkanMemoryAllocator
	)
elseif(LINUX)
	target_compile_definitions(BakeEngine PRIVATE _BAKE_PLATFORM_LINUX)
	target_link_libraries(BakeEngine PRIVATE
		glfw
		glm::glm-header-only
		Vulkan::Vulkan
		GPUOpen::VulkanMemoryAllocator
	)
endif()