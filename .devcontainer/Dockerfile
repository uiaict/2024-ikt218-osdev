

# Stage 1: Building Bochs
FROM ubuntu:22.04 as bochs-builder

# Update and install dependencies
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    libgtk2.0-dev \
    libncurses5-dev \
    libncursesw5-dev \
    libsdl2-dev

# Clone and build Bochs
RUN git clone https://github.com/bochs-emu/Bochs && cd Bochs/bochs && \
    ./configure --enable-smp \
                --enable-cpu-level=6 \
                --enable-all-optimizations \
                --enable-x86-64 \
                --enable-pci \
                --enable-vmx \
                --enable-debugger \
                --enable-disasm \
                --enable-debugger-gui \
                --enable-logging \
                --enable-fpu \
                --enable-3dnow \
                --enable-sb16=dummy \
                --enable-cdrom \
                --enable-x86-debugger \
                --enable-iodebug \
                --disable-plugins \
                --disable-docbook \
                --with-x \
                --with-x11 \
                --with-term \
                --with-sdl2 && \
    make


FROM ubuntu:22.04 as gcc-builder
ARG BINUTILS_VERSION=2.41
ARG GCC_VERSION=13.2.0

# Set the ARGs as environment variables and write them to a file
RUN echo "BINUTILS_VERSION=$BINUTILS_VERSION" > /version_env
RUN echo "GCC_VERSION=$GCC_VERSION" >> /version_env

COPY ./files/src /usr/local/src/
COPY ./files/gcc/t-x86_64-elf /usr/local/src/gcc-${GCC_VERSION}/gcc/config/i386/
COPY ./files/gcc/config.gcc.patch /usr/local/src/gcc-${GCC_VERSION}/gcc/

# Install cross-compiler prerequisites and remove them in the same RUN command to keep the layer size small
RUN set -x \
    && apt-get update \
    && apt-get install -y \
    wget \
    gcc \
    libgmp3-dev \
    libmpfr-dev \
    libisl-dev \
    libmpc-dev \
    texinfo bison \
    flex \
    make \
    bzip2 \
    patch \
    build-essential \
    && mkdir -p /usr/local/src \
    && mkdir -p /usr/local/gcc-install \
    && cd /usr/local/src \
    && wget -q https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.gz \
    && wget -q https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.gz \
    && tar zxf binutils-${BINUTILS_VERSION}.tar.gz \
    && tar zxf gcc-${GCC_VERSION}.tar.gz \
    && rm binutils-${BINUTILS_VERSION}.tar.gz gcc-${GCC_VERSION}.tar.gz \
    && chown -R root:root binutils-${BINUTILS_VERSION} \
    && chown -R root:root gcc-${GCC_VERSION} \
    && chmod -R o-w,g+w binutils-${BINUTILS_VERSION} \
    && chmod -R o-w,g+w gcc-${GCC_VERSION} \
    && cd /usr/local/src \
    && bash build-binutils.sh ${BINUTILS_VERSION} /usr/local \
    && bash build-gcc.sh ${GCC_VERSION} /usr/local \
    # Now remove the build dependencies
    && apt-get purge -y --auto-remove \
    wget \
    gcc \
    texinfo bison \
    flex \
    make \
    bzip2 \
    patch \
    libisl-dev \
    libmpc-dev \
    build-essential \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*



FROM ubuntu:22.04 as devcontainer
RUN apt-get update && apt-get install -y \
    libgtk2.0-0 \
    libncurses5 \
    libsdl2-2.0-0 \
    git \
    sudo \
    make \ 
    cmake \
    nasm \
    ninja-build \
    xorriso \
    qemu \
    qemu-kvm \
    qemu-system-x86 \
    qemu \
    gdb-multiarch \
    tmux \
    dosfstools \
    libisl-dev \
    libmpc-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy GCC installation from the first stage
COPY --from=gcc-builder /usr/local/src /usr/local/src
RUN cd /usr/local/src/build-binutils && make install && cd /usr/local/src/build-gcc && make install-gcc && make install-target-libgcc


# Copy Bochs binaries from the builder stage
COPY --from=bochs-builder /Bochs/bochs/bochs /usr/local/bin/
COPY --from=bochs-builder /Bochs/bochs/bximage /usr/local/bin/
COPY --from=bochs-builder /Bochs/bochs/bios/BIOS-bochs-latest /usr/local/share/bochs/BIOS-bochs-latest
COPY --from=bochs-builder /Bochs/bochs/bios/VGABIOS-lgpl-latest /usr/local/share/bochs/VGABIOS-lgpl-latest

# Download the latest Limine binary release.
RUN  cd /usr/local && git clone https://github.com/limine-bootloader/limine.git --branch=v6.x-branch-binary --depth=1 && make -C limine



RUN groupadd -g 61000 osdev; \
    useradd -g 61000 -l -m -s /bin/bash -u 61000 osdev; \
    mkdir -p /home/osdev/supervisor; \
    touch /home/osdev/.Xauthority; \
    chown -R osdev:osdev /home/osdev;\
    chmod -R 777 /home/osdev ;\
    adduser osdev sudo;\
    echo 'osdev:osdev' | chpasswd;\
    echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers;

RUN apt-get remove -y gcc && apt-get autoremove -y && apt-get clean && rm -rf /var/lib/apt/lists/*

# Set default command to launch Supervisor
COPY ./files/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh && chown osdev:osdev /usr/local/bin/entrypoint.sh

# LIBGL_ALWAYS_INDIRECT=1
ENV LIBGL_ALWAYS_INDIRECT=1


USER osdev
WORKDIR /home/osdev

ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]




# Create GUI
FROM devcontainer as devcontainer-webgui

USER root

ENV DISPLAY=:1 \
    VNC_PORT=5901 \
    NO_VNC_PORT=6901 \
    VNC_COL_DEPTH=32 \
    VNC_RESOLUTION=1920x1080 \
    TERM=xterm \
    DEBIAN_FRONTEND=noninteractive \
    NOVNC_VERSION="v1.4.0" \
    WEBSOCKIFY_VERSION="v0.11.0"

RUN apt-get update && apt-get install -y \
    supervisor \
    xvfb  \
    xauth \
    dbus-x11 \
    xfce4 \
    xfce4-terminal \
    x11-xserver-utils \
    x11-utils \
    tigervnc-standalone-server  \
    tigervnc-common \
    python3-numpy \
    && rm -rf /var/lib/apt/lists/*



# Install NOVNC.
RUN git clone --branch ${NOVNC_VERSION} --single-branch https://github.com/novnc/noVNC.git /opt/noVNC; \
    git clone --branch ${WEBSOCKIFY_VERSION} --single-branch https://github.com/novnc/websockify.git /opt/noVNC/utils/websockify; \
    ls -la /opt/noVNC; \
    ln -s /opt/noVNC/vnc.html /opt/noVNC/index.html


# Supervisor configuration files
COPY ./files/supervisor/supervisord.conf /etc/supervisor/conf.d/supervisord.conf
COPY ./files/supervisor/novnc.conf /etc/supervisor/conf.d/novnc.conf
COPY ./files/supervisor/vncserver.conf /etc/supervisor/conf.d/vncserver.conf
# Expose VNC and noVNC ports
EXPOSE ${VNC_PORT} ${NO_VNC_PORT}

USER osdev







