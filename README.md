# IKT218 - Operating System Development Course Repository

Welcome to the University of Agder's IKT218 course repository. This platform is crucial for students involved in our Operating System Development lab assignments. At the semester's end, students will add their operating system projects to this repository, creating a diverse showcase of their work.

## Repository Contents
This package is designed to support OS development and includes:
- Standard directory structure for source and build files
- i386 linker script
- Configuration for the Limine bootloader using Multiboot2

## Getting Started
Follow these steps for to setup your environment for the lab assignment:

### MacOS Installation Steps

1. **Install Homebrew:**
   - Follow the instructions on the [Homebrew official site](https://brew.sh) to install Homebrew.

2. **Install Visual Studio Code:**
   - Run the following command in the terminal:
     ```bash
     brew install --cask visual-studio-code
     ```

3. **Install Docker:**
   - Install Docker by executing this command in the terminal:
     ```bash
     brew install --cask docker
     ```

### Windows Installation Steps

1. **Install Windows Subsystem for Linux (WSL2):**
   - Ensure you have the latest version of Windows.
   - Follow the installation instructions on the [official guide for WSL2](https://docs.microsoft.com/en-us/windows/wsl/install).

2. **Install Docker:**
   - Download and install Docker for Windows from the [Docker official website](https://www.docker.com/products/docker-desktop).

3. **Install Visual Studio Code:**
   - Download and install Visual Studio Code from the [Visual Studio Code official website](https://code.visualstudio.com/).

### Linux Installation Steps

1. **Install Docker:**
   - Depending on your Linux distribution, follow the Docker installation guide on the [Docker official website](https://docs.docker.com/engine/install/).

2. **Install Visual Studio Code:**
   - Download and install Visual Studio Code from the [Visual Studio Code official website](https://code.visualstudio.com/).

### General Setup for All Operating Systems

1. **Fork the Repository:**
   - Fork this repository
   - Click the 'Fork' button at the top right to create a copy in your account.

2. **Clone the Forked Repository:**
   - Open your terminal or command prompt.
   - Clone the repository using:
     ```bash
     git clone [URL of your forked repository]
     ```
   - Replace `[URL of your forked repository]` with the actual URL.

### Configure your repository

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
