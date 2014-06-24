//
//  CCWebView.h
//
// Created by Vincent on 12-11-27.
// From https://github.com/go3k/CCXWebview
// Modified by zrong on 2014-06-24.
//

#ifndef CCWEBVIEW_H
#define CCWEBVIEW_H

#include "cocos2d.h"

USING_NS_CC;

class CCWebView : public CCObject
{
public:
    CCWebView();
    CCWebView(const char* activityName);
    ~CCWebView();
    
	static CCWebView* create();
	static CCWebView* create(const char* activityName);

	bool init();
    
    /**
     *	@brief Show WebView
     *
     *	@param 	url
     *	@param 	x
     *	@param 	y LEFT_TOP is 0
     *	@param 	width
     *	@param 	height
     */
    void showWebView(const char* url, float x, float y, float width, float height);

    void updateURL(const char* url);
        
    void removeWebView();

	const char* getActivityName();
    
private:
	CCString* _activityName;

};

#endif /* CCWEBVIEW_H */
