#include "Utilities.hpp"


Utilities* Utilities::instance = nullptr;

Utilities::Utilities() {

    p1Unlocked = ccc3(190, 190, 190);
    p2Unlocked = ccc3(245, 245, 245);
    p1Grey = ccc3(30, 30, 30);
    p2Grey = ccc3(80, 80, 80);
    togglePlayerColours = Mod::get()->getSettingValue<bool>("toggle-player-colors");
    gameManager = GameManager::sharedState();
    createAllUnlocks();
}

Utilities* Utilities::getInstance() {
    if (!instance) {
        instance = new Utilities();
    }
    return instance;
}

void Utilities::createAllUnlocks() {

    starUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),

        new UnlockData("100", 23, IconType::Cube, "icon", 1, 10),
        new UnlockData("200", 24, IconType::Cube, "icon", 2, 10),
        new UnlockData("300", 25, IconType::Cube, "icon", 3, 10),
        new UnlockData("400", 26, IconType::Cube, "icon", 4, 10),
        new UnlockData("500", 4, IconType::Ship, "icon", 5, 10),
        new UnlockData("600", 5, IconType::Ship, "icon", 6, 10),
        new UnlockData("700", 7, IconType::Ship, "icon", 7, 10),
        new UnlockData("800", 28, IconType::Cube, "icon", 8, 10),
        new UnlockData("900", 29, IconType::Cube, "icon", 9, 10),
        new UnlockData("1000", 30, IconType::Cube, "icon", 10, 10),

        new UnlockData("1500", 18, IconType::Ship, "icon", 1, 10),
        new UnlockData("2000", 9, IconType::Ball, "icon", 2, 10),
        new UnlockData("2500", 12, IconType::Wave, "icon", 3, 10),
        new UnlockData("3000", 61, IconType::Cube, "icon", 4, 10),
        new UnlockData("3500", 19, IconType::Ship, "icon", 5, 10),
        new UnlockData("4000", 9, IconType::Wave, "icon", 6, 10),
        new UnlockData("4500", 15, IconType::Wave, "icon", 7, 10),
        new UnlockData("5000", 28, "main", "colour", 8, 10),
        new UnlockData("5500", 82, IconType::Cube, "icon", 9, 10),
        new UnlockData("6000", 27, IconType::Ball, "icon", 10, 10),

        new UnlockData("6500", 34, "main", "colour", 1, 10),
        new UnlockData("7000", 30, IconType::Ship, "icon", 2, 10),
        new UnlockData("7500", 100, IconType::Cube, "icon", 3, 10),
        new UnlockData("8000", 4, IconType::Spider, "icon", 4, 10),
        new UnlockData("9000", 83, IconType::Cube, "icon", 5, 10),
        new UnlockData("10000", 8, IconType::Robot, "icon", 6, 10),
        new UnlockData("12000", 18, IconType::Swing, "icon", 7, 10),
        new UnlockData("14000", 51, IconType::Wave, "icon", 8, 10),
        new UnlockData("16000", 80, IconType::Ball, "icon", 9, 10),
        new UnlockData("18000", 37, IconType::Swing, "icon", 10, 10),

        new UnlockData("20000", 19, IconType::Spider, "icon", 1, 3),
        new UnlockData("22500", 122, IconType::Ship, "icon", 2, 3),
        new UnlockData("25000", 73, IconType::Ufo, "icon", 3, 3)
    };
    for (auto unlock : starUnlockDataList) {
        unlock->retain();
    }

    moonUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),

        new UnlockData("100", 26, IconType::Swing, "icon", 1, 10),
        new UnlockData("200", 3, IconType::Jetpack, "icon", 2, 10),
        new UnlockData("300", 86, "main", "colour", 3, 10),
        new UnlockData("400", 207, IconType::Cube, "icon", 4, 10),
        new UnlockData("500", 38, IconType::Ufo, "icon", 5, 10),
        new UnlockData("600", 111, IconType::Ball, "icon", 6, 10),
        new UnlockData("700", 65, "secondary", "colour", 7, 10),
        new UnlockData("800", 158, IconType::Cube, "icon", 8, 10),
        new UnlockData("900", 38, IconType::Robot, "icon", 9, 10),
        new UnlockData("1000", 21, IconType::Swing, "icon", 10, 10),

        new UnlockData("1500", 199, IconType::Cube, "icon", 1, 10),
        new UnlockData("2000", 94, IconType::Ball, "icon", 2, 10),
        new UnlockData("2500", 4, IconType::Jetpack, "icon", 3, 10),
        new UnlockData("3000", 91, "main", "colour", 4, 10),
        new UnlockData("3500", 70, IconType::Ship, "icon", 5, 10),
        new UnlockData("4000", 268, IconType::Cube, "icon", 6, 10),
        new UnlockData("4500", 41, IconType::Wave, "icon", 7, 10),
        new UnlockData("5000", 39, IconType::Spider, "icon", 8, 10),
        new UnlockData("5500", 144, IconType::Ufo, "icon", 9, 10),
        new UnlockData("6000", 108, IconType::Ball, "icon", 10, 10),

        new UnlockData("6500", 457, IconType::Cube, "icon", 1, 6),
        new UnlockData("7000", 75, IconType::Ufo, "icon", 2, 6),
        new UnlockData("7500", 118, IconType::Ball, "icon", 3, 6),
        new UnlockData("8000", 105, IconType::Ship, "icon", 4, 6),
        new UnlockData("9000", 38, IconType::Swing, "icon", 5, 6),
        new UnlockData("10000", 62, IconType::Ball, "icon", 6, 6)
    };
    for (auto unlock : moonUnlockDataList) {
        unlock->retain();
    }

    secretCoinUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),

        new UnlockData("5", 31, IconType::Cube, "icon", 1, 10),
        new UnlockData("10", 2, IconType::Ball, "icon", 2, 10),
        new UnlockData("15", 16, "secondary", "colour", 3, 10),
        new UnlockData("20", 3, IconType::Ufo, "icon", 4, 10),
        new UnlockData("25", 32, IconType::Cube, "icon", 5, 10),
        new UnlockData("30", 15, "main", "colour", 6, 10),
        new UnlockData("35", 3, IconType::Ball, "icon", 7, 10),
        new UnlockData("40", 34, IconType::Cube, "icon", 8, 10),
        new UnlockData("45", 4, IconType::Ufo, "icon", 9, 10),
        new UnlockData("50", 4, IconType::Ball, "icon", 10, 10),
        
        new UnlockData("55", 14, IconType::Ship, "icon", 1, 10),
        new UnlockData("60", 38, IconType::Cube, "icon", 2, 10),
        new UnlockData("65", 6, IconType::Ufo, "icon", 3, 10),
        new UnlockData("70", 6, IconType::Ball, "icon", 4, 10),
        new UnlockData("75", 12, IconType::Ship, "icon", 5, 10),
        new UnlockData("80", 7, IconType::Ufo, "icon", 6, 10),
        new UnlockData("85", 8, IconType::Ufo, "icon", 7, 10),
        new UnlockData("90", 16, IconType::Ship, "icon", 8, 10),
        new UnlockData("95", 43, IconType::Cube, "icon", 9, 10),
        new UnlockData("100", 9, IconType::Ufo, "icon", 10, 10),
        
        new UnlockData("105", 14, IconType::Ball, "icon", 1, 8),
        new UnlockData("110", 56, IconType::Cube, "icon", 2, 8),
        new UnlockData("115", 24, IconType::Ship, "icon", 3, 8),
        new UnlockData("120", 18, IconType::Ufo, "icon", 4, 8),
        new UnlockData("130", 88, IconType::Cube, "icon", 5, 8),
        new UnlockData("140", 36, IconType::Wave, "icon", 6, 8),
        new UnlockData("150", 34, IconType::Swing, "icon", 7, 8),
        new UnlockData("160", 88, IconType::Ship, "icon", 8, 8)
    };
    for (auto unlock : secretCoinUnlockDataList) {
        unlock->retain();
    }

    userCoinUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),

        new UnlockData("1", 2, IconType::Wave, "icon", 1, 10),
        new UnlockData("10", 49, IconType::Cube, "icon", 2, 10),
        new UnlockData("20", 4, IconType::Wave, "icon", 3, 10),
        new UnlockData("30", 25, IconType::Ship, "icon", 4, 10),
        new UnlockData("40", 16, IconType::Ball, "icon", 5, 10),
        new UnlockData("50", 13, IconType::Ufo, "icon", 6, 10),
        new UnlockData("60", 53, IconType::Cube, "icon", 7, 10),
        new UnlockData("70", 6, IconType::Wave, "icon", 8, 10),
        new UnlockData("80", 23, IconType::Ship, "icon", 9, 10),
        new UnlockData("90", 17, IconType::Ball, "icon", 10, 10),

        new UnlockData("100", 6, IconType::Robot, "icon", 1, 10),
        new UnlockData("110", 54, IconType::Cube, "icon", 2, 10),
        new UnlockData("120", 7, IconType::Wave, "icon", 3, 10),
        new UnlockData("130", 21, IconType::Ship, "icon", 4, 10),
        new UnlockData("140", 11, IconType::Ball, "icon", 5, 10),
        new UnlockData("150", 52, IconType::Cube, "icon", 6, 10),
        new UnlockData("160", 17, IconType::Ufo, "icon", 7, 10),
        new UnlockData("170", 10, IconType::Wave, "icon", 8, 10),
        new UnlockData("180", 22, IconType::Ship, "icon", 9, 10),
        new UnlockData("190", 18, IconType::Ball, "icon", 10, 10),

        new UnlockData("200", 4, IconType::Robot, "icon", 1, 10),
        new UnlockData("225", 99, IconType::Cube, "icon", 2, 10),
        new UnlockData("250", 30, "main", "colour", 3, 10),
        new UnlockData("300", 8, IconType::Spider, "icon", 4, 10),
        new UnlockData("350", 32, "main", "colour", 5, 10),
        new UnlockData("425", 29, IconType::Ball, "icon", 6, 10),
        new UnlockData("500", 93, IconType::Cube, "icon", 7, 10),
        new UnlockData("600", 22, IconType::Wave, "icon", 8, 10),
        new UnlockData("700", 15, IconType::Robot, "icon", 9, 10),
        new UnlockData("800", 33, IconType::Ship, "icon", 10, 10),

        new UnlockData("900", 28, IconType::Ball, "icon", 1, 10),
        new UnlockData("1000", 28, IconType::Ufo, "icon", 2, 10),
        new UnlockData("1200", 25, IconType::Swing, "icon", 3, 10),
        new UnlockData("1400", 59, "main", "colour", 4, 10),
        new UnlockData("1600", 325, IconType::Cube, "icon", 5, 10),
        new UnlockData("1800", 66, IconType::Wave, "icon", 6, 10),
        new UnlockData("2000", 134, IconType::Ship, "icon", 7, 10),
        new UnlockData("2300", 284, IconType::Cube, "icon", 8, 10),
        new UnlockData("2600", 21, IconType::Spider, "icon", 9, 10),
        new UnlockData("3000", 41, IconType::Robot, "icon", 10, 10)
    };
    for (auto unlock : userCoinUnlockDataList) {
        unlock->retain();
    }

    diamondUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("100", 31, "main", "colour", 1, 10),
        new UnlockData("250", 87, IconType::Cube, "icon", 2, 10),
        new UnlockData("500", 11, IconType::Robot, "icon", 3, 10),
        new UnlockData("1000", 38, "main", "colour", 4, 10),
        new UnlockData("1500", 19, IconType::Wave, "icon", 5, 10),
        new UnlockData("2000", 101, IconType::Cube, "icon", 6, 10),
        new UnlockData("2500", 32, IconType::Ship, "icon", 7, 10),
        new UnlockData("3000", 24, IconType::Ufo, "icon", 8, 10),
        new UnlockData("4000", 17, IconType::Wave, "icon", 9, 10),
        new UnlockData("5000", 10, IconType::DeathEffect, "item", 10, 10),

        new UnlockData("6000", 159, IconType::Cube, "icon", 1, 8),
        new UnlockData("7000", 82, "main", "colour", 2, 8),
        new UnlockData("9000", 319, IconType::Cube, "icon", 3, 8),
        new UnlockData("11000", 103, IconType::Ship, "icon", 4, 8),
        new UnlockData("14000", 52, "main", "colour", 5, 8),
        new UnlockData("17000", 226, IconType::Cube, "icon", 6, 8),
        new UnlockData("20000", 52, IconType::Wave, "icon", 7, 8),
        new UnlockData("25000", 58, IconType::Robot, "icon", 8, 8)
    };
    for (auto unlock : diamondUnlockDataList) {
        unlock->retain();
    }

    jumpsUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1000", 5, "secondary", "colour", 1, 8),
        new UnlockData("10000", 11, "secondary", "colour", 2, 8),
        new UnlockData("20000", 12, "secondary", "colour", 3, 8),
        new UnlockData("50000", 5, IconType::Ufo, "icon", 4, 8),
        new UnlockData("100000", 13, IconType::Ball, "icon", 5, 8),
        new UnlockData("200000", 56, "main", "colour", 6, 8),
        new UnlockData("300000", 371, IconType::Cube, "icon", 7, 8),
        new UnlockData("400000", 93, IconType::Wave, "icon", 8, 8),

        new UnlockData("500000", 365, IconType::Cube, "icon", 1, 3),
        new UnlockData("750000", 45, IconType::Wave, "icon", 2, 3),
        new UnlockData("1000000", 32, IconType::Swing, "icon", 3, 3)
    };
    for (auto unlock : jumpsUnlockDataList) {
        unlock->retain();
    }

    attemptsUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("100", 6, "secondary", "colour", 1, 10),
        new UnlockData("500", 7, "secondary", "colour", 2, 10),
        new UnlockData("2000", 14, "secondary", "colour", 3, 10),
        new UnlockData("10000", 17, "secondary", "colour", 4, 10),
        new UnlockData("20000", 3, IconType::Wave, "icon", 5, 10),
        new UnlockData("30000", 341, IconType::Cube, "icon", 6, 10),
        new UnlockData("40000", 96, "main", "colour", 7, 10),
        new UnlockData("60000", 161, IconType::Ship, "icon", 8, 10),
        new UnlockData("80000", 407, IconType::Cube, "icon", 9, 10),
        new UnlockData("100000", 9, IconType::Swing, "icon", 10, 10),

        new UnlockData("135000", 117, IconType::Ball, "icon", 1, 4),
        new UnlockData("185000", 46, IconType::Ball, "icon", 2, 4),
        new UnlockData("250000", 65, IconType::Ship, "icon", 3, 4),
        new UnlockData("300000", 368, IconType::Cube, "icon", 4, 4)
    };
    for (auto unlock : attemptsUnlockDataList) {
        unlock->retain();
    }

    destroyedPlayersUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 19, "secondary", "colour", 1, 6),
        new UnlockData("50", 41, IconType::Cube, "icon", 2, 6),
        new UnlockData("100", 27, "secondary", "colour", 3, 6),
        new UnlockData("200", 39, IconType::Cube, "icon", 4, 6),
        new UnlockData("500", 12, IconType::Ball, "icon", 5, 6),
        new UnlockData("750", 71, IconType::Ball, "icon", 6, 6)
    };
    for (auto unlock : destroyedPlayersUnlockDataList) {
        unlock->retain();
    }

    friendsUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 26, "secondary", "colour", 1, 4),
        new UnlockData("10", 27, "main", "colour", 2, 4),
        new UnlockData("25", 296, IconType::Cube, "icon", 3, 4),
        new UnlockData("50", 272, IconType::Cube, "icon", 4, 4)
    };
    for (auto unlock : friendsUnlockDataList) {
        unlock->retain();
    }

    followCreatorsUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 25, "secondary", "colour", 1, 4),
        new UnlockData("10", 24, "secondary", "colour", 2, 4),
        new UnlockData("25", 344, IconType::Cube, "icon", 3, 4),
        new UnlockData("50", 75, IconType::Ball, "icon", 4, 4)
    };
    for (auto unlock : followCreatorsUnlockDataList) {
        unlock->retain();
    }

    likeDislikeUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 8, "secondary", "colour", 1, 7),
        new UnlockData("100", 23, "secondary", "colour", 2, 7),
        new UnlockData("500", 26, "main", "colour", 3, 7),
        new UnlockData("1000", 22, "main", "colour", 4, 7),
        new UnlockData("2000", 3, IconType::Special, "item", 5, 7),
        new UnlockData("3000", 271, IconType::Cube, "icon", 6, 7),
        new UnlockData("4000", 70, IconType::Ball, "icon", 7, 7)
    };
    for (auto unlock : likeDislikeUnlockDataList) {
        unlock->retain();
    }

    rateStarsUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 9, "secondary", "colour", 1, 5),
        new UnlockData("100", 22, "secondary", "colour", 2, 5),
        new UnlockData("500", 5, IconType::Wave, "icon", 3, 5),
        new UnlockData("1000", 23, "main", "colour", 4, 5),
        new UnlockData("2000", 57, IconType::Cube, "icon", 5, 5)
    };
    for (auto unlock : rateStarsUnlockDataList) {
        unlock->retain();
    }

    completedInsaneUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("5", 201, IconType::Cube, "icon", 1, 10),
        new UnlockData("10", 266, IconType::Cube, "icon", 2, 10),
        new UnlockData("25", 50, IconType::Ball, "icon", 3, 10),
        new UnlockData("50", 174, IconType::Cube, "icon", 4, 10),
        new UnlockData("75", 86, IconType::Wave, "icon", 5, 10),
        new UnlockData("100", 277, IconType::Cube, "icon", 6, 10),
        new UnlockData("200", 119, IconType::Ship, "icon", 7, 10),
        new UnlockData("300", 481, IconType::Cube, "icon", 8, 10),
        new UnlockData("400", 37, IconType::Spider, "icon", 9, 10),
        new UnlockData("500", 64, IconType::Ufo, "icon", 10, 10)
    };
    for (auto unlock : completedInsaneUnlockDataList) {
        unlock->retain();
    }

    completedDemonUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 19, IconType::Cube, "icon", 1, 10),
        new UnlockData("2", 20, IconType::Cube, "icon", 2, 10),
        new UnlockData("3", 21, IconType::Cube, "icon", 3, 10),
        new UnlockData("4", 22, IconType::Cube, "icon", 4, 10),
        new UnlockData("5", 3, IconType::Ship, "icon", 5, 10),
        new UnlockData("10", 6, IconType::Ship, "icon", 6, 10),
        new UnlockData("15", 8, IconType::Ship, "icon", 7, 10),
        new UnlockData("20", 5, IconType::Ball, "icon", 8, 10),
        new UnlockData("30", 37, IconType::Cube, "icon", 9, 10),
        new UnlockData("40", 10, IconType::Ball, "icon", 10, 10),

        new UnlockData("50", 15, IconType::Ufo, "icon", 1, 10),
        new UnlockData("60", 35, IconType::Ship, "icon", 2, 10),
        new UnlockData("70", 28, IconType::Robot, "icon", 3, 10),
        new UnlockData("80", 53, "main", "colour", 4, 10),
        new UnlockData("90", 64, IconType::Wave, "icon", 5, 10),
        new UnlockData("100", 45, IconType::Ball, "icon", 6, 10),
        new UnlockData("120", 3, IconType::Swing, "icon", 7, 10),
        new UnlockData("140", 62, "main", "colour", 8, 10),
        new UnlockData("160", 65, IconType::Robot, "icon", 9, 10),
        new UnlockData("180", 446, IconType::Cube, "icon", 10, 10),

        new UnlockData("200", 53, IconType::Robot, "icon", 1, 7),
        new UnlockData("225", 270, IconType::Cube, "icon", 2, 7),
        new UnlockData("250", 46, IconType::Spider, "icon", 3, 7),
        new UnlockData("300", 308, IconType::Cube, "icon", 4, 7),
        new UnlockData("350", 123, IconType::Ship, "icon", 5, 7),
        new UnlockData("400", 37, IconType::Wave, "icon", 6, 7),
        new UnlockData("500", 459, IconType::Cube, "icon", 7, 7)
    };
    for (auto unlock : completedDemonUnlockDataList) {
        unlock->retain();
    }

    completedOnlineUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 11, "main", "colour", 1, 10),
        new UnlockData("10", 12, IconType::Cube, "icon", 2, 10),
        new UnlockData("50", 36, IconType::Cube, "icon", 3, 10),
        new UnlockData("100", 13, IconType::Ship, "icon", 4, 10),
        new UnlockData("200", 19, "main", "colour", 5, 10),
        new UnlockData("300", 40, IconType::Cube, "icon", 6, 10),
        new UnlockData("500", 15, IconType::Ship, "icon", 7, 10),
        new UnlockData("1000", 17, IconType::Ship, "icon", 8, 10),
        new UnlockData("1500", 148, IconType::Ship, "icon", 9, 10),
        new UnlockData("2000", 164, IconType::Cube, "icon", 10, 10),

        new UnlockData("2500", 60, "main", "colour", 1, 4),
        new UnlockData("3000", 161, IconType::Cube, "icon", 2, 4),
        new UnlockData("4000", 200, IconType::Cube, "icon", 3, 4),
        new UnlockData("5000", 108, IconType::Ufo, "icon", 4, 4)
    };
    for (auto unlock : completedOnlineUnlockDataList) {
        unlock->retain();
    }

    completedDailyUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 267, IconType::Cube, "icon", 1, 7),
        new UnlockData("25", 22, IconType::Swing, "icon", 2, 7),
        new UnlockData("50", 58, "main", "colour", 3, 7),
        new UnlockData("100", 403, IconType::Cube, "icon", 4, 7),
        new UnlockData("150", 43, IconType::Spider, "icon", 5, 7),
        new UnlockData("250", 91, IconType::Ufo, "icon", 6, 7),
        new UnlockData("365", 396, IconType::Cube, "icon", 7, 7)
    };
    for (auto unlock : completedDailyUnlockDataList) {
        unlock->retain();
    }

    completedMapPacksUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 33, IconType::Cube, "icon", 1, 10),
        new UnlockData("5", 10, IconType::Ship, "icon", 2, 10),
        new UnlockData("10", 2, IconType::Special, "item", 3, 10),
        new UnlockData("15", 11, IconType::Ship, "icon", 4, 10),
        new UnlockData("20", 7, IconType::Ball, "icon", 5, 10),
        new UnlockData("25", 8, IconType::Ball, "icon", 6, 10),
        new UnlockData("30", 10, IconType::Ufo, "icon", 7, 10),
        new UnlockData("35", 58, IconType::Cube, "icon", 8, 10),
        new UnlockData("40", 15, IconType::Ball, "icon", 9, 10),
        new UnlockData("45", 11, IconType::Wave, "icon", 10, 10)
    };
    for (auto unlock : completedMapPacksUnlockDataList) {
        unlock->retain();
    }

    completedGauntletsUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 242, IconType::Cube, "icon", 1, 4),
        new UnlockData("5", 37, IconType::Ufo, "icon", 2, 4),
        new UnlockData("10", 89, "main", "colour", 3, 4),
        new UnlockData("15", 74, IconType::Wave, "icon", 4, 4)
    };
    for (auto unlock : completedGauntletsUnlockDataList) {
        unlock->retain();
    }

    completedListsUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 246, IconType::Cube, "icon", 1, 7),
        new UnlockData("10", 173, IconType::Cube, "icon", 2, 7),
        new UnlockData("25", 52, IconType::Ball, "icon", 3, 7),
        new UnlockData("50", 140, IconType::Ship, "icon", 4, 7),
        new UnlockData("100", 96, IconType::Ball, "icon", 5, 7),
        new UnlockData("150", 89, IconType::Wave, "icon", 6, 7),
        new UnlockData("200", 39, IconType::Swing, "icon", 7, 7)
    };
    for (auto unlock : completedListsUnlockDataList) {
        unlock->retain();
    }

    likesOnYourLevelUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("50", 63, IconType::Cube, "icon", 1, 5),
        new UnlockData("100", 46, IconType::Cube, "icon", 2, 5),
        new UnlockData("250", 72, IconType::Ball, "icon", 3, 5),
        new UnlockData("500", 238, IconType::Cube, "icon", 4, 5),
        new UnlockData("1000", 275, IconType::Cube, "icon", 5, 5)
    };
    for (auto unlock : likesOnYourLevelUnlockDataList) {
        unlock->retain();
    }

    creatorPointsUnlockDataList = {

        new UnlockData("0", 1, IconType::Cube, "icon", 1, 1),
        
        new UnlockData("1", 16, IconType::Ufo, "icon", 1, 1)
    };
    for (auto unlock : creatorPointsUnlockDataList) {
        unlock->retain();
    }
}

