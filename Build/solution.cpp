#include "../Geometry/geometry.h"
#include "../Geometry/tet_col.h"
#include "../Packing/tet_pack.h"
#include "../Script/tet_script.h"

int main()
{
	/* Simple test for two triangles
	   Each triangle has 3 vertex
	   For each vertex, there are two edges
	   Here we select the first vertex of the triangle only
	   Hence there are two edges for this vertex */
	
	vector<vector<double> > Tri(3, vector<double>(3));
	vector<vector<double> > Tet(4, vector<double>(3));
	vector<vector<double> > Tet0(4, vector<double>(3));
	vector<vector<double> > Tet1(4, vector<double>(3));
	int N_tet = 10;
	vector<vector<vector<double> > > Pack(N_tet, vector<vector<double> > (4, vector<double>(3)));
	vector<vector<vector<double> > >Face(4, vector<vector<double> > (3, vector<double>(3)));

	vector<vector<double> > Q(3, vector<double>(3));
	vector<vector<double> > N(2, vector<double>(3));
	vector<double> N0(3), N1(3), N_new(3);
	
	// Base equilateral triangle
	double len = 1; // size of the triangle edges
	Tri = init_tri(len); // generate the initial triangle
	N = find_vertex(Tri); // find the possible 4th vertex for regular tetrahedra
	Tet = tet_gen(Tri, N[0]);
	Pack = tet_pack(Tet, Pack); // Initialize the packing

	int tet_add = 0;
	bool tet_pass = true;

	while (tet_add <= N_tet - 1){
		for (int k = 0; k <= Pack.size() - 1; k++){
			Face = tet_face(Pack[k]);
			for (int j = 0; j <= Face.size() - 1; j++){
				Tri = Face[j];
				N = find_vertex(Tri); // find the possible 4th vertex for regular tetrahedra
				for (int i = 0; i <= N.size() - 1; i++){
					Tet = tet_gen(Tri, N[i]);
					tet_pass = true;
					for (int m = 0; m <= tet_add; m++){
						if (is_tet_col(Tet, Pack[m])){
							tet_pass = false;
							m = tet_add + 1;
						}
					}
					if (tet_pass){
						tet_add++;
						if (tet_add == N_tet){
							i = N.size();
							j = Face.size();
							k = Pack.size();
						}
						else {
							Pack = tet_pack(Tet, Pack);
						}
					}
				} // i loop
			} // j loop
		} // k loop
	} // while loop
	
	write_basis();
	write_pack(Pack);
// sanity

/*
for (int i = 0; i <= Pack.size() - 1; i++){
	for (int j = 0; j <= Pack.size() - 1; j++){
		if (is_tet_col(Pack[i], Pack[j]) && i!=j ){
			printf("colliding ");
		}
		else {
			printf("disjoint ");
		}
	}
}
*/

/*	if (is_tet_col(Pack[0], Pack[1]))
		printf("colliding\n");
	else
		printf("disjoint\n");
*/


//}
//	Tri = 
//	printf("tet_add %d\n", tet_add);
//}

// Sanity check
/*
	vector<double> N0T0(3), N0T1(3), N0T2(3), N1T0(3), N1T1(3), N1T2(3);
	for (int i = 0; i <= N0T1.size() - 1; i++){
		N0T0[i] = N[0][i] - Tri[0][i];
		N0T1[i] = N[0][i] - Tri[1][i];
		N0T2[i] = N[0][i] - Tri[2][i];

		N1T0[i] = N[1][i] - Tri[0][i];
		N1T1[i] = N[1][i] - Tri[1][i];
		N1T2[i] = N[1][i] - Tri[2][i];
	}

	vector<double> P01(3), P02(3), P12(3);
	for (int i = 0; i <= P01.size() - 1; i++){
		P01[i] = Tri[0][i] - Tri[1][i];
		P02[i] = Tri[0][i] - Tri[2][i];
		P12[i] = Tri[1][i] - Tri[2][i];
	}

	double lengthp0 = magnitude( P01 );
	double lengthp1 = magnitude( P02 );
	double lengthp2 = magnitude( P12 );

	double lengthn00 = magnitude( N0T0 );
	double lengthn01 = magnitude( N0T1 );
	double lengthn02 = magnitude( N0T2 );

	double lengthn10 = magnitude( N1T0 );
	double lengthn11 = magnitude( N1T1 );
	double lengthn12 = magnitude( N1T2 );

	printf("lengthp0 = %f\n", lengthp0);
	printf("lengthp1 = %f\n", lengthp1);
	printf("lengthp2 = %f\n", lengthp2);

	printf("lengthN0T0 = %f\n", lengthn00);
	printf("lengthN0T1 = %f\n", lengthn01);
	printf("lengthN0T2 = %f\n", lengthn02);

	printf("lengthN1T0 = %f\n", lengthn10);
	printf("lengthN1T1 = %f\n", lengthn11);
	printf("lengthN1T2 = %f\n", lengthn12);
	printf("N0 (%f %f %f) N1 (%f %f %f)\n", N[0][0], N[0][1], N[0][2], N[1][0], N[1][1], N[1][2]);
	printf("P: (%f %f %f) (%f %f %f) (%f %f %f)\n",Tri[0][0], Tri[0][1], Tri[0][2], Tri[1][0], Tri[1][1], Tri[1][2], Tri[2][0], Tri[2][1], Tri[2][2]);
	//printf("Q: (%f %f %f) (%f %f %f) (%f %f %f)\n",Q[0][0], Q[0][1], Q[0][2], Q[1][0], Q[1][1], Q[1][2], Q[2][0], Q[2][1], Q[2][2]);

	//if ( !is_colliding(P, Q) ) printf("disjoint triangles\n");
	//else printf("colliding triangles\n");

	vector<double> A(3, 0);
	vector<double> B(3, 0);
	vector<double> C(3, 0);
	A[2] = 1; B[1] = 1;

	C = cross_prod(A,B);
	printf("A (%f %f %f)\n", A[0], A[1], A[2]);
	printf("B (%f %f %f)\n", B[0], B[1], B[2]);
	printf("C (%f %f %f)\n", C[0], C[1], C[2]);
*/
return 0;
}
