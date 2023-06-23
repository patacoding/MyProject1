# Transfer a folder of images into the Unreal Editor Sequencer.
# Author: Atom
# This script will scan a folder for image files with a specific file extension.
# A companion mesh will be generated for each file found in the folder.
# A material will be assigned to the mesh linking the image.
# (c) 2020 Atom
# 10/18/20

import unreal
import os, re, platform, random
import struct, imghdr

# ------------------------------------------------------------------------------
# Constants/Controls

# Sequence time in seconds
SEQUENCE_LENGTH = 12

LOC_CHANNELS = [
    'Location.X',
    'Location.Y',
    'Location.Z',
]
ROT_CHANNELS = 
'Rotation.X',
'Rotation.Y',
'Rotation.Z',
]
SCALE_CHANNELS = 
'Scale.X',
'Scale.Y',
'Scale.Z',
]
# ------------------------------------------------------------------------------

# Unreal Editor Sequencer functions.
def add_actor_to_sequence(target_sequence, actor):
    """
    Add the specified actor into the target sequence with keys

    :param unreal.MovieSceneSequence target_sequence: The sequence to add to
    :param unreal.Actor actor: The image to be added
    :return:
    """
frame_rate = target_sequence.get_display_rate()
frame_rate = frame_rate.numerator / frame_rate.denominator

# Fetch actor transform values.
actor_location = actor.get_actor_location()
actor_location = [actor_location.x, actor_location.y, actor_location.z]

actor_rotation = actor.get_actor_rotation()
actor_rotation = [actor_rotation.roll, actor_rotation.pitch, actor_rotation.yaw]

actor_size = actor.get_actor_relative_scale3d() #get_actor_scale3d()
actor_size = [actor_size.x,actor_size.y,actor_size.z]

sequence = target_sequence.add_possessable(actor)
transform_track = sequence.add_track(unreal.MovieScene3DTransformTrack)
new_section = transform_track.add_section()
new_section.set_range_seconds(0, SEQUENCE_LENGTH)

# Drop down a single keyframe.
channels = new_section.get_channels()
for channel in channels:
channel_name = channel.get_name()
if channel_name in LOC_CHANNELS:
# Key location chanel
channel_index = LOC_CHANNELS.index(channel_name)
channel.add_key(
unreal.FrameNumber(0),
actor_location[channel_index],
interpolation=unreal.MovieSceneKeyInterpolation.LINEAR #AUTO, BREAK, CONSTANT, LINEAR, USER.
)
if channel_name in ROT_CHANNELS:
# Key location chanel
channel_index = ROT_CHANNELS.index(channel_name)
channel.add_key(
unreal.FrameNumber(0),
actor_rotation[channel_index],
interpolation=unreal.MovieSceneKeyInterpolation.LINEAR
)
if channel_name in SCALE_CHANNELS:
channel_index = SCALE_CHANNELS.index(channel_name)
channel.add_key(
unreal.FrameNumber(0),
actor_size[channel_index],
interpolation=unreal.MovieSceneKeyInterpolation.LINEAR
)
'''
channel.add_key(
unreal.FrameNumber(SEQUENCE_LENGTH * frame_rate),
adjusted_location[channel_index],
interpolation=unreal.MovieSceneKeyInterpolation.LINEAR
)
'''


def create_new_level_sequence(new_level_sequence_path, new_level_sequence_name):
"""
Create a new level sequence in engine

:param str new_level_sequence_path: the new level sequence target directory
:param str new_level_sequence_name: name of the new level to be created

:return: The new level sequence if it was created, or None if it failed
:rtype: unreal.LevelSequence | NoneType
"""
asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
return asset_tools.create_asset(
asset_name=new_level_sequence_name,
package_path=new_level_sequence_path,
asset_class=unreal.LevelSequence,
factory=unreal.LevelSequenceFactoryNew()
)

def returnValidUnrealMaterialName(passedItem):
# Replace any illegal characters for names here.
s = re.sub("^0-9a-zA-Z\.]+", "_", passedItem)
s = s.replace(".","_")
return s

