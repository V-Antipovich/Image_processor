//
// Created by vitalii on 3/27/24.
//
#pragma once
#include "BaseFilter.h"
struct VectorR2 {
    double x = 0.0;
    double y = 0.0;
};

class GlassDistortionFilter : public BaseFilter {
private:
    const double displacement_radius_ = 10.0;
    const uint64_t w_ = 512;
    const uint64_t s_ = 256;
    // Random gradient coefs
    const uint64_t mul_a_ = 3284157443;
    const uint64_t mul_b_ = 1911520717;
    const uint64_t mul_a2_ = 2048419325;
    // Coficients for interpolation
    const double coef3_ = 3.0;
    const double coef2_ = 2.0;
    const uint64_t times_perlin_work_ = 12;
    const double grid_size_ = 400;
    const double contrast_coef_ = 1.2;
    const double shift_ = 5.0;

    double GetRandom(uint64_t ix, uint64_t iy) const;

    VectorR2 RandomGradient(uint64_t ix, uint64_t iy);

    double DotGridGradient(uint64_t ix, uint64_t iy, double x, double y);

    double Interpolate(double a0, double a1, double w) const;

    double GetPerlin(double x, double y);

    std::vector<std::vector<double>> GetPerlinNoiseMap(Image& img);

public:
    void UseFilter(Image& img) override;
};
