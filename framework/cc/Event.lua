--[[

Copyright (c) 2011-2014 chukong-inc.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--[[--


]]

local Event = {}

Event.ENTER_SCENE                 = "ENTER_SCENE"
Event.EXIT_SCENE                  = "EXIT_SCENE"
Event.ENTER_TRANSITION_DID_FINISH = "ENTER_TRANSITION_DID_FINISH"
Event.EXIT_TRANSITION_DID_START   = "EXIT_TRANSITION_DID_START"
Event.CLEANUP                     = "CLEANUP"

Event.ENTER_FRAME                 = "ENTER_FRAME"

Event.TOUCH_BEGAN                 = "TOUCH_BEGAN"
Event.TOUCH_MOVED                 = "TOUCH_MOVED"
Event.TOUCH_ENDED                 = "TOUCH_ENDED"
Event.TOUCH_CANCELLED             = "TOUCH_CANCELLED"
Event.TOUCH_CAPTURE_BEGAN         = "TOUCH_CAPTURE_BEGAN"
Event.TOUCH_CAPTURE_MOVED         = "TOUCH_CAPTURE_MOVED"
Event.TOUCH_CAPTURE_ENDED         = "TOUCH_CAPTURE_ENDED"
Event.TOUCH_CAPTURE_CANCELLED     = "TOUCH_CAPTURE_CANCELLED"

Event.MENU_ITEM_CLICKED           = "MENU_ITEM_CLICKED"

Event.ACCELERATE                  = "ACCELERATE"
Event.KEYPAD                      = "KEYPAD"

return Event
