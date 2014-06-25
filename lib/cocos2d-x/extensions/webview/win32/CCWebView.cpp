//
// CCWebView.cpp
// Do nothing in Windows.
//
// Created by zrong on 2014-06-24.
//

#include "CCWebView.h"

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
}

bool CCWebView::init()
{
	return true;
}

void CCWebView::showWebView(const char* url, float x, float y, float width, float height)
{
}

void CCWebView::updateURL(const char* url)
{
}

void CCWebView::removeWebView()
{
}

const char* CCWebView::getActivityName()
{
	return "";
}

