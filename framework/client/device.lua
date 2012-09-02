
local M = {}

M.host     = "ios"
M.model    = "iphone"
M.platform = "ios"

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

log.warning("# device.host                  = "..M.host)
log.warning("# device.model                 = "..M.model)
log.warning("# device.platform              = "..M.platform)
log.warning("# device.language              = "..M.language)
log.warning("#")

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
