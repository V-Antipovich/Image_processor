//
// Created by vitalii on 3/29/24.
//
#include "CropFilter.h"

CropFilter::CropFilter(uint64_t new_width, uint64_t new_height) : new_width_(new_width), new_height_(new_height) {
}

void CropFilter::UseFilter(Image& img) {
    uint64_t w = std::min(img.GetWidth(), new_width_);
    uint64_t h = std::min(img.GetHeight(), new_height_);
    img.SetHeight(h);
    img.SetWidth(w);
}