
local ChinaMobile = {}

local className = "com/qeeplay/frameworks/ChinaMobile_SDK"

function ChinaMobile.init(params)
    local args = {
        params.appName,
        params.key,
        params.secret,
        params.appId
    }
    luaj.callStaticMethod(className, "GameCommunity_initializeSDK", args)
    return true
end

function ChinaMobile.request(name, params)
    name = string.upper(name)
    if name == "GETACHIEVEMENTS" then
        return CCOpenFeint:getAchievementsLua()

    elseif name == "UNLOCKACHIEVEMENT" then
        local achievementId = tostring(params[1])
        if type(achievementId) ~= "string" then
            echoError("[framework.client.api.GameNetwork.OpenFeint] ERR, request(%s) %s",
                      "unlockAchievement", "invalid achievementId")
        end
        return CCOpenFeint:unlockAchievement(achievementId)

    elseif name == "GETLEADERBOARDS" then
        return CCOpenFeint:getLeaderboardsLua()

    elseif name == "SETHIGHSCORE" then
        local leaderboardId = params[1]
        if type(leaderboardId) ~= "string" then
            echoError("[framework.client.api.GameNetwork.OpenFeint] ERR, request(%s) %s",
                      "setHighScore", "invalid leaderboardId")
            return false
        end
        local score = tonumber(params[2])
        if type(score) ~= "number" then
            echoError("[framework.client.api.GameNetwork.OpenFeint] ERR, request(%s) %s",
                      "setHighScore", "invalid score")
            return false
        end
        local displayText = params[3]
        if type(displayText) ~= "string" then
            echoError("[framework.client.api.GameNetwork.OpenFeint] ERR, request(%s) %s",
                      "setHighScore", "invalid displayText")
            return false
        end
        return CCOpenFeint:setHighScore(leaderboardId, score, displayText)

    else
        echoError("[framework.client.api.GameNetwork.OpenFeint] ERR, request() invalid name %s", name)
    end

    return false
end

function ChinaMobile.show(name, params)
    name = string.upper(name)
    if name == "LEADERBOARDS" and #params < 1 then
        CCOpenFeint:showLeaderboards()

    elseif name == "LEADERBOARD" then
        local leaderboardId = params[1]
        if type(leaderboardId) ~= "string" then
            echoError("[framework.client.api.GameNetwork.OpenFeint] ERR, show(%s) %s",
                      "leaderboards", "invalid leaderboardId")
        else
            CCOpenFeint:showLeaderboards(leaderboardId)
        end

    elseif name == "ACHIEVEMENTS" then
        CCOpenFeint:showAchievements()

    elseif name == "CHALLENGES" then
        CCOpenFeint:showChallenges()

    elseif name == "FRIENDS" then
        CCOpenFeint:showFriends()

    elseif name == "PLAYING" then
        CCOpenFeint:showPlaying()

    elseif name == "MOREGAMES" then
        display.pause()
        luaj.callStaticMethod(className, "GameInterface_viewMoreGames")
        display.resume()

    elseif name == "RECOMMEND" then
        display.pause()
        luaj.callStaticMethod(className, "GameCommunity_launchGameRecommend")
        display.resume()

    else -- DASHBOARD
        display.pause()
        luaj.callStaticMethod(className, "GameCommunity_launchGameCommunity")
        display.resume()
    end
end

function ChinaMobile.exit()
    luaj.callStaticMethod(className, "GameCommunity_exit")
    echoWarning("GameCommunity_exit")
end

return ChinaMobile
