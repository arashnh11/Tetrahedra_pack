#include "mylib.h"
#include "Geometry.h"

int main()
{
// Simple test for two triangles
// Each triangle has 3 vertex
// For each vertex, there are two edges
// Here we select the first vertex of the triangle only
// Hence there are two edges for this vertex

vector<vector<double> > P(3, vector<double>(3));
vector<vector<double> > Q(3, vector<double>(3));

// Triangle P
// Point 0
P[0][0] = 0;
P[0][1] = 0;
P[0][2] = 0; 
// Point 1
P[1][0] = 1;
P[1][1] = 0;
P[1][2] = 0; 
// Point 2
P[2][0] = 0;
P[2][1] = 1;
P[2][2] = 0; 

// Triangle Q
// Point 0
Q[0][0] = 1;
Q[0][1] = 1;
Q[0][2] = 0; 
// Point 1
Q[1][0] = 1;
Q[1][1] = 0;
Q[1][2] = 0;
// Point 2
Q[2][0] = 0;
Q[2][1] = 1;
Q[2][2] = 0; 

printf("P: (%f %f %f) (%f %f %f) (%f %f %f)\n",P[0][0], P[0][1], P[0][2], P[1][0], P[1][1], P[1][2], P[2][0], P[2][1], P[2][2]);
printf("Q: (%f %f %f) (%f %f %f) (%f %f %f)\n",Q[0][0], Q[0][1], Q[0][2], Q[1][0], Q[1][1], Q[1][2], Q[2][0], Q[2][1], Q[2][2]);

if ( !is_colliding(P, Q) ) printf("disjoint triangles\n");
else printf("colliding triangles\n");
return 0;
}
