import sys
import scons_compiledb

# Remove this check for yourself if you are on Linux and still
# get exception.
if not sys.platform.startswith("linux"):
    raise ValueError("You are not on a Linux system. If you are, see 'SConstruct'.")

# Get default flags etc.
env = DefaultEnvironment()

# Add compilation database support
scons_compiledb.enable_with_cmdline(env)

# To add to variables from command line
opts = Variables(None, ARGUMENTS)

is64 = sys.maxsize > 2 ** 32

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

if env["target"] in ("debug", "d"):
    SConscript(
        "SConscript", variant_dir="build/debug", exports={"env": env}, duplicate=0
    )
else:
    SConscript(
        "SConscript", variant_dir="build/release", exports={"env": env}, duplicate=0
    )
