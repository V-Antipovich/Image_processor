//
// Created by vitalii on 3/29/24.
//
#include "GlassDistortionFilter.h"

double GlassDistortionFilter::GetRandom(uint64_t ix, uint64_t iy) const {
    ix *= mul_a_;
    iy ^= (ix << s_) | (ix >> (w_ - s_));
    iy *= mul_b_;
    ix ^= (iy << s_) | (iy >> (w_ - s_));
    ix *= mul_a2_;
    return static_cast<double>(ix) * (M_PI / ~(~0u >> 1));
}

VectorR2 GlassDistortionFilter::RandomGradient(uint64_t ix, uint64_t iy) {
    double rnd = GetRandom(ix, iy);
    VectorR2 v;
    v.x = std::sin(rnd);
    v.y = std::cos(rnd);
    return v;
}

double GlassDistortionFilter::DotGridGradient(uint64_t ix, uint64_t iy, double x, double y) {
    // Gradient
    VectorR2 gr = RandomGradient(ix, iy);
    // Lengths
    double dx = x - static_cast<double>(ix);
    double dy = y - static_cast<double>(iy);
    return dx * gr.x + dy * gr.y;
}

double GlassDistortionFilter::Interpolate(double a0, double a1, double w) const {
    return (a1 - a0) * (coef3_ - w * coef2_) * pow(w, 2) + a0;
}

double GlassDistortionFilter::GetPerlin(double x, double y) {
    uint64_t x0 = static_cast<uint64_t>(x);
    uint64_t y0 = static_cast<uint64_t>(y);
    uint64_t x1 = x0 + 1;
    uint64_t y1 = y0 + 1;
    // Interpolation weights
    double int_sx = x - static_cast<float>(x0);
    double int_sy = y - static_cast<float>(y0);
    // Interpolating
    double n0 = DotGridGradient(x0, y0, x, y);
    double n1 = DotGridGradient(x1, y0, x, y);
    double ix0 = Interpolate(n0, n1, int_sx);
    double n2 = DotGridGradient(x0, y1, x, y);
    double n3 = DotGridGradient(x1, y1, x, y);
    double ix1 = Interpolate(n2, n3, int_sx);
    // returning the value itself
    return Interpolate(ix0, ix1, int_sy);
}

std::vector<std::vector<double>> GlassDistortionFilter::GetPerlinNoiseMap(Image& img) {
    uint64_t h = img.GetHeight();
    uint64_t w = img.GetWidth();
    std::vector<std::vector<double>> noisemap(h, std::vector<double>(w, 0.0));
    for (uint64_t x = 0; x < w; ++x) {
        for (uint64_t y = 0; y < h; ++y) {
            double value = 0.0;
            double freq = 1.0;
            double amp = 1.0;
            for (uint64_t i = 0; i < times_perlin_work_; ++i) {
                value +=
                    GetPerlin(static_cast<double>(x) * freq / grid_size_, static_cast<double>(y) * freq / grid_size_) *
                    amp;
                freq *= 2;
                amp /= 2;
            }
            value *= contrast_coef_;
            value = (std::min(0.0, std::max(1.0, value)) + 1.0) / 2;
            noisemap[y][x] = value;
        }
    }
    return noisemap;
}

void GlassDistortionFilter::UseFilter(Image& img) {
    uint64_t h = img.GetHeight();
    uint64_t w = img.GetWidth();
    std::vector<std::vector<double>> noisemap = GetPerlinNoiseMap(img);
    std::vector<std::vector<ColorPixel>> new_matrix = img.GetMatrixCopy();
    for (uint64_t y = 0; y < h; ++y) {
        for (uint64_t x = 0; x < w; ++x) {
            double n0 = noisemap[y][x];
            double n1 = noisemap[y][std::min(x + 1, w - 1)];
            double n2 = noisemap[std::min(y + 1, h - 1)][x];
            int64_t dx = static_cast<int64_t>(floor((n1 - n0) * displacement_radius_ + shift_));
            int64_t dy = static_cast<int64_t>(floor((n2 - n0) * displacement_radius_ + shift_));
            uint64_t sx =
                std::min(static_cast<uint64_t>(std::max(static_cast<int64_t>(x + dx), static_cast<int64_t>(0))), w - 1);
            uint64_t sy =
                std::min(static_cast<uint64_t>(std::max(static_cast<int64_t>(y + dy), static_cast<int64_t>(0))), h - 1);
            new_matrix[y][x] = img.GetColorPixel(sx, sy);
        }
    }
    img.UpdatePixels(new_matrix);
}