const char* Utilities::addCommas(const char* number) {

    std::string str(number);
    int len = str.length();
    int commaCount = (len - 1) / 3;

    std::string result;
    int count = 0;

    for (int i = len - 1; i >= 0; --i) {
        result.push_back(str[i]);
        count++;
        if (count % 3 == 0 && i != 0) {
            result.push_back(',');
        }
    }

    std::reverse(result.begin(), result.end());

    char* resultCStr = new char[result.length() + 1];
    std::copy(result.begin(), result.end(), resultCStr);
    resultCStr[result.length()] = '\0';

    return resultCStr;
}

void Utilities::openUnlockInfo(CCObject* sender) {

    auto button = static_cast<CCMenuItemSpriteExtra*>(sender);
    auto unlockInfo = typeinfo_cast<UnlockInfo*>(button->getUserObject());

    if (unlockInfo->colorType.empty()) {
        auto popup = MyItemInfoPopup::createWithCustomizations(
            unlockInfo->iconId,
            GameManager::sharedState()->iconTypeToUnlockType(unlockInfo->unlockType)
        );
        popup->show();
    } else if (unlockInfo->colorType == "main") {
        auto popup = MyItemInfoPopup::createWithCustomizations(
            unlockInfo->iconId, UnlockType::Col1
        );
        popup->show();
    } else if (unlockInfo->colorType == "secondary") {
        auto popup = MyItemInfoPopup::createWithCustomizations(
            unlockInfo->iconId, UnlockType::Col2
        );
        popup->show();
    }
}

