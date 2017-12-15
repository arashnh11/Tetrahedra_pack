#include "geometry.h"
#include "tri_col.h"
#include <vector>
#include <math.h>
using namespace std;

bool is_tri_col(vector<vector<double> > &P, vector<vector<double> >&Q)
{
	vector<double> P_u(3); 
	vector<double> Q_u(3);
	P_u = unit_norm(P[0], P[1], P[2]);
	Q_u = unit_norm(Q[0], Q[1], Q[2]);
	// Case: if P and Q are identical --> skip the code
	if (P == Q || P_u == Q_u){
		return false;
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

bool is_tet_col(vector<vector<double> > &Tet_P, vector<vector<double> >&Tet_Q){
	
	// Case: if P and Q are identical --> skip the code as they are colliding
//	if (Tet_P[0] == Tet_Q[0] && Tet_P[1] == Tet_Q[1] && 
//		Tet_P[2] == Tet_Q[2] && Tet_P[3] == Tet_Q[3]){
	if (Tet_P == Tet_Q){
		return true;
	}
	vector<vector<vector<double> > >Face_P(4, vector<vector<double> > (3, vector<double>(3)));
	vector<vector<vector<double> > >Face_Q(4, vector<vector<double> > (3, vector<double>(3)));
	
	Face_P = tet_face(Tet_P);
	Face_Q = tet_face(Tet_Q);
	for (int k = 0; k <= Face_P.size() - 1; k++){
		for (int m = 0; m <= Face_Q.size() - 1; m++){
			if (is_tri_col(Face_P[k], Face_Q[m])){
				return true;
			}
		}
	}
	
	return false;
}
