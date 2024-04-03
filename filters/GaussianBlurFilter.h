//
// Created by vitalii on 3/27/24.
//
#pragma once
#include "BaseFilter.h"

class GaussianBlurFilter : public BaseFilter {
private:
    double sigma_sq_2_ = 0.0;
    double inv_sqrt_2pi_sigma_sq_ = 0.0;
    const double core_coef_ = 6;
    int64_t core_size_ = 0;
    int64_t core_center_idx_ = 0;

    double ExpComponent(int64_t x) const;

    std::vector<double> GetHorizontalCore();

    std::vector<std::vector<double>> GetVerticalCore(std::vector<double>& hor_core) const;

public:
    explicit GaussianBlurFilter(double sigma);

    void ApplyHorizontalCore(Image& img, std::vector<double>& core) const;

    void ApplyVerticalCore(Image& img, std::vector<std::vector<double>>& core) const;

    void UseFilter(Image& img) override;
};