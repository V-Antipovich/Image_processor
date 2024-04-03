#pragma once
//
// Created by vitalii on 3/21/24.
//
#include <exception>
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
#include <vector>
#include "filters/BaseFilter.h"
#include "filters/NegFilter.h"
#include "filters/GrayScaleFilter.h"
#include "filters/SharpFilter.h"
#include "filters/CropFilter.h"
#include "filters/EdgeDetectionFilter.h"
#include "filters/GlassDistortionFilter.h"
#include "filters/GaussianBlurFilter.h"

BaseFilter* CreateNegFilter(FilterDescriptor& f);

BaseFilter* CreateCropFilter(FilterDescriptor& f);

BaseFilter* CreateGrayScaleFilter(FilterDescriptor& f);

BaseFilter* CreateSharpFilter(FilterDescriptor& f);

BaseFilter* CreateEdgeFilter(FilterDescriptor& f);

BaseFilter* CreateGaussianBlurFilter(FilterDescriptor& f);

BaseFilter* CreateGlassDistortionFilter(FilterDescriptor& f);

std::unordered_map<std::string, std::function<BaseFilter*(FilterDescriptor&)>> CreateMap();
// class Factory {
// public:
//     std::unordered_map< std::string, std::function< std::unique_ptr<BaseFilter>(const FilterDescriptor&)>>
//     GetFiltersFactory() {
//         std::unordered_map< std::string, std::function< std::unique_ptr<BaseFilter>(const FilterDescriptor&)>>
//         filters_factory = {
//             {"crop", CreateCropFilter}
//         };
//         return filters_factory;
////        filters_factory["crop"] = CreateCropFilter;
//    }
//};
// public:
//    BaseFilter* CreateFilter(FilterDescriptor& f) {
//        if (f.name == "neg") {
//            if (!f.params.empty()) {
//                throw std::runtime_error("Фильтр -neg не принимает параметры.\n");
//            }
//            return new NegFilter();
//        } else if (f.name == "crop") {
//            if (f.params.size() != 2) {
//                throw std::runtime_error(
//                    "Фильтр -crop принимает ровно два положительных целых аргументы: новые ширина и высота "
//                    "картинки.\n");
//            }
//            uint64_t new_width = static_cast<uint64_t>(f.params[0]);
//            uint64_t new_height = static_cast<uint64_t>(f.params[1]);
//            return new CropFilter(new_width, new_height);
//
//        } else if (f.name == "gs") {
//            if (!f.params.empty()) {
//                throw std::runtime_error("Фильтр -gs не принимает параметры.\n");
//            }
//            return new GrayScaleFilter();
//        } else if (f.name == "sharp") {
//            if (!f.params.empty()) {
//                throw std::runtime_error("Фильтр -sharp не принимает параметры.\n");
//            }
//            return new SharpFilter();
//        } else if (f.name == "edge") {
//            if (f.params.size() != 1) {
//                throw std::runtime_error("-edge принимает ровно один действительный аргумент: пороговое значение.\n");
//            }
//            return new EdgeDetectionFilter(f.params[0]);
//        } else if (f.name == "blur") {
//            if (f.params.size() != 1 or (!f.params.empty() && f.params[0] < 0)) {
//                throw std::runtime_error(
//                    "-blur принимает ровно один действительный неотрицательный аргумент: среднеквадратическое "
//                    "отклонение.\n");
//            }
//            return new GaussianBlurFilter(f.params[0]);
//        } else if (f.name == "glass") {
//            if (!f.params.empty()) {
//                throw std::runtime_error("Фильтр -glass не принимает параметры.\n");
//            }
//            return new GlassDistortionFilter();
//        } else {
//            throw std::runtime_error("Фильтра" + f.name + "не существует, проверьте входные данные.\n");
//        }
//    }
