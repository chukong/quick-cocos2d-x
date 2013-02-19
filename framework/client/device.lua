--[[

Copyright (c) 2011-2012 qeeplay.com

http://dualface.github.com/quick-cocos2d-x/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--[[--

Query information about the system (get device information, current language, etc) and execute system functions (show alert view, show input box, etc).

<br />

Following properties predefined:

-   **device.platform** the platform name (the OS name), i.e. one of the following: ios, android, blackberry, mac, windows, linux.

-   **device.environment** returns the environment that the app is running in. i.e. one of the following: simulator, device.

-   **device.model** returns the device model (as specified by the manufacturer) :

    - On iOS: return iPhone, iPad
    - On Android: return Android device model name
    - On Mac, windows, linux: return "unknown"

-   **device.language** returns the default language on the device :

    Value       | Language
    ----------- | -------------
    cn          | Chinese
    fr          | French
    it          | Italian
    gr          | German
    sp          | Spanish
    ru          | Russian
    jp          | Japanese
    en          | English

-   **device.writeablePath** returns the writeable path.

]]

local device = {}

device.platform    = "unknown"
device.environment = "simulator"
device.model       = "unknown"

local sharedApplication = CCApplication:sharedApplication()
local target = sharedApplication:getTargetPlatform()
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

if sharedApplication.getTargetEnvironment and sharedApplication:getTargetEnvironment() == kTargetDevice then
    device.environment = "device"
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
device.writeablePath = CCFileUtils:sharedFileUtils():getWriteablePath()

echoInfo("# device.platform              = " .. device.platform)
echoInfo("# device.environment           = " .. device.environment)
echoInfo("# device.model                 = " .. device.model)
echoInfo("# device.language              = " .. device.language)
echoInfo("# device.writeablePath         = " .. device.writeablePath)
echoInfo("#")

--[[--

Displays a platform-specific activity indicator.

### Note:

Supported platform: ios, android.

]]
function device.showActivityIndicator()
    CCNative:showActivityIndicator()
end

--[[--

Hides activity indicator.

### Note:

Supported platform: ios, android.

]]
function device.hideActivityIndicator()
    CCNative:hideActivityIndicator()
end

--[[--

Displays a popup alert box with one or more buttons. Program activity, including animation, will continue in the background, but all other user interactivity will be blocked until the user selects a button or cancels the dialog.

### Paramters:

-   string **title** The title string displayed in the alert

-   string **message** Message string displayed in the alert text.

-   table **buttonLabels** Table of strings, each of which will create a button with the corresponding label.

-   function **listener** The listener to be notified when a user presses any button in the alert box.

### Note:

Supported platform: ios, android, mac.

]]
function device.showAlert(title, message, buttonLabels, listener)
    buttonLabels = totable(buttonLabels)
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

--[[--

Dismisses an alert box programmatically.

For example, you may wish to have a popup alert that automatically disappears after ten seconds even if the user doesn’t click it. In that case, you could call this function at the end of a ten-second timer.

### Note:

Supported platform: ios, android, mac.

]]
function device.cancelAlert()
    CCNative:cancelAlert()
end

--[[--

Returns OpenUDID for device.

> OpenUDID is a drop-in replacement for the deprecated uniqueIdentifier property of the UIDevice class on iOS (a.k.a. UDID) and otherwise is an industry-friendly equivalent for iOS and Android.

### Returns:

-   string OpenUDID

### Note:

Supported platform: ios, android, mac.

]]
function device.getOpenUDID()
    return CCNative:getOpenUDID()
end

--[[--

Open a web page in the browser; create an email; or call a phone number.

Note: Executing this function will make the app background and switch to the built-in browser, email or phone app.

### Parameters:

-   string **url** url can be one of the following:

    -   Web link: "http://dualface.github.com/quick-cocos2d-x/"

    -   Email address: "mailto:nobody@mycompany.com".

        The email address url can also contain subject and body parameters, both of which must be url encoded.<br />
        Example: "mailto:nobody@mycompany.com?subject=Hi%20there&body=I%20just%20wanted%20to%20say%2C%20Hi!"<br />
        Try this URL encoder to encode your text.

    -   Phone number: "tel:123-456-7890"

### Note:

Supported platform: ios, android.

]]
function device.openURL(url)
    CCNative:openURL(url)
end

--[[--

Displays a popup input dialog with ok and cancel button.

### Parameters:

-   string **title** The title string displayed in the input dialog
-   string **message** Message string displayed in the input dialog
-   string **defaultValue** Displayed in the text box.

### Returns:

-   string User entered text. If uesr cancel input dialog, return nil.

### Note:

Supported platform: mac, windows.

]]
function device.showInputBox(title, message, defaultValue)
    title = title or "INPUT TEXT"
    message = message or "INPUT TEXT, CLICK OK BUTTON"
    defaultValue = defaultValue or ""
    return CCNative:getInputText(title, message, defaultValue)
end

return device
