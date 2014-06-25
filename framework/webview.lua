--- An encapsulation for CCWebView
-- @author zrong(zengrong.net)
-- Creation 2014-06-25

local webview = {}

local _x,_y,_w,_h = 0,0,100,100
local _activityName = nil
local _browser = nil

local function createBrowser()
	assert(_activityName, "ActivityName is necessary!")
	if not _browser then
		_browser = CCWebView:create()
		_browser:retain()
	end
end

function webview.setActivityName(name)
	_activityName = name
end

function webview.gettActivityName()
	return _activityName
end

function webview.setPos(x,y)
	_x = x
	_y = y
end

function webview.getPos()
	return _x, _y
end

function webview.setSize(w,h)
	_w = w
	_h = h
end

function webview.getSize()
	return _w, _h
end

function webview.update(url)
	createBrowser()
	_browser:updateURL(url)
end
webview.updateURL = webview.update

function webview.show(url, x,y,w,h)
	if x and y then webview.setPos(x,y) end
	if w and h then webview.setSize(w,h) end
	createBrowser()
	_browser:showWebView(url, _x, _y, _w, _h)
end
webview.showWebView = webview.show

function webview.remove()
	if _browser then
		_browser:removeWebView()
		_browser:release()
		_browser = nil
	end
end
webview.removeWebView = webview.remove

return webview
