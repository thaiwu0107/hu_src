
local utils = require "hu_lib/utils"
local pinghu_splitlib = require "hu_lib/pinghu_splitlib"

local splitlib = require "hu_lib/splitlib"
local split_next = require "hu_lib/split_next"

local log = require "log"
local LERR = log.error

local SANYUAN_CARDS = {32,33,34}
local SIXI_CARDS = {28,29,30,31}
local YAOJIU_CARDS = {1,9,10,18,19,27}
local ZI_CARDS = {28,29,30,31,32,33,34}

local M= {}

local function get_colors(cards,extra)
      local colors = {0,0,0,0}
      for i,v in pairs(cards) do
          if v > 0 then
              local color = math.floor((i-1)/9) + 1
              colors[color] = 1
          end
      end

      for k, v in ipairs(extra) do
          local card
          if type(v.value) == "table" then
              card = v.value[2] + 1
          else
              card = v.value + 1
          end
          local color = math.floor((card-1)/9) + 1
          colors[color] = 1
      end
      return colors
end

-- 判断清一色,混一色,字一色   带鬼牌
local function is_yise(cards,extra,gui_num)
      local colors = get_colors(cards,extra)
      local qing_yi_se = (colors[1] + colors[2] + colors[3] == 1) and colors[4] == 0
      local zi_yi_se = (colors[1] + colors[2] + colors[3] == 0) and colors[4] == 1
      local hun_yi_se = (colors[1] + colors[2] + colors[3] == 1) and colors[4] == 1
      return qing_yi_se,hun_yi_se,zi_yi_se
end

-- 是否是 碰碰胡，清碰，混碰    带鬼牌
local function is_pengpenghu(cards,extra,gui_num)
	local need = 0
	local pengpeng_hu,qing_peng,hun_peng
  local colors = get_colors(cards,extra)
  local qing_yi_se,hun_yi_se,zi_yi_se = is_yise(cards,extra,gui_num)

  for _, v in ipairs(extra) do
      if not(v.num == 3 or v.num == 4) then
            return
      end
  end
	for i,c in ipairs(cards) do
  		if c > 0 and c < 4 then
  			   need = need + 3 - c
  		elseif c == 4 then
  		 	   need = need + 2
  		end
	end
	if gui_num - need - 2 >= 0 or gui_num - need + 1 >= 0 then
		pengpeng_hu = (gui_num - need - 2)%3 == 0 or (gui_num - need + 1)%3 == 0
    qing_peng = pengpeng_hu and qing_yi_se
    hun_peng = pengpeng_hu and (hun_yi_se or ((colors[1] + colors[2] + colors[3] + colors[4]== 1) and (gui_num-need-2>=0 or gui_num-need+1>0)))
	end
	return pengpeng_hu,qing_peng,hun_peng
end

local function get_first_and_later_num(cards,extra,first_tbl)
      local first_num = 0
      local later_num = 0
      local later_tbl = {}
      local tt = 1

      for k,v in ipairs(extra) do
            if v.num == 3 or v.num == 4 then
                  if table.index(first_tbl,v.value + 1) then
                        first_num = first_num + 3
                  else
                        later_num = later_num + 3
                  end
            end
      end
      for i,c in ipairs(cards) do
            if c > 0 then
                if table.index(first_tbl,i) then
                		if c == 4 then
                			tt = 0
                		end
                		first_num = first_num + c
                else
                        later_num = later_num + c
                        table.insert(later_tbl,i)
                end
            end
      end
      return first_num,later_num,later_tbl,tt
end

local function converse_to_cards_dict(cards,expect_tbl)
      local temp_dict = utils.table_copy(cards)
      for card,c in ipairs(temp_dict) do
            if c > 0 then
                if not table.index(expect_tbl,card) then
                  temp_dict[card] = 0
                end
            end
      end
      return temp_dict
end

-- 判断小三元，带鬼牌
local function is_xiaosanyuan(cards,extra,gui_num)
  local tt = 1
  local lave_gui,need_gui,hu
  local sanyuan_num,expect_num,expect_tbl

  sanyuan_num,expect_num,expect_tbl,tt  = get_first_and_later_num(cards,extra,SANYUAN_CARDS)
  if sanyuan_num > 8 or expect_num > 6 then
      return false
  end
  need_gui = (8 - sanyuan_num) + (6 - expect_num )
  lave_gui = gui_num - (8 - sanyuan_num)

  cards = converse_to_cards_dict(cards,expect_tbl)
  hu = split_next.foreach_eye(cards, lave_gui)
  return gui_num >= need_gui and hu and tt == 1
