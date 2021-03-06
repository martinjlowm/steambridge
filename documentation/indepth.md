# The short, but sufficiently indepth, version

1. Configure with **make config**.  See *configure/utilies.py* for more
   information on how to change the configuration.
2. Copy *libraries/common/include/config.h* to Windows'
   *libraries/common/include/*.
3. Compile the Visual Studio solution (Release build).  Copy
   *steam_api_proxy.dll* in *libraries/Release* to the Linux.
4. Install *build-essential*, *g++*, *g++-multilib*, *wine1.7*, and
   *wine1.7-dev*; or similar.
5. Compile the Winelib DLL by running **make**.
6. Install SteamBridge with **make install**.
  * Unlike the initial SteamBridge release, this does copy to the system.
7. Download an application using *steambridge download*.
  * Various applications won't download correctly, and you'll need
    to use the Windows native Steam client.  Copy the appmanifest file
    in *SteamApps* and the installation directory in *SteamApps/common*
    to *~/.steam/root/SteamApps/* manually.
6. Setup the application using *steambridge setup*.
7. Execute the application using the new desktop shortcut, or run
   *steambridge execute*.
  * You can add this .desktop file back to Steam.  However, it won't be
    imported 100% correctly, and you'll need to add the appid as a
    parameter to *steambridge execute*.

# Windows Proxy DLL

The compilation spits out two DLLs: *steam_api_bridge.dll* and
*steam_api_proxy.dll*.

The Bridge DLL is a simple stub library that implements the same symbols
as the Winelib library.  This is necessary for proxy to correctly link.

Proxy is a drop-in replacement for *steam_api.dll*.  Instead of
communicating with the Windows Steam client inside Wine, it routes them
to the Linux *libsteam_api.dll*, using object pointers retrieved by the
Winelib Bridge.

Note that Proxy depends on the config.h generated by **make config**.
It only uses the Version and App-Name directives, so it doesn't need to
be kept very insync.  Eventually, this will be handled better.

# Linux Bridge Winelib library

Configure with **make config**.  This generates a few configuration
files, notably config.h and config.py.  See *configure/utilities.py*
for more information.

Compile with run **make**.  All, clean, rebuild, config, winemaker,
and install are implemented.  Uninstall is on the horizon as well.
Winemaker reruns the winemaker command, which generates the Bridge
specific Makefile.  This should only be necessary if you add or remove
files.  Install installs to your system.  Unlike the first release of
SteamBridge, this is installed to the system, rather than entirely to
the current home directory.

*steam_api_bridge.dll.so* is the compiled binary, a Winelib
library for use with Wine.

# Deployment and execution notes

* Output is stored in ~/.steam/root/SteamBridge/appdb/[appid]/\*.txt.
  * This is only for output generated by Wine.  Errors by the Python
    scripts themselves are not stored (yet).
* The built-in WINE Visual C+++ Runtime (2010, aka msvcp100.dll) works
  mostly fine.
  * In my test setup, it doesn't work when starting a SteamBridge through
    Linux Steam.  Seems to be an issue setting up stdin/stdout.
  * The real DLL can be installed using **winetricks vcrun2010**.
    Change vcrun2010 if you use a different version of Visual Studio.
* You can run Wine Steam applications through Steam Linux using Steam's
  "Add Non-Steam Game..." feature.  See the .desktop file created by
  Configure.
    * The Steam overlay loads (!) and works mostly correctly (!).
      Steam API calls impact the injected Overlay correctly.
    * The content of the Overlay isn't tied to the appid.  It's
      generic links and content, unfortunately.
* Run time is properly recorded by Steam!
* *libsteam_api.so* is forward compatible, so long as newer function calls
  aren't used (which will crash, hopefully quickly).  The Source 1 SDK is
  behind the library used in Ethan Meteor Hunter, but appears to run fine.

