//
// Created by vitalii on 3/29/24.
//
#include "GaussianBlurFilter.h"

double GaussianBlurFilter::ExpComponent(int64_t x) const {
    return exp(-pow(static_cast<double>(x), 2) * sigma_sq_2_);
}

std::vector<double> GaussianBlurFilter::GetHorizontalCore() {
    std::vector<double> core(core_size_, 0.0);
    for (int64_t i = 0; i < core_size_; ++i) {
        core[i] = inv_sqrt_2pi_sigma_sq_ * ExpComponent(llabs(i - core_center_idx_));
    }
    return core;
}

std::vector<std::vector<double>> GaussianBlurFilter::GetVerticalCore(std::vector<double>& hor_core) const {
    std::vector<std::vector<double>> core(core_size_, std::vector<double>(1, 0.0));
    for (int64_t i = 0; i < core_size_; ++i) {
        core[i][0] = hor_core[i];
    }
    return core;
}

GaussianBlurFilter::GaussianBlurFilter(double sigma) {
    sigma_sq_2_ = 1 / (2 * pow(sigma, 2));
    core_size_ = ceil(core_coef_ * sigma + 1);
    core_size_ += (1 - core_size_ % 2);  // делаем нечетным
    core_center_idx_ = (core_size_ / 2) + 1;
    inv_sqrt_2pi_sigma_sq_ = sqrt(M_1_PI * sigma_sq_2_);
}

void GaussianBlurFilter::ApplyHorizontalCore(Image& img, std::vector<double>& core) const {
    int64_t h = static_cast<int64_t>(img.GetHeight());
    int64_t w = static_cast<int64_t>(img.GetWidth());
    std::vector<std::vector<ColorPixel>> new_matrix = img.GetMatrixCopy();
    for (int64_t y = 0; y < h; ++y) {
        for (int64_t x = 0; x < w; ++x) {
            ColorPixel new_pixel;
            for (int64_t i = 0; i < core_size_; ++i) {
                int64_t dx = x + i - core_center_idx_;
                // Если смещение вылезает за границу [0, h-1], берем крайний
                int64_t take_x = std::max(static_cast<int64_t>(0), std::min(dx, w - 1));
                ColorPixel current = img.GetColorPixel(take_x, y);
                new_pixel.red += current.red * core[i];
                new_pixel.blue += current.blue * core[i];
                new_pixel.green += current.green * core[i];
            }
            new_pixel.Normalize();
            new_matrix[y][x] = new_pixel;
        }
    }
    img.UpdatePixels(new_matrix);
}

void GaussianBlurFilter::ApplyVerticalCore(Image& img, std::vector<std::vector<double>>& core) const {
    int64_t h = static_cast<int64_t>(img.GetHeight());
    int64_t w = static_cast<int64_t>(img.GetWidth());
    std::vector<std::vector<ColorPixel>> new_matrix = img.GetMatrixCopy();
    for (int64_t y = 0; y < h; ++y) {
        for (int64_t x = 0; x < w; ++x) {
            ColorPixel new_pixel;
            for (int64_t j = 0; j < core_size_; ++j) {
                int64_t dy = y + j - core_center_idx_;
                // Если смещение вылезает за границы [0, h-1], берем крайний
                int64_t take_y = std::max(static_cast<int64_t>(0), std::min(dy, h - 1));
                ColorPixel current = img.GetColorPixel(x, take_y);
                new_pixel.red += current.red * core[j][0];
                new_pixel.blue += current.blue * core[j][0];
                new_pixel.green += current.green * core[j][0];
            }
            new_pixel.Normalize();
            new_matrix[y][x] = new_pixel;
        }
    }
    img.UpdatePixels(new_matrix);
}

void GaussianBlurFilter::UseFilter(Image& img) {
    std::vector<double> hor_core = GetHorizontalCore();
    std::vector<std::vector<double>> vert_core = GetVerticalCore(hor_core);
    ApplyHorizontalCore(img, hor_core);
    ApplyVerticalCore(img, vert_core);
}