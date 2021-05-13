  Our final project run outputs three files: A Text File showing the betweenness centrality of each vertex within the dataset,
a text file showing the list of the vertices visited when iterating through our graph, and a PNG of the layered graph drawing 
showing the prerequisite tree of the selected vertex. One can run our program as described in the ReadMe.

One example output is viewing the Prerequisite tree for the class MATH 512. By running

              ./project Courses-and-prereqs/STEM_courses.dat "MATH 512"
              
the output will be three files:

Betweeness_Full_File.txt will show the betweenness centrality of all the vertices in the STEM_courses dataset.

BFS_From_Course.txt and BFS_Full_File.txt will show the vertices traversed during the BFS of the entire dataset's graph and the subgraph of the course.

Layered_Graph_Drawing.png will be the png of the Layered Graph Drawing of the graph.

These can all be found in the ReportFiles/ Folder in the repository.
