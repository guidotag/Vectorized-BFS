Vectorized-BFS
==============

I've developed a vectorized version of BFS, which I describe in detail in a document. I implemented it in x86-64 Assembly using SSE extensions, and compared this version with a traditional BFS queue-implementation. Unfortunately, the vectorized BFS turns to be slower than the traditional one. Nevertheless it is theoretically interesting.

The program expects two folders to exist. To setup these folders run the config script. Then compile and build the program running make, which will place the binary file in the bin folder. The program usage information can be seen running

./bin/bfs -h
