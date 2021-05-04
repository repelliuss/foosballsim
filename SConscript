import os

# Get default flags etc.
Import('env')

# Path to godot specific things
cpp_bindings_path = "godot-cpp/"
godot_headers_path = cpp_bindings_path + "godot-headers/"

# Create godot's cpp library path
cpp_library = "libgodot-cpp.linux"

# Add C++ flags
env.Append(CXXFLAGS=["-fPIC", "-std=c++17"])

# Configurations that depends on target type
if env["target"] in ("debug", "d"):
    cpp_library += ".debug"
    env["target_name"] += "-debug"
    env.Append(CXXFLAGS=["-g3", "-Og"])
else:
    cpp_library += ".release"
    env["target_name"] += "-release"
    env.Append(CXXFLAGS=["-O3"])

cpp_library += "." + str(env["bits"])

# Setup cpp bindings
env.Append(
    CPPPATH=[
        godot_headers_path,
        cpp_bindings_path + "include/",
        cpp_bindings_path + "include/core/",
        cpp_bindings_path + "include/gen/",
    ]
)
env.Append(LIBPATH=[cpp_bindings_path + "bin/"])
env.Append(LIBS=[cpp_library])

# Setup foosimulation

source_paths = []
sources = []
for root, _, filenames in os.walk("src"):
    source_paths.append(root)
    sources.extend(Glob(root + "/*.cpp"))

env.Append(CPPPATH=["include/", "include/core"] + source_paths)

print(env["target_path"])
print(env["target_name"])

library = env.SharedLibrary(
    target= "../../" + env["target_path"] + env["target_name"], source=sources
)

Default(library)
