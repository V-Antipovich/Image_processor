#pragma once
#include <cstdint>
#include <string>
#include <istream>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
#include "ColorPixel.h"
//
// Created by vitalii on 3/16/24.
//
class Image {
private:
    uint64_t height_ = 0;
    uint64_t width_ = 0;
    std::vector<ColorPixel> pixels_array_;
    std::vector<std::vector<ColorPixel>> pixels_matrix_;
    const uint64_t shift_eight_ = 8;
    const uint64_t shift_sixteen_ = 16;
    const uint64_t shift_twenty_four_ = 24;
    const uint64_t twenty_four_ = 24;
    const uint64_t five_ = 5;
    const uint64_t six_ = 6;
    const uint64_t seven_ = 7;
    const uint64_t eight_ = 8;
    const uint64_t nine_ = 9;
    const uint64_t ten_ = 10;
    const uint64_t eleven_ = 11;
    const double norm_coef_ = 255.0;

    void SyncMatrixWithArray();

    void SyncArrayWithMatrix();

    void ShrinkHeight();

    void ShrinkWidth();

public:
    Image();
    Image(uint64_t width, uint64_t height);
    uint64_t GetHeight() const;

    uint64_t GetWidth() const;

    void SetHeight(uint64_t new_height);

    void SetWidth(uint64_t new_width);

    void SetColorPixel(double blue, double green, double red, uint64_t width, uint64_t height);

    void SetColorPixel(ColorPixel pxl, uint64_t width, uint64_t height);

    const ColorPixel GetColorPixel(const uint64_t x, const uint64_t y);

    uint64_t GetPadding() const;

    std::vector<std::vector<ColorPixel>> GetMatrixCopy();

    void UpdatePixels(std::vector<std::vector<ColorPixel>>& new_matrix);

    ColorPixel Shift(uint64_t x, uint64_t y);

    std::vector<std::vector<ColorPixel>> GetSurrounding(uint64_t x, uint64_t y);

    void Import(const std::string& path);

    void Export(const std::string& path);
};