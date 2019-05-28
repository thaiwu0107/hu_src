
local log = require "log"
local LERR = log.error

local M = {}
function M.get_hu_info(cards, gui_tbl)
	local gui_num = 0
	local gui_dict = {}

	if gui_tbl then
		for k,i in ipairs(gui_tbl) do
				if cards[i] then
							gui_dict[i] = cards[i]
							gui_num = gui_num + (cards[i])
							cards[i] = 0
				end
		end
	end

	--确定将牌
	local eye_tbl = {}
	local empty = -1
	for i = 28 ,34 do
		local c = cards[i]
		if c > 0 and not table.index(gui_tbl,i) then
			if c > 2 then
				return false
			else
				table.insert(eye_tbl,i)
			end
		end
	end
	if #eye_tbl >= 2 then
				return false
	elseif #eye_tbl == 0 then
		for i = 1, 34 do
				if cards[i] > 0 and (cards[i] + gui_num >= 2) then
					table.insert(eye_tbl, i)
				end
		end
		table.insert(eye_tbl, 1, empty)
	end

	-- 减去将牌后  手牌为： 3*n
	local hu = false

	for _, eye in ipairs(eye_tbl) do
		if eye == empty then
			hu = M.foreach_eye(cards, gui_num - 2)
		else
			local n = cards[eye]
			if n == 1 then
				cards[eye] = 0
				hu = M.foreach_eye(cards, gui_num - 1)
			else
				cards[eye] = cards[eye] - 2
				hu = M.foreach_eye(cards, gui_num)
			end
			cards[eye] = n
		end
		if hu then
			break
		end
	end

	if gui_tbl then
		if gui_num > 0 then
				for i,c in pairs(gui_dict) do
					 cards[i] = gui_dict[i]
				end
		end
	end
	return hu
end

function M.foreach_eye(cards, gui_num)
	local left_gui = gui_num
	for i = 0, 2 do
		local need_gui = M.check_normal(cards, i*9+1, (i*9+1)+8)
		left_gui = left_gui - need_gui
		if left_gui < 0 then
			return false
		end
	end

	return left_gui >= 0 and left_gui % 3 == 0
end

function M.check_normal(cards, from, to)
	local n = 0
	for i = from, to do
		n = n * 10 + cards[i]
	end

	if n == 0 then
	   return 0
	end

	return M.func(n)
end

function M.func(n)
	local need = 0
    local c,c1,c2

    while n > 0 do
        c = n %10
        if c ~= 0 then
              n = n - c
              c1 = math.floor((n%100)/10)
              c2 = math.floor((n%1000)/100)
              if c1 <= c then
                need = need + c - c1
                n = n - c1*10
              else
                n = n - c*10
              end

              if c2 <= c then
                need = need + c - c2
                n = n - c2*100
              else
                n = n - c*100
              end
        end
        if n == 0 then
             break
        end
        n = n/10
    end

    return need
end

return M
