#include <vector>
#include <math.h>
using namespace std;

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
	double abs_unit = magnitude(unit);
	for (int i = 0; i <= unit.size() - 1; i++){
		unit[i] /= abs_unit;
	}
	return unit;
}

vector<vector<double> >init_tri(double len){
	vector<vector<double> > Tri(3, vector<double>(3, 0));
	Tri[0][0] = 0;
	Tri[0][1] = -1./2;
	Tri[0][2] = 1./(2 * sqrt(2)); 

	Tri[1][0] = 0;
	Tri[1][1] = 1./2;
	Tri[1][2] = 1./(2 * sqrt(2));

	Tri[2][0] = -1./2;
	Tri[2][1] = 0;
	Tri[2][2] = -1./(2 * sqrt(2));
	for (int j = 0; j <= Tri.size() - 1; j++){	
		for (int i = 0; i <= Tri.size() - 1; i++){
			Tri[j][i] *= len;
		}
	}
	return Tri;
}

vector<vector<double> >tet_gen(vector<vector<double> > &Tri, vector<double> &P){
	vector<vector<double> > Tet(4, vector<double>(3, 0));
	for (int j = 0; j <= Tet.size() - 2; j++){
		for (int i = 0; i <= Tri.size() - 1; i++){
			Tet[j][i] = Tri[j][i];
		}
	}
	for (int i = 0; i <= P.size() - 1; i++){
		Tet[3][i] = P[i];
	}
	return Tet;
}

vector<vector<vector<double> > >tet_face(vector<vector<double> > &Tet){
	vector<vector<vector<double> > >Face(4, vector<vector<double> > (3, vector<double>(3)));
	for (int k = 0; k <= Face.size() - 1; k++){
		for (int i = 0; i <= Face[1][1].size() - 1; i++){		
			if (k == 0){
			Face[k][0][i] = Tet[0][i];
			Face[k][1][i] = Tet[1][i];
			Face[k][2][i] = Tet[2][i];
			}
			else if (k == 1){
			Face[k][0][i] = Tet[0][i];
			Face[k][1][i] = Tet[1][i];
			Face[k][2][i] = Tet[3][i];
			}	
			else if (k == 3){
			Face[k][0][i] = Tet[0][i];
			Face[k][1][i] = Tet[2][i];
			Face[k][2][i] = Tet[3][i];
			}
			else {
			Face[k][0][i] = Tet[1][i];
			Face[k][1][i] = Tet[2][i];
			Face[k][2][i] = Tet[3][i];
			}
		}
	}
	return Face;
}

vector<vector<double> >find_vertex(vector<vector<double> >&Tri)
{
	vector<double> P(3), Q(3), R(3), center(3), scale(3);
	vector<vector<double> > vert(2, vector<double>(3, 0));
	for (int i = 0; i <= center.size() - 1; i++){
		center[i] = 1./3 * (Tri[0][i] + Tri[1][i] + Tri[2][i]);
	}

	vector<double> P01(3);
	for (int i = 0; i <= P01.size() - 1; i++){
		P01[i] = Tri[0][i] - Tri[1][i];
	}
	double length = magnitude( P01 );
	for (int i = 0; i <= P.size() - 1; i++){
		P[i] = Tri[0][i];
		Q[i] = Tri[1][i];
		R[i] = Tri[2][i];
	}
	scale = unit_norm(P, Q, R);
	for (int i = 0; i <= scale.size() - 1; i++){
		scale[i] *= sqrt(2./3) * length;
	}
	for (int i = 0; i <= center.size() - 1; i++){
		vert[0][i] = center[i] + scale[i];
		vert[1][i] = center[i] - scale[i];
	}
	return vert;
}
