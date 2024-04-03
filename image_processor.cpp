#include <iostream>
#include <string>
#include "parser.h"
#include "image.h"
#include "factory.h"

int main(int argc, char** argv) {
    std::string help =
        "Справка:\n"
        "Это программа для обработки изображений!\n"
        "Команда, вводящаяся в консоль, состоит из обязательный и опциональных параметров:\n"
        "{имя программы} {путь к входному файлу} {путь к выходному файлу} [-{имя фильтра 1} [параметр фильтра 1] "
        "[параметр фильтра 2] ...] [-{имя фильтра 2} [параметр фильтра 1] [параметр фильтра 2] ...] ...\n"
        "Обязательные:\n"
        "Имя программы - имя исполняемого файла. При отсутствии всех остальных аргументов выводит эту справку.\n"
        "Путь к входному файлу - путь к картинке BMP в unix-формате\n"
        "Путь к выходному файлу - путь и название файла, который должен быть получен на выходе.\n\n"
        "Данное приложение умеет считывать только 24-битные файлы BMP без сжатия и таблицы цветов. Тип DIB Header - "
        "INFOHEADER\n\n"
        "Опциональные аргументы есть цепочка из имен фильтров и их параметров. Имя должно начинаться с '-', аргументы "
        "- без него\n\n"
        "Фильтры без параметров:\n"
        "-glass: 'стекольный' фильтр (Glass Distortion)\n"
        "-gs: преобразование в оттенки серого\n"
        "-neg: преобразование в негатив\n"
        "-sharp: повышение резкости\n\n"
        "Фильтры с параметрами:\n"
        "-blur sigma: размытие изображения методом Гаусса с отклонением sigma (действительное неотрицательное число) \n"
        "-edge threshold: выделение краев - преобразование в оттенки серого, пиксели со значением больше threshold "
        "делаются белыми, все остальные - черными\n"
        "-crop width height: обрезание картинки до размеров width x height (целые положительные числа)\n\n";
    std::string call_for_help =
        "Для подробностей вызовите справку - запустите приложение без аргументов и параметров.\n";
    if (argc == 1) {
        std::cout << help << "\n";
    } else if (argc == 2) {
        std::cout << "Недостаточно аргументов для работы. Можете вызвать справку, запустив приложение вообще без "
                     "параметров.\n";
    } else {
        try {
            std::vector<std::string> args;
            for (int i = 0; i < argc; ++i) {
                args.push_back(std::string(argv[i]));
            }
            Parser parser = Parser(argc, argv);
            Image image;
            image.Import(parser.GetInputFile());
            auto mp = CreateMap();
            for (FilterDescriptor& fd : parser.GetFilterDescriptors()) {
                BaseFilter* filter = mp[fd.name](fd);
                filter->UseFilter(image);
                delete filter;
            }
            image.Export(parser.GetOutputFile());
        } catch (std::runtime_error& re) {
            std::cout << "Ошибка. " << re.what() << " " << call_for_help;
        }
    }
    return 0;
}
