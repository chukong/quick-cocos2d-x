
local device = {}

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

device.platform = "unknown"
device.host     = "simulator"
device.model    = "unknown"

local target = CCApplication:sharedApplication():getTargetPlatform()
if target == kTargetWindows then
    device.platform = "windows"
elseif target == kTargetLinux then
    device.platform = "linux"
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
elseif target == kTargetBlackBerry then
    device.platform = "blackberry"
end

if CCApplication:sharedApplication():getTargetEnvironment() == kTargetDevice then
    device.host = "device"
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

device.language = language_
device.writeablePath = CCFileUtils:sharedFileUtils():getWriteablePath()

echoWarning("# device.host                  = "..device.host)
echoWarning("# device.model                 = "..device.model)
echoWarning("# device.platform              = "..device.platform)
echoWarning("# device.language              = "..device.language)
echoWarning("#")

function device.showActivityIndicator(style)
    if type(style) ~= "number" then
        style = CCActivityIndicatorViewStyleWhiteLarge
    end
    CCNative:showActivityIndicator(style)
end

function device.hideActivityIndicator()
    CCNative:hideActivityIndicator()
end

function device.showAlert(title, message, cancelButtonTitle, listener, ...)
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

function device.cancelAlert()
    CCNative:cancelAlert()
end

function device.getOpenUDID()
    return CCNative:getOpenUDID()
end

function device.openURL(url)
    CCNative:openURL(url)
end

function device.getInputText(title, message, defaultValue)
    title = title or "INPUT TEXT"
    message = message or "INPUT TEXT, CLICK OK BUTTON"
    defaultValue = defaultValue or ""
    return CCNative:getInputText(title, message, defaultValue)
end

return device
