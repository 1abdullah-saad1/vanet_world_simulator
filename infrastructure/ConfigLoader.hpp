#pragma once

#include <string>

namespace vanet {

class ConfigLoader {
public:
    bool loadScenario(const std::string& path) const;
    bool loadPrototypes(const std::string& path) const;
};

}  // namespace vanet
