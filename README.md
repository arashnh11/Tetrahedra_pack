This software generates a dense packing of regular tetrahedra
@ Arash Nemati Hayati
  Dec 15, 2017
  Email: a.nematihayati@gmail.com
  
The scheme used for optimization is a bipyramid propagation algorithm.

1) Sketch the base triangle for a regular tetrahedron. 
2) Find possible vertex which make regular tetrahedra
3) Initialize packing with one of the generated tetrahedra
4) Find faces of the tetrahedra in the pack
5) Find possible vertex as done in 2
6) Consier each possible tetrahedron
7) Check for collision between the new candidates vs the pack tetrahedra
8) If checks passed, add tetrahedron to the pack
9) Continue searching for new candidates as described in 4-6

Note:
Further optmization can be achieved by evaluating the packing density for
	different face selections 
	different propgation directions

and keep those tetrahedra which provides higher density
