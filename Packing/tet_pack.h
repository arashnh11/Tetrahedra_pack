#include <vector>
#include <math.h>
using namespace std;

int static counter = -1;
vector<vector<vector<double> > > tet_pack(vector<vector<double> > &Tet, 
vector<vector<vector<double> > > &Pack){
	counter++;
	for (int j = 0; j <= Tet.size() - 1; j++){
		for (int i = 0; i <= Tet[1].size() - 1; i++){
			Pack[counter][j][i] = Tet[j][i];
		}
	}
	return Pack;
}

vector<vector<vector<double> > > pack_init(vector<vector<double> > &Tet, vector<vector<vector<double> > > &Pack){
	for (int j = 0; j <= Tet.size() - 1; j++){
		for (int i = 0; i <= Tet[1].size() - 1; i++){
			Pack[0][j][i] = Tet[j][i];
		}
	}
	return Pack;
}

bool check_pack_col(vector<vector<vector<double> > > &Pack){
	bool flag = false;
	for (int i = 0; i <= Pack.size() - 1; i++){
		for (int j = 0; j <= Pack.size() - 1; j++){
			if (is_tet_col(Pack[i], Pack[j]) && i!=j){
				flag = true;
				printf("ERROR: Some of the tetrahedra are colliding!!\n");
				exit(1);
			}
		}
	}
	return flag;
}

bool check_pack_size(vector<vector<vector<double> > > &Pack, double len){
	bool flag = false;
	double tol = 1e-15;
	vector<vector<vector<double> > >Face(4, vector<vector<double> > (3, vector<double>(3,0)));
	vector<vector<double> > edge(3, vector<double> (3, 0));
	for (int i = 0; i <= Pack.size() - 1; i++){
		Face = tet_face(Pack[i]);
		for (int j = 0; j <= Face.size() - 1; j++){
			for (int m = 0; m <= Face[1].size() - 1; m++){
				edge[0][m] = Face[j][0][m] - Face[j][1][m];
				edge[1][m] = Face[j][0][m] - Face[j][2][m];
				edge[2][m] = Face[j][1][m] - Face[j][2][m];
			} // end loop m
			for (int k = 0; k <= edge.size() - 1; k++){
				if ( abs(magnitude(edge[k]) - len) > tol ){
					flag = true;
					printf("ERROR: Some of the tetrahedra are not equivalent!!\n");
					exit(1);
				}
			} // loop k
		} // loop j
	} // lopp i
	return flag;
}

vector<vector<vector<double> > > packing(double len, int N_tet){
	vector<vector<double> > Tri(3, vector<double>(3));
	vector<vector<double> > Tet(4, vector<double>(3));
	vector<vector<double> > N(2, vector<double>(3));
	vector<vector<vector<double> > > Pack(N_tet, 
	vector<vector<double> > (4, vector<double>(3)));
	vector<vector<vector<double> > >Face(4, 
	vector<vector<double> > (3, vector<double>(3)));

	// Base equilateral triangle
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
	return Pack;
}