end

-- 判断大三元，带鬼牌
local function is_dasanyuan(cards,extra,gui_num)
    local tt = 1
    local empty = 0
    local need_gui,lave_gui,hu
    local sanyuan_num,expect_num,expect_tbl,temp_dict

    sanyuan_num,expect_num,expect_tbl,tt  = get_first_and_later_num(cards,extra,SANYUAN_CARDS)
    if sanyuan_num > 9 or expect_num > 5 then
        return false
    end
    need_gui = (9 - sanyuan_num) + (5 - expect_num )
    lave_gui = gui_num - (9 - sanyuan_num)

    temp_dict = converse_to_cards_dict(cards,expect_tbl)

    if lave_gui >= 2 then
        table.insert(expect_tbl,1,empty)
    end

    for _, eye in ipairs(expect_tbl) do
        if eye == empty then
            hu = split_next.foreach_eye(temp_dict, lave_gui - 2)
        else
            local n = temp_dict[eye]
            if n == 1 then
                temp_dict[eye] = 0
                hu = split_next.foreach_eye(temp_dict, lave_gui - 1)
            else
                temp_dict[eye] = temp_dict[eye] - 2
                hu = split_next.foreach_eye(temp_dict, lave_gui)
            end
            temp_dict[eye] = n
        end
        if hu then
            break
        end
    end

    return gui_num >= need_gui and hu and tt == 1
end

-- 判断小四喜，带鬼牌
local function is_xiaosixi(cards,extra,gui_num)
      local tt = 1
      local lave_gui,need_gui,hu
      local sixi_num,expect_num,expect_tbl

      sixi_num,expect_num,expect_tbl,tt = get_first_and_later_num(cards,extra,SIXI_CARDS)
      if sixi_num > 11 or expect_num > 3 then
            return false
      end
      need_gui = (11 - sixi_num) + (3 - expect_num)
      lave_gui = gui_num - (11 - sixi_num)

      cards = converse_to_cards_dict(cards,expect_tbl)
      hu = split_next.foreach_eye(cards, lave_gui)

      return gui_num >= need_gui and hu and tt == 1
end

-- 判断大四喜，带鬼牌
local function is_dasixi(cards,extra,gui_num)
      local tt = 1
      local need_gui,hu
      local sixi_num,expect_num,expect_tbl

      sixi_num,expect_num,expect_tbl,tt = get_first_and_later_num(cards,extra,SIXI_CARDS)
      if sixi_num > 12 or expect_num > 2 then
          return false
      end
      need_gui = (12 - sixi_num) + (2 - expect_num)
      hu = #expect_tbl <= 1
      return gui_num >= need_gui and hu and tt == 1
end

-- 判断幺九和牌，混幺九  ,清幺九 ,   带鬼牌
local function is_yaojiuhu(cards,extra,gui_num)
      local yaojiu_num = 0
      local zi_num = 0
      local need = 0
      local hu,qing_yao_jiu,hun_yao_jiu
      local pengpeng_hu = is_pengpenghu(cards,extra,gui_num)

      for k,v in ipairs(extra) do
            if v.num == 3 or v.num == 4 then
                  if utils.table_index(YAOJIU_CARDS,v.value + 1) then
                        yaojiu_num = yaojiu_num + 3
                  elseif utils.table_index(ZI_CARDS,v.value + 1) then
                        zi_num = zi_num + 3
                  else
                      return false,false
                  end
            else
                  return false,false
            end
      end

      for i,c in ipairs(cards) do
            if c > 0 then
                if c == 4 then
                    need = need + 2
                else
                    need = need + 3 - c
                end
                if utils.table_index(YAOJIU_CARDS,i) then
                        yaojiu_num = yaojiu_num + c
                elseif utils.table_index(ZI_CARDS,i) then
                        zi_num = zi_num + c
                else
                        return false,false
                end
            end
      end

      if gui_num - need - 2 >= 0 or gui_num - need + 1 >= 0 then
            hu = gui_num >= (14 - (yaojiu_num + zi_num))
            hu = yaojiu_num + zi_num + gui_num  == 14 and pengpeng_hu
        		hu = (gui_num - need - 2)%3 == 0 or (gui_num - need + 1)%3 == 0
    	end
      qing_yao_jiu = hu and zi_num == 0
      hun_yao_jiu = hu and (zi_num ~= 0 or(gui_num-need-2 >= 0 or gui_num-need+1>0))
      return hun_yao_jiu,qing_yao_jiu
end

