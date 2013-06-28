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

#import "AppController.h"
#import "CreateNewProjectDialogController.h"
#import "ProjectConfigDialogController.h"

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

#include "AppDelegate.h"
#include "CCDirector.h"
#include "SimpleAudioEngine.h"
#include "platform/CCFileUtils.h"

using namespace std;
using namespace cocos2d;

@implementation AppController

@synthesize menu;

- (void) applicationDidFinishLaunching:(NSNotification *)aNotification
{
    waitForRestart = NO;
    isAlwaysOnTop = NO;
    isMaximized = NO;
    hasPopupDialog = NO;
    debugLogFile = 0;

    app = new AppDelegate();

    [self updateProjectConfigFromArgs];
    [self createWindowAndGLView];
    [self startup];
    [self updateOpenRect];
    [self initUI];
    [self updateUI];
}

-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
{
    return YES;
}

-(void) dealloc
{
    CCDirector::sharedDirector()->end();
    [super dealloc];
}

#pragma mark -
#pragma mark functions

- (void) createWindowAndGLView
{
    if (projectConfig.isWriteDebugLogToFile())
    {
        [self writeDebugLogToFile:[self getDebugLogFilePath]];
    }

    const CCSize frameSize = projectConfig.getFrameSize();
    float left = 10;
    float bottom = NSHeight([[NSScreen mainScreen] visibleFrame]) - frameSize.height;
    bottom -= [NSMenuView menuBarHeight] + 10;

    // create the window
    // note that using NSResizableWindowMask causes the window to be a little
    // smaller and therefore ipad graphics are not loaded
    NSRect rect = NSMakeRect(left, bottom, frameSize.width, frameSize.height);
    NSInteger mask = NSClosableWindowMask | NSTitledWindowMask | NSMiniaturizableWindowMask;
    window = [[NSWindow alloc] initWithContentRect:rect
                                         styleMask:mask
                                           backing:NSBackingStoreBuffered
                                             defer:YES];
    window.delegate = self;

    // allocate our GL view
    // (isn't there already a shared EAGLView?)
    glView = [[EAGLView alloc] initWithFrame:rect];

    // set window parameters
    [window becomeFirstResponder];
    [window setContentView:glView];
    [window setTitle:@"quick-x-player"];
    [window makeKeyAndOrderFront:self];
    [window setAcceptsMouseMovedEvents:NO];
    [window center];

    [self setZoom:projectConfig.getFrameScale()];
}

- (void) startup
{
    const string projectDir = projectConfig.getProjectDir();
    if (projectDir.length())
    {
        CCFileUtils::sharedFileUtils()->setSearchRootPath(projectDir.c_str());
    }

    const string writablePath = projectConfig.getWritableRealPath();
    if (writablePath.length())
    {
        CCFileUtils::sharedFileUtils()->setWritablePath(writablePath.c_str());
    }

    app->setStartupScriptFilename(projectConfig.getScriptFileRealPath());
    app->run();
}

- (void) updateOpenRect
{
    NSMutableArray *recents = [NSMutableArray arrayWithArray:[[NSUserDefaults standardUserDefaults] arrayForKey:@"recents"]];

    for (int i = [recents count] - 1; i >= 0; --i)
    {
        id recentItem = [recents objectAtIndex:i];
        if (![[recentItem class] isSubclassOfClass:[NSDictionary class]])
        {
            [recents removeObjectAtIndex:i];
        }
    }

    NSArray *args = [self makeCommandLineArgsFromProjectConfig];
    NSDictionary *item = [NSDictionary dictionaryWithObjectsAndKeys:[NSString stringWithCString:projectConfig.getProjectDir().c_str() encoding:NSUTF8StringEncoding], @"title", args, @"args", nil];

    [recents removeObject:item];
    [recents insertObject:item atIndex:0];
    [[NSUserDefaults standardUserDefaults] setObject:recents forKey:@"recents"];
}