float Utilities::calculateXPosition(std::string type, int unlockNumOnPage, int pageSize, std::string specialCase) {

    std::vector<float> positions;
    if (type.compare("progress_text") == 0) {

        switch (pageSize) {

            case 10:
                positions = {-185, -99, -12.5f, 77, 167.5f, -185, -99, -12.5f, 77, 167.5f};
                break;
            case 8:
                positions = {-185, -99, -12.5f, 77, 167.5f, -99, -12.5f, 77};
                break;
            case 7:
                positions = {-141.75f, -55.75f, 30.75f, 120.25f, -99, -12.5f, 77};
                break;
            case 6:
                positions = {-99, -12.5f, 77, -99, -12.5f, 77};
                break;
            case 5:
                positions = {-99, -12.5f, 77, -55.75f, 30.75f};
                break;
            case 4:
                positions = {-99, -12.5f, 77, -12.5f};
                break;
            case 3:
                positions = {-55.75f, 30.75f, -12.5f};
                break;
            default:    //page size 1
                positions = {-12.5f};
        }
    } else if (type.compare("slider_bar") == 0) {

        switch (pageSize) {

            case 10:
                positions = {-201, -115, -28.5f, 61, 151, -201, -115, -28.5f, 61, 151};
                break;
            case 8:
                positions = {-201, -115, -28.5f, 61, 151, -115, -28.5f, 61};
                break;
            case 7:
                positions = {-157.75f, -71.75f, 14.75f, 104.25f, -115, -28.5f, 61};
                break;
            case 6:
                positions = {-115, -28.5f, 61, -115, -28.5f, 61};
                break;
            case 5:
                positions = {-115, -28.5f, 61, -71.75f, 14.75f};
                break;
            case 4:
                positions = {-115, -28.5f, 61, -28.5f};
                break;
            case 3:
                positions = {-71.75f, 14.75f, -28.5f};
                break;
            default:    //page size 1
                positions = {-28.5f};
        }
    } else if (type.compare("slider_outline") == 0) {
        
        switch (pageSize) {

            case 10:
                positions = {-203, -117, -30.5f, 59, 149, -203, -117, -30.5f, 59, 149};
                break;
            case 8:
                positions = {-203, -117, -30.5f, 59, 149, -117, -30.5f, 59};
                break;
            case 7:
                positions = {-159.75f, -73.75f, 12.75f, 102.25f, -117, -30.5f, 59};
                break;
            case 6:
                positions = {-117, -30.5f, 59, -117, -30.5f, 59};
                break;
            case 5:
                positions = {-117, -30.5f, 59, -73.75f, 12.75f};
                break;
            case 4:
                positions = {-117, -30.5f, 59, -30.5f};
                break;
            case 3:
                positions = {-73.75f, 12.75f, -30.5f};
                break;
            default:    //page size 1
                positions = {-30.5f};
        }
    } else if (type.compare("unlock_text") == 0) {
        
        switch (pageSize) {

            case 10:
                positions = {-142.5f, -55.5f, 33, 122, 211.5f, -142.5f, -55.5f, 33, 122, 211.5f};
                break;
            case 8:
                positions = {-142.5f, -55.5f, 33, 122, 211.5f, -55.5f, 33, 122};
                break;
            case 7:
                positions = {-99.25f, -12.5f, 76.25f, 165.25f, -55.5f, 33, 122};
                break;
            case 6:
                positions = {-55.5f, 33, 122, -55.5f, 33, 122};
                break;
            case 5:
                positions = {-55.5f, 33, 122, -12.5f, 76.25f};
                break;
            case 4:
                positions = {-55.5f, 33, 122, 33};
                break;
            case 3:
                positions = {-12.5f, 76.25f, 33};
                break;
            default:    //page size 1
                positions = {33};
        }
    } else {        //"unlock_button"

        if (specialCase.compare("star-700") == 0) {

            return -342.5f;
        } else if (specialCase.compare("star-7000") == 0) {
            
            return -339.5f;
        } else if (specialCase.compare("diamond-2500") == 0) {
            
            return -344.5f;
        } else if (specialCase.compare("demon-60") == 0) {
            
            return -339;
        } else {

            switch (pageSize) {

                case 10:
                    positions = {-427, -340.5f, -252, -163, -73, -427, -340.5f, -252, -163, -73};
                    break;
                case 8:
                    positions = {-427, -340.5f, -252, -163, -73, -340.5f, -252, -163};
                    break;
                case 7:
                    positions = {-383.5f, -297.5f, -208.5f, -119.5f, -340.5f, -252, -163};
                    break;
                case 6:
                    positions = {-340.5f, -252, -163, -340.5f, -252, -163};
                    break;
                case 5:
                    positions = {-340.5f, -252, -163, -297.5f, -208.5f};
                    break;
                case 4:
                    positions = {-340.5f, -252, -163, -252};
                    break;
                case 3:
                    positions = {-297.5f, -208.5f, -252};
                    break;
                default:    //page size 1
                    positions = {-251};
            }
        }
    }

    if (unlockNumOnPage == positions.size()) {  //last index in page
        return positions[positions.size() - 1];
    }

    return positions[(unlockNumOnPage % positions.size()) - 1];     //returns the correct index of where the icon is in the page
}

