//
// Created by Antares on 2022/5/27.
//

#ifndef STUDENTMANAGER_FILEMAPPER_HPP
#define STUDENTMANAGER_FILEMAPPER_HPP

#include <fstream>
#include <list>
#include <string>
#include <vector>

class FileMapper {
    using LineList = std::vector<std::string>;

   public:
    static std::string FILE_DIR;

   private:
    static LineList split(const std::string &str,
                          const std::string &delimiter = ",") {
        LineList result;
        size_t start = 0;
        size_t end = str.find(delimiter);
        while (end != -1) {
            result.push_back(str.substr(start, end - start));
            start = end + delimiter.size();
            end = str.find(delimiter, start);
        }
        result.push_back(str.substr(start));
        return result;
    }

    static std::string join(LineList &line,
                            const std::string &delimiter = ",") {
        bool flag = false;
        std::string result;
        for (auto &item : line) {
            if (flag) result += ",";
            result += item;
            flag = true;
        }
        return result;
    }

   public:
    static std::unique_ptr<std::list<LineList>> readFile(
        const std::string &filename) {
        if (!FILE_DIR.empty() && FILE_DIR.back() != '/') FILE_DIR += '/';
        std::ifstream ifs(FILE_DIR + filename + ".csv");
        std::unique_ptr<std::list<LineList>> result(new std::list<LineList>);
        if (!ifs.is_open()) return result;
        while (!ifs.eof()) {
            std::string line;
            std::getline(ifs, line);
            if (line.empty()) continue;
            result->push_back(split(line));
        }
        ifs.close();
        return result;
    }

    static void writeFile(const std::string &filename,
                          std::list<LineList> &data) {
        if (!FILE_DIR.empty() && FILE_DIR.back() != '/') FILE_DIR += '/';
        std::ofstream ofs(FILE_DIR + filename + ".csv");
        for (auto &line : data) {
            ofs << join(line) << "\n";
        }
        ofs.flush();
        ofs.close();
    }
};

std::string FileMapper::FILE_DIR;

#endif  // STUDENTMANAGER_FILEMAPPER_HPP
