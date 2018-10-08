# Dominating Set Finder
Find a dominating set of size k, should there be one, in a graph represented by edge listings.

## Compile

```
gcc dominatingSet.c -std=c99 -Wall -o yourOutputFileNameHere
```

## Run

```
./yourOutputFileNameHere
```

## Input

Takes a .txt file of the following (edge listing) form:
```
<number of vertices> <number of edges> <dominating set size (k)>
<vertex> <vertex>
...
<vertex> <vertex>
```

Example (included in test_graph.txt):
```
5 6 2
1 2
1 3
1 4
2 3
2 4
4 5
```

To use more files, simply make another call to the checkDominatingSet() function in main() specifying the file name you wish to test.
