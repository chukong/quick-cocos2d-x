
### 如何使用 mac 工程

1.  用 Xcode 打开 mac 工程后，选择菜单 Product -> Scheme -> 你的项目名字
2.  选择菜单 Product -> Scheme -> Edit Scheme，打开 Scheme 对话框
3.  从对话框左侧选中 "Run"
4.  从右侧选中 "Arguments"
5.  在 Arguments Passed On Launch 里点 "+" 添加命令参数

    ~~~
    -quick $(QUICK_COCOS2DX_ROOT)
    -workdir $(SRCROOT)/../
    -landscape
    ~~~

6.  第三个参数是指定启动时的屏幕尺寸。如果是横屏，用 -landscape，如果是竖屏用 -portrait。

![](res/README_PROJECT_MAC_DEBUG_SETTINGS.png)

~

### 如何使用 win32 工程

1.  用 Visual Studio 打开 win32 工程
2.  确保从 Solution Explorer （解决方案管理器）中选中了你的项目
3.  选择菜单 Project -> Properties，打开 Project Property 对话框
4.  从对话框左侧选中 "Configuration Properties / Debugging"
5.  从右侧选中 "Command Arguments"，添加内容：

    ~~~
    -quick $(QUICK_COCOS2DX_ROOT)
    -workdir $(ProjectDir)/../
    -landscape
    ~~~

6.  第三个参数是指定启动时的屏幕尺寸。如果是横屏，用 -landscape，如果是竖屏用 -portrait。

![](res/README_PROJECT_WIN_DEBUG_SETTINGS.png)

