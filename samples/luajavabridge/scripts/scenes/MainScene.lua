
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    local item = ui.newTTFLabelMenuItem({
        text = "call Java - showAlertDialog()",
        size = 64,
        x = display.cx,
        y = display.cy,
        align = ui.TEXT_ALIGN_CENTER,
        listener = function()
            if device.platform ~= "android" then
                print("please run this on android device")
                return
            end
            
            -- call Java method
            local javaClassName = "org/cocos2d_x/samples/luajavabridge/Luajavabridge"
            local javaMethodName = "showAlertDialog"
            local javaParams = {
                "How are you ?",
                "I'm great !",
                function(event)
                    printf("Java method callback value is [%s]", event)
                end
            }
            local javaMethodSig = "(Ljava/lang/String;Ljava/lang/String;I)V"
            luaj.callStaticMethod(javaClassName, javaMethodName, javaParams, javaMethodSig)
        end
    })
    self:addChild(ui.newMenu({item}))
end

function MainScene:onEnter()
end

return MainScene
