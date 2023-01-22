cmake_minimum_required(VERSION 3.23)  # CMake version check
project(AP_1_ex_4)              # Create project "simple_example"

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_CXX_STANDARD 11)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)

include_directories(..)

add_subdirectory(knnserver_src)
add_subdirectory(knnset_src)
add_subdirectory(cli_src)


# Add executable target with source files listed in SOURCE_FILES variable
add_executable(server knnserver_src/server_main.cpp)


add_executable(AP_1_ex_4
        cli_src/UploadCSV.h
        cli_src/UploadCSV.cpp
        cli_src/StandardIO.h
        cli_src/StandardIO.cpp
        cli_src/Exit.h
        cli_src/Exit.cpp
        cli_src/DownloadResults.h
        cli_src/DownloadResults.cpp
        cli_src/DisplayResults.h
        cli_src/DisplayResults.cpp
        cli_src/DefaultIO.h
        cli_src/DefaultIO.cpp
        cli_src/Command.h
        cli_src/Command.cpp
        cli_src/CLI.h
        knnserver_src/server_main.cpp
        knnserver_src/KNN_MainServer.cpp
        knnserver_src/KNN_MainServer.h
        knnserver_src/KNN_ClientServer.h
        knnserver_src/KNN_ClientServer.cpp
        knnserver_src/AbstractPeer.h
        knnserver_src/AbstractPeer.cpp
        knnserver_src/Client.cpp
        knnserver_src/Client.h
        knnserver_src/client_main.cpp
        knnset_src/ClassifiedVector.cpp
        knnset_src/ClassifiedVector.h
        knnset_src/KNN_Set.cpp
        knnset_src/KNN_Set.h
        knnset_src/VectorDist.cpp
        knnset_src/VectorDist.h)

