
local M = {}

-- enum TargetPlatform
-- {
--     kTargetWindows,
--     kTargetLinux,
--     kTargetMacOS,
--     kTargetAndroid,
--     kTargetIphone,
--     kTargetIpad,
--     kTargetBlackBerry,
-- };

M.platform = "unknown"
M.host     = "simulator"
M.model    = "unknown"

local target = CCApplication:sharedApplication():getTargetPlatform()
if target == kTargetWindows then
    M.platform = "windows"
elseif target == kTargetLinux then
    M.platform = "linux"
elseif target == kTargetMacOS then
    M.platform = "mac"
elseif target == kTargetAndroid then
    M.platform = "android"
elseif target == kTargetIphone or target == kTargetIpad then
    M.platform = "ios"
    if target == kTargetIphone then
        M.model = "iphone"
    else
        M.model = "ipad"
    end
elseif target == kTargetBlackBerry then
    M.platform = "blackberry"
end

if CCApplication:sharedApplication():getTargetEnvironment() == kTargetDevice then
    M.host = "device"
end

local language_ = CCApplication:sharedApplication():getCurrentLanguage()
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

M.language = language_
M.writeablePath = CCFileUtils:sharedFileUtils():getWriteablePath()

echoWarning("# device.host                  = "..M.host)
echoWarning("# device.model                 = "..M.model)
echoWarning("# device.platform              = "..M.platform)
echoWarning("# device.language              = "..M.language)
echoWarning("#")

function M.showActivityIndicator(style)
    if type(style) ~= "number" then
        style = CCActivityIndicatorViewStyleWhiteLarge
    end
    CCNative:showActivityIndicator(style)
end

function M.hideActivityIndicator()
    CCNative:hideActivityIndicator()
end

function M.showAlert(title, message, cancelButtonTitle, listener, ...)
    CCNative:createAlert(title, message, cancelButtonTitle)
    for i = 1, select("#", ...) do
        local buttonTitle = select(i, ...)
        CCNative:addAlertButton(buttonTitle)
    end
    if type(listener) ~= "function" then
        listener = function() end
    end
    CCNative:showAlertLua(listener)
end

function M.cancelAlert()
    CCNative:cancelAlert()
end

function M.getOpenUDID()
    return CCNative:getOpenUDID()
end

function M.openURL(url)
    CCNative:openURL(url)
end

return M
