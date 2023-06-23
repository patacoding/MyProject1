import unreal
import time

import sys


unreal.log_warning('Number of arguments:' + str(len(sys.argv)) + 'arguments.')
unreal.log_warning('Argument List:' + str(sys.argv))


unreal.log('Hello World!' + str(time.time()))
unreal.log_warning('Hello World! warning' + str(time.time()))
unreal.log_error('Hello World!' + str(time.time()))

unreal.EditorDialog().show_message(
    'dialog title!',
    'Hello World for dialog!',
    unreal.AppMsgType.OK)
