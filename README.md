# davidm12-gcredi2-lzefran2

How to run our code:

1) Open a terminal to the root directory of our repository: davidm12-gcredi2-lzefran2
2) Type < make > to compile the main user code (not specific test cases)
3) To run our algorithms (BFS, Betweeness Centrality, and Layered Graph Drawing), type:
        
        ./project   < Filepath to Data set >    < "Course name and number" >
    
    Examples    
    EX  ./project ./Courses-and-prereqs/STEM_courses.dat "CS 225"
    EX2 ./project ./Courses-and-prereqs/AllPrereqs.dat "ECE 391"
    EX3 ./project ./Courses-and-prereqs/TestData.dat "ADV 101"

    *note: the course name must be in all caps, and any invalid course name will result
            in undefined behavior.

4) The output of all algorithms are stored in the Outputs folder, each named accordingly




Location of important code files:       (foo/  indicates the whole folder "foo" is dedicated to listed algorithm)

Parsed Data:
    Courses-and-prereqs/
Graph Structure:
    Graph/
    ClassGraph.h
    ClassGraph.cpp
    dataConvert.h
    dataConvert.cpp
    utils.h
    utils.cpp
BFS:
    Davids_Work/
Betweeness Centrality:
    Graph/Graph.cpp
    Graph/Graph.cpp
Layered Graph Drawing:
    LGD/
    Stickers/
Output Data Files:
    Outputs/

