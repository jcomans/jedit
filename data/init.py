
editor = jedit.editor()
key_handler = jedit.key_handler()    

editor.set_font("DroidSansMono")
editor.add_text("\nHello world!\n")

def self_insert():
    for char in key_handler.key_buffer():
        editor.insert_char(char)

global_keymap = {}

global_keymap['C-n'] = editor.next_line
global_keymap['C-p'] = editor.previous_line
global_keymap['C-f'] = editor.char_right
global_keymap['C-b'] = editor.char_left
global_keymap['C-j'] = editor.new_line

global_keymap['RET']  = editor.new_line
global_keymap['UP']   = editor.previous_line
global_keymap['DOWN'] = editor.next_line

def handle_key(cmd):
    if cmd in global_keymap:
        global_keymap[cmd]()

    else:
        self_insert()
