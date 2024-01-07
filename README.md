f# IKT218 - Operating System Development Course Repository

Welcome to the University of Agder's IKT218 course repository. This platform is crucial for students involved in our Operating System Development lab assignments. At the semester's end, students will add their operating system projects to this repository, creating a diverse showcase of their work.

## Repository Contents
This package is designed to support OS development and includes:
- Standard directory structure for source and build files
- i386 linker script
- Configuration for the Limine bootloader using Multiboot2

## Getting Started
Follow these steps for your lab assignment:

1. **Rename the Directory**: Change `group_name` to a name that reflects your project or group. Apply this change to both the source and build directories.

2. **Update VS Code Settings**:
   Edit `.vscode/settings.json` to match your new group name:
   ```json
   "cmake.buildDirectory": "${workspaceFolder}/build/<your_group_name>",
   "cmake.sourceDirectory": "${workspaceFolder}/src/<your_group_name>",
   ```
   **Note**: Do not push changes to anything but the `build/<your_group_name>` or `src/<your_group_name>` directories to avoid conflicts.

3. **Set Up Your Development Environment**:
   Prepare your environment as instructed in the lectures (Devcontainer). These are tested on Windows, Linux, and MacOS (arm64). Customized setups are allowed, but receive limited support.

4. **Maintain Professional Coding Standards**:
   Use appropriate variable names and comments. Unprofessional practices will negatively affect your grade.

## Project Submission
Your submission should include:
- A working operating system
- The source code
- A final report in PDF format

Arrange your project like this:
```
.vscode/
.devcontainer/
.github/
.gitignore
build/<your_group_name>/
src/<your_group_name>/
```

## Showcase
Your projects will be displayed at the end of the semester on [UIA ICT OS Dev Showcase](https://uiaict.github.io/2024-ikt218-osdev/).

## Additional Information
Refer to your lecture materials and use the course forum for any questions.
