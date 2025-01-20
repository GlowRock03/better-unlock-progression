#pragma once

#include <Geode/Geode.hpp>
#include <fstream>
#include <thread>
#include <chrono>

#include <filesystem>

using namespace geode::prelude;

class ProcessLevelObjects {
private:

    std::vector<int> allLikes;

    std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
        log::info("Splitting string: '{}' with delimiter: '{}'", str, delimiter);
        std::vector<std::string> tokens;
        size_t start = 0, end;
        while ((end = str.find(delimiter, start)) != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
        }
        tokens.push_back(str.substr(start));
        return tokens;
    }

public:
    void processLevels(const std::vector<std::string>& levelObjects, int userId) {
        // Vector to store levels as tuples of (levelID, likes)
        std::vector<std::tuple<int, int>> levels;

        for (const auto& levelObject : levelObjects) {
            auto keyValuePairs = split(levelObject, ":");
            int levelId = 0;
            int likes = 0;

            // Iterate through the key-value pairs
            for (size_t i = 0; i < keyValuePairs.size(); i += 2) {
                if (i + 1 < keyValuePairs.size()) {
                    int key = std::stoi(keyValuePairs[i]);
                    if (key == 14) {
                        likes = std::stoi(keyValuePairs[i + 1]); // Key 14: Likes
                        break;
                    }
                }
            }
            allLikes.push_back(likes);
        }
    }

    int findMaxLikes() {

        return *max_element(allLikes.begin(), allLikes.end());
    }

    const std::vector<int>& getAllLikes() {
        return allLikes;
    }
};
