
local device = {}

device.platform    = "unknown"
device.model       = "unknown"

local sharedApplication = CCApplication:sharedApplication()
local target = sharedApplication:getTargetPlatform()
if target == kTargetWindows then
    device.platform = "windows"
elseif target == kTargetMacOS then
    device.platform = "mac"
elseif target == kTargetAndroid then
    device.platform = "android"
elseif target == kTargetIphone or target == kTargetIpad then
    device.platform = "ios"
    if target == kTargetIphone then
        device.model = "iphone"
    else
        device.model = "ipad"
    end
end

local language_ = sharedApplication:getCurrentLanguage()
if language_ == kLanguageChinese then
    language_ = "cn"
elseif language_ == kLanguageFrench then
    language_ = "fr"
elseif language_ == kLanguageItalian then
    language_ = "it"
elseif language_ == kLanguageGerman then
    language_ = "gr"
elseif language_ == kLanguageSpanish then
    language_ = "sp"
elseif language_ == kLanguageRussian then
    language_ = "ru"
else
    language_ = "en"
end

device.language = language_
device.writablePath = CCFileUtils:sharedFileUtils():getWritablePath()
device.cachePath = CCFileUtils:sharedFileUtils():getCachePath()
device.directorySeparator = "/"
device.pathSeparator = ":"
if device.platform == "windows" then
    device.directorySeparator = "\\"
    device.pathSeparator = ";"
end

echoInfo("# device.platform              = " .. device.platform)
echoInfo("# device.model                 = " .. device.model)
echoInfo("# device.language              = " .. device.language)
echoInfo("# device.writablePath          = " .. device.writablePath)
echoInfo("# device.cachePath             = " .. device.cachePath)
echoInfo("# device.directorySeparator    = " .. device.directorySeparator)
echoInfo("# device.pathSeparator         = " .. device.pathSeparator)
echoInfo("#")

function device.showActivityIndicator()
    CCNative:showActivityIndicator()
end

function device.hideActivityIndicator()
    CCNative:hideActivityIndicator()
end

function device.showAlert(title, message, buttonLabels, listener)
    if type(buttonLabels) ~= "table" then
        buttonLabels = {tostring(buttonLabels)}
    end
    local defaultLabel = ""
    if #buttonLabels > 0 then
        defaultLabel = buttonLabels[1]
        table.remove(buttonLabels, 1)
    end

    CCNative:createAlert(title, message, defaultLabel)
    for i, label in ipairs(buttonLabels) do
        CCNative:addAlertButton(label)
    end

    if type(listener) ~= "function" then
        listener = function() end
    end

    CCNative:showAlertLua(listener)
end

function device.cancelAlert()
    CCNative:cancelAlert()
end

function device.getOpenUDID()
    return CCNative:getOpenUDID()
end

function device.openURL(url)
    CCNative:openURL(url)
end

function device.showInputBox(title, message, defaultValue)
    title = title or "INPUT TEXT"
    message = message or "INPUT TEXT, CLICK OK BUTTON"
    defaultValue = defaultValue or ""
    return CCNative:getInputText(title, message, defaultValue)
end

return device
