// state.h - Records the state of the app, specifically stuff that's
//           internal and can't be cleanly tossed back to the app via 
//           the existing (and expected) classes/interfaces.

#pragma once

#include <deque>

class SteamClientWrapper;
class SteamUserWrapper;
class SteamFriendsWrapper;
class SteamAppsWrapper;
class SteamUserStatsWrapper;
class SteamUtilsWrapper;

class AppState
{
  public:
    AppState();
    ~AppState();

    void setAppId(int appid);
    int getAppId();

    void setSafeMode(bool safe);
    bool getSafeMode();

    void addCallback(class CCallbackBase *callback);

    SteamClientWrapper *getSteamClient();
    SteamUserWrapper *getSteamUser();
    SteamFriendsWrapper *getSteamFriends();
    SteamAppsWrapper *getSteamApps();
    SteamUserStatsWrapper *getSteamUserStats();
    SteamUtilsWrapper *getSteamUtils();

  private:
    int appid;

    bool safeMode;

    std::deque<class CCallbackBase *> callbacks;

    SteamClientWrapper *steamClient;
    SteamUserWrapper *steamUser;
    SteamFriendsWrapper *steamFriends;
    SteamAppsWrapper *steamApps;
    SteamUserStatsWrapper *steamUserStats;
    SteamUtilsWrapper *steamUtils;
};

extern AppState state;
