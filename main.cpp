#include <iostream>

#include "Application.hpp"
#include "FileMapper.hpp"

int main(const int argc, const char *argv[]) {
    if (argc > 1) {
        FileMapper::FILE_DIR = argv[1];
    }
    std::unique_ptr<Application> app(new Application());
    app->start();
    return 0;
}