def get_image_size(file_path):
"""
Return (width, height) for a given img file content - no external
dependencies except the os and struct modules from core
"""
with open(file_path, 'rb') as fhandle:
head = fhandle.read(24)
if len(head) != 24:
return
if imghdr.what(file_path) == 'png':
check = struct.unpack('>i', head[4:8])[0]
if check != 0x0d0a1a0a:
return
width, height = struct.unpack('>ii', head[16:24])
elif imghdr.what(file_path) == 'gif':
width, height = struct.unpack('<HH', head[6:10])
elif imghdr.what(file_path) == 'jpeg':
try:
fhandle.seek(0) # Read 0xff next
size = 2
ftype = 0
while not 0xc0 <= ftype <= 0xcf:
fhandle.seek(size, 1)
byte = fhandle.read(1)
while ord(byte) == 0xff:
byte = fhandle.read(1)
ftype = ord(byte)
size = struct.unpack('>H', fhandle.read(2))[0] - 2
# We are at a SOFn block
fhandle.seek(1, 1) # Skip `precision' byte.
height, width = struct.unpack('&gt;HH', fhandle.read(4))
except Exception: #IGNORE:W0703
return
else:
return
return width, height

def returnFilesLike(passedFolderName, passedFileExtension = ".jpg"):
result = ]
#print passedFolderName
for file in os.listdir(passedFolderName):
if file.endswith(passedFileExtension):
result.append(os.path.join(passedFolderName,file))
return result

def importListOfImageMaps(passedList, passedTargetFolder):
lst_texture2D = ]
data = unreal.AutomatedAssetImportData()
data.set_editor_property('destination_path', passedTargetFolder) # Unreal game folder.
data.set_editor_property('filenames', passedList)
lst_texture2D = unreal.AssetToolsHelpers.get_asset_tools().import_assets_automated(data)
return lst_texture2D

def createNewImageMapOpaqueMaterial(passedAssetPath, passedMaterialName, passedDiffuseTexture, passedNormalTexture, passedDiffuseColor, passedSpec, passedRough):
# Create a material.
assetTools = unreal.AssetToolsHelpers.get_asset_tools()
mf = unreal.MaterialFactoryNew()
mat_closure = assetTools.create_asset("M_%s" % passedMaterialName, passedAssetPath, unreal.Material, mf)
mat_closure.set_editor_property("blend_mode", unreal.BlendMode.BLEND_TRANSLUCENT) #BLEND_TRANSLUCENT, BLEND_OPAQUE, BLEND_MASKED

# Make a texture diffuse node.
if passedDiffuseTexture!=None:
# Add an image node.
ts_node_diffuse = unreal.MaterialEditingLibrary.create_material_expression(mat_closure,unreal.MaterialExpressionTextureSample,-384,-200)
ts_node_diffuse.texture = passedDiffuseTexture
unreal.MaterialEditingLibrary.connect_material_property(ts_node_diffuse, "RGB", unreal.MaterialProperty.MP_BASE_COLOR)
unreal.MaterialEditingLibrary.connect_material_property(ts_node_diffuse, "A", unreal.MaterialProperty.MP_OPACITY)
else:
# Add a color constant node.
ts_node_diffuse = unreal.MaterialEditingLibrary.create_material_expression(mat_closure,unreal.MaterialExpressionConstant3Vector,-384,-200)
value = unreal.LinearColor(float(passedDiffuseColor[0]),float(passedDiffuseColor[1]),float(passedDiffuseColor[2]),1.0)
ts_node_diffuse.set_editor_property("constant", value)
unreal.MaterialEditingLibrary.connect_material_property(ts_node_diffuse, "", unreal.MaterialProperty.MP_BASE_COLOR)

# Make a texture normal node.
if passedNormalTexture!=None:
ts_node_normal = unreal.MaterialEditingLibrary.create_material_expression(mat_closure,unreal.MaterialExpressionTextureSample,-384,200)
unreal.MaterialEditingLibrary.connect_material_property(ts_node_normal, "RGB", unreal.MaterialProperty.MP_NORMAL)
# Change this sampler color sample type to work with normal types.
ts_node_normal.sampler_type = unreal.MaterialSamplerType.SAMPLERTYPE_NORMAL
ts_node_normal.texture = passedNormalTexture

# Make a constant float node.
ts_node_roughness = unreal.MaterialEditingLibrary.create_material_expression(mat_closure,unreal.MaterialExpressionConstant,-125,150)
ts_node_roughness.set_editor_property('R', passedRough)
unreal.MaterialEditingLibrary.connect_material_property(ts_node_roughness, "", unreal.MaterialProperty.MP_ROUGHNESS)

