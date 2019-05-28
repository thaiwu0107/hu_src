-- 包含各种胡牌牌型检测
local utils = require "hu_lib/utils"

local log = require "log"
local LERR = log.error


local SHISANYAO_CARDS = {1,9,10,18,19,27,28,29,30,31,32,33,34}

local M = {}

-- 判断七对，豪华个数，带鬼牌
local function is_7_dui(cards_dict,gui_num)
    local sum = 0
    local dui = 0
    local need_gui = 0
    local haohua = 0
    local lave = gui_num

    for i,c in ipairs(cards_dict) do
        if c > 0 then
                sum = sum + c
                if c <= 2 then
                    dui = dui + 1
                    lave = lave - (2 - c)
                    need_gui = need_gui + (2 - c)
                else
                    haohua = haohua + 1
                    lave = lave - (4 - c)
                    need_gui = need_gui + (4 - c)
                end
        end
    end
    if lave/2 >= dui and lave >= 0 then
        haohua = haohua + dui + (lave/2 - dui)/2
    elseif lave/2 < dui and lave >= 0 then
        haohua = haohua + lave/2
    end

    return sum + gui_num == 14 and gui_num >= need_gui, math.floor(haohua)
end

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

--- 判断十三幺 ,带鬼牌
local function is_13_19(cards_dict,gui_num)
    local sum = 0
    local without_count = 0
    local eye =false

    for _,i in ipairs(SHISANYAO_CARDS) do
          if cards_dict[i] ~= 0 then
              if cards_dict[i] > 2 then
                  return false
              end
              if cards_dict[i] == 2 then
                  if eye then
                      return false
                  else
                      eye = true
                  end
              end
              sum = sum + cards_dict[i]
          else
              without_count = without_count + 1
          end
    end

    if eye then
          return without_count == gui_num and sum + gui_num == 14
    else
          return without_count + 1 == gui_num and sum + gui_num == 14
    end
end

local function is_yise(cards,extra,gui_num)
      local colors = get_colors(cards,extra)
      local qing_yi_se = (colors[1] + colors[2] + colors[3] == 1) and colors[4] == 0
      --local zi_yi_se = (colors[1] + colors[2] + colors[3] == 0) and colors[4] == 1
      local hun_yi_se = (colors[1] + colors[2] + colors[3] == 1) and colors[4] == 1
      return qing_yi_se,hun_yi_se
end


local function get_all_special_hu(cards,cards_dict,extra,gui_tbl,gui_num)
    local hu_tbl = {}
    local xiao_qi_dui,haohua = is_7_dui(cards_dict,gui_num)
    local shi_san_yao = is_13_19(cards_dict,gui_num)
    local qing_yi_se,hun_yi_se = is_yise(cards_dict,extra,gui_num)

    if xiao_qi_dui then
          --LERR("  ================> 检测到：七小对 胡牌 , 豪华个数: %d",haohua)
          if haohua == 0 then
              table.insert(hu_tbl, "qi_xiao_dui")
              if qing_yi_se then
                table.insert(hu_tbl, "qing_yi_se_qi_xiao_dui")
              end
              if hun_yi_se then
                table.insert(hu_tbl, "hun_yi_se_qi_xiao_dui")
              end
          elseif haohua == 1 then
              table.insert(hu_tbl, "hh_qi_xiao_dui")
              if qing_yi_se then
                table.insert(hu_tbl, "qing_yi_se_hh_qi_xiao_dui")
              end
              if hun_yi_se then
                table.insert(hu_tbl, "hun_yi_se_hh_qi_xiao_dui")
              end
          elseif haohua == 2 then
              table.insert(hu_tbl, "double_qi_xiao_dui")
              if qing_yi_se then
                table.insert(hu_tbl, "qing_yi_se_double_qi_xiao_dui")
              end
          elseif haohua == 3 then
              if qing_yi_se then
                table.insert(hu_tbl, "qing_yi_se_triple_qi_xiao_dui")
              end
              table.insert(hu_tbl, "triple_qi_xiao_dui")
          end
    end

    if shi_san_yao then
          table.insert(hu_tbl,"shi_san_yao")
          --LERR("  ================> 检测到：十三幺 胡牌")
    end

    return hu_tbl
end

function M.main(cards,cards_dict,extra,gui_tbl,gui_num)
	  return get_all_special_hu(cards,cards_dict,extra,gui_tbl,gui_num)
end

return M
