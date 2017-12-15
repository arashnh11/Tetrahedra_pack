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
