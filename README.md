# HEngine
## What is HEngine
This is a framework that let do some graphics pritty easily.
Now it can run on windows only, but it will support other platforms in the futur.

## Building
Those are the commands to build the framework with the test.

- Building the framework itself.
```bash
g++ -DUNICODE -c HEngine/src/*.cpp -I HEngine/include -L HEngine/lib -lgdi32
```
- Moving object files into the **_bin_**  directory.
```bash
move *.o HEngine/bin
```
- Making a static library in the **_lib_** folder.
```bash
ar rvs HEngine/lib/libHEngine.a HEngine/bin/*.o
```
- Finally build the test including the library.
> This does needs the **_gdi32_** windows library to build successfully.
```bash
g++ --std=c++17 -DUNICODE Test/src/*.cpp -I HEngine/include -I Test/include -L HEngine/lib -lHEngine -lgdi32 -o Test/main
```
- Finally you can run the application.
```bash
start Test/main.exe
```