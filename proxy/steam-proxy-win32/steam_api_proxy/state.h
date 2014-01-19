// state.h - Records the state of the app, specifically stuff that's
//           internal and can't be cleanly tossed back to the app via 
//           the existing (and expected) classes/interfaces.

#pragma once

#include <deque>

class SteamUserWrapper;
class SteamFriendsWrapper;
class SteamAppsWrapper;

class AppState
{
  public:
    AppState();
    ~AppState();

    void setAppId(int appid);
    int getAppId();

    void setSafeMode(bool safe);
    bool getSafeMode();

    void addCallbackWrapper(class CallbackWrapper *wrapper);

    SteamUserWrapper *getSteamUser();
    SteamFriendsWrapper *getSteamFriends();
    SteamAppsWrapper *getSteamApps();

  private:
    int appid;

    bool safeMode;

    std::deque<class CallbackWrapper *> callbackWrappers;

    SteamUserWrapper *steamUser;
    SteamFriendsWrapper *steamFriends;
    SteamAppsWrapper *steamApps;
};

extern AppState state;