# Make a constant float node.
ts_node_specular = unreal.MaterialEditingLibrary.create_material_expression(mat_closure,unreal.MaterialExpressionConstant,-125,50)
ts_node_specular.set_editor_property('R', passedSpec)
unreal.MaterialEditingLibrary.connect_material_property(ts_node_specular, "", unreal.MaterialProperty.MP_SPECULAR)

unreal.MaterialEditingLibrary.recompile_material(mat_closure)
return mat_closure

def imagesToPlanes (passedPath, passedType, passedMaterialPath, passedTexturePath):
lst_files = returnFilesLike(passedPath, passedType)
if len(lst_files):
as_cube = True

# Make a new sequence to stage new candidates.
local_path = os.path.dirname(passedMaterialPath)
print local_path
new_sequence = create_new_level_sequence(local_path, 'FolderToSequence')
print new_sequence

# Collect list of image files associated with this folder.
lst_textures = importListOfImageMaps(lst_files, texture_path) #should match the length of list_files.

for i,file in enumerate(lst_files):
depth = i * 25.0
thickness = 0.0005
w,h = get_image_size(file)

# Create a map file asset for each image in our list.
local_name = os.path.basename(file)
local_name_only = os.path.splitext(local_name)[0]
shader_name = returnValidUnrealMaterialName("%s" % local_name_only)
mesh_name = returnValidUnrealMaterialName("SM_iap_%s" % local_name_only)

# Defaults for new material.
reflection_weight = 0.1
reflection_roughness = 0.23
diffuse_color = [0.18,0.18,0.18]
temp_material = createNewImageMapOpaqueMaterial(passedMaterialPath, shader_name, lst_textures*, None, diffuse_color, reflection_weight, reflection_roughness)

# Make a static mesh plane.
ell = unreal.EditorLevelLibrary
eal = unreal.EditorAssetLibrary
mesh_actor = ell.spawn_actor_from_class(unreal.StaticMeshActor.static_class(), unreal.Vector(depth, 0, 100), unreal.Rotator(0, 0, 0))
mesh_actor.set_actor_label(mesh_name)
mesh_comp = mesh_actor.get_component_by_class(unreal.StaticMeshComponent.static_class())
if as_cube:
temp_mesh = eal.load_asset("StaticMesh'/Engine/BasicShapes/Cube.Cube'") # Assume asset is created at default scale of 1.0.
else:
temp_mesh = eal.load_asset("StaticMesh'/Engine/BasicShapes/Plane.Plane'") # Assume asset is created at default scale of 1.0.
mesh_comp.set_static_mesh(temp_mesh)
mesh_comp.set_editor_property("override_materials", [temp_material])
if w != -1:
# Guestimate from brief file header review.
mesh_comp.set_editor_property("relative_scale3d", unreal.Vector(thickness, w*0.001, h*0.001))
else:
# Default to 16:9.
mesh_comp.set_editor_property("relative_scale3d", unreal.Vector(thickness, 1.6, 0.9)) # Set the aspect ratio of image here

# Add this mesh to the sequencer.
add_actor_to_sequence(new_sequence, mesh_actor)
else:
print"This combination %s].%s] produces no results." % (passedPath, passedType)

# Program begins here.
asset_path = "/Game"
# Select which disk folder to scan.
n = 3
if n==1:
folder_path = r'F:\Keep\Maps\Bullet_Holes'
extension = ".png"
material_path = "%s/Bullet_Holes/Mats" % asset_path
texture_path = "%s/Bullet_Holes/Tex" % asset_path
if n==2:
folder_path = r'F:\Keep\Maps\fur'
extension = ".jpg"
material_path = "%s/Fur/Mats" % asset_path
texture_path = "%s/Fur/Tex" % asset_path
if n==3:
folder_path = r'F:\Keep\Maps\Artwork\heart'
extension = ".png"
material_path = "%s/Heart/Mats" % asset_path
texture_path = "%s/Heart/Tex" % asset_path
if n==4:
# Add your own path here and set n=4
pass

imagesToPlanes (folder_path,extension,material_path,texture_path)
print "Folder to Sequencer complete."