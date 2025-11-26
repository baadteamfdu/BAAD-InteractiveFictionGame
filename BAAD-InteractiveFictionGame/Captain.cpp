#include "Captain.h"

// resetting the captain behavior after the game starts

Captain::Captain()
{
    reset();
}

// setting the booleans as needed. (This is by default behavior)

void Captain::reset()
{
    isAwake = false;
    hasWater = false;
    isFollowing = false;
    hasProtectedOnce = false;
    isAlive = true;
    introduced = false;
    playerName = "";
}

// Getters
bool Captain::getIsAwake() { return isAwake; }
bool Captain::getHasWater() { return hasWater; }
bool Captain::getIsFollowing() { return isFollowing; }
bool Captain::getHasProtectedOnce() { return hasProtectedOnce; }
bool Captain::getIsAlive() { return isAlive; }
bool Captain::getIntroduced() { return introduced; }
string Captain::getPlayerName() { return playerName; }

// Setters
void Captain::setIsAwake(bool awake) { isAwake = awake; }
void Captain::setHasWater(bool water) { hasWater = water; }
void Captain::setIsFollowing(bool follow) { isFollowing = follow; }
void Captain::setHasProtectedOnce(bool used) { hasProtectedOnce = used; }
void Captain::setIsAlive(bool alive) { isAlive = alive; }
void Captain::setIntroduced(bool intro) { introduced = intro; }
void Captain::setPlayerName(const string& name) { playerName = name; }

// Can the captain still protect the player exactly once
bool Captain::canProtectPlayer()
{
    return isAwake && isAlive && isFollowing && !hasProtectedOnce;
}
