
local utils = require "hu_lib/utils"
local splitlib = require "hu_lib/splitlib"
local pinghu_splitlib = require "hu_lib/pinghu_splitlib"

local normal_dahu = require "hu_lib/normal_dahu"
local special_hu = require "hu_lib/special_hu"

local log = require "log"
local LERR = log.error


local M= {}


local HU_FAN_TYPE = {
      "qing_yi_shi_ba_luo_han", --清一色十八罗汉
      "qing_yi_se_double_qi_xiao_dui", --清一色双豪七
      "shi_ba_luo_han" , -- 十八罗汉
      "double_qi_xiao_dui",-- "2豪华七小对",
      "zi_yi_se" , --"字一色",
      "shi_san_yao"  , --十三幺
      "qing_yao_jiu" , --"清幺九",
      "da_si_xi" , --大四喜
      "da_san_yuan" , --"大三元",
      "qing_yao_jiu",--"清幺九",

      "zi_yi_se" , --"字一色",
      "hun_yao_jiu" , --"混幺九",

      "triple_qi_xiao_dui",-- "3豪华七小对",
      "double_qi_xiao_dui",-- "2豪华七小对",
      "hh_qi_xiao_dui", -- "豪华七小对",

      "xiao_san_yuan" , --"小三元",
      "xiao_si_xi" , --"小四喜",
      "qing_peng" , --"清碰",

      "qi_xiao_dui"  , --"七小对"
      "qing_yi_se" , --"清一色",
      "hun_peng" , --"混碰",

      "hun_yi_se"  ,--"混一色"
      "peng" , --"碰碰胡"

      "ping" , --"平胡"
      "ji_hu" , --"鸡胡"
}

local function converse_hand_to_dict(cards,card,gui_tbl)
      local dict = {}
      local temp = {}
      local cards_dict
      local gui_num = 0

      for _, v in ipairs(cards) do
          dict[v] = (dict[v] or 0) + 1
      end

      if card then
          dict[card] = (dict[card] or 0) + 1
      end

      for i=1,34 do
            temp[i] = dict[i-1] or 0
      end

      cards_dict = utils.table_copy(temp)
      if gui_tbl then
            for k,i in ipairs(gui_tbl) do
                gui_tbl[k] = gui_tbl[k] + 1
            end

            for k,i in ipairs(gui_tbl) do
                  if cards_dict[i] and (i>=1 and i<=34) then
                    gui_num = gui_num + (cards_dict[i])
                    cards_dict[i] = 0
                  end
            end
      end

      return temp,cards_dict,gui_num
end

local function get_max_hu(normal_dahu_tbl,special_hu_tbl)
      local max_hu
      local hu_tbl = {}
      if special_hu_tbl then
    	    for k,v in pairs(special_hu_tbl) do
    	        table.insert(hu_tbl,v)
    	    end
  	  end

    	if normal_dahu_tbl then
    	    for k,v in pairs(normal_dahu_tbl) do
    	        table.insert(hu_tbl,v)
    	    end
    	end

      for i,t in ipairs(HU_FAN_TYPE) do
            if hu_tbl and utils.table_index(hu_tbl,tostring(t)) then
                 max_hu = t
                 break
            end
      end
      return hu_tbl,max_hu
end

function M.main(temp_cards,extra,card,temp_gui_tbl)
    	local gui_num, cards,cards_dict,gui_tbl
      local special_hu_tbl,normal_hu_tbl,hu,hu_tbl,max_hu
      gui_tbl = table.copy(temp_gui_tbl or {})
      cards = table.copy(temp_cards or {})
      cards,cards_dict,gui_num = converse_hand_to_dict(cards,card,gui_tbl)
      hu = splitlib.get_hu_info(cards, gui_tbl)
      special_hu_tbl = special_hu.main(cards,cards_dict,extra,gui_tbl,gui_num)

      if hu then
         normal_hu_tbl = normal_dahu.main(cards,cards_dict,extra,gui_tbl,gui_num)
      elseif not hu and not (next(special_hu_tbl)) then
             return hu,hu_tbl
      end

      hu_tbl,max_hu = get_max_hu(normal_hu_tbl,special_hu_tbl)

      if hu or max_hu then
              LERR("\n\n============> hu_tbl:  %s",table.dump(hu_tbl))
              LERR("============> hu_flag = %s, max_hu：%s \n\n",hu,max_hu)
      end

      return hu, hu_tbl
end

return M