float Utilities::calculateYPosition(std::string type, int unlockNumOnPage, int pageSize) {

    float position;
    bool isSecondRow = false;

    if ((pageSize == 10 || pageSize == 8) && unlockNumOnPage >= 6) {
        isSecondRow = true;
    } else if (pageSize == 7 && unlockNumOnPage >= 5) {
        isSecondRow = true;
    } else if ((pageSize >= 4 && pageSize <= 6) && unlockNumOnPage >= 4) {
        isSecondRow = true;
    } else if (pageSize == 3 && unlockNumOnPage == 3) {
        isSecondRow = true;
    }
    
    if (type.compare("progress_text") == 0) {

        if (pageSize != 1) {
            position = isSecondRow ? 73 : 138;
        } else {
            position = 110.5f;
        }
        
    } else if (type.compare("slider_bar") == 0 || type.compare("slider_outline") == 0) {

        if (pageSize != 1) {
            position = isSecondRow ? 85 : 150;
        } else {
            position = 122.5f;
        }
    } else if (type.compare("unlock_text") == 0) {
        
        if (pageSize != 1) {
            position = isSecondRow ? 55 : 120;
        } else {
            position = 92.5f;
        }
    } else {        //"unlock_button"
        
        if (pageSize != 1) {
            position = isSecondRow ? -75 : -10;
        } else {
            position = -37.5f;
        }
    }

    return position;
}

