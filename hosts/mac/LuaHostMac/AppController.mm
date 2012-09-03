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
#import "AppDelegate.h"

static AppDelegate s_sharedApplication;

@implementation AppController

@synthesize window, glView, menu;

-(void) applicationDidFinishLaunching:(NSNotification *)aNotification
{
    waitForRestart = NO;
    
    NSUserDefaults *args = [NSUserDefaults standardUserDefaults];
    
    int width = 480;
    int height = 320;
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
    float left = 100;
    float top = 100;
    if (window)
    {
        left = [window frame].origin.x;
        top = [window frame].origin.y;
        
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
    NSRect rect = NSMakeRect(left, top, frameSize.width, frameSize.height);
    window = [[NSWindow alloc] initWithContentRect:rect
                                         styleMask:( NSClosableWindowMask | NSTitledWindowMask )
                                           backing:NSBackingStoreBuffered
                                             defer:YES];
    
    // allocate our GL view
    // (isn't there already a shared EAGLView?)
    glView = [[EAGLView alloc] initWithFrame:rect];
    
    // set window parameters
    [window becomeFirstResponder];
    [window setContentView:glView];
    [window setTitle:@"LuaHostMac"];
    [window makeKeyAndOrderFront:self];
    [window setAcceptsMouseMovedEvents:NO];
}

-(void) startup
{
    CCApplication* app = CCApplication::sharedApplication();
    app->setStartupScriptFilename(startupScriptFilename.c_str());
    if (workingDir.length() > 0)
    {
        CCFileUtils::sharedFileUtils()->setResourceDirectory(workingDir.c_str(), true);
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
    [NSTimer scheduledTimerWithTimeInterval:0.051
                                     target:self
                                   selector:@selector(restartRefresh)
                                   userInfo:nil
                                    repeats:NO];
}

-(void) restartRefresh
{
    if (CCScriptEngineManager::sharedManager()->getScriptEngine())
    {
        CCScriptEngineManager::sharedManager()->removeScriptEngine();
        CCScriptEngineManager::purgeSharedManager();
    }
    
    [self createWindowAndGLView];
    [self startup];
    
    waitForRestart = NO;
}

-(IBAction) toggleFullScreen:(id)sender
{
    EAGLView* pView = [EAGLView sharedEGLView];
    [pView setFullScreen:!pView.isFullScreen];
}

-(IBAction) exitFullScreen:(id)sender
{
    [[EAGLView sharedEGLView] setFullScreen:NO];
}

@end
