FROM ubuntu:22.04

# Avoid interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install Qt 6.8.2 dependencies and development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    gcc \
    g++ \
    git \
    wget \
    python3 \
    python3-pip \
    pkg-config \
    libgl1-mesa-dev \
    libxkbcommon-x11-dev \
    libxcb-*-dev \
    libx11-xcb-dev \
    libxcb1-dev \
    libxcursor-dev \
    libxrender-dev \
    libfontconfig1-dev \
    libdbus-1-dev \
    libssl-dev \
    libudev-dev \
    libxext-dev \
    libxfixes-dev \
    libxi-dev \
    libxrandr-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set up directory for Qt
WORKDIR /opt

RUN pip3 install aqtinstall && \
    python3 -m aqt list-qt linux desktop --arch 6.6.3

# Install Qt using aqtinstall - fixed command syntax
RUN pip3 install aqtinstall && \
    python3 -m aqt install-qt linux desktop 6.6.3 gcc_64 --outputdir /opt

# Set environment variables for Qt
ENV PATH="/opt/6.6.3/gcc_64/bin:${PATH}"
ENV LD_LIBRARY_PATH="/opt/6.6.3/gcc_64/lib:${LD_LIBRARY_PATH}"
ENV QT_PLUGIN_PATH="/opt/6.6.3/gcc_64/plugins"
ENV QML2_IMPORT_PATH="/opt/6.6.3/gcc_64/qml"

# Set up a working directory for your project
WORKDIR /project

# Create a script to build projects
RUN echo '#!/bin/bash' > /usr/local/bin/build-qt-project && \
    echo 'mkdir -p build && cd build' >> /usr/local/bin/build-qt-project && \
    echo 'cmake .. -GNinja -DCMAKE_PREFIX_PATH=/opt/6.6.2/gcc_64' >> /usr/local/bin/build-qt-project && \
    echo 'ninja' >> /usr/local/bin/build-qt-project && \
    chmod +x /usr/local/bin/build-qt-project

# Volume for sharing code
VOLUME ["/project"]

# Default command
CMD ["/bin/bash"]