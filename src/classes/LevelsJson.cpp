#pragma once

#include <Geode/Geode.hpp>
#include <fstream>
#include <thread>
#include <chrono>

#include <filesystem>

#include "include/json.hpp"

using namespace geode::prelude;
using json = nlohmann::json;

class LevelsJson {
public:
    void processLevels(const std::vector<std::string>& levelObjects, int userId) {
        // Vector to store levels as tuples of (levelID, likes)
        std::vector<std::tuple<int, int>> levels;

        for (const auto& levelObject : levelObjects) {
            auto keyValuePairs = split(levelObject, ":");
            int levelId = 0;
            int likes = 0;

            try {
                // Iterate through the key-value pairs
                for (size_t i = 0; i < keyValuePairs.size(); i += 2) {
                    if (i + 1 < keyValuePairs.size()) {
                        int key = std::stoi(keyValuePairs[i]);
                        if (key == 1) {
                            levelId = std::stoi(keyValuePairs[i + 1]); // Key 1: Level ID
                        } else if (key == 14) {
                            likes = std::stoi(keyValuePairs[i + 1]); // Key 14: Likes
                        }
                    }
                }

                if (levelId != 0) { // Ensure valid levelId was found
                    levels.emplace_back(levelId, likes);
                } else {
                    log::info("Missing Level ID in data: {}", levelObject);
                }

            } catch (const std::exception& e) {
                log::info("Error processing level: {}. Exception: {}", levelObject, e.what());
            }
        }

        log::info("Processed levels: {}", levels);

        // Save levels to JSON
        saveLevelsToJSON(levels, userId);
    }

    int findMaxLikes() {
        int maxLikes = 0; // Initialize with the smallest possible value

        // Get the correct path to the mod's resources directory
        auto resourcesDir = Mod::get()->getResourcesDir();
        auto jsonFilePath = resourcesDir / "levels_data.json";

        // Retrieve the user ID
        int userId = GameManager::sharedState()->m_playerUserID;
        std::string userIdStr = std::to_string(userId);

        // Check if the JSON file exists
        if (!std::filesystem::exists(jsonFilePath)) {
            log::error("[Icon Progression]: JSON file not found at {}", jsonFilePath.string());
            return maxLikes; // Return default maxLikes if file is missing
        }

        try {
            // Load JSON data
            json jsonData;
            std::ifstream inputFile(jsonFilePath);
            if (inputFile.is_open()) {
                inputFile >> jsonData;
                inputFile.close();
            } else {
                log::error("[Icon Progression]: Unable to open JSON file at {}", jsonFilePath.string());
                return maxLikes;
            }

            // Check if the user ID exists in the JSON
            if (jsonData.contains(userIdStr)) {
                const auto& userLevels = jsonData[userIdStr];
                if (userLevels.is_object()) {
                    // Iterate through the user's levels to find the maximum likes
                    for (const auto& [levelId, likes] : userLevels.items()) {
                        if (likes.is_number_integer()) { // Ensure the likes value is an integer
                            maxLikes = std::max(maxLikes, likes.get<int>());
                        }
                    }
                }
            } else {
                log::info("[Icon Progression]: User ID {} not found in JSON data.", userId);
            }

            log::info("Maximum likes found for user {}: {}", userId, maxLikes);
        } catch (const std::exception& e) {
            log::error("[Icon Progression]: Error reading or parsing JSON file: {}. Exception: {}", jsonFilePath.string(), e.what());
        }

        return maxLikes;
    }

private:
    void saveLevelsToJSON(const std::vector<std::tuple<int, int>>& levels, int userId) {
        // Get the correct path to the mod's resources directory
        auto resourcesDir = Mod::get()->getResourcesDir();
        auto jsonFilePath = resourcesDir / "levels_data.json";

        // Ensure the resources directory exists
        try {
            if (!std::filesystem::exists(resourcesDir)) {
                std::filesystem::create_directories(resourcesDir);
                log::info("[Icon Progression]: Resources directory created at {}", resourcesDir.string());
            }
        } catch (const std::exception& e) {
            log::error("[Icon Progression]: Failed to create resources directory: {}. Exception: {}", resourcesDir.string(), e.what());
            return; // Exit early if we cannot ensure the directory exists
        }

        json jsonData;

        // Load existing JSON data if the file exists
        try {
            std::ifstream inputFile(jsonFilePath);
            if (inputFile.is_open()) {
                inputFile >> jsonData;
                inputFile.close();
            } else {
                log::info("[Icon Progression]: No existing JSON file found. A new file will be created.");
            }
        } catch (const std::exception& e) {
            log::error("[Icon Progression]: Error reading JSON file: {}. Exception: {}", jsonFilePath.string(), e.what());
        }

        // Retrieve the user ID
        //int userId = GameManager::sharedState()->m_playerUserID;
        //int userId = 36314;
        std::string userIdStr = std::to_string(userId);

        // Ensure the userId key exists in the JSON object, without overwriting any existing data
        if (!jsonData.contains(userIdStr)) {
            jsonData[userIdStr] = json::object(); // Create a new key for this userId
        }

        // Update JSON data for the userId with the new levels
        for (const auto& level : levels) {
            int levelId = std::get<0>(level);
            int likes = std::get<1>(level);

            // Add or update the likes for the levelId under this userId
            jsonData[userIdStr][std::to_string(levelId)] = likes;
        }

        // Save updated JSON data
        try {
            std::ofstream outputFile(jsonFilePath);
            if (!outputFile.is_open()) {
                throw std::ios_base::failure("Unable to open file for writing.");
            }
            outputFile << jsonData.dump(4); // Pretty print with 4 spaces
            outputFile.close();
            log::info("[Icon Progression]: JSON data successfully saved to {}", jsonFilePath.string());
        } catch (const std::exception& e) {
            log::error("[Icon Progression]: Error writing to JSON file: {}. Exception: {}", jsonFilePath.string(), e.what());
        }
    }

    std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0, end;
        while ((end = str.find(delimiter, start)) != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
        }
        tokens.push_back(str.substr(start));
        return tokens;
    }
};
