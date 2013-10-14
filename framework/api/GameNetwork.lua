
--[[--

Game Network allows access to 3rd party libraries that enables social gaming features
such as public leaderboards and achievements.

Currently, Game Center (iOS only) libraries are supported.

@module framework.api.GameNetwork

]]

local GameNetwork = {}

local provider = __FRAMEWORK_GLOBALS__["api.GameNetwork"]

--[[--

Initializes an app with the parameters (e.g., product key, secret, display name, etc.)
required by the game network provider.

**Syntax:**

    -- OpenFeint
    framework.api.GameNetwork.init("openfeint", {
        productKey  = ...,
        secret      = ...,
        displayName = ...,
    })

    -- GameCenter
    framework.api.GameNetwork.init("gamecenter", {
        listener = ...
    })

**Example:**

    require("framework.api.GameNetwork")
    framework.api.GameNetwork.init("openfeint", {
        productKey  = ...,
        secret      = ...,
        displayName = ...
    })

    --
    local achievements = framework.api.GameNetwork.request("getAchievements")
    dump(achievements, "All achievements")

    local leaderboards = framework.api.GameNetwork.request("getLeaderboards")
    dump(leaderboards, "All leaderboards")

    local score = math.random(100, 200)
    local displayText = string.format("My score is %d", score)
    framework.api.GameNetwork.request("setHighScore", "916960912", score, displayText)

    local i = math.random(#achievements)
    framework.api.GameNetwork.request("unlockAchievement", achievements[i].id)

    framework.api.GameNetwork.show("dashboard")

**Note:**

GameNetwork only supports one provider at a time (you cannot call this API multiple times for
different providers).

<br />

@param providerName
String of the game network provider. ("gamecenter", case insensitive)

@param params
If using GameCenter, the params.listener allows you to specify a callback function.
(Instead of secret keys, your bundle identifier is used automatically to identify your app.)
On successful login, event.data will be 'true'. On unsuccessful init, event.data will be false.
When problems such as network errors occur, event.errorCode (integer) and event.errorString
(string) will be defined.

Also be aware that iOS backgrounding will cause your app to automatically log out your user
from Game Center. When the app is resumed, Game Center will automatically try to re-login
your user. The callback function you specified here will be invoked again telling you the
result of that re-login attempt. Thus, this callback function exists for the life of your
application. With Game Center, it is advisable to avoid calling other Game Center functions
when the user is not logged in.

@return Nothing.

]]
function GameNetwork.init(providerName, params)
    if provider then
        echoError("[framework.api.GameNetwork] ERR, init() GameNetwork already init")
        return false
    end

    if type(params) ~= "table" then
        echoError("[framework.api.GameNetwork] ERR, init() invalid params")
        return false
    end

    providerName = string.upper(providerName)
    if providerName == "GAMECENTER" then
        provider = require("framework.api.gamenetwork.GameCenter")
    elseif providerName == "OPENFEINT" then
        provider = require("framework.api.gamenetwork.OpenFeint")
    elseif providerName == "CHINAMOBILE" then
        provider = require("framework.api.gamenetwork.ChinaMobile")
    else
        echoError("[framework.api.GameNetwork] ERR, init() invalid providerName: %s", providerName)
        return false
    end

    provider.init(params)
    __FRAMEWORK_GLOBALS__["api.GameNetwork"] = provider
end

--[[--
Send or request information to/from the game network provider:

**Syntax:**

    GameNetwork.request( command [, params ...] )

**Example:**

    -- For OpenFeint:
    -- setHighScore, leaderboard id, score, display text
    GameNetwork.request("setHighScore", "abc123", 99, "99 sec")

    -- unlockAchievement, achievement id
    GameNetwork.request("unlockAchievement", "1242345322")


**OpenFeint**

Command supported by the OpenFeint provider:

-   getAchievements:

        local achievements = framework.api.GameNetwork.request("getAchievements")
        for achievementId, achievement in pairs(achievements) do
            -- achievement.id (string)
            -- achievement.title (string)
            -- achievement.description (string)
            -- achievement.iconUrl (string)
            -- achievement.gameScore (integer)
            -- achievement.isUnlocked (boolean)
            -- achievement.isSecret (boolean)
        end

-   unlockAchievement: achievement id

        framework.api.GameNetwork.request("unlockAchievement", "1242345322")

-   getLeaderboards:

        local leaderboards = framework.api.GameNetwork.request("getLeaderboards")
        for i, leaderboard = ipairs(leaderboards) do
            -- leaderboard.id (string)
            -- leaderboard.name (string)
            -- leaderboard.currentUserScore (integer)
            -- leaderboard.currentUserScoreDisplayText (string)
            -- leaderboard.descendingScoreOrder (boolean)
        end

-   setHighScore: leaderboard id, score, display text

        framework.api.GameNetwork.request("setHighScore", "abc123", 99, "99 sec")


**GameCenter**

Coming soon.

<br />

@param command
Command string supported by the provider (case insensitive).

@param ...
Parmeters used in the commands.

@return Nothing.

]]
function GameNetwork.request(command, ...)
    if not provider then
        echoError("[framework.api.GameNetwork] ERR, request() GameNetwork not init")
        return
    end

    return provider.request(command, {...})
end

--[[--
Shows (displays) information from game network provider on the screen.

**Syntax:**

    framework.api.GameNetwork.show(command [, params] )

**Example:**

    framework.api.GameNetwork("leaderboards")

**OpenFeint:**

Command supported by the OpenFeint provider.

-   leaderboard: leaderboard id

        framework.api.GameNetwork.show("leaderboard", "abc123")

-   leaderboards:

        framework.api.GameNetwork.show("leaderboards")

-   achievements:

        framework.api.GameNetwork.show("achievements")

-   challenges:

        framework.api.GameNetwork.show("challenges")

-   friends:

        framework.api.GameNetwork.show("friends")

-   playing:

        framework.api.GameNetwork.show("playing")

-   dashboard:

        framework.api.GameNetwork.show("dashboard")


**GameCenter:**

Coming soon.

<br />

@param command
Strings supported by provider.

@param ...
Parameters used by command.

@return Nothing.

]]
function GameNetwork.show(command, ...)
    if not provider then
        echoError("[framework.api.GameNetwork] ERR, request() GameNetwork not init")
        return
    end

    provider.show(command, {...})
end

function GameNetwork.exit()
    if not provider then
        echoError("[framework.api.GameNetwork] ERR, request() GameNetwork not init")
        return
    end

    provider.exit()
end

return GameNetwork
