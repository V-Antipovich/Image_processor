//
// Created by vitalii on 3/27/24.
//
#pragma once
#include "MatrixBaseFilter.h"
#include "GrayScaleFilter.h"

class EdgeDetectionFilter : public MatrixBaseFilter {
private:
    const double four_ = 4.0;
    double threshold_;

public:
    explicit EdgeDetectionFilter(double threshold);

    void UseFilter(Image& img) override;
};