bool Utilities::placeUnlockable(CCObject* object, int value, CCLabelBMFont* currentProgressText, bool progressPlaced, CCNode* tierContainer, CCMenu* tierMenu, UnlockData* previousUnlockData, UnlockData* currentUnlockData, UnlockData* endOfPreviousTier, UnlockData* endOfTier, std::string specialPlacement) {

    auto sliderOutlineSpr = CCSprite::createWithSpriteFrameName("progressOutline.png"_spr);
    sliderOutlineSpr->setID("Progress-Outline");
    auto sliderBarSpr = togglePlayerColours ? CCSprite::create("sliderBar2.png") : CCSprite::create("sliderBar.png");
    sliderBarSpr->setID("Slider-Bar");
    sliderBarSpr->setUserObject(CCFloat::create(sliderBarSpr->getContentSize().width));
    float ratio = (float)(value - std::stoi(previousUnlockData->numberString)) / (float)(std::stoi(currentUnlockData->numberString) - std::stoi(previousUnlockData->numberString));
    float scale = ratio >= 0.98f ? sliderBarSpr->getContentSize().width * 0.98f : sliderBarSpr->getContentSize().width * ratio;
    sliderBarSpr->setTextureRect(CCRectMake(0, 0, scale, sliderBarSpr->getContentSize().height));
    auto unlockText = CCLabelBMFont::create(Utilities::addCommas(currentUnlockData->numberString.c_str()), "bigFont.fnt");
    unlockText->setID("Unlock-Text");
    auto lock = CCSprite::createWithSpriteFrameName("GJ_lockGray_001.png");
    lock->setID("Lock");

    UnlockInfo* unlockInfo = nullptr;
    if (currentUnlockData->type.compare("colour") == 0) {
        unlockInfo = new UnlockInfo(currentUnlockData->unlockId, currentUnlockData->colorType);
    } else {
        unlockInfo = new UnlockInfo(currentUnlockData->unlockId, currentUnlockData->iconType);
    }
    unlockInfo->autorelease();
    
    SimplePlayer* unlockIcon = nullptr;           //needed for scoping issues
    ColorChannelSprite* unlockColour = nullptr;
    GJItemIcon* unlockItem = nullptr;
    if (currentUnlockData->type.compare("icon") == 0) {
        unlockIcon = SimplePlayer::create(1);
        unlockIcon->setID("Icon");
    } else if (currentUnlockData->type.compare("colour") == 0) {
        unlockColour = ColorChannelSprite::create();
        unlockColour->setID("Colour");
    } else {
        unlockItem = GJItemIcon::createBrowserItem(gameManager->iconTypeToUnlockType(unlockInfo->unlockType), currentUnlockData->unlockId);
        unlockItem->setID("Item");
    }

    bool isInTier = value >= std::stoi(endOfPreviousTier->numberString) && value < std::stoi(endOfTier->numberString);
    if (ratio < 1.f && isInTier && !progressPlaced) {

        currentProgressText->setString(addCommas(std::to_string(value).c_str()));
        currentProgressText->setPosition({ calculateXPosition("progress_text", currentUnlockData->index, currentUnlockData->pageSize, ""), calculateYPosition("progress_text", currentUnlockData->index, currentUnlockData->pageSize) });
        tierContainer->addChild(currentProgressText);   
        progressPlaced = true;
    }

    togglePlayerColours ? sliderBarSpr->setColor(gameManager->colorForIdx(gameManager->getPlayerColor())) : void();
    if (currentUnlockData->type.compare("icon") == 0) {
        unlockIcon->updatePlayerFrame(unlockInfo->iconId, unlockInfo->unlockType);
        if (ratio >= 1.f) {        //unlocked
            lock->setVisible(false);
            if (togglePlayerColours) {
                unlockIcon->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                if (gameManager->m_playerGlow) {
                    unlockIcon->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                }
            } else {
                unlockIcon->setColors(p1Unlocked, p2Unlocked);
                unlockIcon->disableGlowOutline();
            }
        } else {                        //locked
            unlockIcon->setColors(p1Grey, p2Grey);
            unlockIcon->disableGlowOutline();
        }
    } else {       // Death Effects + Trails + Colours
        if (currentUnlockData->type.compare("colour") == 0) {
            unlockColour->setColor(gameManager->colorForIdx(unlockInfo->iconId));
        }
        if (ratio >= 1.f) {
            lock->setVisible(false);
        }
    }
    
    sliderBarSpr->setAnchorPoint({ 0, .5f }); sliderBarSpr->setZOrder(-1); sliderBarSpr->setPosition({ calculateXPosition("slider_bar", currentUnlockData->index, currentUnlockData->pageSize, ""), calculateYPosition("slider_bar", currentUnlockData->index, currentUnlockData->pageSize) });
    sliderOutlineSpr->setAnchorPoint({ 0, .5f }); sliderOutlineSpr->setScaleX(1.1f); sliderOutlineSpr->setPosition({ calculateXPosition("slider_outline", currentUnlockData->index, currentUnlockData->pageSize, ""), calculateYPosition("slider_outline", currentUnlockData->index, currentUnlockData->pageSize) });      
    if (currentUnlockData->type.compare("colour") == 0) {     
        lock->setPosition({17.75f, 18.25f});
    } else if (currentUnlockData->type.compare("item") == 0) {
        lock->setPosition({15, 15});
    }
    lock->setZOrder(1); 
    unlockText->setScale(.5f); unlockText->setPosition({ calculateXPosition("unlock_text", currentUnlockData->index, currentUnlockData->pageSize, ""), calculateYPosition("unlock_text", currentUnlockData->index, currentUnlockData->pageSize) });

    CCMenuItemSpriteExtra* unlockButton = nullptr;
    if (currentUnlockData->type.compare("icon") == 0) {
        unlockIcon->addChild(lock);
        unlockButton = CCMenuItemSpriteExtra::create(
            unlockIcon,
            object,
            menu_selector(Utilities::openUnlockInfo)
        );
    } else if (currentUnlockData->type.compare("colour") == 0) {
        unlockColour->addChild(lock);
        unlockButton = CCMenuItemSpriteExtra::create(
            unlockColour,
            object,
            menu_selector(Utilities::openUnlockInfo)
        );
    } else {
        unlockItem->addChild(lock);
        unlockButton = CCMenuItemSpriteExtra::create(
            unlockItem,
            object,
            menu_selector(Utilities::openUnlockInfo)
        );
    }
    unlockButton->setID("Unlock-Button");
    unlockButton->setUserObject(unlockInfo);

    if (currentUnlockData->type.compare("icon") == 0) {
        unlockButton->setContentSize({unlockIcon->m_firstLayer->getContentSize().width, unlockIcon->m_firstLayer->getContentSize().height});
        auto innerSpr = static_cast<cocos2d::CCSprite*>(unlockButton->getNormalImage());
        innerSpr->setPosition({unlockIcon->m_firstLayer->getContentSize().width / 2.f, unlockIcon->m_firstLayer->getContentSize().height / 2.f});
    }

    unlockButton->setPosition({ calculateXPosition("unlock_button", currentUnlockData->index, currentUnlockData->pageSize, specialPlacement), calculateYPosition("unlock_button", currentUnlockData->index, currentUnlockData->pageSize) });
    
    tierContainer->addChild(sliderBarSpr);
    tierContainer->addChild(sliderOutlineSpr);
    tierMenu->addChild(unlockButton);
    tierContainer->addChild(unlockText);

    tierMenu->setID("Tier-Unlock-Menu");

    return progressPlaced;
}

