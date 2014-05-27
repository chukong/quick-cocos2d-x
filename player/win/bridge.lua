
-- string.split()

function lua_string_split(s, p)
    local rt= {}
    string.gsub(s, '[^'..p..']+', function(w) table.insert(rt, w) end )
    return rt
end
  
-- helper

-- @return -p @packageName -f -r portrait -o @projectPath
function GET_CREATE_PROJECT_COMMAND_ARGS( projectPath, packageName, isPortrait )
    local screen = (isPortrait and " -r portrait") or " -r landscape"

    local cmd = "-f -p "..packageName..screen.." -o "..projectPath
    return  cmd, " "
end

-- core

local core = {}
function core.openDemo( demoId )
    QT_INTERFACE("core.openProject")
end

function core.login( data )
    user = json.decode(data)
    -- process user.user & user.pwd
    print(data)
end

function core.positionNofity(name)
    local notificationCenter = CCNotificationCenter:sharedNotificationCenter()
    notificationCenter:postNotification(name)
end


-- player : register submodule

local PLAYER = {core=core}

-- interface for player

function LUA_Interface(messageId, messageData)
    local messageList = lua_string_split(messageId, ".")
    local messageSize = #messageList;

    if messageSize == 1 then
        PLAYER[messageId](messageData)
    else
        local object = PLAYER[messageList[1]]
        for i=2, messageSize-1 do
            object = object[messageList[i]]
            i=i+1
        end
        local functionName = messageList[messageSize]

        object[functionName](messageData)
    end

end

-- init 
function __QT_INIT()
    local notificationCenter = CCNotificationCenter:sharedNotificationCenter()
    notificationCenter:registerScriptObserver(nil, function() QT_INTERFACE("core.newProject") end, "WELCOME_NEW_PROJECT")
    notificationCenter:registerScriptObserver(nil, function() QT_INTERFACE("core.openProject") end, "WELCOME_OPEN_PROJECT")
    notificationCenter:registerScriptObserver(nil, function(x, y) 
        local strObj = tolua.cast(y, "CCString") 
        -- QT_INTERFACE("core.onOpenProjectWithArgs", strObj:getCString()) 
        QT_INTERFACE("core.onCreateNewPlayerWithArgs", strObj:getCString())
        end, "WELCOME_OPEN_PROJECT_ARGS")
    notificationCenter:registerScriptObserver(nil, function() QT_INTERFACE("core.openURL", "http://quick.cocoachina.com/wiki/doku.php?id=zh_cn") end,"WELCOME_OPEN_COMMUNITY")
    notificationCenter:registerScriptObserver(nil, function() QT_INTERFACE("core.openURL", "http://quick.cocoachina.com/wiki/doku.php?id=zh_cn") end,"WELCOME_OPEN_DOCUMENTS")
end

__QT_INIT()
