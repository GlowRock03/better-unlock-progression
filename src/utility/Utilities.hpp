#pragma once

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <ccTypes.h>

#include "../modify/MyItemInfoPopup.hpp"

using namespace geode::prelude;

class Utilities {
private:

    static Utilities* instance;
    Utilities();    

public:

    // some class members 

    struct PlayerStats {
        int stars;
        int moons;
        int secretCoins;
        int userCoins;
        int diamonds;
        int jumps;
        int attempts;
        int destoryedPlayers;
        int friends;
        int followedCreators;
        int likesAndDislikes;
        int rateStarsOnLevels;
        int completedInsanes;
        int completedDemons;
        int completedOnline;
        int completedDaily;
        int completedMapPacks;
        int completedGauntlets;
        int completedLists;
        int maxLikes;
        int ratedLevels;
    };
    PlayerStats m_playerStats;

    struct UnlockData : public cocos2d::CCObject {
        std::string numberString;   //unlock value
        int unlockId;               //icon id
        IconType iconType;          //icon type
        std::string colorType;      //main, secondary or nullptr
        std::string type;           //icon, colour, item
        int index;
        int pageSize;

        UnlockData(const std::string& num, int id, const std::string& colourType, std::string type, int pageIndex, int pageSize) : numberString(num), unlockId(id), colorType(colourType), type(type), index(pageIndex), pageSize(pageSize) {}
        UnlockData(const std::string& num, int id, IconType iconType, std::string type, int pageIndex, int pageSize) : numberString(num), unlockId(id), iconType(iconType), type(type), index(pageIndex), pageSize(pageSize) {}
    };

    struct UnlockInfo : public cocos2d::CCObject {
        int iconId;
        IconType unlockType;
        std::string colorType;

        UnlockInfo(int id, std::string type) : iconId(id), colorType(type) {}
        UnlockInfo(int id, IconType type) : iconId(id), unlockType(type), colorType("") {}
    };

    cocos2d::ccColor3B p1Unlocked;     
    cocos2d::ccColor3B p2Unlocked;
    cocos2d::ccColor3B p1Grey;
    cocos2d::ccColor3B p2Grey;
    bool togglePlayerColours;
    GameManager* gameManager;

    std::vector<UnlockData*> starUnlockDataList;
    std::vector<UnlockData*> moonUnlockDataList;
    std::vector<UnlockData*> secretCoinUnlockDataList;
    std::vector<UnlockData*> userCoinUnlockDataList;
    std::vector<UnlockData*> diamondUnlockDataList;
    std::vector<UnlockData*> jumpsUnlockDataList;
    std::vector<UnlockData*> attemptsUnlockDataList;
    std::vector<UnlockData*> destroyedPlayersUnlockDataList;
    std::vector<UnlockData*> friendsUnlockDataList;
    std::vector<UnlockData*> followCreatorsUnlockDataList;
    std::vector<UnlockData*> likeDislikeUnlockDataList;
    std::vector<UnlockData*> rateStarsUnlockDataList;
    std::vector<UnlockData*> completedInsaneUnlockDataList;
    std::vector<UnlockData*> completedDemonUnlockDataList;
    std::vector<UnlockData*> completedOnlineUnlockDataList;
    std::vector<UnlockData*> completedDailyUnlockDataList;
    std::vector<UnlockData*> completedMapPacksUnlockDataList;
    std::vector<UnlockData*> completedGauntletsUnlockDataList;
    std::vector<UnlockData*> completedListsUnlockDataList;
    std::vector<UnlockData*> likesOnYourLevelUnlockDataList;
    std::vector<UnlockData*> creatorPointsUnlockDataList;

    // class functions

    static Utilities* getInstance();

    void createAllUnlocks();

    const char* addCommas(const char* number);                                              //to do: both of these
    void openUnlockInfo(CCObject* sender);

    float calculateXPosition(std::string type, int unlockNumOnPage, int pageSize, std::string specialCase);
    float calculateYPosition(std::string type, int unlockNumOnPage, int pageSize);

    bool placeUnlockable(CCObject* object, int value, CCLabelBMFont* currentProgressText,                     //to do: add positioning. def struct/list and use positions found to place based on page size and unlock number
                        bool progressPlaced, CCNode* tierContainer, CCMenu* tierMenu, 
                        UnlockData* previousUnlockData, UnlockData* currentUnlockData, 
                        UnlockData* endOfPreviousTier, UnlockData* endOfTier, std::string specialPlacement);

    void updatePage(int newValue, CCNode* pageNode, std::vector<UnlockData*> unlockList, const char* iconSprName);

    std::vector<std::string> split(const std::string& str, const std::string& delimiter);
};

#endif