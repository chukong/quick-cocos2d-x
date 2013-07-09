//
//  ConsoleWindowController.h
//  quick-x-player
//
//  Created by fireyang on 13-7-5.
//  Copyright (c) 2013年 qeeplay.com. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ConsoleWindowController : NSWindowController
{
    NSTextView *textView;
    IBOutlet NSButton *checkScroll;
    IBOutlet NSButton *topCheckBox;
}
@property (assign) IBOutlet NSTextView *textView;


- (void) trace:(NSString*) msg;
- (IBAction)onClear:(id)sender;
- (IBAction)onScrollChange:(id)sender;
- (IBAction)onTopChange:(id)sender;

@end



