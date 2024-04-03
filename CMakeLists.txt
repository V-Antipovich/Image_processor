cmake_minimum_required(VERSION 3.5)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        image_processor
        image_processor.cpp
        filters/MatrixBaseFilter.cpp
        factory.cpp
        ColorPixel.cpp
        image.cpp
        filters/EdgeDetectionFilter.cpp
        filters/GaussianBlurFilter.cpp
        filters/SharpFilter.cpp
        filters/GlassDistortionFilter.cpp
        filters/GrayScaleFilter.cpp
        filters/NegFilter.cpp
        filters/CropFilter.cpp
)
#add_catch(
#        test_image_processor test.cpp parser.h image.h
#)