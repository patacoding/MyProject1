import unreal
import time

unreal.log('Hello World!' + str(time.time()))
unreal.log_warning('Hello World! warning' + str(time.time()))
unreal.log_error('Hello World!' + str(time.time()))

unreal.EditorDialog().show_message(
    'dialog title!',
    'Hello World for dialog!',
    unreal.AppMsgType.OK)
