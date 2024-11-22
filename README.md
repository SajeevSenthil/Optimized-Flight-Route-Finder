# Optimized-Flight-Route-Finder
The Optimized Flight Route Finder is a project that demonstrates the application of Dijkstra's Algorithm for determining the shortest and most efficient flight paths between 89 domestic airports in India. The program processes a manually curated dataset of travel times between airports (in minutes) stored in a CSV file. It supports functionality to compute direct shortest paths, stopover paths, and track recently queried routes.

# Features
1) Shortest Path: Calculate the fastest travel route between two selected airports.
2) Stopover Path: Identify the optimal route with a specified intermediate stopover.
3) Recent Routes: View the last five routes explored for easy access and reference.

# Algorithm Complexity
**Dijkstra's Algorithm**:
- **Time Complexity**: 
  - \(O(V^2)\) for adjacency matrix implementation.
  - \(O((V + E)log V)\) for priority queue implementation with adjacency list.
- **Space Complexity**:
  - \(O(V + E)\), where \(V\) is the number of vertices (airports), and \(E\) is the number of edges (connections).

# Key Functions in the Code
**1) loadAdjacencyMatrix:**
Reads the travel time data from a CSV file and generates an adjacency matrix representation of the airport network.
Treats missing or invalid data as infinite travel time.

**2) dijkstra:**
Implements Dijkstra's algorithm to compute the shortest path between a source and a destination airport.
Tracks the path using a parent array and outputs the total travel time.

**3) printPath:**
Recursively prints the route from source to destination by traversing the parent array.

**4) dijkstraWithStopover:**
Combines two runs of Dijkstra's algorithm to find the shortest route with a specified stopover airport.

**5) displayRecentRoutes:**
Maintains a deque to store and display the last five calculated routes for user reference.

**6) main:**
Provides a menu-driven interface for users to select between different functionalities: finding shortest paths, stopover paths, or viewing recent routes.

# Data Structures used:

**1) Priority Queue:** 
To fetch the airport with the smallest travel time efficiently

**2) Graph:**
The graph is represented as an adjacency matrix, where each node (airport) is connected to others with weights corresponding to travel times.

**3) Doubly Ended Queue (deque):**
Used to track and store the last five queried routes (source-destination pairs) for quick retrieval and management.
