## Project Proposal (davidm12, gcredi2, lzefran2)

1. **Leading Question** Given a class in the UIUC CS, ECE, Physics, and Mathematics departments, we would like to find the shortest possible sequence of classes to satisfy the class’ prerequisites and we would like student's to be able to visualize how different classes interact and lead to other classes by printing out the prerec chains in the departments.

2. **Data Acquisition & Processing** We will use data from the CIS API to get data for all the courses offered in the various departments in Fall of 2021. From that, we will parse the descriptions to get the class prerequisites for all of the relevant courses. The weight on the edge from A to B would be some measure of how difficult B is as measured by GPA or a similar metric.

3. **Algorithms**
We will be implementing BFS, Dijkstra (a variant), and layered graph drawing. The variant of Dijkstra would be Dijkstra but applicable to returning a set of paths, as some classes have multiple prerequisites. Thus if we had an example scenario, with a user wanting to take CS 225, then since it has TWO classes as a prerequisite (CS 126/128 / ECE 220) AND (CS 173 / MATH 213/347/412/413) we would use Dijkstras to find optimal paths from the ORIGIN node to both of the two prereqs and then it would return a set consisting of those two paths.

4. **Timeline**

  April 8 - complete project proposal and team contract

  April 9 - submit project proposal and team contract

  April 12 - set up initial repository and Makefile

  April 15 - finish parsing class data from CIS API to usable form. Begin BFS iterators and test writing.

  April 19 - convert CIS Data into graph format and pass simple tests. Finish BFS Iterators

  April 22 - Begin work on Dijkstra and Graph drawing, and writing relevant tests

  April 29 - (Hopefully) finish writing Dijkstra, all work on graph output.

  May 5 - write layered graph drawing algorithm and verify with tests

  May 7 - finish report

  May 9 - record final presentation

  May 11 - finish editing presentation and submit





