//
// Created by vitalii on 3/29/24.
//
#include "SharpFilter.h"

SharpFilter::SharpFilter() {
    matrix_ = {{0.0, -1.0, 0.0}, {-1.0, five_, -1.0}, {0.0, -1.0, 0.0}};
}

void SharpFilter::UseFilter(Image& img) {
    ApplyMatrix(img);
}