# Voronoi-Diagram
Code generating Voronoi Diagrams using Fortune's Algorithm

Main features:
  - Red-Black binary search tree for storing the beachfront
    - Red-Black tree can be printed to a .dot file
  - Min-heap priority queue for storing site and circle events
  - O(log(n)) running time
  
 To do:
  - Finalise event processing
  - Add node-deletion and tree merging to the Red-Black tree
  - Add DCEL to store the Voronoi diagram
  - Add a rendering routine, to display the finalised diagram
    - Store finalised diagram as bitmap image
