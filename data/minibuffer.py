import jedit

def start_minibuf_capture(action, completer):
    jedit.minibuf_action    = action
    jedit.minibuf_completer = completer
    jedit.current_keymap    = jedit.minibuf_keymap
    jedit.current_keytarget = jedit.mini_buffer()

def confirm_minibuf_action():

    name = jedit.mini_buffer().get_dynamic()

    jedit.minibuf_action(name)

    cancel_minibuf_action()

def cancel_minibuf_action():

    jedit.mini_buffer().cancel()
    jedit.current_keymap    = jedit.global_keymap
    jedit.current_keytarget = jedit.editor()
    jedit.minibuf_action    = None
    jedit.minibuf_completer = None

def complete_minibuf():
    if jedit.minibuf_completer:
        jedit.minibuf_completer()
