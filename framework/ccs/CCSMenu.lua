
function ccs.menu(params)
	local listener = params.listener
	local menu = ccs.panel(params)

	local function touchChild(point)
		local children = menu:getChildren()
		for i=1,children:count() do
			local uiwidget = tolua.cast(children:objectAtIndex(i-1),widget_table[UI_WIDGET].name)
			if uiwidget:hitTest(point) then
				menu.focused = uiwidget
				return
			end
		end
		menu.focused = nil
	end

	local function TouchBegin(uiwidget)
		local point = menu:getTouchStartPos()
		touchChild(point)
		if menu.focused then
			menu.focused:onTouchBegan(point)
		end 
	end

	local function moveEvent(uiwidget)
		local point = menu:getTouchMovePos()
		if not menu.focused or menu.focused:hitTest(point) == false then
			if menu.focused then
				menu.focused:onTouchCancelled(point)
			end
			touchChild(point)
			if menu.focused then
				menu.focused:onTouchBegan(point)
			end
		elseif menu.focused and menu.focused:hitTest(point) then
			menu.focused:onTouchMoved(point)
		end
	end

	local function TouchEnded(uiwidget)
		local point = menu:getTouchEndPos()
		if menu.focused then
			menu.focused:onTouchEnded(point)
			menu.focused = nil
		end
	end
	defaultcallback = {[ccs.TouchEventType.moved] = moveEvent,
					  [ccs.TouchEventType.began] = TouchBegin,
					  [ccs.TouchEventType.ended] = TouchEnded}
	if listener then
		table.merge(defaultcallback,listener)
	end
	menu:setListener(defaultcallback)
	return menu
end

