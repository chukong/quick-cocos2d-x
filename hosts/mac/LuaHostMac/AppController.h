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
#include <string>

@interface AppController : NSObject <NSApplicationDelegate, NSWindowDelegate>
{
    NSWindow *window;
    EAGLView *glView;
    NSMenu *menu;

    BOOL waitForRestart;
    BOOL isAlwaysOnTop;
    BOOL isMaximized;
    
    NSSize frameSize;
    NSSize prevFrameSize;
    std::string workingDir;
    std::string startupScriptFilename;
}

@property (nonatomic, assign) IBOutlet NSWindow* window;
@property (nonatomic, assign) IBOutlet EAGLView* glView;
@property (nonatomic, assign) IBOutlet NSMenu* menu;

-(IBAction) openWorkingDirectory:(id)sender;
-(IBAction) selectStartupScript:(id)sender;
-(IBAction) restart:(id)sender;

-(IBAction) resize_iPhone3G:(id)sender;
-(IBAction) resize_iPhone4:(id)sender;
-(IBAction) resize_iPhone5:(id)sender;
-(IBAction) resize_iPad:(id)sender;
-(IBAction) resize_New_iPad:(id)sender;
-(IBAction) resize_Android_854_480:(id)sender;
-(IBAction) resize_Android_800_480:(id)sender;
-(IBAction) resize_Android_1024_600:(id)sender;
-(IBAction) resize_Android_1280_720:(id)sender;
-(IBAction) resize_Android_1280_800:(id)sender;
-(IBAction) toggleMaximize:(id)sender;
-(IBAction) toggleAlwaysOnTop:(id)sender;

-(IBAction) toggleFullScreen:(id)sender;
-(IBAction) exitFullScreen:(id)sender;

@end
