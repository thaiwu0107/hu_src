
local M = {}

function M.foreach_eye(cards, gui_num)

	for i = 28, 34 do
			if cards[i] == 4 then
				return false
			end
	end

	local max_gui = gui_num
	local left_gui = gui_num
	for i = 0, 2 do
		local need_gui = M.check_normal(cards, i*9+1, (i*9+1)+8, max_gui)
		left_gui = left_gui - need_gui
		if left_gui < 0 then
			return false
		end
	end

	local need_gui = M.check_zi(cards, max_gui)
	return left_gui >= need_gui and (left_gui - need_gui)%3 == 0 , gui_num - left_gui
end

function M.check_normal(cards, from, to, max_gui)
	local n = 0
	for i = from, to do
		n = n * 10 + cards[i]
	end

	if n == 0 then
	   return 0
	end

	return M.next_split(n, 0, max_gui)
end

function M.next_split(n, need_gui, max_gui)
	local c = 0
	repeat
		if n == 0 then
		   return need_gui
		end

		while (n > 0) do
			c = n % 10
			n = math.floor(n / 10)
			if c ~= 0 then
			   break
			end
		end
		if c == 1 or c == 4 then
			return M.one(n, need_gui, max_gui)
		elseif c == 2 then
			return M.two(n, need_gui, max_gui)
		end
	until false
end

function M.one(n, need_gui, max_gui)
	local c1 = n % 10
	local c2 = math.floor((n % 100) / 10)

	if c1 == 0 then
	    need_gui = need_gui + 1
	else
		n = n - 1
    end

	if c2 == 0 then
	   need_gui = need_gui + 1
	else
	   n = n - 10
	end

	if n == 0 then
	   return need_gui
	end

	if need_gui > max_gui then
	   return need_gui
	end

	return M.next_split(n, need_gui, max_gui)
end

function M.two(n, need_gui, max_gui)
	local c1 = n % 10
	local c2 = math.floor((n % 100) / 10)
	local c3 = math.floor((n % 1000) / 100)
	local c4 = math.floor((n % 10000) / 1000)

	local choose_ke = true
	if c1 == 0 then
		choose_ke = true
	elseif c1 == 1 then
		-- 刻子
		if c2 == 0 or c2 == 1 then
			choose_ke = true
		elseif c2 == 2 then
			if c3 == 2 then
				if c4 == 2 then
					choose_ke = false
				end
			elseif c3 == 3 then
				if c4 ~= 2 then
					choose_ke = false
				end
			else
				choose_ke = false
			end
		elseif c2 == 3 then
			if c3 == 0 or c3 == 2 or c3 == 1 or c3 == 4 then
				choose_ke = false
			end
		elseif c2 == 4 then
			if c3 == 2 then
				if c4 == 2 or c4 == 3 or c4 == 4 then
					choose_ke = false
				end
			elseif c3 == 3 then
				choose_ke = false
			end
		end
	elseif c1 == 2 then
		choose_ke = false
	elseif c1 == 3 then
		if c2 == 2 then
			if c3 == 1 or c3 == 4 then
				choose_ke = false
			elseif c3 == 2 then
				if c4 ~= 2 then
					choose_ke = false
				end
			end
		end
		if c2 == 3 then
			choose_ke = false
		elseif c2 == 4 then
			if c3 == 2 then
				choose_ke = false
			end
		end
	elseif c1 == 4 then
		if c2 == 2 and c3 ~= 2 then
			choose_ke = false
		elseif c2 == 3 then
			if c3 == 0 or c3 == 1 or c3 == 2 then
				choose_ke = false
			end
		elseif c2 == 4 then
			if c3 == 2 then
				choose_ke = false
			end
		end
	end

	if choose_ke then
		need_gui = need_gui + 1
	else
		if c1 < 2 then
			need_gui = need_gui + (2 - c1)
			n = n - c1
		else
			n = n - 2
		end

		if c2 < 2 then
			need_gui = need_gui + (2 - c2)
			n = n - c2*10
		else
			n = n - 20
		end
	end

	if n == 0 then
	   return need_gui
	end

	if need_gui > max_gui then
	   return need_gui
	end

	return M.next_split(n, need_gui, max_gui)
end

function M.check_zi(cards,  max_gui)
	local need_gui = 0
	for i = 28, 34 do
			local c = cards[i]
			if c == 1 or c == 4 then
				need_gui = need_gui + 2
			elseif c == 2 then
				need_gui = need_gui + 1
			end
			if need_gui > max_gui then
			   return need_gui
			end
	end
	return need_gui
end

return M
