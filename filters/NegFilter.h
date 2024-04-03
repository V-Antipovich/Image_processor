#pragma once
#include "BaseFilter.h"
//
// Created by vitalii on 3/27/24.
//
class NegFilter : public BaseFilter {
public:
    void UseFilter(Image& img) override;
};