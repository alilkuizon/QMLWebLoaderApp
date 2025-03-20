#!/bin/bash

# Configuration variables
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"  # Script directory (docker folder)
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"                      # Parent directory of docker folder
PRO_FILE_DIR="$PROJECT_DIR"                                 # Directory containing the .pro file
PRO_FILE="QMLWebLoaderApp.pro"                                      # Name of the .pro file (change as needed)
OUTPUT_DIR="$PROJECT_DIR/binaries"                          # Output directory for binaries
CONTAINER_DIR="/project"                                    # Directory inside container
DOCKER_IMAGE="qt682-ubuntu22"                                   # Your pre-built Qt6 image name
BINARY_NAME="${PRO_FILE%.pro}" 

# Check if Docker is installed
if ! command -v docker &> /dev/null; then
    echo "Docker is not installed. Please install Docker first."
    exit 1
fi

# Create output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"

echo "Starting Qt6 build process in Docker container..."
echo "Project directory: $PROJECT_DIR"
echo "Pro file location: $PRO_FILE_DIR/$PRO_FILE"
echo "Output directory: $OUTPUT_DIR"

# Run Docker container with Qt6
docker run --rm -it \
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
        
        echo \"Build completed. Binary copied to binaries/\$BINARY_NAME\"
    "

echo "Process completed."

# Run the binary in the background
if [ -f "$OUTPUT_DIR/$BINARY_NAME" ]; then
    echo "Starting $BINARY_NAME in the background..."
    cd "$OUTPUT_DIR" && ./$BINARY_NAME &
    BINARY_PID=$!
    echo "$BINARY_NAME started with PID: $BINARY_PID"
    
    # Optional: Write the PID to a file for later use (stopping the process)
    echo $BINARY_PID > "$OUTPUT_DIR/.${BINARY_NAME}.pid"
    echo "PID saved to $OUTPUT_DIR/.${BINARY_NAME}.pid"
else
    echo "Cannot start $BINARY_NAME: Binary not found in $OUTPUT_DIR"
fi
