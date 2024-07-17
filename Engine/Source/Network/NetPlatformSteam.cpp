#include "NetPlatformSteam.h"
#include "Assertion.h"
#include "Log.h"

#if NET_PLATFORM_STEAM

#if PLATFORM_WINDOWS
#pragma comment(lib, "steam_api64.lib")
#pragma comment(lib, "sdkencryptedappticket64.lib")
#endif

void SteamAPIDebugTextHook(int nSeverity, const char* pchDebugText)
{
	// if you're running in the debugger, only warnings (nSeverity >= 1) will be sent
	// if you add -debug_steamapi to the command-line, a lot of extra informational messages will also be sent
	if (nSeverity >= 1)
	{
		LogError(pchDebugText);
		OCT_ASSERT(0);
	}
	else
	{
		LogDebug(pchDebugText);
	}
}

// Lifecycle
void NetPlatformSteam::Create()
{
	if (false /*SteamAPI_RestartAppIfNecessary(k_uAppIdInvalid)*/)
	{
		// if Steam is not running or the game wasn't started through Steam, SteamAPI_RestartAppIfNecessary starts the 
		// local Steam client and also launches this game again.

		// Once you get a public Steam AppID assigned for this game, you need to replace k_uAppIdInvalid with it and
		// removed steam_appid.txt from the game depot.

		return;
	}

	// Initialize SteamAPI, if this fails we bail out since we depend on Steam for lots of stuff.
	// You don't necessarily have to though if you write your code to check whether all the Steam
	// interfaces are NULL before using them and provide alternate paths when they are unavailable.
	//
	// This will also load the in-game steam overlay dll into your process.  That dll is normally
	// injected by steam when it launches games, but by calling this you cause it to always load,
	// even when not launched via steam.
	SteamErrMsg errMsg = { 0 };
	if (SteamAPI_InitEx(&errMsg) != k_ESteamAPIInitResult_OK)
	{
		LogError("SteamAPI_Init() failed: ");
		LogError(errMsg);

		LogError("Fatal Error", "Steam must be running to play this game (SteamAPI_Init() failed).");
		return;
	}

	// set our debug handler
	SteamClient()->SetWarningMessageHook(&SteamAPIDebugTextHook);

	// Ensure that the user has logged into Steam. This will always return true if the game is launched
	// from Steam, but if Steam is at the login prompt when you run your game from the debugger, it
	// will return false.
	if (!SteamUser()->BLoggedOn())
	{
		LogWarning("Steam user is not logged in");
		return;
	}
}

void NetPlatformSteam::Destroy()
{

}

void NetPlatformSteam::Update()
{

}


// Login
void NetPlatformSteam::Login()
{

}

void NetPlatformSteam::Logout()
{

}

bool NetPlatformSteam::IsLoggedIn() const
{
	return SteamUser()->BLoggedOn();
}


// Matchmaking
void NetPlatformSteam::OpenSession()
{

}

void NetPlatformSteam::CloseSession()
{

}

void NetPlatformSteam::BeginSessionSearch()
{

}

void NetPlatformSteam::EndSessionSearch()
{

}

void NetPlatformSteam::UpdateSearch()
{

}

bool NetPlatformSteam::IsSearching() const
{
	return false;
}

#endif