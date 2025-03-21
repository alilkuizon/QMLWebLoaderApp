#!/bin/bash

# Configuration variables
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"  # Script directory (docker folder)
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"                      # Parent directory of docker folder
PRO_FILE_DIR="$PROJECT_DIR"                                 # Directory containing the .pro file
PRO_FILE="QMLWebLoaderApp.pro"                                      # Name of the .pro file (change as needed)
OUTPUT_DIR="$PROJECT_DIR/binaries"                          # Output directory for binaries
CONTAINER_DIR="/project"                                    # Directory inside container
DOCKER_IMAGE="qt6.6.3-ubuntu22"                                   # Your pre-built Qt6 image name
BINARY_NAME="${PRO_FILE%.pro}" 

# Install Docker Engine on Ubuntu
echo "Installing Docker Engine..."

# Update the apt package index and install packages to allow apt to use a repository over HTTPS
sudo apt-get update
sudo apt-get install -y \
    ca-certificates \
    curl \
    gnupg

# Add Docker’s official GPG key
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg

# Set up the repository
echo \
  "deb [arch=\"$(dpkg --print-architecture)\" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo \"$VERSION_CODENAME\") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

# Update the apt package index again
sudo apt-get update

# Install Docker packages
sudo apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

# Verify that Docker Engine is installed correctly
sudo docker run hello-world

# Check if the Docker image exists locally
if [[ "$(sudo docker images -q "$DOCKER_IMAGE" 2> /dev/null)" == "" ]]; then
    echo "Docker image '$DOCKER_IMAGE' not found locally. Building from Dockerfile..."

    # Check if Dockerfile exists in the script directory
    if [[ -f "$SCRIPT_DIR/Dockerfile" ]]; then
        sudo docker build -t "$DOCKER_IMAGE" "$SCRIPT_DIR"
        echo "Docker image '$DOCKER_IMAGE' built successfully."
    else
        echo "Dockerfile not found in '$SCRIPT_DIR'. Cannot build Docker image."
        exit 1
    fi
else
    echo "Docker image '$DOCKER_IMAGE' found locally."
fi
# Create output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"

echo "Starting Qt6 build process in Docker container..."
echo "Project directory: $PROJECT_DIR"
echo "Pro file location: $PRO_FILE_DIR/$PRO_FILE"
echo "Output directory: $OUTPUT_DIR"

# Run Docker container with Qt6
sudo docker run --rm -it \
    -v "$PROJECT_DIR:$CONTAINER_DIR" \
    --workdir "$CONTAINER_DIR" \
    "$DOCKER_IMAGE" \
    /bin/bash -c "
        # Create build directory inside container
        mkdir -p build && \
        cd build && \
        
        # Run qmake on the .pro file
        qmake6 ../$PRO_FILE && \
        
        # Run make
        make -j\$(nproc) && \
        
        # Copy the gcc_64 folder from the Qt installation to the output directory
        cp -r /opt/6.6.3/gcc_64 $CONTAINER_DIR/binaries/ && \
        
        # Fix permissions (make all files readable/writable)
        chmod -R a+rwX $CONTAINER_DIR/build $CONTAINER_DIR/binaries && \
        
        echo \"Build completed. Binary copied to binaries/\$BINARY_NAME\"
    "

echo "Process completed."

# Install necessary system packages
sudo apt-get update
sudo apt-get install -y \
    ca-certificates \
    curl \
    gnupg \
    libxkbcommon-x11-0 \
    libxcb-cursor0\
    libxcb-shape0 \
    libxcb-icccm4

# Check if the binary exists
if [ -f "$OUTPUT_DIR/$BINARY_NAME" ]; then
    echo "Starting $BINARY_NAME in the background..."
    cd "$OUTPUT_DIR" || exit 1
    nohup "./$BINARY_NAME" > /dev/null 2>&1 &
    echo "$BINARY_NAME has been started."
else
    echo "Cannot start $BINARY_NAME: Binary not found in $OUTPUT_DIR"
fi

# Exit the script
exit 0