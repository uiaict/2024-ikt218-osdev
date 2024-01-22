# IKT218 - Operating System Development Course Repository

Welcome to the University of Agder's IKT218 course repository. This platform is crucial for students involved in our Operating System Development lab assignments. At the semester's end, students will add their operating system projects to this repository, creating a diverse showcase of their work.

**Are your project out of sync with this repository?:**
You will see something like this in your fork:` This branch is xxx commits behind uiaict/2024-ikt218-osdev:master.`. If this is the case you can click this message and perform a pull-request from `uiaict/2024-ikt218-osdev:master` to your repository to get the latest changes. You should never have a merge conflict, if you do, you have not followed the structure described below.

## Repository Contents
This package is designed to support OS development and includes:
- Standard directory structure for source and build files
- i386 linker script
- Configuration for the Limine bootloader using Multiboot2

## Getting Started
Follow these steps for to setup your environment for the lab assignment:
The first thing you need to do is to g into `devcontainer.json` and uncomment the section that belongs to your machine. We have tested Arch Linux on X11, Windows 11 with WSL2, and MacOS M1 (Arm).

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

4. **Install Pulseaudio:**
   - install pulseaudio by executing this command in the terminal:
   ```
   brew install pulseaudio
   ```
   - after installation you should run
   ```
   brew services start pulseaudio
   pactl load-module module-native-protocol-tcp auth-anonymous=1
   lsof -i -P | grep -i "listen"
   ```
   - ensure that the output of lsof contains a line binding to port 4713 like so `TCP *:4713 (LISTEN)`

5. **Install XQuartz:**
   - XQuartz is in charge of forwarding display from Mac to Docker container
   ```
   brew install --cask xquartz
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

1. **Copy the directory**: The first step is to copy `group_name` folder and rename the newly copied folder to `<group_id>_<group_name>`. If you are running the project without a group, use the `solo` prefix like `solo_<group_name>`. After this change, the file structure of your `src` and `build` folder should look like this:
   ```
   src/group_name
   src/<group_id>_<group_name>
   build/group_name
   build/<group_id>_<group_name>
   ```

3. **Update VS Code Settings**:
   Edit `.vscode/settings.json` to match your new group name:
   ```json
   "cmake.buildDirectory": "${workspaceFolder}/build/<your_group_name>",
   "cmake.sourceDirectory": "${workspaceFolder}/src/<your_group_name>",
   ```
   **Note**: Do not push changes to anything but the `build/<your_group_name>` or `src/<your_group_name>` directories to avoid conflicts.

4. **Set Up Your Development Environment**:
   Prepare your environment as instructed in the lectures (Devcontainer). These are tested on Windows, Linux, and MacOS (arm64). Customized setups are allowed, but receive limited support.

5. **Maintain Professional Coding Standards**:
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
