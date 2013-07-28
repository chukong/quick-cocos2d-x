//
//  ConsoleWindowController.m
//  quick-x-player
//
//  Created by fireyang on 13-7-5.
//  Copyright (c) 2013年 qeeplay.com. All rights reserved.
//

#import "ConsoleWindowController.h"

@interface ConsoleWindowController ()

@end

@implementation ConsoleWindowController
@synthesize textView;

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
       
    }
    
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    [self.window setLevel:NSFloatingWindowLevel];
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

- (void) trace:(NSString *)msg{
    NSAttributedString *string = [[NSAttributedString alloc] initWithString:msg];
	NSTextStorage *storage = [textView textStorage];
	
	[storage beginEditing];
	[storage appendAttributedString:string];
	[storage endEditing];
    [self changeScroll];
}

- (void) changeScroll{
    BOOL scroll = [checkScroll state] == NSOnState;
    if(scroll){
        [self.textView scrollRangeToVisible: NSMakeRange(self.textView.string.length, 0)];
    }
}

- (IBAction)onClear:(id)sender {
    NSTextStorage *storage = [textView textStorage];
    [storage setAttributedString:[[[NSAttributedString alloc] initWithString:@""] autorelease]];
}

- (IBAction)onScrollChange:(id)sender {
    [self changeScroll];
}

- (IBAction)onTopChange:(id)sender {
    BOOL isTop = [topCheckBox state] == NSOnState;
    if(isTop){
        [self.window setLevel:NSFloatingWindowLevel];
    }else{
        [self.window setLevel:NSNormalWindowLevel];
    }
}

@end
