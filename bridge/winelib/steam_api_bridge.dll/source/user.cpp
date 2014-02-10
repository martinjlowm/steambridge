// user.cpp - Implements various functions related to the ISteamUser class.

#include <cstdio>

#include <steam_api.h>

#define NOMINMAX
#include <windef.h>
#include <winbase.h>
#include <wine/debug.h>

#include "api.h"
#include "core.h"
#include "logging.h"

WINE_DEFAULT_DEBUG_CHANNEL(steam_bridge);

extern "C"
{

STEAM_API_BRIDGE_API void steam_bridge_SteamUser_GetSteamID(
    ISteamUser *steamUser, CSteamID *id)
{
  WINE_TRACE("(%p,%p)\n", steamUser, id);

  if (!steamUser) __ABORT("NULL steamUser pointer!");
  if (!id) __ABORT("NULL CSteamID result pointer!");

  *id = steamUser->GetSteamID();
  WINE_TRACE("Got steamUser ID of %lu\n", id->ConvertToUint64());
}

STEAM_API_BRIDGE_API bool steam_bridge_SteamUser_BLoggedOn(
    ISteamUser *steamUser)
{
  WINE_TRACE("(%p)\n", steamUser);

  if (!steamUser)
    __ABORT("NULL steamUser pointer!");

  return steamUser->BLoggedOn();
}

STEAM_API_BRIDGE_API int steam_bridge_SteamUser_InitiateGameConnection(
    ISteamUser *steamUser, void *pAuthBlob, int cbMaxAuthBlob,
    CSteamID steamIDGameServer, uint32 unIPServer, uint16 usPortServer,
    bool bSecure)
{
  WINE_TRACE("(%p,%p,%i,%llu,%u,%hu,%i)\n", steamUser, pAuthBlob,
      cbMaxAuthBlob, steamIDGameServer.ConvertToUint64(), unIPServer,
      usPortServer, bSecure);

  return steamUser->InitiateGameConnection(pAuthBlob, cbMaxAuthBlob,
      steamIDGameServer, unIPServer, usPortServer, bSecure);
}

STEAM_API_BRIDGE_API void steam_bridge_SteamUser_TerminateGameConnection(
    ISteamUser *steamUser, uint32 unIPServer, uint16 usPortServer)
{
  WINE_TRACE("(%p,%u,%hu)\n", steamUser, unIPServer, usPortServer);

  return steamUser->TerminateGameConnection(unIPServer, usPortServer);
}

STEAM_API_BRIDGE_API ISteamUser *steam_bridge_SteamUser()
{
  WINE_TRACE("\n");

  if (!context)
  {
    WINE_ERR("Context is NULL, Init either failed or wasn't called\n");
    return NULL;
  }

  return context->getSteamUser();
}

} // extern "C"

