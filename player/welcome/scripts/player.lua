
require("framework.init") -- for cjson

local simpleList = {
    {id="demo1_id", text="<b>One Demo</b> <br/> <img src=:/QuickIcon.png</img>"},
    {id="demo2_id", text="<b>Two Demo</b> <br/> <img src=:/QuickIcon.png</img>"},
}

function getDemoData()
    -- body
    local demoDataList = {{id="demo1", text="<b>One Demo</b> <br/> <img src=:/fQuickIcon.png</img>"}
                  , {id="demo2", text="<b>Two Demo</b> <br/> <img src=:/QuickIcon.png</img>"}}

    QT_INTERFACE("core.addDemoList", json.encode(demoDataList))
end

-- @return -p @packageName -f -r portrait -o @projectPath
function GET_CREATE_PROJECT_COMMAND_ARGS( projectPath, packageName, isPortrait )
    local screen = (isPortrait and " -r portrait") or " -r landscape"

    local cmd = "-f -p "..packageName..screen.." -o "..projectPath
    return  cmd, " "
end

function GET_QUICK_SIMPLES()
    return json.encode(simpleList)
end

function openDemo( demoId )
    QT_INTERFACE("core.openProject")
end

function LUA_Interface(messageId, messageData)
    -- print("messageId: ", messageId, "data : ", messageData)
    if messageId == "core.openDemo" then
        openDemo(messageData)
    end
end

function PlayerLoginCallback(userName, password)
    print("Get username: ", userName, " passworld: ", password)
    -- return true, ""
    -- return false, "user name or password is invalid"
    return true, "user name or password is error"
end

function __QT_INIT()
    local notificationCenter = CCNotificationCenter:sharedNotificationCenter()
    notificationCenter:registerScriptObserver(nil, function() QT_INTERFACE("core.newProject") end, "WELCOME_NEW_PROJECT")
    notificationCenter:registerScriptObserver(nil, function() QT_INTERFACE("core.openProject") end, "WELCOME_OPEN_PROJECT")
    notificationCenter:registerScriptObserver(nil, function() QT_INTERFACE("core.openDemo") end, "WELCOME_LIST_SAMPLES")
    notificationCenter:registerScriptObserver(nil, function() QT_INTERFACE("core.openURL", "http://quick.cocoachina.com/wiki/doku.php?id=zh_cn") end,"WELCOME_OPEN_COMMUNITY")
    notificationCenter:registerScriptObserver(nil, function() QT_INTERFACE("core.openURL", "http://quick.cocoachina.com/wiki/doku.php?id=zh_cn") end,"WELCOME_OPEN_DOCUMENTS")
end

__QT_INIT()