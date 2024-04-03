//
// Created by vitalii on 3/29/24.
//
#include "image.h"
void Image::SyncMatrixWithArray() {
    // Вызывать только после импорта: пиксели должны быть перевернуты
    pixels_matrix_ = std::vector(height_, std::vector<ColorPixel>(width_));
    for (uint64_t y = 0; y < height_; ++y) {
        for (uint64_t x = 0; x < width_; ++x) {
            pixels_matrix_[y][x] = pixels_array_[y * width_ + x];
        }
    }
    std::reverse(pixels_matrix_.begin(), pixels_matrix_.end());
}

void Image::SyncArrayWithMatrix() {
    // Вызывать только перед экспортом, потому что ее надо переворачивать
    std::reverse(pixels_matrix_.begin(), pixels_matrix_.end());

    pixels_array_.resize(width_ * height_);
    for (uint64_t y = 0; y < height_; ++y) {
        for (uint64_t x = 0; x < width_; ++x) {
            pixels_array_[y * width_ + x] = pixels_matrix_[y][x];
        }
    }
}
void Image::ShrinkHeight() {
    pixels_matrix_.resize(height_);
}
void Image::ShrinkWidth() {
    for (uint64_t i = 0; i < height_; ++i) {
        pixels_matrix_[i].resize(width_);
    }
}
Image::Image() {
}

