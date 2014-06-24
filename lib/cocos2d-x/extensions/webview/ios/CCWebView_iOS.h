//
// CCWebView_iOS.h
//
// Created by Vincent on 12-11-27.
// From https://github.com/go3k/CCXWebview
// Modified by zrong on 2014-06-24.
//

#import <Foundation/Foundation.h>

@interface CCWebView_iOS : NSObject <UIWebViewDelegate>
{
    UIWebView* m_webview;
}

- (void)showWebView_x:(float)x y:(float)y width:(float) widht height:(float)height;

- (void)updateURL:(const char*)url;

- (void)removeWebView;

@end
