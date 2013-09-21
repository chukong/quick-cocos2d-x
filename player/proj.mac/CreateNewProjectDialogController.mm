
#import "CreateNewProjectDialogController.h"

@implementation CreateNewProjectDialogController

@synthesize textFieldProjetLocation;
@synthesize textFieldPackageName;
@synthesize textView;

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

- (IBAction) onSelectProjectLocation:(id)sender
{
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    [openDlg setTitle:@"Select New Project Location"];
    [openDlg setCanChooseDirectories:YES];
    [openDlg setCanChooseFiles:NO];
    [openDlg setCanHide:YES];
    [openDlg setCanCreateDirectories:YES];
    [openDlg setCanSelectHiddenExtension:NO];
    [openDlg setAllowsMultipleSelection:NO];

    if ([openDlg runModal] == NSFileHandlingPanelOKButton)
    {
        NSString *path = [[openDlg.URLs objectAtIndex:0] path];
        [textFieldProjetLocation setStringValue:path];
    }
}

- (IBAction) onCancel:(id)sender
{
    [self close];
    [NSApp endSheet:self.window returnCode:NSRunAbortedResponse];
}

- (IBAction) onCreate:(id)sender
{
    NSString *projectLocation = [textFieldProjetLocation stringValue];
    NSString *packageName = [textFieldPackageName stringValue];

    NSString *commandLine = [NSString stringWithFormat:@"", packageName];
}

@end
