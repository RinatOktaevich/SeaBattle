## C++ compiler via MSYS2

MSYS2 is a collection of tools and libraries providing you with an easy-to-use environment for building, installing and running native Windows software.

Install to get c++ compiler [MSYS2](https://www.msys2.org).

Then run `pacman -S mingw-w64-x86_64-gcc`

Verify installation `g++ --version`

## Environment Variables
System variables → Path → Edit add `C:\mingw64\bin` or whatever your `mingw64\bin` folder is contained.

## To build project run

```
g++ Main.cpp Print.cpp -o seaBattle.exe -Wwrite-strings -static -static-libgcc -static-libstdc++
```
Flags `-static -static-libgcc -static-libstdc++` allow .exe to include all libraries it reqiure, so it can run on other machines.

To install compiler run `pacman -S mingw-w64-x86_64-gcc`.


## Setup build task (so you don’t type commands every time)
In VS Code:

* Press Ctrl + Shift + P
* Type: Tasks: Configure Task
* Choose: Create tasks.json from template
* Select: Others

Replace content with:
```
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build cpp",
      "type": "shell",
      "command": "g++",
      "args": [
        "-g",
        "main.cpp",
        "-o",
        "main.exe"
      ],
      "group": {
        "kind": "build",
        "isDefault": true
      }
    }
  ]
}
```

## Debugging setup (Optional) 
Install debugger (already included with MinGW usually), then:

* Go to Run → Add Configuration
* Choose C++ (GDB/LLDB)

VS Code will generate `launch.json`