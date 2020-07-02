function main()
--    local str = "Hello, world!"
--    for i=0, #str do
--            local c = str:sub(i,i)
--            put_char(c, i, 0)
--    end
    register_keypress("on_keypress")
end

function on_keypress(chr)
    put_char("H", 0, 0)
end
