//
// Created by vitalii on 3/29/24.
//
#include "GrayScaleFilter.h"

void GrayScaleFilter::UseFilter(Image& img) {
    for (uint64_t x = 0; x < img.GetWidth(); ++x) {
        for (uint64_t y = 0; y < img.GetHeight(); ++y) {
            ColorPixel curr = img.GetColorPixel(x, y);
            double new_col = red_coef_ * curr.red + green_coef_ * curr.green + blue_coef_ * curr.blue;
            img.SetColorPixel(new_col, new_col, new_col, x, y);
        }
    }
}