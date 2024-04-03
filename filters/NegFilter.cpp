//
// Created by vitalii on 3/29/24.
//
#include "NegFilter.h"

void NegFilter::UseFilter(Image& img) {
    for (uint64_t x = 0; x < img.GetWidth(); ++x) {
        for (uint64_t y = 0; y < img.GetHeight(); ++y) {
            ColorPixel curr = img.GetColorPixel(x, y);
            img.SetColorPixel(1 - curr.blue, 1 - curr.green, 1 - curr.red, x, y);
        }
    }
}