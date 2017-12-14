#include "tetpack.h"
#include <math.h>

int main()
{
// Simple test for two triangles
// Each triangle has 3 vertex
// For each vertex, there are two edges
// Here we select the first vertex of the triangle only
// Hence there are two edges for this vertex

vector<vector<double> > Tri(3, vector<double>(3));
vector<vector<double> > Q(3, vector<double>(3));
vector<vector<double> > N(2, vector<double>(3));

// Triangle 

// Base
Tri[0][0] = 0;
Tri[0][1] = -1./2;
Tri[0][2] = 1./(2 * sqrt(2)); 

Tri[1][0] = 0;
Tri[1][1] = 1./2;
Tri[1][2] = 1./(2 * sqrt(2));

Tri[2][0] = -1./2;
Tri[2][1] = 0;
Tri[2][2] = -1./(2 * sqrt(2));

N = find_vertex(Tri);


vector<double> N0T1(3);
	for (int i = 0; i <= N0T1.size() - 1; i++){
		N0T1[i] = N[0][i] - Tri[1][i];
	}
	double length = magnitude( N0T1 );
//	double length2 = magnitude( P[0] - P[2] );
//	double length3 = magnitude( (P[1] - P[2]) );

	printf("lengthN0T1 = %f\n", length);

printf("N0 (%f %f %f) N1 (%f %f %f)\n", N[0][0], N[0][1], N[0][2], N[1][0], N[1][1], N[1][2]);
printf("P: (%f %f %f) (%f %f %f) (%f %f %f)\n",Tri[0][0], Tri[0][1], Tri[0][2], Tri[1][0], Tri[1][1], Tri[1][2], Tri[2][0], Tri[2][1], Tri[2][2]);
//printf("Q: (%f %f %f) (%f %f %f) (%f %f %f)\n",Q[0][0], Q[0][1], Q[0][2], Q[1][0], Q[1][1], Q[1][2], Q[2][0], Q[2][1], Q[2][2]);

//if ( !is_colliding(P, Q) ) printf("disjoint triangles\n");
//else printf("colliding triangles\n");
return 0;
}
