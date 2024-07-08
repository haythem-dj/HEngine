# HEngine
## What is HEngine
This is a framework that let do some graphics pritty easily.
Now it can run on windows only, but it will support other platforms in the futur.

## Building
To generate build files, you need premake5 to be installed on your computer.

### Generate vs2022 solution

```bash
git clone https://github.com/haythem-dj/HEngine
cd HEngine
premake5 vs2022
```

### Build with make

```bash
git clone https://github.com/haythem-dj/HEngine
cd HEngine
premake5 gmake
make config=release
```
