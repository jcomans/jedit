
editor = jedit.editor()
key_handler = jedit.key_handler()    

editor.set_font("DroidSansMono")
editor.add_text("\nHello world!\n")

def self_insert():
    editor.insert_char(key_handler.key_buffer())

global_keymap = {}

global_keymap['a'] = self_insert

global_keymap['C-n'] = editor.next_line
global_keymap['C-p'] = editor.previous_line
global_keymap['C-j'] = editor.new_line

def handle_key(cmd):
    if cmd in global_keymap:
        global_keymap[cmd]()
