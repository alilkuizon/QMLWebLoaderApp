#!/bin/bash

# Exit on error
set -e

echo "Starting repository setup process..."

# Check if applicationFile directory already exists
if [ -d "applicationFile" ]; then
    echo "Found existing applicationFile directory. Deleting it..."
    rm -rf applicationFile
    echo "Old directory removed."
fi

# Create a fresh applicationFile directory
echo "Creating applicationFile directory..."
mkdir -p applicationFile
cd applicationFile

# Clone the repositories
echo "Cloning repositories..."
git clone https://github.com/alilkuizon/SimpleWebServer.git
git clone https://github.com/alilkuizon/QMLWebLoaderApp.git
# Setup server
echo "Setting up server..."
cd SimpleWebServer

# Add execute permission to setup.sh
chmod +x setup.sh

# Run the setup script
echo "Running server setup script..."
./setup.sh

# Activate the virtual environment
echo "Activating Python virtual environment..."
source venv/bin/activate

# Run the server in the background
echo "Starting server in background..."
python server.py &
SERVER_PID=$!

# Wait for the server to generate the port file
echo "Waiting for server to initialize and generate port file..."
while [ ! -f "../server_port.txt" ]; do
  sleep 1
  echo "Waiting for server_port.txt to be created..."
done

# Copy the server_port.txt file to the client directory
echo "Copying server_port.txt to client directory..."
cp ../server_port.txt ../QMLWebLoaderApp/

# Go back to the root directory
cd ..

# Go to the client directory
echo "Setting up client..."
cd QMLWebLoaderApp

# Go to the docker directory
cd docker

# Add executable permission to build.sh
chmod +x build.sh

# Run the build script
echo "Running client build script..."
./build.sh

echo "Setup completed successfully!"
echo "Server is running in the background with PID: $SERVER_PID"
