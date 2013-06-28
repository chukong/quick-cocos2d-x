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

-(void) dealloc
{
    CCDirector::sharedDirector()->end();
    [super dealloc];
}

#pragma mark -
#pragma delegates

- (void) applicationDidFinishLaunching:(NSNotification *)aNotification
{
    waitForRestart = NO;
    isAlwaysOnTop = NO;
    isMaximized = NO;
    hasPopupDialog = NO;
    debugLogFile = 0;

    app = new AppDelegate();

    [self updateProjectConfigFromCommandLineArgs];
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

- (BOOL) applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
{
    return NO;
}

- (BOOL) validateUserInterfaceItem:(id <NSValidatedUserInterfaceItem>)anItem
{
    return hasPopupDialog == NO;
}

- (void) windowWillClose:(NSNotification *)notification
{
    [[NSApplication sharedApplication] terminate:self];
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
    [window setContentView:glView];
    [window setTitle:@"quick-x-player"];
    [window center];

    [self setZoom:projectConfig.getFrameScale()];
    CCPoint pos = projectConfig.getWindowOffset();
    if (pos.x != 0 && pos.y != 0)
    {
        [window setFrameOrigin:NSMakePoint(pos.x, pos.y)];
    }

    [window becomeFirstResponder];
    [window makeKeyAndOrderFront:self];
    [window setAcceptsMouseMovedEvents:NO];
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
        if (![[recentItem class] isSubclassOfClass:[NSDictionary class]] || [[recentItem objectForKey:@"title"] length] == 0)
        {
            [recents removeObjectAtIndex:i];
        }
    }

    NSString *title = [NSString stringWithCString:projectConfig.getProjectDir().c_str() encoding:NSUTF8StringEncoding];

    if ([title length] > 0)
    {
        for (int i = [recents count] - 1; i >= 0; --i)
        {
            id recentItem = [recents objectAtIndex:i];
            if ([title compare:[recentItem objectForKey:@"title"]] == NSOrderedSame)
            {
                [recents removeObjectAtIndex:i];
            }
        }

        NSMutableArray *args = [self makeCommandLineArgsFromProjectConfig];
        [args removeLastObject];
        [args removeLastObject];
        NSDictionary *item = [NSDictionary dictionaryWithObjectsAndKeys:title, @"title", args, @"args", nil];
        [recents insertObject:item atIndex:0];
    }
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

- (NSMutableArray*) makeCommandLineArgsFromProjectConfig
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

    [args addObject:@"-offset"];
    [args addObject:[NSString stringWithFormat:@"{%0.0f,%0.0f}", window.frame.origin.x, window.frame.origin.y]];

    return args;
}

- (void) updateProjectConfigFromCommandLineArgs
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
        else if ([arg compare:@"-offset"] == NSOrderedSame)
        {
            ++i;
            CCPoint pos = CCPointFromString([[args objectAtIndex:i] cStringUsingEncoding:NSUTF8StringEncoding]);
            projectConfig.setWindowOffset(pos);
        }

        ++i;
    }

    projectConfig.dump();
}

- (void) launch:(NSArray*)args
{
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle] bundlePath]];
    NSMutableDictionary *configuration = [NSMutableDictionary dictionaryWithObject:args forKey:NSWorkspaceLaunchConfigurationArguments];
    NSError *error = [[[NSError alloc] init] autorelease];
    [[NSWorkspace sharedWorkspace] launchApplicationAtURL:url
                                                  options:NSWorkspaceLaunchNewInstance
                                            configuration:configuration error:&error];
}

- (void) relaunch:(NSArray*)args
{
    [self launch:args];
    [[NSApplication sharedApplication] terminate:self];
}

- (void) relaunch
{
    [self relaunch:[self makeCommandLineArgsFromProjectConfig]];
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


#pragma mark -
#pragma mark IB Actions

- (IBAction) onFileNewProject:(id)sender
{
    [self showAlert:@"Coming soon :-)" withTitle:@"quick-x-player"];
    //    [self showModelSheet];
    //    CreateNewProjectDialogController *controller = [[CreateNewProjectDialogController alloc] initWithWindowNibName:@"CreateNewProjectDialog"];
    //    [NSApp beginSheet:controller.window modalForWindow:window didEndBlock:^(NSInteger returnCode) {
    //        [self stopModelSheet];
    //        [controller release];
    //    }];
}

- (IBAction) onFileNewPlayer:(id)sender
{
    NSMutableArray *args = [self makeCommandLineArgsFromProjectConfig];
    [args removeLastObject];
    [args removeLastObject];
    [self launch:args];
}

- (IBAction) onFileOpen:(id)sender
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
            [self relaunch];
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

- (IBAction) onFileClose:(id)sender
{
    [[NSApplication sharedApplication] terminate:self];
}

- (IBAction) onPlayerWriteDebugLogToFile:(id)sender
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

- (IBAction) onPlayerOpenDebugLog:(id)sender
{
    const string path = [self getDebugLogFilePath];
    [[NSWorkspace sharedWorkspace] openFile:[NSString stringWithCString:path.c_str() encoding:NSUTF8StringEncoding]];
}

- (IBAction) onPlayerRelaunch:(id)sender
{
    [self relaunch];
}

- (IBAction) onPlayerShowProjectSandbox:(id)sender
{
    [[NSWorkspace sharedWorkspace] openFile:[NSString stringWithCString:CCFileUtils::sharedFileUtils()->getWritablePath().c_str() encoding:NSUTF8StringEncoding]];
}

- (IBAction) onPlayerShowProjectFiles:(id)sender
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
        [self relaunch];
    }
}

- (IBAction) onScreenPortait:(id)sender
{
    if ([sender state] == NSOnState) return;
    [sender setState:NSOnState];
    [[[[[window menu] itemWithTitle:@"Screen"] submenu] itemWithTitle:@"Landscape"] setState:NSOffState];
    projectConfig.changeFrameOrientationToPortait();
    [self relaunch];
}

- (IBAction) onScreenLandscape:(id)sender
{
    if ([sender state] == NSOnState) return;
    [sender setState:NSOnState];
    [[[[[window menu] itemWithTitle:@"Screen"] submenu] itemWithTitle:@"Portait"] setState:NSOffState];
    projectConfig.changeFrameOrientationToLandscape();
    [self relaunch];
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

-(IBAction) onWindowAlwaysOnTop:(id)sender
{
    [self setAlwaysOnTop:!isAlwaysOnTop];
}

@end
