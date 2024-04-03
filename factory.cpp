//
// Created by vitalii on 3/29/24.
//
#include "factory.h"

BaseFilter* CreateNegFilter(FilterDescriptor& f) {
    if (!f.params.empty()) {
        throw std::runtime_error("Фильтр -neg не принимает параметры.\n");
    }
    return new NegFilter();
}

BaseFilter* CreateCropFilter(FilterDescriptor& f) {
    if (f.params.size() != 2) {
        throw std::runtime_error(
            "Фильтр -crop принимает ровно два положительных целых аргументы: новые ширина и высота "
            "картинки.\n");
    }
    uint64_t new_width = static_cast<uint64_t>(f.params[0]);
    uint64_t new_height = static_cast<uint64_t>(f.params[1]);
    return new CropFilter(new_width, new_height);
}

BaseFilter* CreateGrayScaleFilter(FilterDescriptor& f) {
    if (!f.params.empty()) {
        throw std::runtime_error("Фильтр -gs не принимает параметры.\n");
    }
    return new GrayScaleFilter();
}

BaseFilter* CreateSharpFilter(FilterDescriptor& f) {
    if (!f.params.empty()) {
        throw std::runtime_error("Фильтр -sharp не принимает параметры.\n");
    }
    return new SharpFilter();
}

BaseFilter* CreateEdgeFilter(FilterDescriptor& f) {
    if (f.params.size() != 1) {
        throw std::runtime_error("-edge принимает ровно один действительный аргумент: пороговое значение.\n");
    }
    return new EdgeDetectionFilter(f.params[0]);
}

BaseFilter* CreateGaussianBlurFilter(FilterDescriptor& f) {
    if (f.params.size() != 1 or (!f.params.empty() && f.params[0] < 0)) {
        throw std::runtime_error(
            "-blur принимает ровно один действительный неотрицательный аргумент: среднеквадратическое "
            "отклонение.\n");
    }
    return new GaussianBlurFilter(f.params[0]);
}

BaseFilter* CreateGlassDistortionFilter(FilterDescriptor& f) {
    if (!f.params.empty()) {
        throw std::runtime_error("Фильтр -glass не принимает параметры.\n");
    }
    return new GlassDistortionFilter();
}

std::unordered_map<std::string, std::function<BaseFilter*(FilterDescriptor&)>> CreateMap() {
    std::unordered_map<std::string, std::function<BaseFilter*(FilterDescriptor&)>> function_map;
    function_map["crop"] = CreateCropFilter;
    function_map["neg"] = CreateNegFilter;
    function_map["gs"] = CreateGrayScaleFilter;
    function_map["sharp"] = CreateSharpFilter;
    function_map["edge"] = CreateEdgeFilter;
    function_map["blur"] = CreateGaussianBlurFilter;
    function_map["glass"] = CreateGlassDistortionFilter;
    return function_map;
}