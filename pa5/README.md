[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/KPrrdehF)


My design decisions were basically just "the system wouldn't realistically be that big anyways, considering the state of American Healthcare" so I didn't bother with such a small dataset (although I of course didn't make anything O(n!) of course)
I used AI as it should be used, as a compaion to have running right next to my vscode window. I used multiple models, deepseek and github ai which I think is using claude 4.5, but because they are free and I am mega broke.
My Dijkstra implementation isn't 100% the same as the MA3 implementation but I explained why in the video. I allowed AI to make changes to my implementation of most functions so I wouldn't spend countless hours debugging for no reason, and I even had AI make my launch.json and tasks.json since for some reason they just dont get premade with some sort of template. Of course I edited those to fit the actual file locations.

Below are my notes that I kept looking over at during the video, just in case it was suspicious that I kept cutting the video or moving my mouse to the side. I had to do this with mic off so the video took longer to explain, and I even sped it up by 1.5x as I was 10 minutes over...

Anyway, here's the notes. They aren't super duper accurate with line numbers, but I made a few changes between writing and recording as I would realize that it was kinda dumb what I was doing:





Emergency Command Deep Dive:

- For parsing breakdown, point on 117 in main, explain how parsing works from there

- For finding nearest open hospital, point on line 158 of EmergencySystem, explain all steps prior to that return statement where it measures weights and stuff. Can also walk thru Dijkstra implementation, since it is precomputing all paths to be used later (Line 15 of EmergencySystems, last lines of Graph)

- For Priority Queue stuff, line 47 of EmergencySystems takes you to line 4 of Hospital which takes you to line 31 of PriorityQueue and line 5 to maintain heap property after insertion.

- For time complexity, when V=cities E=edges N=patients in queue and M=patients being merged, Emergency operation is O(V + logN), Priority queue insertion is O(logN), and Dijkstra is O((V+E) logV)




Hospital Close Command:

- For how it is marked, see line 66 of EmergencySystem, takes you to Hospital.h file on line 23.

- For finding nearest hospital, go to line 41 of EmergencySystem to show that it checks if a city is open and then looks for the nearest hospital around that one if it is closed by using line 139

- For merging, that is started in Hospital on line 21, which takes you to the bottom function of PriorityQueue. Insertion is the same insert used for regularly inserting patients on line 31 and lines 5 and 12 for the heapify functions, sorting them by severity like normal.

- During the merge the heap property is maintained after every insertion during the merge process, ensuring the list is in order before inserting a new patient. At the end it's as if the patients were just regularly inserted. It is a slower process of course, especially with long lists, but it's reliable, and you don't want to forget to treat a patient in the name of optimization ;)

- Time complexity is O(M log(N+M)) where N is the patient queue count and M is the merge queue length.




Treat Command:

- Treating is handled in EmergencySystem starting on line 96. It then takes you to line 36 of PriorityQueue where it will extract the top patient of that hospital, removing them from the list.

- At the end of the extractMax function it will call heapifyDown from the root if the heap isn't empty. You can show off heapifyDown on line 12 of PriorityQueue.

- Time complexity is O(logN) for treat since it is the same for extract.




Dijkstra's Implementation:

- Header of Graph contains the structure for an edge and node. It also shows the map and vector for the adjList and the cities. adjList is for storing cities in a way that makes it easy to find neighbors and, in turn, their distances.

- Show line 80 of Graph to show the precomputation of shortest paths between cities. Show that for each city it returns a map of the shortest paths to other cities directly above that function starting on line 42.

- Point out that the algorithm doesn't handle closed nodes, but instead gets used when it is found that a node is closed, allowing the algorithm to use precomputed data to find the closest open node instead of just the closest node. This is done on line 139 of EmergencySystem

- The time complexity overall for Dijkstras is O((V+E) logV) where V is the city count and E is the edge count, and the space complexity is O(V+E).

- Time complexity for precomputing is O(V^2 logV) where V is the city count, and the space complexity is O(V^2). This is not ideal, but doing this early means the longest wait is at the beginning when everything is initialized, and then everything is faster with this data ready to go.


- The changes made to the MA3 implementation are that now instead of running dual sets we are running a map to store the distances from the start node to other cities. The set to store which ones have been visited remains the same. This is because at the end of the day those are the safest choices for their purposes and the performance is relatively equal, especially for a set this small. I asked AI if there were better ways for programs that scale perfectly with much larger datasets and it gave me options, but it also said this was a good setup