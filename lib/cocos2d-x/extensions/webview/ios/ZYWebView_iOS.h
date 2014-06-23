//
//  ZYWebView_iOS.h
//  CCXWebview
//
//  Created by Vincent on 12-11-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ZYWebView_iOS : NSObject <UIWebViewDelegate>
{
    UIWebView* m_webview;
}

- (void)showWebView_x:(float)x y:(float)y width:(float) widht height:(float)height;

- (void)updateURL:(const char*)url;

- (void)removeWebView;

@end
