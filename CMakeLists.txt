cmake_minimum_required(VERSION 3.0)
project(ITKMemoryContiguity)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(ITKMemory ITKMemory.cxx)
target_link_libraries(ITKMemory ${ITK_LIBRARIES})

add_executable(ITKVectorImage ITKVectorImage.cxx)
target_link_libraries(ITKVectorImage ${ITK_LIBRARIES})

add_executable(ITKRGBRGBA ITKRGBRGBA.cxx)
target_link_libraries(ITKRGBRGBA ${ITK_LIBRARIES})
