#include "tetcoll.h"
#include <vector>
#include <math.h>
using namespace std;

bool is_colliding(vector<vector<double> > &P, vector<vector<double> >&Q)
{
	// Case: if P and Q are identical --> skip the code as they are colliding
	if (P[0] == Q[0] && P[1] == Q[1] && P[2] == Q[2]){
		return true;
	}

	vector<vector<double> > EP(2, vector<double>(3));
	vector<vector<double> > EQ(2, vector<double>(3));

	// Case : if P and Q have common edge/face -> add eps to assure disjoint detection
	double eps = 1e-15;
	for (int j = 0; j <= 1; j++){
		for (int k = 0; k <= 2; k++){
			EP[j][k] = P[j+1][k] - P[0][k] + eps; // edges of first vertex
			EQ[j][k] = Q[j+1][k] - Q[0][k] + eps; // edge of first vertex
		}
	}
	double *p = P[0].data();
	double *q = Q[0].data();
	double *ep0 = EP[0].data();
	double *ep1 = EP[1].data();
	double *eq0 = EQ[0].data();
	double *eq1 = EQ[1].data();
	int res = tr_tri_intersect3D(p, ep0, ep1, q, eq0, eq1);
	if (res == 1) return true;
	else return false;
}

vector<double> cross_prod(vector<double> &P, vector<double> &Q){
	vector<double> cross(3);
	cross[0] = P[1] * Q[2] - P[2] * Q[1];
	cross[1] = P[2] * Q[0] - P[0] * Q[2];
	cross[2] = P[0] * Q[1] - P[1] * Q[0];
	return cross;
}

double magnitude(vector<double> &P){
	double mag = sqrt( P[0] * P[0] + P[1] * P[1] + P[2] * P[2] );
	return mag;
}

vector<double> unit_norm(vector<double> &P, vector<double> &Q, vector<double> &R){
	vector<double> unit(3);
	vector<double> A(3);
	vector<double> B(3);
	for (int i = 0; i <= A.size() - 1; i++){
		A[i] = R[i] - P[i];
		B[i] = Q[i] - P[i];
	}
	unit = cross_prod( A, B );
	for (int i = 0; i <= unit.size() - 1; i++){
		unit[i] /= magnitude(unit);
	}
	return unit;
}

vector<vector<double> >find_vertex(vector<vector<double> >&Tet)
{
	vector<double> P(3), Q(3), R(3), center(3), scale(3);
	vector<vector<double> > vert(2, vector<double>(3, 0));
	for (int i = 0; i <= center.size() - 1; i++){
		center[i] = 1./3 * (Tet[0][i] + Tet[1][i] + Tet[2][i]);
	}

	vector<double> P01(3);
	for (int i = 0; i <= P01.size() - 1; i++){
		P01[i] = Tet[0][i] - Tet[1][i];
	}
	double length = magnitude( P01 );
	for (int i = 0; i <= P.size() - 1; i++){
		P[i] = Tet[0][i];
		Q[i] = Tet[1][i];
		R[i] = Tet[2][i];
	}
	scale = unit_norm(P, Q, R);
	for (int i = 0; i <= scale.size() - 1; i++){
		scale[i] *= 2./3 * length;
	}
	for (int i = 0; i <= center.size() - 1; i++){
		vert[0][i] = center[i] + scale[i];
		vert[1][i] = center[i] - scale[i];
	}
	return vert;
}
