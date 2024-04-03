//
// Created by vitalii on 3/27/24.
//
#pragma once
#include "MatrixBaseFilter.h"

class SharpFilter : public MatrixBaseFilter {
private:
    const double five_ = 5.0;

public:
    SharpFilter();

    void UseFilter(Image& img) override;
};
