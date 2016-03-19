import jedit
import keymap

keymap.load_default_keymap()

jedit.current_keymap    = jedit.global_keymap
jedit.current_keytarget = jedit.editor()


jedit.editor().set_font("DroidSansMono")
jedit.editor().set_caret_style(2)



jedit.buffer_list().find_file("app.cpp")




def handle_key(cmd):

    partial_matches = [i for i in jedit.current_keymap if i[0:len(cmd)] == cmd ]

    if cmd in jedit.current_keymap:
        jedit.current_keymap[cmd]()
        return True
    elif len(cmd) > 1 and len(partial_matches) > 0:
        return False
    else:
        keymap.self_insert()

    return True
