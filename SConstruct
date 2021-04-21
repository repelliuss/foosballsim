import sys

# Remove this check for yourself if you are on Linux and still
# get exception.
if not sys.platform.startswith("linux"):
    raise ValueError("You are not on a Linux system. If you are, see 'SConstruct'.")

# Get default flags etc.
env = DefaultEnvironment()

# To add to variables from command line
opts = Variables(None, ARGUMENTS)

is64 = sys.maxsize > 2 ** 32

# Add cli options
opts.Add(
    EnumVariable(
        "target", "Compilation target.", "debug", ["d", "debug", "r", "release"]
    )
)
opts.Add(
    EnumVariable("bits", "Target platform bits.", "64" if is64 else "32", ["32", "64"])
)
opts.Add(
    PathVariable(
        "target_path",
        "The path where lib is installed.",
        "foosim/bin/x11/",
        PathVariable.PathExists,
    )
)
opts.Add(
    PathVariable(
        "target_name", "The library name.", "libgdfoosim", PathVariable.PathAccept
    )
)

# Update env with our variables
opts.Update(env)

# Add their help texts to '-h|--help' options
Help(opts.GenerateHelpText(env))

# Path to godot specific things
cpp_bindings_path = "godot-cpp/"
godot_headers_path = cpp_bindings_path + "godot-headers/"

# Create godot's cpp library path
cpp_library = "libgodot-cpp.linux"

# Add C++ flags
env.Append(CXXFLAGS=["-fPIC", "-std=c++17"])

# Configurations that depends on target type
variant_dir = "build/"
if env["target"] in ("debug", "d"):
    cpp_library += ".debug"
    variant_dir += "debug/"
    env["target_name"] += "-debug"
    env.Append(CXXFLAGS=["-g3", "-Og"])
else:
    cpp_library += ".release"
    variant_dir += "release/"
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
env.Append(CPPPATH=["include/", "src/"])
env.VariantDir(variant_dir, "src/", duplicate=0)
sources = Glob(variant_dir + "*.cpp")

library = env.SharedLibrary(
    target=env["target_path"] + env["target_name"], source=sources
)

Default(library)