-- 判断 惠州庄  混幺九  ,幺九胡 ,   带鬼牌
local function hzz_is_yaojiuhu(cards,extra,gui_num)
  local yaojiu_num = 0
  local zi_num = 0
  local need_gui = 0
  local lave

  local a = 0
  local b = 0
  local aa = 0
  local bb = 0

  local pengpeng_hu = is_pengpenghu(cards,extra,gui_num)
  local hu,hzz_yao_jiu_hu,hzz_hun_yao_jiu
  local colors = get_colors(cards,extra)

  for k,v in ipairs(extra) do
        if v.num == 3 or v.num == 4 then
              if utils.table_index(YAOJIU_CARDS,v.value + 1) then
                    yaojiu_num = yaojiu_num + 3
              elseif utils.table_index(ZI_CARDS,v.value + 1) then
                    zi_num = zi_num + 3
              else
                  return false,false
              end
        else
              return false,false
        end
  end

  for i,c in ipairs(cards) do
        if c > 0 then
            if c == 4 then
                return false,false
            end
            if utils.table_index(YAOJIU_CARDS,i) then
                    yaojiu_num = yaojiu_num + c
                    if c == 2 then
                        b = b + 1
                    elseif c== 1 then
                        a = a + 1
                    end
            elseif utils.table_index(ZI_CARDS,i) then
                    zi_num = zi_num + c
                    if c == 2 then
                        bb = bb + 1
                    elseif c== 1 then
                        aa = aa + 1
                    end
            else
                    return false,false
            end
        end
  end
  need_gui = need_gui + 14 - (yaojiu_num + zi_num)
  hu = gui_num >= need_gui and yaojiu_num + zi_num + gui_num  == 14 and pengpeng_hu

  lave = gui_num - (b + 2*a + bb + 2*aa - 1)
  if colors[1] + colors[2] + colors[3] + colors[4]  < 2 then
        hzz_hun_yao_jiu = hu and lave >= 2
        if colors[4] == 0 then
            hzz_yao_jiu_hu = hu and lave >= 2
        else
            hzz_yao_jiu_hu = hu and lave >= 5
        end
  elseif colors[1] + colors[2] + colors[3] + colors[4] == 2 then
        if colors[4] == 0 then
            hzz_yao_jiu_hu = hu
            hzz_hun_yao_jiu = false
        else
            hzz_yao_jiu_hu = hu and lave >= 2
            hzz_hun_yao_jiu = hu
        end
  else
        hzz_yao_jiu_hu = hu
        hzz_hun_yao_jiu = false
  end

  return hzz_yao_jiu_hu,hzz_hun_yao_jiu
end

-- 判断十八罗汉，带鬼牌
local function is_shibaluohan(cards,extra,gui_num)
      local count = 0
      local hu = false
      for k,v in ipairs(extra) do
          if v.num == 4 then
               count = count + 1
          else
               return false
          end
      end
      for _,c in ipairs(cards) do
          hu = c + gui_num == 2
          if hu then
              break
          end
      end
      return count == 4 and hu
end

-- 判断平胡 （顺子 + 将），带鬼牌
local function is_pinghu(cards,cards_dict,extra,gui_tbl,gui_num)
      local kezi
      local temp_cards = table.copy(cards)
      local hu = pinghu_splitlib.get_hu_info(temp_cards,gui_tbl)
      for k,v in ipairs(extra) do
            if type(v.value) ~= "table" then
                  kezi = true
                  break
            end
      end
      return hu and not kezi
end

-- 判断鸡胡 （m刻子+n顺子 + 将），带鬼牌
local function is_jihu(cards_dict,extra,gui_tbl,gui_num)
      local kezi,need,hu
      local empty = 0
      local eye_tbl = {}

      for k,v in ipairs(extra) do
            if type(v.value) ~= "table" then
                  kezi = true
                  return true
            end
      end

      for i,c in ipairs(cards_dict) do
            if c > 0 then
                table.insert(eye_tbl,i)
            end
      end

      if gui_num >= 3 then
          table.insert(eye_tbl,1,empty)
      end

      for _, eye in ipairs(eye_tbl) do
          kezi  =  true
          if eye == empty then
                hu = splitlib.get_hu_info(cards_dict,gui_tbl,gui_num - 3)
          else
              local n = cards_dict[eye]
              if n == 1 or n == 2 then
                  cards_dict[eye] = 0
                  hu = splitlib.get_hu_info(cards_dict,gui_tbl,gui_num - (3-n))
              elseif n == 3 or n == 4 then
                  cards_dict[eye] = cards_dict[eye] - 3
                  hu = splitlib.get_hu_info(cards_dict,gui_tbl,gui_num)
              end
              cards_dict[eye] = n
          end
          if hu then
              break
          end
      end

      return kezi and hu
