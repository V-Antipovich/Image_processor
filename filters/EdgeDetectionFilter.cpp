//
// Created by vitalii on 3/29/24.
//
#include "EdgeDetectionFilter.h"

EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : threshold_(threshold) {
    matrix_ = {{0.0, -1.0, 0.0}, {-1.0, four_, -1.0}, {0.0, -1.0, 0.0}};
}
void EdgeDetectionFilter::UseFilter(Image& img) {
    GrayScaleFilter grayscale;
    grayscale.UseFilter(img);
    ApplyMatrix(img);
    for (uint64_t x = 0; x < img.GetWidth(); ++x) {
        for (uint64_t y = 0; y < img.GetHeight(); ++y) {
            if (img.GetColorPixel(x, y).red > threshold_) {
                img.SetColorPixel({1, 1, 1}, x, y);
            } else {
                img.SetColorPixel({0, 0, 0}, x, y);
            }
        }
    }
}