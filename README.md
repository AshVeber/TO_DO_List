# TO_DO_LIST
To Do List is a C++ full independent, backend open source project for organization your tasks that attracts with its own readable code, simplicity, low weight and automation.

It provides the modern features for controling your work and functions making your life easier than it was before. This is the huge but simple system that contains fresh file methods.

## Thank you for choosing me! 

# WELCOME TO TO-DO LIST
ATM focuses on the convenience andhigh functionality of its products. While other ATMs offer only dull, utilitarian features, I invite you to step into the shoes of an IT specialist and run my project via the terminal. The task may seem simple but that's only on paper!
So, why us? Good question!
## ATM IS ABOUT:
- simplicity (some 253 code lines)
- cross-platform capability (Windows, Linux, Android, whatever.)
- open source


# QUICK START

## LINUX
*Required dependencies: git, g++ compiler, CMake*

### Step 1:
Open the terminal and run those commands.

*Install Cmake*

Arch Linux:
```
# Bash
sudo pacman -S cmake
sudo yay -S cmake
```
Ubuntu-based/Debian:
```
# Bash
sudo apt install cmake
```
*Install g++ compiler*

Arch Linux:
```
# Bash
sudo pacman -S g++
sudo yay -S g++
```
Ubuntu-based/Debian:
```
# Bash
sudo apt-get install g++
```
*Install git*

Arch Linux:
```
# Bash
sudo pacman -S git
sudo yay -S git
```
Ubuntu-based/Debian:
```
# Bash
sudo apt install git
```
### Step 2:

Clone the repository.
```
# Bash
git clone REPOSITORY
```

### step 3:

Find the path to the repository.
```
# Bash
find -name "ATM"
```
Write this commands
```
# Bash
cd <YOUR_PATH_TO_ATM>
mkdir build && cd build
cmake ..
make
./ATM
```
*ENJOY!*


## WINDOWS (not tested)
*Required dependencies: git, VScode, CMake*

### Step 1:

*Install git*
> https://git-scm.com/install/windows

*Install VScode*
> https://code.visualstudio.com/download?_exp_download=fb315fc982

*Install CMake*
>https://cmake.org/download/

### Step 2:
- Run the VScode.
- Download "CMake Tools" and "C/C++ Extension Pack" from Extensions (CTRL+SHIFT+X)
- Create folder.
- Create ".vscode" folder in previous folder.
- Open VScode and create "tasks.json" in ".vscode" and write this:
```
  {
    "version":"2.0.0",
    "tasks": [
        {
            "label":"Build and Run C++",
            "type":"shell",
            "command":"g++",
            "args": ["${file}", "-o", "${fileDirname}\\${fileBasenameNoExtension}.exe", "&&", "${fileDirname}\\${fileBasenameNoExtension}.exe"],
            "problemMatcher":["$gcc"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```
### Step 3:
Clone the repository using git
```
# Bash
git clone <REPOSITORY>
```
Write this commands
```
# Bash
cd <YOUR_PATH_TO_ATM>
mkdir build
cd build
cmake ..
cmake --build .
```
*ENJOY!*

## MacOs (not tested)
*Required dependencies: compiler, CMake*

### Step 1:

*Install compiler*
```
# Bash
xcode-select --install
```

*Install CMake*
(Install Homebrew before)
```
# Bash
brew install cmake
```
### Step 2:
Follow this commands:
```
# Bash
git clone <REPOSITORY>
cd ATM
mkdir build
cd build
cmake ..
make
./ATM
```
*ENJOY!*

# ABOUT OWNER
## *Ash Veber*
The young prorammer with huge potential! Ash interests ML engineering, devops, backend, frontend and ...BLENDER!

### Veber's contacts
Telegram: @Tolfee

email: ashveber42@gmail.com
