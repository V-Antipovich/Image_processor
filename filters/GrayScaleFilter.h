//
// Created by vitalii on 3/27/24.
//
#pragma once
#include "BaseFilter.h"
class GrayScaleFilter : public BaseFilter {
private:
    const double red_coef_ = 0.299;
    const double blue_coef_ = 0.114;
    const double green_coef_ = 0.587;

public:
    void UseFilter(Image& img) override;
};
