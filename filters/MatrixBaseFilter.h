//
// Created by vitalii on 3/29/24.
//
#pragma once
#include "BaseFilter.h"
class MatrixBaseFilter : public BaseFilter {
protected:
    std::vector<std::vector<double>> matrix_ = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};

    void ApplyMatrix(Image& img);
};