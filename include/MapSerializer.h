#pragma once
#pragma once
#include "Map.h"
#include <string>

class MapSerializer {
public:
    static void saveMapToJson(const Map& map, const std::string& filename);
};