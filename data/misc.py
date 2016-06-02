import jedit


editor      = jedit.editor()
buffer_list = jedit.buffer_list()

buffer = buffer_list.current()

def insert_tab():
    jedit.current_keytarget.insert_char(" ")
    jedit.current_keytarget.insert_char(" ")

def set_mark():
    point = editor.get_pos()
    buffer.set_mark(point)

    print('Mark set at: {}'.format(point))

def exange_point_and_mark():
    point = editor.get_pos()

    mark  = buffer.get_mark()

    print('Setting point')
    editor.set_pos(mark)
    print('Setting mark')
    buffer.set_mark(point)
    print('(p:{},m:{}) --> (p:{},m:{})'.format(point,mark, editor.get_pos(), buffer.get_mark()))


