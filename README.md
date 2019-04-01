# simple-voxels
A simple voxel engine.

## Dependencies
This project uses git submodules to manage dependencies. Run the following commands after cloning to download them.
```
git submodule init
git submodule update --recursive
```

The following dependencies are used:
- [Catch2](https://github.com/catchorg/Catch2) for testing.
- [SDL2](https://github.com/spurious/SDL-mirror) for the game executable.

### SDL2
SDL2 is currently being built from source. Make sure you have the required dependencies. To read about them you can go
[here](http://wiki.libsdl.org/Installation). ([Windows](http://wiki.libsdl.org/Installation#Windows_XP.2FVista.2F7),
[Linux](http://wiki.libsdl.org/Installation#Linux.2FUnix), [Mac OS](http://wiki.libsdl.org/Installation#Mac_OS_X).)

## Building
```
mkdir build
cd build
cmake .. -DBUILD_TESTS=ON
cmake --build .
```

