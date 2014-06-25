//
//  CCWebView.cpp
//
//  Created by Vincent on 12-11-27.
// From https://github.com/go3k/CCXWebview
// Modified by zrong on 2014-06-24.
//

#include "CCWebView.h"
#import "CCWebView_iOS.h"

static CCWebView_iOS* m_webViewiOS;

CCWebView* CCWebView::create()
{
	CCWebView* webview = new CCWebView();
	if(webview && webview->init())
	{
		webview->autorelease();
		return webview;
	}
	else
	{
		delete webview;
		webview = NULL;
		return NULL;
	}
}

CCWebView* CCWebView::create(const char* activityName)
{
    return CCWebView::create();
}

CCWebView::CCWebView()
: _activityName(NULL)
{
    
}

CCWebView::CCWebView(const char* activityName)
{
    
}

CCWebView::~CCWebView()
{
    [m_webViewiOS release];
    m_webViewiOS = NULL;
}

bool CCWebView::init()
{
	return true;
}

void CCWebView::showWebView(const char* url, float x, float y, float width, float height)
{
    m_webViewiOS = [[CCWebView_iOS alloc] init];
    [m_webViewiOS showWebView_x:x y:y width:width height:height];
    
    this->updateURL(url);
}

void CCWebView::updateURL(const char* url)
{
    [m_webViewiOS updateURL:url];
}

void CCWebView::removeWebView()
{
    [m_webViewiOS removeWebView];
}

const char* CCWebView::getActivityName()
{
    return "";
}