- (void) initUI
{
    NSMenu *submenu = [[[window menu] itemWithTitle:@"Screen"] submenu];

    SimulatorConfig *config = SimulatorConfig::sharedDefaults();
    int current = config->checkScreenSize(projectConfig.getFrameSize());
    for (int i = config->getScreenSizeCount() - 1; i >= 0; --i)
    {
        SimulatorScreenSize size = config->getScreenSize(i);
        NSMenuItem *item = [[[NSMenuItem alloc] initWithTitle:[NSString stringWithCString:size.title.c_str() encoding:NSUTF8StringEncoding]
                                                       action:@selector(onScreenChangeFrameSize:)
                                                keyEquivalent:@""] autorelease];
        [item setTag:i];

        if (i == current)
        {
            [item setState:NSOnState];
        }
        [submenu insertItem:item atIndex:0];
    }

    NSArray *recents = [[NSUserDefaults standardUserDefaults] arrayForKey:@"recents"];
    submenu = [[[[[window menu] itemWithTitle:@"File"] submenu] itemWithTitle:@"Open Recent"] submenu];
    for (int i = [recents count] - 1; i >= 0; --i)
    {
        NSDictionary *recentItem = [recents objectAtIndex:i];
        NSMenuItem *item = [[[NSMenuItem alloc] initWithTitle:[recentItem objectForKey:@"title"]
                                                       action:@selector(onFileOpenRecent:)
                                                keyEquivalent:@""] autorelease];
        [submenu insertItem:item atIndex:0];
    }
}

- (void) updateUI
{
    NSMenu *menuPlayer = [[[window menu] itemWithTitle:@"Player"] submenu];
    NSMenuItem *itemWriteDebugLogToFile = [menuPlayer itemWithTitle:@"Write Debug Log to File"];
    [itemWriteDebugLogToFile setState:projectConfig.isWriteDebugLogToFile() ? NSOnState : NSOffState];

    NSMenu *menuScreen = [[[window menu] itemWithTitle:@"Screen"] submenu];
    NSMenuItem *itemPortait = [menuScreen itemWithTitle:@"Portait"];
    NSMenuItem *itemLandscape = [menuScreen itemWithTitle:@"Landscape"];
    if (projectConfig.isLandscapeFrame())
    {
        [itemPortait setState:NSOffState];
        [itemLandscape setState:NSOnState];
    }
    else
    {
        [itemPortait setState:NSOnState];
        [itemLandscape setState:NSOffState];
    }

    NSMenuItem *itemActual = [menuScreen itemWithTitle:@"Actual (100%)"];
    NSMenuItem *itemZoomOut = [menuScreen itemWithTitle:@"Zoom Out (50%)"];
    if (projectConfig.getFrameScale() > 0.5f)
    {
        [itemActual setState:NSOnState];
        [itemZoomOut setState:NSOffState];
    }
    else
    {
        [itemActual setState:NSOffState];
        [itemZoomOut setState:NSOnState];
    }

    NSArray *recents = [[NSUserDefaults standardUserDefaults] arrayForKey:@"recents"];
    NSMenu *menuRecents = [[[[[window menu] itemWithTitle:@"File"] submenu] itemWithTitle:@"Open Recent"] submenu];
    while (true)
    {
        NSMenuItem *item = [menuRecents itemAtIndex:0];
        if ([item isSeparatorItem]) break;
        [menuRecents removeItemAtIndex:0];
    }

    for (int i = [recents count] - 1; i >= 0; --i)
    {
        NSDictionary *recentItem = [recents objectAtIndex:i];
        NSMenuItem *item = [[[NSMenuItem alloc] initWithTitle:[recentItem objectForKey:@"title"]
                                                       action:@selector(onFileOpenRecent:)
                                                keyEquivalent:@""] autorelease];
        [menuRecents insertItem:item atIndex:0];
    }

    [window setTitle:[NSString stringWithFormat:@"quick-x-player (%0.0f%%)", projectConfig.getFrameScale() * 100]];
}

