//
// Created by vitalii on 3/29/24.
//
#include "ColorPixel.h"
void ColorPixel::Normalize() {
    red = std::min(1.0, std::max(0.0, red));
    green = std::min(1.0, std::max(0.0, green));
    blue = std::min(1.0, std::max(0.0, blue));
}
ColorPixel::ColorPixel() : red(0), green(0), blue(0) {
}
ColorPixel::ColorPixel(double r, double g, double b) : red(r), green(g), blue(b) {
    Normalize();
}
bool ColorPixel::operator==(const ColorPixel& pxl) const {
    return (pxl.blue == blue && pxl.green == green && pxl.red == red);
}