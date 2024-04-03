//
// Created by vitalii on 3/16/24.
//
#pragma once
#include <string>
#include "filters/BaseFilter.h"

class Parser {
private:
    std::string input_file_;
    std::string output_file_;
    std::vector<FilterDescriptor> filter_descriptors_;

public:
    Parser(int argc, char** argv) {
        // Всё равно надо учесть вариант, когда аргументов <= 1
        if (argc <= 2) {
            throw std::runtime_error("Недостаточно аргументов для правильной работы парсера.\n");
        }
        int64_t arg_count = 1;
        for (auto** parstr = argv + 1; *parstr != argv[argc]; ++parstr) {
            std::string tmp;
            for (auto c = *parstr; *c != '\0'; ++c) {
                tmp.push_back(*c);
            }
            if (arg_count == 1) {
                input_file_ = tmp;
            } else if (arg_count == 2) {
                output_file_ = tmp;
            } else if (tmp[0] == '-') {
                if (tmp.size() == 1) {
                    throw std::runtime_error(
                        "Ошибка. Нельзя передать пустой ('-') аргумент. Со списком аргументов можно ознакомиться в "
                        "справке (вызовите приложение без параметров).");
                }
                filter_descriptors_.push_back({.name = tmp.substr(1, tmp.size())});
            } else {
                if (filter_descriptors_.empty()) {
                    throw std::runtime_error(
                        "Ошибка. Параметры аргументов должны идти после имени аргумента. Вызовите справку для "
                        "прояснения (вызовите приложение без параметров).");
                }
                try {  // TODO: принимать только неотрицательные?
                    filter_descriptors_.back().params.push_back(std::stod(tmp));
                } catch (std::invalid_argument& ie) {
                    throw std::runtime_error(
                        "Все параметры аргументов должны быть числами (целыми или действительными - уточните для "
                        "конкретного фильтра по вызову справки (запустите приложение без параметров))");
                }
            }
            ++arg_count;
        }
    }
    std::string& GetInputFile() {
        return input_file_;
    }
    std::string& GetOutputFile() {
        return output_file_;
    }
    std::vector<FilterDescriptor>& GetFilterDescriptors() {
        return filter_descriptors_;
    }
};