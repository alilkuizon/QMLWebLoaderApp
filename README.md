
# QML Web Loader

This application loads qml files served in webservers. A local host webserver can be run using the Simple Web Server repo found here:

https://github.com/alilkuizon/SimpleWebServer

## Setup Instructions

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
6. **(Optional) Execute with sudo if there are permission errors**
