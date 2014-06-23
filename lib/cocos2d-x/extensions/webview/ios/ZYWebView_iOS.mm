//
//  ZYWebView_iOS.m
//  CCXWebview
//
//  Created by Vincent on 12-11-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "ZYWebView_iOS.h"
#import "EAGLView.h"

@implementation ZYWebView_iOS


- (void)showWebView_x:(float)x y:(float)y width:(float) widht height:(float)height
{
    if (!m_webview)
    {
        m_webview = [[UIWebView alloc] initWithFrame:CGRectMake(x, y, widht , height)];
        [m_webview setDelegate:self];

        [[EAGLView sharedEGLView] addSubview:m_webview];
        [m_webview release];
        
        m_webview.backgroundColor = [UIColor clearColor];
        m_webview.opaque = NO;
        
        for (UIView *aView in [m_webview subviews])  
        { 
            if ([aView isKindOfClass:[UIScrollView class]])  
            { 
                UIScrollView* scView = (UIScrollView *)aView;
                
//                [(UIScrollView *)aView setShowsVerticalScrollIndicator:NO]; //右侧的滚动条 （水平的类似）
                [scView setShowsHorizontalScrollIndicator:NO];
//                scView.bounces = NO;
                
                for (UIView *shadowView in aView.subviews)  
                {
                    if ([shadowView isKindOfClass:[UIImageView class]]) 
                    { 
                        shadowView.hidden = YES;  //上下滚动出边界时的黑色的图片 也就是拖拽后的上下阴影
                    } 
                } 
            } 
        }  
    }
}

- (void)updateURL:(const char*)url
{
    NSString *request = [NSString stringWithUTF8String:url];
    [m_webview loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:request] 
                                            cachePolicy:NSURLRequestReloadIgnoringLocalCacheData 
                                        timeoutInterval:60]];
}

- (void)removeWebView
{
    [m_webview removeFromSuperview];
    m_webview = NULL;
}

#pragma mark - WebView
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    return true;
}

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    
}

@end
