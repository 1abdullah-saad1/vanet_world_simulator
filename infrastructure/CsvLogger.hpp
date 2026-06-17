#pragma once

#include <string>

namespace vanet {

class CsvLogger {
public:
    void writeLine(const std::string& line, const std::string& path) const;
};

}  // namespace vanet
