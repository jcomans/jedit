import jedit

def start_minibuf_capture(action, completer):
    jedit.minibuf_action    = action
    jedit.minibuf_completer = completer
    jedit.current_keymap    = jedit.minibuf_keymap
    jedit.current_keytarget = jedit.mini_buffer()
