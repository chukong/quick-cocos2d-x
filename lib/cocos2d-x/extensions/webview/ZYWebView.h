//
//  BFWebView.h
//  CCXWebview
//
//  Created by Vincent on 12-11-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef NewPuzzle_BFWebView_h
#define NewPuzzle_BFWebView_h

#include "cocos2d.h"

USING_NS_CC;

class ZYWebView : public CCObject
{
public:
    ZYWebView();
    ~ZYWebView();
    
    CREATE_FUNC(ZYWebView);
	bool init();
    
    /**
     *	@brief	显示WebView
     *
     *	@param 	url 	地址
     *	@param 	x 	x位置
     *	@param 	y 	y位置(左上的位置，坐标系为左上0)
     *	@param 	width 	宽度
     *	@param 	height 	高度
     */
    void showWebView(const char* url, float x, float y, float width, float height);

    
    void updateURL(const char* url);
        
    void removeWebView();
    
private:

};

#endif