end

-- 得到所有3n+2胡牌的牌型，带鬼牌
local function get_all_normal_dahu(cards,cards_dict,extra,gui_tbl,gui_num)
    local hu_tbl = {}
    local qing_yi_se,hun_yi_se,zi_yi_se = is_yise(cards_dict,extra,gui_num)
    local peng_peng,qing_peng,hun_peng = is_pengpenghu(cards_dict,extra,gui_num)
    local xiao_san_yuan = is_xiaosanyuan(cards_dict,extra,gui_num)
    local da_san_yuan = is_dasanyuan(cards_dict,extra,gui_num)
    local xiao_si_xi = is_xiaosixi(cards_dict,extra,gui_num)
    local da_si_xi = is_dasixi(cards_dict,extra,gui_num)
    local shi_ba_luo_han = is_shibaluohan(cards_dict,extra,gui_num)
    local hun_yao_jiu,qing_yao_jiu = is_yaojiuhu(cards_dict,extra,gui_num)
    local ping_hu = is_pinghu(cards,cards_dict,extra,gui_tbl,gui_num)
    local ji_hu = is_jihu(cards_dict,extra,gui_tbl,gui_num)

    local hzz_yao_jiu_hu,hzz_hun_yao_jiu = hzz_is_yaojiuhu(cards_dict,extra,gui_num)

    if qing_yi_se then
        table.insert(hu_tbl,"qing_yi_se")
        --LERR("================> 检测到：清一色  胡牌")
    end
    if hun_yi_se then
        table.insert(hu_tbl,"hun_yi_se")
        --LERR("================> 检测到：混一色  胡牌")
    end
    if zi_yi_se then
        table.insert(hu_tbl,"zi_yi_se")
        --LERR("================> 检测到：字一色  胡牌")
    end

    if peng_peng then
          if qing_peng then
              table.insert(hu_tbl,"qing_peng")
              --LERR("================> 检测到：清碰   胡牌")
          end
          if hun_peng then
              table.insert(hu_tbl,"hun_peng")
              --LERR("================> 检测到：混碰   胡牌")
          end
          if peng_peng then
            table.insert(hu_tbl,"peng")
            --LERR("================> 检测到：碰碰胡  胡牌")
          end
    end

    if da_si_xi then
        table.insert(hu_tbl,"da_si_xi")
        --LERR("================> 检测到：大四喜 胡牌")
    end

    if xiao_si_xi then
        table.insert(hu_tbl,"xiao_si_xi")
        --LERR("================> 检测到：小四喜 胡牌")
    end

    if da_san_yuan then
        table.insert(hu_tbl,"da_san_yuan")
        --LERR("================> 检测到：大三元 胡牌")
    end

    if xiao_san_yuan then
        table.insert(hu_tbl,"xiao_san_yuan")
        --LERR("================> 检测到：小三元 胡牌")
    end

    if hun_yao_jiu then
        table.insert(hu_tbl,"hun_yao_jiu")
        --LERR("================> 检测到：混幺九 胡牌")
    end

    if qing_yao_jiu then
        table.insert(hu_tbl,"qing_yao_jiu")
        --LERR("================> 检测到：清幺九 胡牌")
    end

    if hzz_hun_yao_jiu then
        table.insert(hu_tbl,"hzz_hun_yao_jiu")
        --LERR("================> 检测到：惠州庄 混幺九 胡牌")
    end

    if hzz_yao_jiu_hu then
        table.insert(hu_tbl,"hzz_yao_jiu_hu")
        --LERR("================> 检测到：惠州庄 幺九胡 胡牌")
    end

    if shi_ba_luo_han then
        table.insert(hu_tbl,"shi_ba_luo_han")
        if qing_yi_se then
          table.insert(hu_tbl, "qing_yi_shi_ba_luo_han")
        end
        --LERR("================> 检测到：十八罗汉 胡牌")
    end

    if ping_hu then
        table.insert(hu_tbl,"ping")
        --LERR("================> 检测到：平胡 && 胡牌")
    end

    if ji_hu then
        table.insert(hu_tbl,"ji_hu")
        ----LERR("================> 检测到：鸡胡 && 胡牌")
    end

    return hu_tbl
end

function M.main(cards,cards_dict,extra,gui_tbl,gui_num)
      return  get_all_normal_dahu(cards,cards_dict,extra,gui_tbl,gui_num)
end

return M
