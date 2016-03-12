import os

from subprocess import Popen, PIPE, STDOUT
import xml.etree.ElementTree as xmlet

editor      = jedit.editor()
key_handler = jedit.key_handler()    
buffer_list = jedit.buffer_list()
mini_buffer = jedit.mini_buffer()

editor.set_font("DroidSansMono")
editor.set_caret_style(2)

global_keymap = {}
minibuf_keymap = {}

current_keymap    = global_keymap
current_keytarget = editor

minibuf_action = None

buffer_list.find_file("app.cpp")

def self_insert():

    for char in key_handler.key_buffer():
        current_keytarget.insert_char(char)

def find_file(name):
    buffer_list.find_file(name)

def start_find_file():

    global minibuf_action
    global current_keymap
    global current_keytarget

    minibuf_action    = find_file
    current_keymap    = minibuf_keymap
    current_keytarget = mini_buffer

    mini_buffer.start_capture("Find file: ", "find_file")
    mini_buffer.set_dynamic('./')

def confirm_minibuf_action():

    name = mini_buffer.get_dynamic()

    minibuf_action(name)

    cancel_minibuf_action()

def cancel_minibuf_action():

    global minibuf_action
    global current_keymap
    global current_keytarget

    mini_buffer.cancel()
    current_keymap    = global_keymap
    current_keytarget = editor
    minibuf_action    = None

def complete_minibuf():

    current_content = mini_buffer.get_dynamic()

    directory = os.path.dirname(current_content)
    part      = os.path.basename(current_content)
    entries = os.listdir(directory)

    completions = [ i for i in entries if i[0:len(part)] == part ]

    prefix = os.path.commonprefix(completions)

    mini_buffer.set_dynamic(os.path.join(directory, prefix))

def format_buffer():
    contents = editor.get_text()
    
    pipe = Popen(['clang-format','-output-replacements-xml','-style=LLVM'], stdout=PIPE, stdin=PIPE, stderr=STDOUT)
    
    clang_stdout = pipe.communicate(input=contents.encode('UTF-8'))[0]

    repl_xml = clang_stdout.decode()

    root = xmlet.fromstring(repl_xml)

    replacements = [ (child.attrib['offset'],child.attrib['length'],child.text) for child in root ]

    for o, l, r in reversed(replacements):
        offset = int(o)
        length = int(l)
        repl   = r

        editor.delete_range(offset, length)
        editor.insert_text(offset, repl)


global_keymap['C-n'] = editor.next_line
global_keymap['C-p'] = editor.previous_line
global_keymap['C-f'] = editor.char_right
global_keymap['C-b'] = editor.char_left
global_keymap['C-j'] = editor.new_line
global_keymap['C-a'] = editor.line_start
global_keymap['C-e'] = editor.line_end


global_keymap['RET']  = editor.new_line
global_keymap['UP']   = editor.previous_line
global_keymap['DOWN'] = editor.next_line

global_keymap['BS']  = editor.backspace
global_keymap['C-d'] = editor.delete

global_keymap['C-S-_'] = editor.undo

global_keymap['C-x C-f'] = start_find_file
global_keymap['C-x b']   = buffer_list.switch_buffer
global_keymap['C-x k']   = buffer_list.kill_buffer
global_keymap['C-x C-s'] = buffer_list.save_file

global_keymap['C-M-\\'] = format_buffer

global_keymap['C-x C-c'] = jedit.exit

minibuf_keymap['BS']  = mini_buffer.backspace
minibuf_keymap['RET'] = confirm_minibuf_action
minibuf_keymap['C-g'] = cancel_minibuf_action
minibuf_keymap['TAB'] = complete_minibuf

def handle_key(cmd):

    partial_matches = [i for i in current_keymap if i[0:len(cmd)] == cmd ]

    if cmd in current_keymap:
        current_keymap[cmd]()
        return True
    elif len(cmd) > 1 and len(partial_matches) > 0:
        return False
    else:
        self_insert()

    return True
