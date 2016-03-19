import jedit

editor = jedit.editor()

from subprocess import Popen, PIPE, STDOUT
import xml.etree.ElementTree as xmlet

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
