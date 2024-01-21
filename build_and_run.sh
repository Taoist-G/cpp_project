#!/bin/bash

# Define the output executable name
EXECUTABLE_NAME="main1"
OBJECTS_DIR="ex"

# Create the objects directory if it doesn't exist
mkdir -p "$OBJECTS_DIR"

# Clean up the previous build
echo "Cleaning up..."
rm -f "$OBJECTS_DIR"/*.o
rm -f "$EXECUTABLE_NAME"

# Compile the project
echo "Compiling..."
g++ -c -o "$OBJECTS_DIR"/GameBoard.o GameBoard.cpp
g++ -c -o "$OBJECTS_DIR"/GameWindow.o GameWindow.cpp
g++ -c -o "$OBJECTS_DIR"/WindowSetup.o WindowSetup.cpp
g++ -c -o "$OBJECTS_DIR"/main1.o main1.cpp
g++ -o "$EXECUTABLE_NAME" "$OBJECTS_DIR"/main1.o "$OBJECTS_DIR"/GameWindow.o "$OBJECTS_DIR"/WindowSetup.o "$OBJECTS_DIR"/GameBoard.o -lfltk -lfltk_images

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    ./"$EXECUTABLE_NAME"
else
    echo "Compilation failed."
fi
