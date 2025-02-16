#ifndef UNLOCKPAGE_HPP
#define UNLOCKPAGE_HPP

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Event.hpp>
#include <Geode/binding/GameLevelManager.hpp>
#include <Geode/binding/LevelDownloadDelegate.hpp>


#include "../basePage/BasePage.hpp"
#include "../utility/Utilities.hpp"
#include "../utility/MyLevelDownloadDelegate.hpp"

using namespace geode::prelude;

class UnlockPage : public BasePage {
private:

    int tierCount;
    int unlockCount;
    std::vector<Utilities::UnlockData*> unlockList;
    const char* iconSprName;

    CCNode* pageNode;

    EventListener<web::WebTask> mostLikedListener;
    EventListener<web::WebTask> creatorPointsListener;
    int userId;
    int accountId;
    std::vector<int> allLikes;
    
public:

    UnlockPage(FLAlertLayer* parentPopup, std::vector<Utilities::UnlockData*> unlockList, const char* iconSprName);
    ~UnlockPage();
    
    CCNode* createPage(int value) override;
    CCNode* createTier(int tier, int value) override;

    void createRefreshButton();
    void refreshFriends(CCObject* sender);
    void refreshMaxLikes(CCObject* sender);
    void refreshCreatorPoints(CCObject* sender);
    void makeInfoPopup(std::string type);
    void openSupportMeLevel(CCObject* sender);

    int processFriendCount();

    void requestMostLiked(int page);
    void processLevels(const std::vector<std::string>& levelObjects, int userId);
    std::tuple<std::vector<std::string>, int, int, int> parseResponse(const std::string& response);
    int findMaxLikes();

    void requestCreatorPoints();
    int findCreatorPoints(const std::string& fullResponse);
};

#endif