- (void) showModelSheet
{
    hasPopupDialog = YES;
    CCDirector::sharedDirector()->pause();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

- (void) stopModelSheet
{
    hasPopupDialog = NO;
    CCDirector::sharedDirector()->resume();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

- (NSArray *) makeCommandLineArgsFromProjectConfig
{
    NSMutableArray *args = [NSMutableArray array];
    [args addObject:@"-workdir"];
    [args addObject:[NSString stringWithCString:projectConfig.getProjectDir().c_str() encoding:NSUTF8StringEncoding]];
    [args addObject:@"-file"];
    [args addObject:[NSString stringWithCString:projectConfig.getScriptFileRealPath().c_str() encoding:NSUTF8StringEncoding]];
    [args addObject:@"-writable"];
    [args addObject:[NSString stringWithCString:projectConfig.getWritableRealPath().c_str() encoding:NSUTF8StringEncoding]];

    const string packagePath = projectConfig.getPackagePath();
    if (packagePath.length())
    {
        [args addObject:@"-package.path"];
        [args addObject:[NSString stringWithCString:packagePath.c_str() encoding:NSUTF8StringEncoding]];
    }

    [args addObject:@"-size"];
    [args addObject:[NSString stringWithFormat:@"%0.0fx%0.0f", projectConfig.getFrameSize().width, projectConfig.getFrameSize().height]];

    if (projectConfig.getFrameScale() < 1.0f)
    {
        [args addObject:@"-scale"];
        [args addObject:[NSString stringWithFormat:@"%0.2f", projectConfig.getFrameScale()]];
    }

    if (projectConfig.isWriteDebugLogToFile())
    {
        [args addObject:@"-write-debug-log"];
    }

    return args;
}

- (void) updateProjectConfigFromArgs
{
    NSArray *args = [[NSProcessInfo processInfo] arguments];

    unsigned int i = 0;
    while (i < [args count])
    {
        NSString *arg = [args objectAtIndex:i];
        if ([arg compare:@"-workdir"] == NSOrderedSame)
        {
            ++i;
            string workdir = string([[args objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding]);
            projectConfig.setProjectDir(workdir);
            projectConfig.setWritablePath(workdir);
        }
        else if ([arg compare:@"-writable"] == NSOrderedSame)
        {
            ++i;
            projectConfig.setWritablePath(string([[args objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding]));
        }
        else if ([arg compare:@"-file"] == NSOrderedSame)
        {
            ++i;
            projectConfig.setScriptFile(string([[args objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding]));
        }
        else if ([arg compare:@"-package.path"] == NSOrderedSame)
        {
            ++i;
            projectConfig.setPackagePath(string([[args objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding]));
        }
        else if ([arg compare:@"-size"] == NSOrderedSame)
        {
            ++i;
            string sizeStr([[args objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding]);
            int pos = sizeStr.find('x');
            int width = 0;
            int height = 0;
            if (pos != sizeStr.npos && pos > 0)
            {
                string widthStr, heightStr;
                widthStr.assign(sizeStr, 0, pos);
                heightStr.assign(sizeStr, pos + 1, sizeStr.length() - pos);
                width = atoi(widthStr.c_str());
                height = atoi(heightStr.c_str());
                projectConfig.setFrameSize(CCSize(width, height));
            }
        }
        else if ([arg compare:@"-scale"] == NSOrderedSame)
        {
            ++i;
            float scale = atof([[args objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding]);
            projectConfig.setFrameScale(scale);
        }
        else if ([arg compare:@"-write-debug-log"] == NSOrderedSame)
        {
            projectConfig.setWriteDebugLogToFile(true);
        }

        ++i;
    }

    projectConfig.dump();
}

- (void) relaunch:(NSArray*)args
{
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    NSMutableDictionary *configuration = [NSMutableDictionary dictionaryWithObject:args forKey:NSWorkspaceLaunchConfigurationArguments];
    NSError *error = [[[NSError alloc] init] autorelease];
    [[NSWorkspace sharedWorkspace] launchApplicationAtURL:url
                                                  options:NSWorkspaceLaunchNewInstance
                                            configuration:configuration error:&error];
    [[NSApplication sharedApplication] terminate:self];
}

- (void) showAlert:(NSString*)message withTitle:(NSString*)title
{

    NSAlert *alert = [[[NSAlert alloc] init] autorelease];
	[alert addButtonWithTitle:@"OK"];
	[alert setMessageText:message];
	[alert setInformativeText:title];
	[alert setAlertStyle:NSWarningAlertStyle];

	[alert beginSheetModalForWindow:window
					  modalDelegate:self
					 didEndSelector:nil
						contextInfo:nil];
}

- (const string) getDebugLogFilePath
{
    //    string path([NSTemporaryDirectory() cStringUsingEncoding:NSUTF8StringEncoding]);
    string path(projectConfig.getProjectDir());
    path.append("debug.log");
    return path;
}

- (bool) writeDebugLogToFile:(const string)path
{
    if (debugLogFile) return true;

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    debugLogFile = open(path.c_str(), O_WRONLY | O_APPEND | O_CREAT, mode);
    if (dup2(debugLogFile, fileno(stderr)) != fileno(stderr) || dup2(debugLogFile, fileno(stdout)) != fileno(stdout))
    {
        perror("Unable to redirect output");
        [self showAlert:[NSString stringWithFormat:@"Unable to redirect output to file \"%s\"", path.c_str()] withTitle:@"quick-x-player error"];
        return false;
    }
    else
    {
        return true;
    }
}

- (void) closeDebugLogFile
{
    if (debugLogFile)
    {
        close(debugLogFile);
        debugLogFile = 0;
    }
}

- (void) setZoom:(float)scale
{
    [glView setFrameZoomFactor:scale];
    projectConfig.setFrameScale(scale);
}

#pragma mark -
#pragma delegates

- (BOOL)validateUserInterfaceItem:(id <NSValidatedUserInterfaceItem>)anItem
{
    return hasPopupDialog == NO;
}

- (void)windowWillClose:(NSNotification *)notification
{
    [[NSApplication sharedApplication] terminate:self];
}

#pragma mark -
#pragma mark IB Actions

- (IBAction) fileNewProject:(id)sender
{
    [self showAlert:@"Coming soon :-)" withTitle:@"quick-x-player"];
    //    [self showModelSheet];
    //    CreateNewProjectDialogController *controller = [[CreateNewProjectDialogController alloc] initWithWindowNibName:@"CreateNewProjectDialog"];
    //    [NSApp beginSheet:controller.window modalForWindow:window didEndBlock:^(NSInteger returnCode) {
    //        [self stopModelSheet];
    //        [controller release];
    //    }];
}

- (IBAction) fileOpen:(id)sender
{
    [self showModelSheet];
    ProjectConfigDialogController *controller = [[ProjectConfigDialogController alloc] initWithWindowNibName:@"ProjectConfigDialog"];
    [controller setProjectConfig:projectConfig];
    [NSApp beginSheet:controller.window modalForWindow:window didEndBlock:^(NSInteger returnCode) {
        [self stopModelSheet];
        if (returnCode == NSRunStoppedResponse)
        {
            projectConfig = controller.projectConfig;
            projectConfig.dump();
            [self relaunch:[self makeCommandLineArgsFromProjectConfig]];
        }
        [controller release];
    }];
}

- (IBAction) onFileOpenRecent:(id)sender
{
    NSArray *recents = [[NSUserDefaults standardUserDefaults] objectForKey:@"recents"];
    NSDictionary *recentItem = nil;
    NSString *title = [sender title];
    for (int i = [recents count] - 1; i >= 0; --i)
    {
        recentItem = [recents objectAtIndex:i];
        if ([title compare:[recentItem objectForKey:@"title"]] == NSOrderedSame)
        {
            [self relaunch:[recentItem objectForKey:@"args"]];
            break;
        }
    }
}

- (IBAction) onFileOpenRecentClearMenu:(id)sender
{
    [[NSUserDefaults standardUserDefaults] setObject:[NSArray array] forKey:@"recents"];
    [self updateUI];
}

- (IBAction) fileClose:(id)sender
{
    [[NSApplication sharedApplication] terminate:self];
}

- (IBAction) playerWriteDebugLogToFile:(id)sender
{
    bool isWrite = projectConfig.isWriteDebugLogToFile();
    if (!isWrite)
    {
        if ([self writeDebugLogToFile:[self getDebugLogFilePath]])
        {
            projectConfig.setWriteDebugLogToFile(true);
            [(NSMenuItem*)sender setState:NSOnState];
        }
    }
    else
    {
        projectConfig.setWriteDebugLogToFile(false);
        [self closeDebugLogFile];
        [(NSMenuItem*)sender setState:NSOffState];
    }
}

- (IBAction) playerOpenDebugLog:(id)sender
{
    const string path = [self getDebugLogFilePath];
    [[NSWorkspace sharedWorkspace] openFile:[NSString stringWithCString:path.c_str() encoding:NSUTF8StringEncoding]];
}

- (IBAction) playerRelaunch:(id)sender
{
    [self relaunch:[self makeCommandLineArgsFromProjectConfig]];
}

- (IBAction) playerShowProjectSandbox:(id)sender
{
    [[NSWorkspace sharedWorkspace] openFile:[NSString stringWithCString:CCFileUtils::sharedFileUtils()->getWritablePath().c_str() encoding:NSUTF8StringEncoding]];
}

- (IBAction) playerShowProjectFiles:(id)sender
{
    [[NSWorkspace sharedWorkspace] openFile:[NSString stringWithCString:projectConfig.getProjectDir().c_str() encoding:NSUTF8StringEncoding]];
}

- (IBAction) onScreenChangeFrameSize:(id)sender
{
    int i = [sender tag];
    if (i >= 0 && i < SimulatorConfig::sharedDefaults()->getScreenSizeCount())
    {
        SimulatorScreenSize size = SimulatorConfig::sharedDefaults()->getScreenSize(i);
        projectConfig.setFrameSize(projectConfig.isLandscapeFrame() ? CCSize(size.height, size.width) : CCSize(size.width, size.height));
        [self relaunch:[self makeCommandLineArgsFromProjectConfig]];
    }
}

- (IBAction) onScreenPortait:(id)sender
{
    if ([sender state] == NSOnState) return;
    [sender setState:NSOnState];
    [[[[[window menu] itemWithTitle:@"Screen"] submenu] itemWithTitle:@"Landscape"] setState:NSOffState];
    projectConfig.changeFrameOrientationToPortait();
    [self relaunch:[self makeCommandLineArgsFromProjectConfig]];
}

- (IBAction) onScreenLandscape:(id)sender
{
    if ([sender state] == NSOnState) return;
    [sender setState:NSOnState];
    [[[[[window menu] itemWithTitle:@"Screen"] submenu] itemWithTitle:@"Portait"] setState:NSOffState];
    projectConfig.changeFrameOrientationToLandscape();
    [self relaunch:[self makeCommandLineArgsFromProjectConfig]];
}

- (IBAction) onScreenActual:(id)sender
{
    if ([sender state] == NSOnState) return;
    [self setZoom:1.0f];
    [self updateUI];
}

- (IBAction) onScreenZoomOut:(id)sender
{
    if ([sender state] == NSOnState) return;
    [self setZoom:0.5f];
    [self updateUI];
}


#pragma ----------------------------------------

-(IBAction) restart:(id)sender
{
    if (waitForRestart) return;
    waitForRestart = YES;

    CCDirector::sharedDirector()->end();
    [NSTimer scheduledTimerWithTimeInterval:0.1
                                     target:self
                                   selector:@selector(restartComplete)
                                   userInfo:nil
                                    repeats:NO];
}

-(void) restartComplete
{
    [self createWindowAndGLView];
    [self startup];
    [self setAlwaysOnTop:isAlwaysOnTop];
    waitForRestart = NO;
}

-(void) removeMaximize
{
    isMaximized = NO;
    NSMenuItem *windowMenu = [[window menu] itemWithTitle:@"View"];
    NSMenuItem *menuItem = [[windowMenu submenu] itemWithTitle:@"Toggle Maximize"];
    [menuItem setState:NSOffState];
}

-(IBAction) toggleMaximize:(id)sender
{
    //    NSMenuItem *windowMenu = [[window menu] itemWithTitle:@"View"];
    //    NSMenuItem *menuItem = [[windowMenu submenu] itemWithTitle:@"Toggle Maximize"];
    //    if (!isMaximized)
    //    {
    //        prevFrameSize = frameSize;
    //        frameSize = [[NSScreen mainScreen] visibleFrame].size;
    //        frameSize.height -= window.frame.size.height - [glView getHeight];
    //        [menuItem setState:NSOnState];
    //    }
    //    else
    //    {
    //        frameSize = prevFrameSize;
    //        [menuItem setState:NSOffState];
    //    }
    //    isMaximized = !isMaximized;
    //    [self restart:sender];
}

-(void) setAlwaysOnTop:(BOOL)alwaysOnTop
{
    NSMenuItem *windowMenu = [[window menu] itemWithTitle:@"Window"];
    NSMenuItem *menuItem = [[windowMenu submenu] itemWithTitle:@"Always On Top"];
    if (alwaysOnTop)
    {
        [window setLevel:NSFloatingWindowLevel];
        [menuItem setState:NSOnState];
    }
    else
    {
        [window setLevel:NSNormalWindowLevel];
        [menuItem setState:NSOffState];
    }
    isAlwaysOnTop = alwaysOnTop;
}

-(IBAction) toggleAlwaysOnTop:(id)sender
{
    [self setAlwaysOnTop:!isAlwaysOnTop];
}

-(IBAction) toggleFullScreen:(id)sender
{
    //    EAGLView* pView = [EAGLView sharedEGLView];
    //    [pView setFullScreen:!pView.isFullScreen];
}

-(IBAction) exitFullScreen:(id)sender
{
    //    [[EAGLView sharedEGLView] setFullScreen:NO];
}

//- (void)windowDidEndLiveResize:(NSNotification *)notification
//{
//    frameSize = window.frame.size;
//    [self restart:nil];
//}

@end
