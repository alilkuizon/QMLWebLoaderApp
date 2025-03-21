
# QML Web Loader
This application loads qml files served in webservers. 

**Build Process only supports Native Linux(Ubuntu) and Linux Subsytem Windows (Ubuntu).**
Developed and tested in Ubuntu 24.04. 

A local host webserver can be run using the Simple Web Server repo found here:
https://github.com/alilkuizon/SimpleWebServer

## Quick Setup Instruction
The quick setup method uses run_all.sh runs both a webserver (Repo stated above) and the client(this repo QML Web Loader App). 
All dependencies are generated in a folder called applicationFolder. 
1. **Add execute permissions to the run_all.sh script**

   ```bash
   chmod +x run_all.sh
2. **Run the script (Use sudo for proper access)**
   
   ```bash
   sudo ./run_all.sh
3. **Wait for setup to finish and it will automatically run the QML Loader Application**
4. **Binaries are available in /applicationFolder/QMLWebLoaderApp/binaries**

   NOTE: TO ENSURE RELIABILITY OF DEPENDENCIES ALWAYS RUN THE APP THROUGH THE run_all.sh script


## Manual Setup Instructions (Only use when Quick Setup doesn't work)

1. **Initialize a webserver first. Follow the SimpleWebServer Repo Instructions**
2. **When running the webserver take note of the port number printed on the command line**:

   ```bash
   Example: Server is running on port 13117

3. **In this repository edit server_port.txt and put the port number from step 2**
4. **Go to the docker folder and add execute permissions to build.sh**
    
    ```bash
   chmod +x build.sh
5. **Execute build.sh and it will build and run the application**

    ```bash
   ./build.sh
6. **The executable application is also located in the binaries Folder created after running build.sh**
7. **(Optional) Execute with sudo if there are permission errors**
