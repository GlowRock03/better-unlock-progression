#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Event.hpp>

#include "../classes/LevelsJson.cpp"

using namespace geode::prelude;

class RequestLevelsForMaxLikedLevel {
protected:
    EventListener<web::WebTask> m_listener;
    std::vector<std::string> allLevels;
	int userId;
    LevelsJson exporter;

public:
    void levelsWebRequest(int page) {
        userId = GameManager::sharedState()->m_playerUserID;

        
        auto resourcesDir = Mod::get()->getResourcesDir();
        auto jsonFilePath = resourcesDir / "levels_data.json";
        json existingLevels;

        try {
            if (std::filesystem::exists(jsonFilePath)) {
                std::ifstream inputFile(jsonFilePath);
                if (inputFile.is_open()) {
                    inputFile >> existingLevels;
                    inputFile.close();
                    log::info("[Icon Progression]: Loaded existing levels data from {}", jsonFilePath.string());
                }
            }
        } catch (const std::exception& e) {
            log::error("[Icon Progression]: Error reading JSON file: {}. Exception: {}", jsonFilePath.string(), e.what());
        }

        // Send initial request to get total levels from server
        m_listener.bind([this, page, jsonFilePath, existingLevels](web::WebTask::Event* e) mutable {
            if (web::WebResponse* value = e->getValue()) {
                auto str = value->string().unwrap();
                log::info("Response for Page {}: {}", page, str);

                if (str == "-1") {
                    log::warn("No levels found!");
                    return;
                }

                // Parse response
                auto [levels, total, offset, amount] = this->parseResponse(str);
                allLevels.insert(allLevels.end(), levels.begin(), levels.end());

                if (!existingLevels.empty()) {
                    // Retrieve the user ID
                    std::string userIdStr = std::to_string(userId);

                    // Get the correct path to the mod's resources directory
                    auto resourcesDir = Mod::get()->getResourcesDir();
                    auto jsonFilePath = resourcesDir / "levels_data.json";

                    try {
                        // Load JSON data
                        json jsonData;
                        std::ifstream inputFile(jsonFilePath);
                        if (inputFile.is_open()) {
                            inputFile >> jsonData;
                            inputFile.close();
                        }

                        // Check if the user ID exists in the JSON
                        if (jsonData.contains(userIdStr)) {
                            const auto& userLevels = jsonData[userIdStr];
                            if (userLevels.is_object() && userLevels.size() == total) {
                                log::info("[Icon Progression]: Total levels match for user {}. No further requests needed.", userId);
                                return;
                            }
                        }
                    } catch (const std::exception& e) {
                        log::error("[Icon Progression]: Error reading or parsing JSON file for levelsWebRequest: {}. Exception: {}", jsonFilePath.string(), e.what());
                    }
                }

                //LevelsJson exporter;
                exporter.processLevels(allLevels, userId);

                // Continue fetching pages if needed
                if (offset + amount < total) {
                    log::info("Fetching next page...");
                    levelsWebRequest(page + 1);
                } else {
                    log::info("All levels fetched: {}", allLevels.size());

                    if (!allLevels.empty()) {
                        int maxLikes = exporter.findMaxLikes();
                        log::info("The level with the most likes has {} likes.", maxLikes);
                    } else {
                        log::warn("No levels found to process.");
                    }
                }

            } else if (e->getProgress()) {
                log::info("Fetching page {} in progress...", page);

            } else if (e->isCancelled()) {
                log::warn("Request for page {} was cancelled.", page);
            }
        });

        // Send request for the given page
        auto req = web::WebRequest().userAgent("").bodyString(fmt::format(
            "secret=Wmfd2893gb7&type=5&page={}&str={}", page, userId));
        auto task = req.post("http://www.boomlings.com/database/getGJLevels21.php");
        m_listener.setFilter(task);
    }

protected:
    std::tuple<std::vector<std::string>, int, int, int> parseResponse(const std::string& response) {
        // Split the response into parts
        auto parts = split(response, "#");
        if (parts.size() < 4) {
            log::warn("Unexpected response format!");
            return {{}, 0, 0, 0};
        }

        // Extract levels
        auto levels = split(parts[0], "|");

        // Extract page info
        auto pageInfo = split(parts[3], ":");
        if (pageInfo.size() < 3) {
            log::warn("Invalid page info!");
            return {{}, 0, 0, 0};
        }

        int total = std::stoi(pageInfo[0]);
        int offset = std::stoi(pageInfo[1]);
        int amount = std::stoi(pageInfo[2]);

        return {levels, total, offset, amount};
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