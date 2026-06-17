#include "infrastructure/CsvLogger.hpp"

#include <fstream>

namespace vanet {

void CsvLogger::writeLine(const std::string& line, const std::string& path) const {
    std::ofstream output(path, std::ios::app);
    output << line << '\n';
}

}  // namespace vanet
