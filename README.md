This software generates a dense packing of regular tetrahedra
@ Arash Nemati Hayati
  Dec 15, 2017
  Email: a.nematihayati@gmail.com
  
The scheme used for optimization is a tight bipyramid propagation algorithm.

1) Sketch the base triangle for a regular tetrahedron. 
2) Find possible vertex which make regular tetrahedra
3) Initialize packing with one of the generated tetrahedra
4) Find faces of the tetrahedra in the pack
5) Find possible vertex as done in 2
6) Consier each possible tetrahedron
7) Check for collision between the new candidates vs the pack tetrahedra
8) If checks passed, add tetrahedron to the pack
9) Continue searching for new candidates as described in 4-6

Notes for furture improvements:
-- Further optmization can be achieved by evaluating the 
	packing density for different face selections different 
	propgation directions and keep those tetrahedra which provides higher density.

-- Another dimension to the shceme complexity can be addded
    by rotating/translation of the base bipyramid

-- In this version, there is a limitation in the packing
	configuration. To get optimum packing, not all combinations
	of N_tet (number of tetrahedra in the pack) and len (length of tetrahedra)
	are possible. The threshold packing sizes at different length for this version are:
	 N_tet = 25, len = 1 
	 N_tet = 70, len = 0.01
	
	For other packing configuations, sizes should be relaxed by reducing N_tet and/or len.
	(This is suggested in the software if the input case cannot be efficiency optimized.)

Notes for execution on a Linux machine:

1) Download the package from github at:
git@github.com:arashnh11/Tetrahedra_pack.git

2) Extract the files and then open a terminal:
cd Tetrahedra_pack
cd Build
make


