import jedit

import buffer_handling
import clang
import file_handling
import minibuffer

editor      = jedit.editor()
buffer_list = jedit.buffer_list()
key_handler = jedit.key_handler()


def load_default_keymap():
    jedit.global_keymap['C-n'] = editor.next_line
    jedit.global_keymap['C-p'] = editor.previous_line
    jedit.global_keymap['C-f'] = editor.char_right
    jedit.global_keymap['C-b'] = editor.char_left
    jedit.global_keymap['C-j'] = editor.new_line
    jedit.global_keymap['C-a'] = editor.line_start
    jedit.global_keymap['C-e'] = editor.line_end


    jedit.global_keymap['RET']  = editor.new_line
    jedit.global_keymap['UP']   = editor.previous_line
    jedit.global_keymap['DOWN'] = editor.next_line

    jedit.global_keymap['BS']  = editor.backspace
    jedit.global_keymap['C-d'] = editor.delete

    jedit.global_keymap['C-S-_'] = editor.undo

    jedit.global_keymap['C-x C-f'] = file_handling.start_find_file
    jedit.global_keymap['C-x b']   = buffer_handling.start_switch_buffer
    jedit.global_keymap['C-x k']   = buffer_handling.start_kill_buffer
    jedit.global_keymap['C-x C-s'] = buffer_handling.start_save_buffer

    jedit.global_keymap['C-M-\\'] = clang.format_buffer

    jedit.global_keymap['C-x C-c'] = jedit.exit

    jedit.minibuf_keymap['BS']  = jedit.mini_buffer().backspace
    jedit.minibuf_keymap['RET'] = minibuffer.confirm_minibuf_action
    jedit.minibuf_keymap['C-g'] = minibuffer.cancel_minibuf_action
    jedit.minibuf_keymap['TAB'] = minibuffer.complete_minibuf

def self_insert():

    for char in key_handler.key_buffer():
        jedit.current_keytarget.insert_char(char)
