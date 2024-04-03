//
// Created by vitalii on 3/27/24.
//
#include "../../contrib/catch/catch.hpp"
#include "parser.h"
#include "image.h"
#include "factory.h"
#include "ColorPixel.h"
char** CastArgv(std::vector<std::string>& args) {
    char** argv = new char*[args.size()];
    for (uint64_t i = 0; i < args.size(); ++i) {
        argv[i] = new char[args[i].size() + 1];
        std::strcpy(argv[i], args[i].c_str());
    }
    return argv;
}

TEST_CASE("Parser") {
    std::vector<std::string> args = {"abcdef", "ghijkl"};
    char** argv = CastArgv(args);

    int argc = static_cast<int>(args.size());

    // По логике работы парсер запускается если аргументов (кроме первого) >= 2
    CHECK_THROWS(Parser(argc, argv));
    delete[] argv;

    // Распарсить только import path и export path
    std::vector<std::string> args1 = {"image_processor", "input", "output"};
    int argc1 = static_cast<int>(args1.size());
    char** argv1 = CastArgv(args1);
    Parser parser1 = Parser(argc1, argv1);
    REQUIRE("input" == parser1.GetInputFile());
    REQUIRE("output" == parser1.GetOutputFile());
    delete[] argv1;

    // Словить ошибку если первый аргумент после output не начинается с -
    std::vector<std::string> args2 = {"image_processor", "input", "output", "filtername1",  "arg11", "arg12", "arg13",
                                      "-filtername2",    "arg21", "arg22",  "-filtername3", "arg31"};
    int argc2 = static_cast<int>(args2.size());
    char** argv2 = CastArgv(args2);
    CHECK_THROWS(Parser(argc2, argv2));
    delete[] argv2;

    // Должно сработать всё правильно
    std::vector<std::string> args3 = {
        "image_processor", "input",     "output", "-filtername1", "1.0",          "111",  "1111",
        "-filtername2",    "111.11111", "0.1234", "-filtername3", "-filtername4", "0.234"};
    int argc3 = static_cast<int>(args3.size());
    char** argv3 = CastArgv(args3);
    Parser parser3 = Parser(argc3, argv3);
    REQUIRE(4 == parser3.GetFilterDescriptors().size());
    REQUIRE("filtername1" == parser3.GetFilterDescriptors()[0].name);
    REQUIRE(1.0 == parser3.GetFilterDescriptors()[0].params[0]);
    REQUIRE(111 == parser3.GetFilterDescriptors()[0].params[1]);
    REQUIRE(1111 == parser3.GetFilterDescriptors()[0].params[2]);
    REQUIRE("filtername2" == parser3.GetFilterDescriptors()[1].name);
    REQUIRE(111.11111 == parser3.GetFilterDescriptors()[1].params[0]);
    REQUIRE(0.1234 == parser3.GetFilterDescriptors()[1].params[1]);
    REQUIRE("filtername3" == parser3.GetFilterDescriptors()[2].name);
    REQUIRE(0 == parser3.GetFilterDescriptors()[2].params.size());
    REQUIRE("filtername4" == parser3.GetFilterDescriptors()[3].name);
    REQUIRE(0.234 == parser3.GetFilterDescriptors()[3].params[0]);
    delete[] argv3;
}