Image::Image(uint64_t width, uint64_t height)
    : height_(height), width_(width), pixels_array_(std::vector<ColorPixel>(width * height)) {
    pixels_matrix_ = std::vector<std::vector<ColorPixel>>(height, std::vector<ColorPixel>(width));
}
uint64_t Image::GetHeight() const {
    return height_;
}
uint64_t Image::GetWidth() const {
    return width_;
}
void Image::SetHeight(uint64_t new_height) {
    height_ = new_height;
    ShrinkHeight();
}
void Image::SetWidth(uint64_t new_width) {
    width_ = new_width;
    ShrinkWidth();
}
void Image::SetColorPixel(double blue, double green, double red, uint64_t width, uint64_t height) {
    pixels_matrix_[height][width].green = green;
    pixels_matrix_[height][width].blue = blue;
    pixels_matrix_[height][width].red = red;
}
void Image::SetColorPixel(ColorPixel pxl, uint64_t width, uint64_t height) {
    pixels_matrix_[height][width] = pxl;
}
const ColorPixel Image::GetColorPixel(const uint64_t x, const uint64_t y) {
    return pixels_matrix_[y][x];
}
uint64_t Image::GetPadding() const {
    return (4 - (width_ * 3) % 4) % 4;
}
std::vector<std::vector<ColorPixel>> Image::GetMatrixCopy() {
    return pixels_matrix_;
}
void Image::UpdatePixels(std::vector<std::vector<ColorPixel>>& new_matrix) {
    if (new_matrix.size() != height_ && new_matrix[0].size() != width_) {
        throw std::runtime_error("Картинку можно обновить только матрицей тех же размеров, что и она сама.");
    }
    for (uint64_t y = 0; y < height_; ++y) {
        for (uint64_t x = 0; x < width_; ++x) {
            SetColorPixel(new_matrix[y][x], x, y);
        }
    }
}
ColorPixel Image::Shift(uint64_t x, uint64_t y) {
    return GetColorPixel(std::min(width_ - 1, std::max(static_cast<uint64_t>(0), x)),
                         std::min(height_ - 1, std::max(static_cast<uint64_t>(0), y)));
}
std::vector<std::vector<ColorPixel>> Image::GetSurrounding(uint64_t x, uint64_t y) {
    //    std::vector<std::vector<ColorPixel>> surrounding = {{Shift(x - 1, y - 1), Shift(x, y - 1), Shift(x - 1, y +
    //    1)},
    //    {Shift(x, y - 1), Shift(x, y), Shift(x, y + 1)},
    //    {Shift(x + 1, y - 1), Shift(x + 1, y), Shift(x + 1, y + 1)}};
    std::vector<std::vector<ColorPixel>> surrounding;
    if (x == 0) {
        if (y == 0) {
            surrounding = {{GetColorPixel(x, y), GetColorPixel(x, y), GetColorPixel(x + 1, y)},
                           {GetColorPixel(x, y), GetColorPixel(x, y), GetColorPixel(x + 1, y)},
                           {GetColorPixel(x, y + 1), GetColorPixel(x, y + 1), GetColorPixel(x + 1, y + 1)}};
        } else if (y == height_ - 1) {
            surrounding = {{GetColorPixel(x, y - 1), GetColorPixel(x, y - 1), GetColorPixel(x + 1, y - 1)},
                           {GetColorPixel(x, y), GetColorPixel(x, y), GetColorPixel(x + 1, y)},
                           {GetColorPixel(x, y), GetColorPixel(x, y), GetColorPixel(x + 1, y)}};
        } else {
            surrounding = {{GetColorPixel(x, y - 1), GetColorPixel(x, y - 1), GetColorPixel(x + 1, y - 1)},
                           {GetColorPixel(x, y), GetColorPixel(x, y), GetColorPixel(x + 1, y)},
                           {GetColorPixel(x, y + 1), GetColorPixel(x, y + 1), GetColorPixel(x + 1, y + 1)}};
        }
    } else if (x == width_ - 1) {
        if (y == 0) {
            surrounding = {{GetColorPixel(x - 1, y), GetColorPixel(x, y), GetColorPixel(x, y)},
                           {GetColorPixel(x - 1, y), GetColorPixel(x, y), GetColorPixel(x, y)},
                           {GetColorPixel(x - 1, y + 1), GetColorPixel(x, y + 1), GetColorPixel(x, y + 1)}};
        } else if (y == height_ - 1) {
            surrounding = {{GetColorPixel(x - 1, y - 1), GetColorPixel(x, y - 1), GetColorPixel(x, y - 1)},
                           {GetColorPixel(x - 1, y), GetColorPixel(x, y), GetColorPixel(x, y)},
                           {GetColorPixel(x - 1, y), GetColorPixel(x, y), GetColorPixel(x, y)}};
        } else {
            surrounding = {{GetColorPixel(x - 1, y - 1), GetColorPixel(x, y - 1), GetColorPixel(x, y - 1)},
                           {GetColorPixel(x - 1, y), GetColorPixel(x, y), GetColorPixel(x, y)},
                           {GetColorPixel(x - 1, y + 1), GetColorPixel(x, y + 1), GetColorPixel(x, y + 1)}};
        }
    } else {
        if (y == 0) {
            surrounding = {{GetColorPixel(x - 1, y), GetColorPixel(x, y), GetColorPixel(x + 1, y)},
                           {GetColorPixel(x - 1, y), GetColorPixel(x, y), GetColorPixel(x + 1, y)},
                           {GetColorPixel(x - 1, y + 1), GetColorPixel(x, y + 1), GetColorPixel(x + 1, y + 1)}};
        } else if (y == height_ - 1) {
            surrounding = {{GetColorPixel(x - 1, y - 1), GetColorPixel(x, y - 1), GetColorPixel(x + 1, y - 1)},
                           {GetColorPixel(x - 1, y), GetColorPixel(x, y), GetColorPixel(x + 1, y)},
                           {GetColorPixel(x - 1, y), GetColorPixel(x, y), GetColorPixel(x + 1, y)}};
        } else {
            surrounding = {{GetColorPixel(x - 1, y - 1), GetColorPixel(x, y - 1), GetColorPixel(x + 1, y - 1)},
                           {GetColorPixel(x - 1, y), GetColorPixel(x, y), GetColorPixel(x + 1, y)},
                           {GetColorPixel(x - 1, y + 1), GetColorPixel(x, y + 1), GetColorPixel(x + 1, y + 1)}};
        }
    }

    /*
        {{Shift(x - 1, y - 1), Shift(x, y - 1), Shift(x + 1, y - 1)},
        {Shift(x - 1, y), Shift(x, y), Shift(x + 1, y)},
        {Shift(x - 1, y + 1), Shift(x, y + 1), Shift(x + 1, y + 1)}}
     */
    return surrounding;
}
void Image::Import(const std::string& path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error("Невозможно открыть входной файл. Проверьте правильность указанного пути.\n");
    }
    // Сколько зарезервировано под Header
    const uint64_t file_header_size = 14;
    // Сколько зарезервировано под InfoHeader
    const uint64_t information_header_size = 40;

    unsigned char file_header[file_header_size];
    f.read(reinterpret_cast<char*>(file_header), file_header_size);

    if (file_header[0] != 'B' or file_header[1] != 'M') {
        f.close();
        throw std::runtime_error(
            "Данное приложение умеет считывать только 24-битные файлы BMP без сжатия и таблицы цветов.\n"
            "Тип DIB Header - INFOHEADER\n");
    }

    unsigned char information_header[information_header_size];
    f.read(reinterpret_cast<char*>(information_header), information_header_size);

    width_ = information_header[4] + (information_header[five_] << shift_eight_) +
             (information_header[six_] << shift_sixteen_) + (information_header[seven_] << shift_twenty_four_);
    height_ = information_header[eight_] + (information_header[nine_] << shift_eight_) +
              (information_header[ten_] << shift_sixteen_) + (information_header[eleven_] << shift_twenty_four_);
    pixels_array_.resize(width_ * height_);

    const uint64_t padding_amount = this->GetPadding();
    for (uint64_t y = 0; y < height_; ++y) {
        for (uint64_t x = 0; x < width_; ++x) {
            unsigned char color[3];
            f.read(reinterpret_cast<char*>(color), 3);
            auto idx = y * width_ + x;
            pixels_array_[idx].blue = static_cast<double>(color[0]) / norm_coef_;
            pixels_array_[idx].green = static_cast<double>(color[1]) / norm_coef_;
            pixels_array_[idx].red = static_cast<double>(color[2]) / norm_coef_;
        }
        f.ignore(static_cast<std::streamsize>(padding_amount));
    }
    f.close();
    // Все операции для удобства будут производиться с таблицей, а не одномерным массивом
    SyncMatrixWithArray();
}

