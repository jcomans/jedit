import jedit

import os

mini_buffer = jedit.mini_buffer()
buffer_list = jedit.buffer_list()

def find_file(name):
    buffer_list.find_file(name)

def start_find_file():

    jedit.minibuf_action    = find_file
    jedit.minibuf_completer = complete_filename
    jedit.current_keymap    = jedit.minibuf_keymap
    jedit.current_keytarget = mini_buffer

    mini_buffer.start_capture("Find file: ", "find_file")
    mini_buffer.set_dynamic('./')

def complete_filename():

    current_content = mini_buffer.get_dynamic()

    directory = os.path.dirname(current_content)
    part      = os.path.basename(current_content)
    entries = os.listdir(directory)

    completions = [ i for i in entries if i[0:len(part)] == part ]

    prefix = os.path.commonprefix(completions)

    mini_buffer.set_dynamic(os.path.join(directory, prefix))
