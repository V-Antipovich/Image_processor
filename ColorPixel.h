//
// Created by vitalii on 3/29/24.
//
#pragma once
#include <algorithm>
class ColorPixel {
public:
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;

    void Normalize();

    ColorPixel();

    ColorPixel(double r, double g, double b);

    bool operator==(const ColorPixel& pxl) const;
};