void Utilities::updatePage(int newValue, CCNode* pageNode, std::vector<UnlockData*> unlockList, const char* iconSprName) {

    int tier = 0;
    int unlockCount = (int)unlockList.size() - 1;
    int tierCount = (unlockCount + 9) / 10;

    int startIdx;
    int endIdx;

    std::vector<float> ratioList(unlockCount);

    for (int i = 0; i < unlockCount; i++) {
        int prevValue = std::stoi(unlockList[i]->numberString);
        int nextValue = std::stoi(unlockList[i + 1]->numberString);

        if (newValue >= prevValue && newValue < nextValue) {
            ratioList[i] = (float)(newValue - prevValue) / (float)(nextValue - prevValue);
        } else if (newValue >= nextValue) {
            ratioList[i] = 1.0f;
        } else {
            ratioList[i] = 0.0f;
        }
    }

    for (auto tierNode : CCArrayExt<CCNode*>(pageNode->getChildren())) {

        if (tierNode->getID() != "Tier-Node") continue;

        // Determine start and end indices
        if (strcmp(iconSprName, "jumps_spr.png"_spr) == 0) {
            startIdx = tier * 8;
            endIdx = (tier == tierCount - 1) ? unlockCount : std::min(startIdx + 8, unlockCount);
        } else {
            startIdx = tier * 10;
            endIdx = (tier == tierCount - 1) ? unlockCount : std::min(startIdx + 10, unlockCount);
        }

        int unlockIndex = 0;
        for (auto node : CCArrayExt<CCNode*>(tierNode->getChildren())) {

            // Progress bar
            if (auto sliderBar = typeinfo_cast<CCSprite*>(node)) {
                if (sliderBar->getID() == "Slider-Bar") {

                    auto originalWidthObj = typeinfo_cast<CCFloat*>(sliderBar->getUserObject());
                    float originalWidth = originalWidthObj->getValue();

                    float scale = ratioList[unlockIndex] >= 0.98f ? originalWidth * 0.98f : originalWidth * ratioList[unlockIndex];
                    sliderBar->setTextureRect(CCRectMake(0, 0, scale, sliderBar->getContentSize().height));
                }
            }

            // Progress text
            if (auto progressText = typeinfo_cast<CCLabelBMFont*>(node)) {
                if (progressText->getID() == "Progress-Text") {

                    bool progressPlaced = false;
                    for (int progressIndex = startIdx + 1; progressIndex <= endIdx; ++progressIndex) {

                        if (progressIndex - 1 >= ratioList.size() || progressIndex >= unlockList.size()) break;

                        float ratio = ratioList[progressIndex - 1];
                        bool isInTier = newValue >= std::stoi(unlockList[startIdx]->numberString) &&
                                        newValue < std::stoi(unlockList[endIdx]->numberString);

                        if (ratio < 1.f && isInTier && !progressPlaced) {
                            progressText->setString(addCommas(std::to_string(newValue).c_str()));
                            progressText->setPosition({
                                calculateXPosition("progress_text", unlockList[progressIndex]->index, unlockList[progressIndex]->pageSize, ""),
                                calculateYPosition("progress_text", unlockList[progressIndex]->index, unlockList[progressIndex]->pageSize)
                            });
                            progressPlaced = true;
                        }
                    }

                    if (newValue >= std::stoi(unlockList[endIdx]->numberString)) {
                        progressText->setString("");
                    }
                }
            }

            // Unlock icons
            if (auto buttonMenu = typeinfo_cast<CCMenu*>(node)) {

                int lockCount = 0;
                for (auto unlockButtonObj : CCArrayExt<CCNode*>(buttonMenu->getChildren())) {

                    auto unlockButton = typeinfo_cast<CCMenuItemSpriteExtra*>(unlockButtonObj);
                    if (!unlockButton) continue;

                    auto unlockInfo = static_cast<UnlockInfo*>(unlockButton->getUserObject());
                    if (!unlockInfo) continue;

                    for (auto iconObject : CCArrayExt<CCNode*>(unlockButton->getChildren())) {

                        if (lockCount >= unlockList.size()) break;
                        int unlockValue = std::stoi(unlockList[lockCount]->numberString);

                        auto unlockFunc = [&](CCNode* iconNode) {
                            if (auto icon = typeinfo_cast<SimplePlayer*>(iconNode)) {
                                if (newValue >= unlockValue) {
                                    icon->setColors(gameManager->colorForIdx(gameManager->getPlayerColor()), gameManager->colorForIdx(gameManager->getPlayerColor2()));
                                    if (gameManager->m_playerGlow)
                                        icon->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                                } else {
                                    icon->setColors(p1Grey, p2Grey);
                                    icon->disableGlowOutline();
                                }

                                for (auto inner : CCArrayExt<CCNode*>(icon->getChildren())) {
                                    if (auto sprite = typeinfo_cast<CCSprite*>(inner)) {
                                        if (sprite->getID() == "Lock") sprite->setVisible(newValue < unlockValue);
                                    }
                                }
                            } else if (auto colourIcon = typeinfo_cast<ColorChannelSprite*>(iconNode)) {
                                for (auto inner : CCArrayExt<CCNode*>(colourIcon->getChildren())) {
                                    if (auto sprite = typeinfo_cast<CCSprite*>(inner)) {
                                        if (sprite->getID() == "Lock") sprite->setVisible(newValue < unlockValue);
                                    }
                                }
                            } else if (auto itemIcon = typeinfo_cast<GJItemIcon*>(iconNode)) {
                                for (auto inner : CCArrayExt<CCNode*>(itemIcon->getChildren())) {
                                    if (auto sprite = typeinfo_cast<CCSprite*>(inner)) {
                                        if (sprite->getID() == "Lock") sprite->setVisible(newValue < unlockValue);
                                    }
                                }
                            }
                        };

                        unlockFunc(iconObject);
                        ++lockCount;
                    }
                }
            }

            unlockIndex++;
        }

        tier++;
    }

    // Completion stars
    for (auto tierNode : CCArrayExt<CCNode*>(pageNode->getChildren())) {
        if (tierNode->getID() != "Tier-Node") continue;

        bool found = false;
        for (auto innerNode : CCArrayExt<CCNode*>(tierNode->getChildren())) {
            if (innerNode->getID() == "Completion-Star-1" || innerNode->getID() == "Completion-Star-2") {
                found = true;
            }
        }

        if (strcmp(iconSprName, "jumps_spr.png"_spr) == 0) {
            startIdx = tier * 8;
            endIdx = (tier == tierCount - 1) ? unlockCount : std::min(startIdx + 8, unlockCount);
        } else {
            startIdx = tier * 10;
            endIdx = (tier == tierCount - 1) ? unlockCount : std::min(startIdx + 10, unlockCount);
        }

        if (!found && newValue >= std::stoi(unlockList[endIdx]->numberString)) {

            auto tierCompletedStar1 = CCSprite::createWithSpriteFrameName("GJ_bigStar_001.png");
            tierCompletedStar1->setID("Tier-Complete-Top");
            auto tierCompletedStarGlow1 = CCSprite::createWithSpriteFrameName("GJ_bigStar_glow_001.png");
            tierCompletedStarGlow1->setID("Tier-Complete-Bottom");
            tierCompletedStarGlow1->setAnchorPoint({0, 0});
            tierCompletedStarGlow1->setPosition({-11, -11});
            tierCompletedStarGlow1->setZOrder(-1);
            tierCompletedStar1->setID("Completion-Star-1");
            tierCompletedStar1->addChild(tierCompletedStarGlow1);

            auto tierCompletedStar2 = CCSprite::createWithSpriteFrameName("GJ_bigStar_001.png");
            tierCompletedStar2->setID("Tier-Complete-Top");
            auto tierCompletedStarGlow2 = CCSprite::createWithSpriteFrameName("GJ_bigStar_glow_001.png");
            tierCompletedStarGlow2->setID("Tier-Complete-Bottom");
            tierCompletedStarGlow2->setAnchorPoint({0, 0});
            tierCompletedStarGlow2->setPosition({-11, -11});
            tierCompletedStarGlow2->setZOrder(-1);
            tierCompletedStar2->setID("Completion-Star-2");
            tierCompletedStar2->addChild(tierCompletedStarGlow2);

            tierCompletedStar1->setAnchorPoint({0, 0});
            tierCompletedStar2->setAnchorPoint({0, 0});
            tierCompletedStar1->setPosition({-72, 8});
            tierCompletedStar2->setPosition({77, 8});
            tierCompletedStar1->setScale(0.5f);
            tierCompletedStar2->setScale(0.5f);
            tierNode->addChild(tierCompletedStar1);
            tierNode->addChild(tierCompletedStar2);
        }

        tier++;
    }

    pageNode->visit();
    pageNode->update(0);
}

std::vector<std::string> Utilities::split(const std::string& str, const std::string& delimiter) {

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