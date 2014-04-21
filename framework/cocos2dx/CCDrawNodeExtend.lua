--- @author zrong(zengrong.net)
-- Creation: 2014-04-10

CCDrawNodeExtend = class("CCDrawNodeExtend", CCNodeExtend)
CCDrawNodeExtend.__index = CCDrawNodeExtend

function CCDrawNodeExtend.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CCDrawNodeExtend)
    return target
end

function CCDrawNodeExtend:drawPol(points, params)
	local segments = #points
	fillColor = cc.c4f(1,1,1,1)
	borderWidth  = 0
	borderColor  = cc.c4f(0,0,0,1)
	if params then
		if params.fillColor then fillColor = params.fillColor end
		if params.borderWidth then borderWidth = params.borderWidth end
		if params.borderColor then borderColor = params.borderColor end
	end
	local pa = CCPointArray:create(segments)
	for i=1,segments do
		pa:add(cc.p(points[i][1], points[i][2]))
	end
	self:drawPolygon(pa:fetchPoints(), pa:count(), fillColor, borderWidth, borderColor)
	return self
end

function CCDrawNodeExtend:drawCircle(radius, params)
	local fillColor = cc.c4f(1,1,1,1)
	local borderColor = cc.c4f(1,1,1,1)
	local segments = 32
	local startRadian = 0
	local endRadian = math.pi*2
	local borderWidth = 0
	if params then
		if params.segments then segments = params.segments end
		if params.startAngle then
			startRadian = math.angle2Radian(params.startAngle)
		end
		if params.endAngle then
			endRadian = startRadian+math.angle2Radian(params.endAngle)
		end
		if params.fillColor then fillColor = params.fillColor end
		if params.borderColor then borderColor = params.borderColor end
		if params.borderWidth then borderWidth = params.borderWidth end
	end
	local radianPerSegm = 2 * math.pi/segments
	local points = CCPointArray:create(segments)
	for i=1,segments do
		local radii = startRadian+i*radianPerSegm
		if radii > endRadian then break end
		points:add(cc.p(radius * math.cos(radii), radius * math.sin(radii)))
	end
	self:drawPolygon(points:fetchPoints(), points:count(), fillColor, borderWidth, borderColor)
	return self
end

function CCDrawNodeExtend:drawDot(point, radius, color)
	getmetatable(self).drawDot(self, point, radius, color)
	return self
end

function CCDrawNodeExtend:drawRect(xywh, params)
	local points = {}
	local x = 0
	local y = 0
	local w = 100
	local h = 100
	-- Treat xywh as a table
	if type(xywh) == "table" then
		-- The table is {x=num, y=num, w=num, h=num}
		if xywh.x then
			x = xywh.x
			y = xywh.y
			w = xywh.w
			h = xywh.h
		-- The table is {x, y, w, h}
		else
			x = xywh[1]
			y = xywh[2]
			w = xywh[3]
			h = xywh[4]
		end
	-- Treat xywh as a CCRect
	else
		x = xywh.origin.x
		y = xywh.origin.y
		w = xywh.size.width
		h = xywh.size.height
	end
	points[1] = {x,y}
	points[2] = {x,y+h}
	points[3] = {x+w,y+h}
	points[4] = {x+w,y}
	self:drawPol(points, params)
	return self
end

function CCDrawNodeExtend:drawLine(from, to, radius, color)
	radius = radius or 1
	color = color or cc.c4f(0,0,0,1)
	assert(from or to, "Need a from point and a to point!")
	if type(from) == "table" then
		from = cc.p(from[1], from[2])
		to = cc.p(to[1], to[2])
	end
	self:drawSegment(from, to, radius, color)
	return self
end

function CCDrawNodeExtend:clear()
	getmetatable(self).clear(self)
	return self
end
