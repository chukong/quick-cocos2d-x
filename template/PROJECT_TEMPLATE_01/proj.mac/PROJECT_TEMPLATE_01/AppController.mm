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

#include "AppDelegate.h"
#include "CCDirector.h"
#include "SimpleAudioEngine.h"
#include "platform/CCFileUtils.h"
#include "draw_nodes/CCDrawingPrimitives.h"

using namespace std;
using namespace cocos2d;

static AppDelegate* s_sharedApplication = NULL;

@implementation AppController

@synthesize window, glView, menu;

-(void) applicationDidFinishLaunching:(NSNotification *)aNotification
{
    waitForRestart = NO;
    isAlwaysOnTop = NO;
    isMaximized = NO;
    
    NSUserDefaults *args = [NSUserDefaults standardUserDefaults];
    
    int width = 960;
    int height = 640;
    NSString *nssize = [args stringForKey:@"size"];
    if (nssize)
    {
        const char *csize = [nssize cStringUsingEncoding:NSUTF8StringEncoding];
        string size(csize);
        int pos = size.find('x');
        if (pos != size.npos && pos > 0)
        {
            string widthStr, heightStr;
            widthStr.assign(size, 0, pos);
            heightStr.assign(size, pos + 1, size.length() - pos);
            width = (float)atoi(widthStr.c_str());
            height = (float)atoi(heightStr.c_str());
            if (width < 480) width = 480;
            if (height < 320) height = 320;
        }
    }
    frameSize.width = width;
    frameSize.height = height;
    
    NSString *nsstartupScriptFilename = [args stringForKey:@"file"];
    if (nsstartupScriptFilename)
    {
        startupScriptFilename = string([nsstartupScriptFilename cStringUsingEncoding:NSUTF8StringEncoding]);
    }
    else
    {
        startupScriptFilename = string("main.lua");
    }
    
    NSString *nsworkingDir = [args stringForKey:@"workdir"];
    if (nsworkingDir)
    {
        workingDir = string([nsworkingDir cStringUsingEncoding:NSUTF8StringEncoding]);
    }
    
    [self createWindowAndGLView];
    [self startup];
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

-(void) createWindowAndGLView
{
    if (s_sharedApplication)
    {
        delete s_sharedApplication;
    }
    s_sharedApplication = new AppDelegate();

    float left = 10;
    float bottom = NSHeight([[NSScreen mainScreen] visibleFrame]) - frameSize.height;
    bottom -= [NSMenuView menuBarHeight] + 10;
    if (window)
    {
        left = window.frame.origin.x;
        bottom = window.frame.origin.y + ([glView getHeight] - frameSize.height);
        
        [window setContentView:nil];
        [glView release];
        glView = nil;
        
        [window setReleasedWhenClosed:YES];
        [window close];
        window = nil;
    }
    
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
    [window setTitle:@"LuaHostMac"];
    [window makeKeyAndOrderFront:self];
    [window setAcceptsMouseMovedEvents:NO];
    
    ccDrawInit();
}

-(void) startup
{
    if (CCScriptEngineManager::sharedManager()->getScriptEngine())
    {
        CCScriptEngineManager::sharedManager()->removeScriptEngine();
        CCScriptEngineManager::purgeSharedManager();
    }
    CocosDenshion::SimpleAudioEngine::end();
    
    CCApplication* app = CCApplication::sharedApplication();
    app->setStartupScriptFilename(startupScriptFilename);
    if (workingDir.length() > 0)
    {
        CCFileUtils::sharedFileUtils()->setSearchRootPath(workingDir.c_str());
    }
    
    app->run();
}

#pragma mark -
#pragma mark IB Actions

-(IBAction) openWorkingDirectory:(id)sender
{
    CCLOG("openWorkdingDirectory");
}

-(IBAction) selectStartupScript:(id)sender
{
}

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

-(IBAction) resize_iPhone3G:(id)sender
{
    frameSize.width = 480;
    frameSize.height = 320;
    [self removeMaximize];
    [self restart:sender];
}

-(IBAction) resize_iPhone4:(id)sender
{
    frameSize.width = 960;
    frameSize.height = 640;
    [self removeMaximize];
    [self restart:sender];
}

-(IBAction) resize_iPhone5:(id)sender
{
    frameSize.width = 1136;
    frameSize.height = 640;
    [self removeMaximize];
    [self restart:sender];
}

-(IBAction) resize_iPad:(id)sender
{
    frameSize.width = 1024;
    frameSize.height = 768;
    [self removeMaximize];
    [self restart:sender];
}

-(IBAction) resize_New_iPad:(id)sender
{
    frameSize.width = 2048;
    frameSize.height = 1536;
    [self removeMaximize];
    [self restart:sender];
}

-(IBAction) resize_Android_854_480:(id)sender
{
    frameSize.width = 854;
    frameSize.height = 480;
    [self removeMaximize];
    [self restart:sender];
}

-(IBAction) resize_Android_800_480:(id)sender
{
    frameSize.width = 800;
    frameSize.height = 480;
    [self removeMaximize];
    [self restart:sender];
}

-(IBAction) resize_Android_1024_600:(id)sender
{
    frameSize.width = 1024;
    frameSize.height = 600;
    [self removeMaximize];
    [self restart:sender];
}

-(IBAction) resize_Android_1280_720:(id)sender
{
    frameSize.width = 1280;
    frameSize.height = 720;
    [self removeMaximize];
    [self restart:sender];
}

-(IBAction) resize_Android_1280_800:(id)sender
{
    frameSize.width = 1280;
    frameSize.height = 800;
    [self removeMaximize];
    [self restart:sender];
}

-(IBAction) toggleMaximize:(id)sender
{
    NSMenuItem *windowMenu = [[window menu] itemWithTitle:@"View"];
    NSMenuItem *menuItem = [[windowMenu submenu] itemWithTitle:@"Toggle Maximize"];
    if (!isMaximized)
    {
        prevFrameSize = frameSize;
        frameSize = [[NSScreen mainScreen] visibleFrame].size;
        frameSize.height -= window.frame.size.height - [glView getHeight];
        [menuItem setState:NSOnState];
    }
    else
    {
        frameSize = prevFrameSize;
        [menuItem setState:NSOffState];
    }
    isMaximized = !isMaximized;
    [self restart:sender];
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
