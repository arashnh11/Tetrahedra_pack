//#include "../Geometry/geometry.h"
#include "../Geometry/tet_col.h"
#include "../Packing/tet_pack.h"
#include "../Script/tet_script.h"

int main()
{
	// Inputs for regular tetrahedra packing
	int N_tet = 70; // Number of Tetrahedra in the pack
	double len = 0.01; // size of the triangle edges
	
	// Run the packing scheme
	vector<vector<vector<double> > > Pack(N_tet, 
	vector<vector<double> > (4, vector<double>(3)));	
	Pack = packing(len, N_tet);
	
	// Control check on the packing 
	check_pack_col(Pack); // Is there any collison in the pack?
	check_pack_size(Pack, len); // Are all packing tetrahedra equilateral?

	// Output Results
	write_basis(); // Write the basis vector
	write_pack(Pack); // Write the optimum packing of tetrahedra
					  // Each row corresponds to a tetrahedron
					  // Each row has 4 vertex coordinates (Vert1x Vert1y Vert1z ...Vert4z)
}					


