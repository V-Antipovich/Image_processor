//
// Created by vitalii on 3/29/24.
//
#include "MatrixBaseFilter.h"

void MatrixBaseFilter::ApplyMatrix(Image& img) {
    uint64_t h = img.GetHeight();
    uint64_t w = img.GetWidth();
    std::vector<std::vector<ColorPixel>> new_matrix = img.GetMatrixCopy();
    for (uint64_t y = 0; y < h; ++y) {
        for (uint64_t x = 0; x < w; ++x) {
            std::vector<std::vector<ColorPixel>> surrounding = img.GetSurrounding(x, y);
            double red = 0.0;
            double green = 0.0;
            double blue = 0.0;
            for (uint64_t i = 0; i < 3; ++i) {
                for (uint64_t j = 0; j < 3; ++j) {
                    red += surrounding[i][j].red * matrix_[i][j];
                    green += surrounding[i][j].green * matrix_[i][j];
                    blue += surrounding[i][j].blue * matrix_[i][j];
                }
            }
            new_matrix[y][x] = ColorPixel(red, green, blue);
        }
    }
    img.UpdatePixels(new_matrix);
}