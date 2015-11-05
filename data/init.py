# import string

# hello.say_hello()

# def do_exit(key):
#     hello.write('Exiting\n')

# def self_insert(key):
#     hello.write(key)

# def show_character_code(key):
#     hello.write('|{0:02x}|'.format(ord(key)))

# global_key_map = {}
# global_key_map[27] = do_exit

# def handle_key(key):
#     if key in global_key_map:
#         global_key_map[key](key)
#     elif key in string.printable:
#         self_insert(key)
#     else:
#         show_character_code(key)

editor = jedit.editor()    

editor.set_font("DroidSansMono")
editor.add_text("\nHello world!\n")
