#pragma once
#pragma once
#include <string>
using namespace std;

class Captain
{
private:
    bool isAwake;                     //  whether the captain has been woken from cryo.
    bool hasWater;                    //  whether the captain has been served water.
    bool isFollowing;                 //  whether the captain is following the player.
    bool hasProtectedOnce;            //  check if the captain has saved the player already.
    bool isAlive;                     //  check if the captain is alive.
    bool introduced;                  //  check if the captain has been introduced with the player.
    string playerName;                //  storing  playername into captain's class for dialogue enhancements. 

public:
    Captain();

    // Getters
    bool getIsAwake();
    bool getHasWater();
    bool getIsFollowing();
    bool getHasProtectedOnce();
    bool getIsAlive();
    bool getIntroduced();
    string getPlayerName();

    // Setters
    void setIsAwake(bool awake);
    void setHasWater(bool water);
    void setIsFollowing(bool follow);
    void setHasProtectedOnce(bool used);
    void setIsAlive(bool alive);
    void setIntroduced(bool intro);
    void setPlayerName(const string& name);

    // Helper: can the captain still save the player once
    bool canProtectPlayer();

    // Reset (which is not needed just doing it anyway).
    void reset();
};
