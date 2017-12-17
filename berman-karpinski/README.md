8/7-Approximation Algorithm for (1,2)-TSP
=========================================

Original paper: http://theory.cs.uni-bonn.de/ftp/reports/cs-reports/2006/85274-CS.pdf (written by Berman-Karpinski)

Input format
------------

`main.cpp` -- source code in C++11.

Input is read from `input.txt` file.
Format is:
```
<vertices_number> <edges_number>
a1 b1
a2 b2
...
a<edges_number> b<edges_number>
```
Edges listed are those with weight 1. Absent ones are assumed of weight 2.
`ai` `bi` are 1-indexed vertex numbers representing i'th edge.

How to test?
------------

```bash
your_favorite_editor input.txt  # write input test in input.txt
g++ -std=c++11 main.cpp
./a.out
```
