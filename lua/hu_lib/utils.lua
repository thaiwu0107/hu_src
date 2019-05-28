local M = {}

function M.table_index(tbl, obj)
    if tbl == nil or obj == nil then
        return nil
    end
    for i,v in ipairs(tbl) do
        if v == obj then
            return i
        end
    end
    return nil
end

function M.table_copy( src )
    local dst = {}
    for k,v in pairs(src) do
        dst[k] = v
    end
    return dst
end

function M.table_length(tbl)
    local n = 0
    for _ in ipairs(tbl) do
        n = n + 1
    end
    return n
end

return M