void Image::Export(const std::string& path) {
    // Все изменения над матрицей отразим в одномерном массиве, который и будет записан в BMP
    SyncArrayWithMatrix();
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error("Не получается считать выходной файл. Проверьте правильность ввода пути.\n");
    }
    unsigned char bm_pad[3] = {0, 0, 0};
    // Отступ
    const uint64_t padding_amount = this->GetPadding();

    // Сколько зарезервировано под Header
    const uint64_t file_header_size = 14;
    // Сколько зарезервировано под InfoHeader
    const uint64_t information_header_size = 40;

    const uint64_t file_size =
        file_header_size + information_header_size + width_ * height_ * 3 + padding_amount * height_;

    unsigned char file_header[file_header_size] = {'B',
                                                   'M',
                                                   static_cast<unsigned char>(file_size),
                                                   static_cast<unsigned char>(file_size >> shift_eight_),
                                                   static_cast<unsigned char>(file_size >> shift_sixteen_),
                                                   static_cast<unsigned char>(file_size >> shift_twenty_four_),
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   file_header_size + information_header_size,
                                                   0,
                                                   0,
                                                   0};
    unsigned char information_header[information_header_size] = {
        information_header_size,
        0,
        0,
        0,
        static_cast<unsigned char>(width_),
        static_cast<unsigned char>(width_ >> shift_eight_),
        static_cast<unsigned char>(width_ >> shift_sixteen_),
        static_cast<unsigned char>(width_ >> shift_twenty_four_),
        static_cast<unsigned char>(height_),
        static_cast<unsigned char>(height_ >> shift_eight_),
        static_cast<unsigned char>(height_ >> shift_sixteen_),
        static_cast<unsigned char>(height_ >> shift_twenty_four_),
        1,
        0,
        static_cast<unsigned char>(twenty_four_),
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };
    // Заполняем заголовки
    f.write(reinterpret_cast<char*>(file_header), file_header_size);
    f.write(reinterpret_cast<char*>(information_header), information_header_size);
    // Заполняем матрицу битов
    for (uint64_t y = 0; y < height_; ++y) {
        for (uint64_t x = 0; x < width_; ++x) {
            ColorPixel current_pixel = GetColorPixel(x, y);

            unsigned char r = static_cast<unsigned char>(current_pixel.red * norm_coef_);
            unsigned char g = static_cast<unsigned char>(current_pixel.green * norm_coef_);
            unsigned char b = static_cast<unsigned char>(current_pixel.blue * norm_coef_);

            unsigned char color[] = {b, g, r};

            f.write(reinterpret_cast<char*>(color), 3);
        }
        // Докидываем отступы
        f.write(reinterpret_cast<char*>(bm_pad), static_cast<std::streamsize>(padding_amount));
    }
    f.close();
}