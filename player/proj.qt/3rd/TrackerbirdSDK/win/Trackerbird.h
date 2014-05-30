// ==================================================================
//               *** TRACKERBIRD SOFTWARE ANALYTICS ***  
//               ******** www.trackerbird.com  ********
// ==================================================================
// © 2014 Trackerbird. All rights reserved.
//
// SDK Version: 3.2.6 (C++)
// Release date: 29 May 2014
//
// You may get the latest version from: http://docs.trackerbird.com
// For customer support please visit: http://helpdesk.trackerbird.com
// ==================================================================
//

#define TRACKERBIRD_API extern "C" __declspec(dllexport) 

#define	TB_OK							1
#define TB_FUNCTION_NOT_AVAIL			-1	
#define TB_CONN_ERROR					-2
#define TB_AUTH_FAILURE					-3
#define TB_SERVER_ERROR					-4
#define TB_CONFIG_NOT_CREATED			-5
#define TB_CONFIG_ALREADY_CREATED		-6
#define TB_APP_CONFIG_NOT_LOADED		-7
#define TB_INVALID_PARAMETER			-9
#define TB_INVALID_PATH					-10
#define TB_ACCESS_DENIED				-11

#define TB_START_OK						2
#define TB_START_LOADING				1
#define TB_START_NOT_CALLED				0
#define TB_START_CONNECTION_ERROR		-2
#define TB_START_AUTH_FAILURE			-3
#define TB_START_SERVER_ERROR			-4
#define TB_START_RESPONSE_ERROR			-5
#define TB_START_GENERIC_ERROR			-6

#define TB_CONNCHECK_OK					1

#define TB_KEYTYPE_EVALUATION			0
#define TB_KEYTYPE_PURCHASED			1
#define TB_KEYTYPE_FREEWARE				2
#define TB_KEYTYPE_UNKNOWN				3
#define TB_KEYTYPE_NFR					4
#define TB_KEYTYPE_CUSTOM1				5
#define TB_KEYTYPE_CUSTOM2				6
#define TB_KEYTYPE_CUSTOM3				7

#define TB_MESSAGETYPE_ALL				0
#define TB_MESSAGETYPE_TEXT				1
#define TB_MESSAGETYPE_URL				2

#define TB_VERSIONCHECK_UP_TO_DATE		0
#define TB_VERSIONCHECK_NEW_VER_AVAIL	1

#define TB_PRIVACYMODE_OFF				0
#define TB_PRIVACYMODE_LOW				1
#define TB_PRIVACYMODE_HIGH				2

#define TB_KEY_ACTIVE_INDEX				0
#define TB_KEY_BLACKLIST_INDEX			1
#define TB_KEY_EXPIRED_INDEX			2
#define TB_KEY_WHITELIST_INDEX			3
#define TB_KEY_TYPE_INDEX				4

#define TB_START_SYN					0
#define TB_START_NO_REACHOUT			-1
#define TB_START_NO_SYN					-2

#define TB_STOP_SYN						0
#define TB_STOP_NO_SYN                  -1

typedef int TBRESULT;

TRACKERBIRD_API TBRESULT tbCreateConfig(wchar_t* szUrl, wchar_t* szProductID, wchar_t* szProductVersion, wchar_t* szProductBuildNumber, BOOL bMultiSessionEnabled);
TRACKERBIRD_API TBRESULT tbSetFilePath(wchar_t* filePath);
TRACKERBIRD_API TBRESULT tbStart(int doSync = TB_START_SYN);
TRACKERBIRD_API TBRESULT tbSync(BOOL getReachout = TRUE);
TRACKERBIRD_API TBRESULT tbKeyCheck(wchar_t* licKey, int *tbLicenseArray);
TRACKERBIRD_API TBRESULT tbKeyChanged(wchar_t* newKey, int *tbLicenseArray);
TRACKERBIRD_API TBRESULT tbVersionCheck(wchar_t* internalNewVersion, wchar_t* userFriendlyNewVersion, wchar_t* downloadURL, wchar_t* changelogURL);
TRACKERBIRD_API TBRESULT tbMessageCheck(wchar_t* message, int* messageType);
TRACKERBIRD_API TBRESULT tbMessageCheckWithMessageType(wchar_t* message, int messageTypeExpected);
TRACKERBIRD_API TBRESULT tbSetLicense(int keyType, BOOL keyExpired, BOOL keyActivated, BOOL keyBlacklisted, BOOL keyWhitelisted);
TRACKERBIRD_API TBRESULT tbSetPrivacyMode(int privacyMode);
TRACKERBIRD_API TBRESULT tbSetProductEdition(wchar_t* productEdition);
TRACKERBIRD_API TBRESULT tbSetProductLanguage(wchar_t* productLanguage);
TRACKERBIRD_API TBRESULT tbSetProductVersion(wchar_t* productVersion);
TRACKERBIRD_API TBRESULT tbSetProductBuildNumber(wchar_t* productBuildNumber);
TRACKERBIRD_API TBRESULT tbStartStatus();
TRACKERBIRD_API TBRESULT tbStop(int doSync = TB_STOP_SYN);
TRACKERBIRD_API TBRESULT tbSessionStart(wchar_t* sessionID);
TRACKERBIRD_API TBRESULT tbSessionStop(wchar_t* sessionID);
TRACKERBIRD_API TBRESULT tbStartAutoSync(BOOL getReachout = TRUE);
TRACKERBIRD_API TBRESULT tbStopAutoSync();
TRACKERBIRD_API TBRESULT tbGetPrivacyMode();
TRACKERBIRD_API TBRESULT tbSetDefaultProxyCredentials(wchar_t* username, wchar_t* password);
TRACKERBIRD_API TBRESULT tbExceptionTrack(wchar_t* className, wchar_t* methodName, wchar_t* exceptionMessage, wchar_t* stackTrace);
TRACKERBIRD_API TBRESULT tbEventTrack(wchar_t* category, wchar_t* eventName, wchar_t* sessionID);
TRACKERBIRD_API TBRESULT tbEventTrackNum(wchar_t* category, wchar_t* eventName, double customValue, wchar_t* sessionID);
TRACKERBIRD_API TBRESULT tbEventTrackTxt(wchar_t* category, wchar_t* eventName, wchar_t* customValue, wchar_t* sessionID);
TRACKERBIRD_API TBRESULT tbConnectionCheck(wchar_t* url);
TRACKERBIRD_API TBRESULT tbSetProxy(wchar_t* address, wchar_t* username, wchar_t* password);
TRACKERBIRD_API TBRESULT tbSetCustomProperty(unsigned short index, wchar_t* customValue);
