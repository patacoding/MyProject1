import unreal


@unreal.uclass()
class PythonBridgeImplementation(unreal.PythonBridge):

    @unreal.ufunction(override=True)
    def function_implemented_in_python(self):
        unreal.log_warning("Wow! This is the BEST")