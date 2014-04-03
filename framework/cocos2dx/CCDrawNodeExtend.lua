
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

function CCDrawNodeExtend:drawCircle(radius, params)
	local fillColor = cc.c4f(1,1,1,1)
	local borderColor = cc.c4f(1,1,1,1)
	local segments = 32
	local startRadian = 0
	local endRadian = math.pi*2
	local borderWidth = 0
	if params then
		if params.segments then segments = params.segments end
		if params.startDegree then
			startRadian = params.startDegree*math.pi/180
		end
		if params.degree then
			endRadian = startRadian+(params.degree)*math.pi/180
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
