# DataVisualizer-Cpp

####Project Description

Data visualizer is a QT/C++ based application designed to give a visual representation of various data structures, currently, stack, queue, and binary min heap. It provides an easy to add framework so that additional data structuress may be added in future.

####Tools and Technology

The project has been developed in QT Creator IDE, using C++ based QGraphics framework for GUI elements. Specific instructions on how to download, setup and run using QT creator are present in the Instructions Wiki.

####The Repository Details

This repository consists of a "DataVisualizer" folder that has all the source, UI and header files. This folder can be opened as a project in QT creator IDE.

Every datastructure to be visualized has a UI file, a CPP source file and a header file with a class definition. Common interface APIs has been added for every datastructure such as insert/remove/clear/cleanup. These APIs have the implementation required for displaying a specific data structure type. 

Further, as the queue/stack displays the data as list and min Heap/BST displays the data as tree, the display logic for these datastructure has been abstracted into list and tree classes. Any enhancement to this application such as adding AVL trees/Red Black trees will only require adding the datastructure specific details in their respective class definition and the display logic can be borrowed from these abstract classes. The definition of these abstract types can be found in visualizer.h and visualizer.cpp files. Top level GUI source/UI is handled in files titled "main".

####How to work on an Issue

    You can view the open issues for the repository under Issues. If there is a particular existing issue that you would like to fix, please leave a comment below it with intent and details of how you intend to fix it. This will reduce duplication of effort.
    If you would like to propose an enhancement, or report a bug that you would like to work on, feel free to open new issues and we will assign them to you.

####How to get help

Have questions, comments, feedback or looking for help? We are available and can be reached at the Slack channel created specifically for this project. IRC channels are so a thing of the past! If you are having trouble signing up, you can reach us at ghcfoss@gmail.com for signup help.
