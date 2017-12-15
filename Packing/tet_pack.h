#include <vector>
#include <math.h>
using namespace std;

// Add a tetrahedron to the pack
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

// Initialize the pack with the base regular tetrahedron
vector<vector<vector<double> > > pack_init(vector<vector<double> > &Tet, vector<vector<vector<double> > > &Pack){
	for (int j = 0; j <= Tet.size() - 1; j++){
		for (int i = 0; i <= Tet[1].size() - 1; i++){
			Pack[0][j][i] = Tet[j][i];
		}
	}
	return Pack;
}

// Check if there is any collision between the tetrahedra in the final pack
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

// Check if there is any irregular tetrahedra or non-equivalent one in the pack
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

// Packing scheme based on bipyramid progagation
vector<vector<vector<double> > > packing(double len, int N_tet){
	vector<vector<double> > Tri(3, vector<double>(3));
	vector<vector<double> > Tet(4, vector<double>(3));
	vector<vector<double> > N(2, vector<double>(3));
	vector<vector<vector<double> > > Pack(N_tet, 
	vector<vector<double> > (4, vector<double>(3)));
	vector<vector<vector<double> > >Face(4, 
	vector<vector<double> > (3, vector<double>(3)));

	// packing initialization
	Tri = init_tri(len); // generate the initial triangle
	N = find_vertex(Tri); // find the possible 4th vertex for regular tetrahedra
	Tet = tet_gen(Tri, N[0]);
	Pack = tet_pack(Tet, Pack); // Initialize the packing
	int tet_add = 0;
	bool tet_pass = true;

	// packing optimization scheme
	while (tet_add <= N_tet - 1){ // continue the packing until enough tetrahedra are added
		for (int k = 0; k <= Pack.size() - 1; k++){
			Face = tet_face(Pack[k]); // find faces of the tetrahedron
			for (int j = 0; j <= Face.size() - 1; j++){
				Tri = Face[j];
				N = find_vertex(Tri); // find the possible 4th vertex for regular tetrahedra
				for (int i = 0; i <= N.size() - 1; i++){
					Tet = tet_gen(Tri, N[i]); // generate new bipyramid tetrahedra
					tet_pass = true;
					for (int m = 0; m <= tet_add; m++){ // check for collision between new object and the pack
						if (is_tet_col(Tet, Pack[m])){
							tet_pass = false;
							m = tet_add + 1;
						}
					}
					if (tet_pass){ // If check passes, add the tetrahedron to the pack
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
	return Pack; // return the final packing
}
