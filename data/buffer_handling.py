import jedit
import util

buffer_list = jedit.buffer_list()

def switch_buffer(scratch):
    buffer_list.switch_buffer()

def start_switch_buffer():
    
    util.start_minibuf_capture(switch_buffer, None)

    jedit.mini_buffer().start_capture("Switch buffer?");

def kill_buffer(scratch):
    
    buffer_list.kill_buffer()

def start_kill_buffer():
    
    util.start_minibuf_capture(kill_buffer, None)

    buffer_name = buffer_list.current().name()

    jedit.mini_buffer().start_capture("Kill buffer (default {}): ".format(buffer_name));

def save_buffer(scratch):
    
    buffer_list.save_file()


def start_save_buffer():
    
    save_buffer(None);
