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

4) The output of all algorithms are stored in the ./Outputs/ folder
    /Betweeness_Full_File           output of the betweeness centrality test on the whole graph
    /BFS_Full_File                  output of a BFS iterator that traverses every course in the whole graph
    /BFS_From_Course                output of a BFS iterator starting at the user defined course in command line arg
    /Layered_Graph_Drawing.png      is the image output of the LGD algorithm
    



How to run tests:

1) Open a terminal to the root directory of our repository: davidm12-gcredi2-lzefran2
2) Type < make test > to compile the specific test code 
3) To test our algorithms (BFS, Betweeness Centrality), type:
        
        ./test

4) The output of all tests will be in the terminal, using CATCH




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

