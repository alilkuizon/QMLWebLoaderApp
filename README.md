
# QML Web Loader
This application loads qml files served in webservers. 

**Build Process only supports Native Linux(Ubuntu) and Linux Subsytem Windows (Ubuntu).**
Developed and tested in Ubuntu 24.04. 

A local host webserver can be run using the Simple Web Server repo found here:
https://github.com/alilkuizon/SimpleWebServer

## Quick Setup Instruction
The quick setup method uses run_all.sh runs both a webserver (Repo stated above) and the client(this repo QML Web Loader App). 

Note: 'run_all.sh' is independent and can be copied into any directories and ran in isolation. It will generate a folder called applicationFolder which contains the dependencies
1. **Add execute permissions to the run_all.sh script**

   ```bash
   chmod +x run_all.sh
2. **Run the script (Use sudo for proper access)**
   
   ```bash
   sudo ./run_all.sh
3. **Wait for setup to finish and it will automatically run the QML Loader Application**
4. **When needed, binaries are available in /applicationFolder/QMLWebLoaderApp/binaries**

   ```bash
   cd /applicationFolder/QMLWebLoaderApp/binaries &&
   sudo ./QMLWebLoaderApp

5. Use run_all.sh to run and re-run the application as it automatically runs the webserver for you. When manually running binaries from the binaries folder you have to start the server again yourself when it is killed.

   ```bash
   cd /applicationFolder/SimpleWebServer &&
   chmod +x setup.sh &&
   sudo ./setup.sh
   //Then you can follow step number 4 again to re-run the application


## Manual Setup Instructions (Only use when Quick Setup doesn't work)

1. **Initialize a webserver first. Follow the SimpleWebServer Repo Instructions**
2. **When running the webserver take note of the port number printed on the command line**:

   ```bash
   Example: Server is running on port 13117

3. **Clone this repository into your local directory**
   
    ```bash
    git clone https://github.com/alilkuizon/QMLWebLoaderApp.git

4. **Go into the cloned project**

   ```bash
    cd QMLWebLoaderApp
   
4. **In this repository edit server_port.txt and put the port number from step 2**
5. **Go to the docker folder and add execute permissions to build.sh**
    
    ```bash
   chmod +x build.sh
6. **Execute build.sh and it will build and run the application**

    ```bash
   ./build.sh
7. **The executable application is also located in the binaries Folder created after running build.sh**
8. **(Optional) Execute with sudo if there are permission errors**
