# Workflow

CTRL+SHIFT+P henceforth know as _menu_

Once environment is set up just open VSCode and the container will automatically be rebuilt. After rebuild do "CMake configure..." again in the menu, and then choose the correct compiler (3.2.0). Whenever you make changes you can just go into the menu and "CMake build" or something to that effect.

### Conflicts

If you have synced remotely on GitHub or made changes locally and you want to git pull/push you might have to 
```
git pull --rebase origin master
```

Afterwards make sure everything works allright.


# Setting up environment & other stuff

#### (1) Make sure WSL2 is installed
```
wsl --install
```
_AND_ install the extensions in VSCode:

- CMake
- CMake Tools
- C/C++
- C/C++ Extension Pack
- Dev Containers
- WSL
- WSL Remote Development
- Ayu (If you want a good looking theme)

I didn't list all I have, but these should suffice.

#### (2) Install a linux distro on your machine
Go to microsoft store and install Ubuntu 22.04

#### (3) Go to your git bash terminal and
```
wsl --list --verbose
wsl --set-default Ubuntu-22.04
// A success message should show
wsl --list --verbose
```
Confirm here that you have * next to Ubuntu to indicate it is the default


#### (4) Go to start and run Ubuntu 22.04
A terminal will show up that will prompt you to make a UNIX user. Enter your username and password.

#### (5) Now, finally, you can open VSCode and connect to WSL

#### (6) To get started you need to clone the git repository, this will save the repo into your linux distribution.

#### (7) Once you have cloned the repo you need to make a few alterations
See lecture/other about that. _BUT_ this is the important part, you need to configure git in your linux distro terminal, which you can run from start or the one available in your VSCode (called bash). In any case, once configured just close and open it again for changes to take effect. _NOW_ you are set up to start commiting and pushing to the remote repo. 
_ALSO_ Uncomment the windows portion of the .devcontainer.json file.
_IMPORTANT_ Never push settings.json

#### (8) _NOW_ you can press the "connect" button to the lower-left side of VSCode, and choose the option that shows up "Reopen in devcontainer".

#### (9) CTRL+SHIFT+P and choose CMake Configure, choose the GCC compiler 3.2.0

#### (10) Now that you have built the project
You can go into the "Run and Debug" CTRL+SHIFT+D and simply click the play button. The QEMU emulator will run now, and if you have made an OS it will run your OS.

## END-OF-YEAR DELIVERY
This is important, _ONLY_ changes under _YOUR_ build and src directories should be different from the source repo.

I have made changes to .gitignore, they will need to be reverted end-of-year before pull request.