TEST_CASE("Image") {
    /*
     * Import and Export are actually tested by mr. Sskvor's implemented system tests
     * Plus, it would be a little problematic to implement them by myself in one day
     */

    const uint64_t h = 480;
    const uint64_t w = 640;
    Image img(w, h);
    for (uint64_t y = 0; y < h; ++y) {
        for (uint64_t x = 0; x < w; ++x) {
            double xw = static_cast<double>(x) / static_cast<double>(w);
            double yh = static_cast<double>(y) / static_cast<double>(h);
            img.SetColorPixel(xw, 1.0 - xw, yh, x, y);
        }
    }
    // Check size
    REQUIRE(h == img.GetHeight());
    REQUIRE(w == img.GetWidth());

    // Check padding
    REQUIRE(0 == img.GetPadding());

    ColorPixel white(1, 1, 1);
    ColorPixel black(0, 0, 0);
    ColorPixel red(1, 0, 0);
    ColorPixel blue(0, 0, 1);
    ColorPixel green(0, 1, 0);
    ColorPixel grey(0.501, 0.501, 0.501);
    std::vector<std::vector<ColorPixel>> new_matrix = {{white, black, green}, {red, blue, grey}};

    // Check size altering
    auto mtrx = img.GetMatrixCopy();
    img.SetWidth(300);
    img.SetHeight(300);
    REQUIRE_FALSE(480 == img.GetHeight());
    REQUIRE_FALSE(640 == img.GetWidth());

    // Check if matrix has changed after altering size
    REQUIRE_FALSE(mtrx == img.GetMatrixCopy());

    // Check if we can update the matrix with vector of another size
    // Should throw an error
    CHECK_THROWS(img.UpdatePixels(new_matrix));

    img.SetColorPixel(black, 0, 0);
    img.SetColorPixel(white, 0, 1);
    img.SetColorPixel(blue, 1, 0);
    img.SetColorPixel(red, 1, 1);
    std::vector<std::vector<ColorPixel>> corner = {{black, black, blue}, {black, black, blue}, {white, white, red}};
    REQUIRE(img.GetSurrounding(0, 0) == corner);
}

 TEST_CASE("Factory") { // TODO: factory concept should be changed
//     Factory factory;
    auto factory = CreateMap();
     // Несуществующий фильтр
     FilterDescriptor f = {"negg"};
     CHECK_THROWS(factory[f.name](f));

     //  Всё как должно быть
     FilterDescriptor negfilterdesc = {"neg"};
     CHECK_NOTHROW(factory[f.name](negfilterdesc));
     FilterDescriptor cropfilterdesc = {"crop", {100, 100}};
     CHECK_NOTHROW(factory[f.name](cropfilterdesc));
     FilterDescriptor gsfilterdesc = {"gs"};
     CHECK_NOTHROW(factory[f.name](gsfilterdesc));
     FilterDescriptor sharpfilterdesc = {"sharp"};
     CHECK_NOTHROW(factory[f.name](sharpfilterdesc));
     FilterDescriptor edgefilterdesc = {"edge", {0.1}};
     CHECK_NOTHROW(factory[f.name](edgefilterdesc));
     FilterDescriptor blurfilterdesc = {"blur", {7}};
     CHECK_NOTHROW(factory[f.name](blurfilterdesc));
     FilterDescriptor glassfilterdesc = {"glass"};
     CHECK_NOTHROW(factory[f.name](glassfilterdesc));

     // Фильтру без аргументов пихают аргументы
     FilterDescriptor gsfilterdesc2 = {"gs", {0.1}};
     CHECK_THROWS(factory[f.name](gsfilterdesc2));
     FilterDescriptor sharpfilterdesc2 = {"sharp", {0, 1, 2}};
     CHECK_THROWS(factory[f.name](sharpfilterdesc2));
     // Фильтру с аргументами пихают не то
     FilterDescriptor cropfilterdesc2 = {"crop", {}};
     CHECK_THROWS(factory[f.name](cropfilterdesc2));
     FilterDescriptor blurfilterdesc2 = {"blur", {7, 8}};
     CHECK_THROWS(factory[f.name](blurfilterdesc2));
     FilterDescriptor edgefilterdesc2 = {"edge", {0.1, 0.3, 0.4}};
     CHECK_THROWS(factory[f.name](edgefilterdesc2));
 }

TEST_CASE("Some filters") {
    /*
     * Minor checks again, because filters have been checked automatically
     * */
    const uint64_t h = 480;
    const uint64_t w = 640;
    Image img(w, h);
    NegFilter neg_filter;
    neg_filter.UseFilter(img);
    ColorPixel black = {1, 1, 1};
    for (uint64_t y = 0; y < h; ++y) {
        for (uint64_t x = 0; x < w; ++x) {
            REQUIRE(black == img.GetColorPixel(x, y));
        }
    }
    CropFilter crop_filter(300, 200);

    crop_filter.UseFilter(img);
    REQUIRE(200 == img.GetHeight());
    REQUIRE(300 == img.GetWidth());
}