# IKT218 - Operating System Developer Repository

## Description
This repository holds the code needed for students to partake in the lab assignments in IKT218 at the University of Agder, Norway. At the end of the semester, each student will make a pull request to this repository, which should end up with a collection of operating systems, later to be hosted at [https://uiaict.github.io/ikt218-osdev/](https://uiaict.github.io/ikt218-osdev/)

This repository, along with the `group_name`directory is a starter pack for getting started with OSDevelopment. It provides a basic directory structure, a i386 linker script, and GRUB2 configuration.

## Starting your lab assignment
1. Rename `group_name` to an **approriate** name.
2. Go into `.vscode/settings.json` and set the same group name as in step 1 
```json
    "cmake.buildDirectory": "${workspaceFolder}/build_group_name", <-- Change
    "cmake.sourceDirectory": "${workspaceFolder}/group_name", <-- Change
```
Note: **DO NOT** push any changes to `.vscode` or `web`. Else we will have a hassle with pull request at the end...

3. Set up your development environment according to guides supplied in lecture. If you choose to run customized environment setups, that is completely fine, but you will get no support :D
4. **DO NOT** shit around with inapproriate variable names or comments. As it is expected that the candidates hold the capability of basic understanding of social norms, failing to present code that adhere to these will set your grade back substantially. Please, just be civil :D

## At delivery
1. You should have a fully functional operating system, including source code, and a final report in `pdf` format. The structure of your final project repository should be:
```
.vscode
build_group_name
group_name
web
```