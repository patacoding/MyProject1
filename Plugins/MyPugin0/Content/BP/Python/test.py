import unreal
import time

import sys


# unreal.log_warning('Number of arguments:' + str(len(sys.argv)) + 'arguments.')
# unreal.log_warning('Argument List:' + str(sys.argv))


unreal.log('Hello World log!' + str(time.time()))
unreal.log_warning('Hello World! warning' + str(time.time()))
unreal.log_error('Hello World!' + str(time.time()))

# unreal.EditorDialog().show_message(
#     'dialog title!',
#     'Hello World for dialog!',
#     unreal.AppMsgType.OK)


level_sequence_asset_path = "/Game/NewLevelSequence2"
level_sequence = unreal.load_asset(level_sequence_asset_path)

# set playback range
level_sequence.set_playback_start(0)
level_sequence.set_playback_end(500)

actor = unreal.EditorLevelLibrary.get_selected_level_actors()[0]

actor_location = actor.get_actor_location()
actor_location = [actor_location.x, actor_location.y, actor_location.z]

unreal.log(actor.get_name())

actor_binding = level_sequence.add_possessable(actor)

transform_track = actor_binding.add_track(unreal.MovieScene3DTransformTrack)
transform_section = transform_track.add_section()

transform_section.set_range(0, 100)

# list all channels of the transform section
for index, ch in enumerate(transform_section.get_channels()):
    unreal.log(index)
    unreal.log(ch.get_name())

loc_x = transform_section.get_channels()[0]
unreal.log(loc_x.get_name())

loc_x.add_key(
    unreal.FrameNumber(10),
    4000.0,
    interpolation=unreal.MovieSceneKeyInterpolation.LINEAR  # AUTO, BREAK, CONSTANT, LINEAR, USER.
)


loc_x.add_key(
    unreal.FrameNumber(20),
    6000.0,
    interpolation=unreal.MovieSceneKeyInterpolation.LINEAR  # AUTO, BREAK, CONSTANT, LINEAR, USER.
)


loc_x.add_key(
    unreal.FrameNumber(30),
    8000.0,
    interpolation=unreal.MovieSceneKeyInterpolation.LINEAR  # AUTO, BREAK, CONSTANT, LINEAR, USER.
)
