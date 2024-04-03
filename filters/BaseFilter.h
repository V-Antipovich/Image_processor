#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>
#include <cmath>
#include <algorithm>
#include "../image.h"

//
// Created by vitalii on 3/27/24.
//

struct FilterDescriptor {
    std::string name;
    std::vector<double> params;
};

class BaseFilter {
public:
    BaseFilter() {
    }
    virtual void UseFilter(Image&) {
    }
    virtual ~BaseFilter() = default;
};