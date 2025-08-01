//#include "MapSerializer.h"
//#include "json.hpp"
//#include <fstream>
//
//using json = nlohmann::json;
//
//// Helper to convert entity vectors to JSON
//void entitiesToJson(json& j, const std::string& key, const std::vector<std::vector<Entity*>>& sections) {
//    j[key] = json::array();
//    for (const auto& section : sections) {
//        for (const auto& entity : section) {
//            if (entity) {
//                json entityJson;
//                entityJson["type"] = typeid(*entity).name(); // Or a more readable name
//                entityJson["position"] = { {"x", entity->getPosition().x}, {"y", entity->getPosition().y} };
//                j[key].push_back(entityJson);
//            }
//        }
//    }
//}
//
//void MapSerializer::saveMapToJson(const Map& map, const std::string& filename) {
//    json mapJson;
//
//    mapJson["width"] = map.getMapWidth();
//    mapJson["sectionWidth"] = map.getSectionWidth();
//    mapJson["startPosition"] = { {"x", map.getStartPositionForPlayer().x}, {"y", map.getStartPositionForPlayer().y} };
//
//    // Note: The const_cast is used here because the getter methods in Map are not marked as const.
//    // In a real application, it would be better to make the getter methods in Map const.
//    entitiesToJson(mapJson, "monsters", const_cast<Map&>(map).getMonstersSection());
//    entitiesToJson(mapJson, "items", const_cast<Map&>(map).getItemsSection());
//    entitiesToJson(mapJson, "blocks", const_cast<Map&>(map).getBlocksSection());
//    entitiesToJson(mapJson, "interactiveTiles", const_cast<Map&>(map).getInteractiveTilesSection());
//    entitiesToJson(mapJson, "nonInteractiveTiles", const_cast<Map&>(map).getNonInteractiveTilesSection());
//
//    std::ofstream o(filename);
//    o << std::setw(4) << mapJson << std::endl;
//}