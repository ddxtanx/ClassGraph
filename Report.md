  Our final project run outputs three files: A Text File showing the betweenness centrality of each vertex within the dataset,
a text file showing the list of the vertices visited when iterating through our graph, and a PNG of the layered graph drawing 
showing the prerequisite tree of the selected vertex. One can run our program as described in the ReadMe.

One example output is viewing the Prerequisite tree for the class MATH 512. By running

              ./project Courses-and-prereqs/STEM_courses.dat "MATH 512"
              
the output will be three files:

Betweeness_Full_File.txt will show the betweenness centrality of all the vertices in the STEM_courses dataset.

BFS_From_Course.txt and BFS_Full_File.txt will show the vertices traversed during the BFS of the entire dataset's graph and the subgraph of the course.

Layered_Graph_Drawing.png will be the png of the Layered Graph Drawing of the graph.

These can all be found in the Outputs folder in the repository.

[Betweeness_Full_File.txt](https://github-dev.cs.illinois.edu/cs225-sp21/davidm12-gcredi2-lzefran2/blob/master/Outputs/Betweeness_Full_File.txt)

[BFS_From_Course.txt](https://github-dev.cs.illinois.edu/cs225-sp21/davidm12-gcredi2-lzefran2/blob/master/Outputs/BFS_From_Course.txt)

[BFS_Full_File.txt](https://github-dev.cs.illinois.edu/cs225-sp21/davidm12-gcredi2-lzefran2/blob/master/Outputs/BFS_Full_File.txt)

[Layered_Graph_Drawing.png](https://github-dev.cs.illinois.edu/cs225-sp21/davidm12-gcredi2-lzefran2/blob/master/Outputs/Layered_Graph_Drawing.png)

As one can see from the two Full_File.txt documents, our Betweenness Centrality and Breadth First Search Algorithms both work as expected. The Betweenness Centrality Algorithm
Functions as expectd due to the fact that it can go through all the vertices in the graph, calculate their betweenness centrality, and return the vertex with the
highest betweenness centrality. We can see that the Breadth First Search Algorithm works as expected because it traverses all the vertices in the graph as we can see from 
BFS_Full_File.txt containing all the vertices in the dataset and the BFS_From_Course.txt containg all of the vertices in the Course's Prerequisite chain.

However, our Layered Graph Drawing Algorithm falls short and does not work as expected. Our graph is messy, there are cross edges all over the place, 
And the dummy vertices that we intended to draw using Sugiyama's algorithm are sometimes present and sometimes not. Aditionally, our ouput graph does not differentiate between 
Or classes- For example, CS 225 has a prerequisite of either MATH 213 or CS 173, but our graph displays both of them as required prerequisites when that is not what is desired. While we are successfully able to draw a given graph, our problem is that we are not drawing the correct graph. This is due to us biting off more than we could chew and attempting to do the entire graph drawing algorithm in one function. If it were to be split up into smaller helper function, the code would be much easier to debug and we could have figured out our bugs. The main source of our issue was how we decided to assign layers to vertices, a key step of the Sugiyama method. We did this in a method that ended up being inefficient and causing memory issues, as well as causing the mess in our outputs since it was possible to have courses which one was a prerequisite of the other next to each other on the same layer, which ended up having edges drawn accross them. Our inadequate testing left us scrambling to find out the source of the bugs, and we were unable to go deep enough into the code to find the source and fix them.


However, despite the bugs present in our layered drawing algorithm, we believe that we were successfully able to meet our goals, albeit one did change due to the advice of Professor Evans. Instead of doing Dijkstra's algorithm on our graph, he advised us to do Betweenness Centrality since Dijkstra's algorithm would not output the shortest path if a course had multiple prerequisites, as many do. We then changed our goal to find the Betweenness Centrality of each vertex, and we met this goal. We also were able to meet our goal of implementing a Breadth First Search of the courses in the ECE,MATH,CS, and PHYS departments since we were able to efficiently visit all of the vertices. Finally, despite our final output graphs being somewhat hard to read and messy, we met our goal of displaying the Course Prerequisite Graph for a given vertex, allowing students to see which courses require the most prerequisites.
