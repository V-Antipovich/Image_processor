//
// Created by vitalii on 3/27/24.
//

#pragma once
#include "BaseFilter.h"
class CropFilter : public BaseFilter {
private:
    uint64_t new_width_;
    uint64_t new_height_;

public:
    CropFilter(uint64_t new_width, uint64_t new_height);

    void UseFilter(Image& img) override;
};
