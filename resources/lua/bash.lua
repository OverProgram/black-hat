cursor_x = 0
cursor_y = 0
width, height = terminal.get_size()

function new_line()
    cursor_x = 0
    cursor_y = cursor_y + 1
    if cursor_y == height then
        cursor_y = height - 1
    end
end

function inc_cursor()
    cursor_x = cursor_x + 1
    if cursor_x > width then
        new_line()
    end
end

function dec_cursor()
    cursor_x = cursor_x - 1
    if cursor_x < 0 then
        cursor_x = width - 1
        cursor_y = cursor_y - 1
        if cursor_y < 0 then
            cursor_y = 0
        end
    end
end

function backspace()
    dec_cursor()
    terminal.put_char(string.char(0), cursor_x, cursor_y)
end

function print_char(chr)
    if string.byte(chr) == 10 then
        new_line()
    elseif string.byte(chr) == 9 then
        for i = 1, 4 do
            print_char(string.char(0))
        end
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
    if string.byte(chr) == 8 then
        backspace()
    else
        print_char(chr)
    end
end

function main()
    terminal.register_keypress("on_keypress")
    print("Hello, world!")
end
