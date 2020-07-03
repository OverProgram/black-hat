cursor_x = 0
cursor_y = 0
width, height = terminal.get_size()

function inc_cursor()
    cursor_x = cursor_x + 1
    if cursor_x > width then
        cursor_x = 0
        cursor_y = cursor_y + 1
    end
end

function print_char(chr)
    if chr == '\n' then
        cursor_y = cursor_y + 1
    elseif chr == ' ' then
        inc_cursor()
    else
        terminal.put_char(chr, cursor_x, cursor_y)
        inc_cursor()
    end
end

function print(str)
    for i = 1, #str do
        local c = str:sub(i, i)
        print_char(c)
    end
end

function on_keypress(chr)
    print_char(chr)
end

function main()
    terminal.register_keypress("on_keypress")
    print("Hello, world!")
end
