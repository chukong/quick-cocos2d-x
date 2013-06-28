
#import "CreateNewProjectDialogController.h"

@implementation CreateNewProjectDialogController

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)dealloc
{
    [super dealloc];
    NSLog(@"[CreateNewProjectDialogController dealloc]");
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
}

- (IBAction) onCancel:(id)sender
{
    [self close];
    [NSApp endSheet:self.window returnCode:NSRunAbortedResponse];
}

@end
