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

## Building
```
mkdir build
cd build
cmake .. -DBUILD_TESTS=ON
cmake --build .
```

