/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
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
 ****************************************************************************/

#import "EAGLView.h"
#import "NSApplication+SheetAdditions.h"
#import "ConsoleWindowController.h"

#include <string>
#include "ProjectConfig/SimulatorConfig.h"
#include "AppDelegate.h"

class AppControllerBridge;

@interface AppController : NSObject <NSApplicationDelegate, NSWindowDelegate>
{
    NSWindow *window;
    EAGLView *glView;
    NSMenu *menu;

    BOOL waitForRestart;
    BOOL isAlwaysOnTop;
    BOOL isMaximized;

    AppDelegate *app;
    ProjectConfig projectConfig;
    BOOL hasPopupDialog;

    int debugLogFile;

    AppControllerBridge *bridge;
    
    //log file
    ConsoleWindowController *consoleController;
    NSFileHandle *fileHandle;
    //console pipe
    NSPipe *pipe;
    NSFileHandle *pipeReadHandle;
}

@property (nonatomic, assign) IBOutlet NSMenu* menu;

- (void) welcomeNewProject;
- (void) welcomeOpen;
- (void) welcomeSamples;
- (void) welcomeGetStarted;
- (void) welcomeCommunity;
- (void) welcomeOpenRecent:(cocos2d::CCObject*)object;

- (IBAction) onFileNewProject:(id)sender;
- (IBAction) onFileNewPlayer:(id)sender;
- (IBAction) onFileOpen:(id)sender;
- (IBAction) onFileOpenRecentClearMenu:(id)sender;
- (IBAction) onFileWelcome:(id)sender;
- (IBAction) onFileClose:(id)sender;

- (IBAction) onPlayerWriteDebugLogToFile:(id)sender;
- (IBAction) onPlayerOpenDebugLog:(id)sender;
- (IBAction) onPlayerRelaunch:(id)sender;
- (IBAction) onPlayerShowProjectSandbox:(id)sender;
- (IBAction) onPlayerShowProjectFiles:(id)sender;

- (IBAction) onScreenPortait:(id)sender;
- (IBAction) onScreenLandscape:(id)sender;
- (IBAction) onScreenZoomOut:(id)sender;

- (IBAction) onWindowAlwaysOnTop:(id)sender;

@end
