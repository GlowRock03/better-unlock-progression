#ifndef UNLOCKPAGE_HPP
#define UNLOCKPAGE_HPP

#include "../basePage/BasePage.hpp"
#include "../utility/Utilities.hpp"

using namespace geode::prelude;

class UnlockPage : public BasePage {
private:

    int tierCount;
    int unlockCount;
    std::vector<Utilities::UnlockData*> unlockList;
    const char* iconSprName;
    
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
    int processFriendCount();

};

#endif