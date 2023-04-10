env: Environment = Environment(COMPILATIONDB_USE_ABSPATH=True, CCFLAGS="-Wall")

env.Tool("compilation_db")
env.CompilationDatabase()

# build konkyo framework
kyo = SConscript("submodules/konkyo/SConscript", exports="env", variant_dir="build")

game_env = env.Clone(CPPPATH=["submodules/konkyo/include", "include"])
game = game_env.Program(
    "game",
    Glob("src/*.cpp") + Glob("src/rpg/*.cpp"),
    LINKFLAGS=["--static"],
    LIBS=["kyo", "sfml-graphics", "sfml-window", "sfml-system"],
    LIBPATH="build",
)

Requires(game, kyo)
