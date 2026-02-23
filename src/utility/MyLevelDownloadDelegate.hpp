#pragma once

#ifndef MYLEVELDOWNLOADDELEGATE_HPP
#define MYLEVELDOWNLOADDELEGATE_HPP

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/binding/GameLevelManager.hpp>

using namespace geode::prelude;

#include <Geode/binding/LevelManagerDelegate.hpp>
class MyLevelDownloadDelegate : public LevelManagerDelegate {
private:

    int id = 122518349; //Iris by me: 114471227, my niece's level: 122518349
public:

    static MyLevelDownloadDelegate* get() {

        static MyLevelDownloadDelegate instance;
        return &instance;
    }

    void loadLevelsFinished(CCArray* levels, const char* key, int) override;
    void loadLevelsFailed(const char* key, int) override;
};

#endif