#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Event.hpp>
#include <future>

using namespace geode::prelude;

class RequestCreatorPoints {
protected:
    EventListener<web::WebTask> m_listener;
	int accountId;

public:
    int makeWebRequest() {

        accountId = GJAccountManager::sharedState()->m_accountID;

        std::promise<int> promiseResult;
        std::future<int> futureResult = promiseResult.get_future();
        bool promiseSet = false;

        // Capture `this` explicitly
        m_listener.bind([this, &promiseResult, &promiseSet](web::WebTask::Event* e) {
            if (promiseSet) {
                promiseResult.set_value(-1);
                return;
            }

            if (web::WebResponse* value = e->getValue()) {
                auto str = value->string().unwrap();
                log::info("Response: {}", str);

                int creatorPoints = this->findCreatorPoints(str);
                log::info("Extracted Creator Points: {}", creatorPoints);
                promiseResult.set_value(creatorPoints);
                promiseSet = true;

            } else if (web::WebProgress* progress = e->getProgress()) {
                log::info("{}", "progress");

            } else if (e->isCancelled()) {
                log::info("{}", "fail");
                promiseResult.set_value(-1);
                promiseSet = true;
            }
        });

        auto req = web::WebRequest().userAgent("").bodyString(fmt::format("secret=Wmfd2893gb7&targetAccountID={}", accountId));
        auto task = req.post("http://www.boomlings.com/database/getGJUserInfo20.php");
        m_listener.setFilter(task);

        return futureResult.get();
    }

protected:
    int findCreatorPoints(const std::string& fullResponse) {
        int creatorPoints = 0;
        auto keyValuePairs = split(fullResponse, ":");

        try {
            for (size_t i = 0; i < keyValuePairs.size(); i += 2) {
                if (i + 1 < keyValuePairs.size()) {
                    int key = std::stoi(keyValuePairs[i]);
                    if (key == 8) { // Key 8: Creator Points
                        creatorPoints = std::stoi(keyValuePairs[i + 1]);
                        break; // Exit early once creator points are found
                    }
                }
            }
        } catch (const std::exception& e) {
            log::info("Error processing creator points: {}. Exception: {}", fullResponse, e.what());
        }

        if (creatorPoints == 0) {
            log::info("Creator points not found in data: {}", fullResponse);
        }

        return creatorPoints;
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