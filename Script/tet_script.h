#include <vector>
#include <math.h>
using namespace std;

int write_basis(){
	vector<vector<double> > Base(3, vector<double>(3,0));
	for (int i = 0; i <= Base.size() - 1; i++){
		Base[i][i] = 1;
	}
	for (int j = 0; j <= Base.size() - 1; j++){
		for (int i = 0; i <= Base[1].size() - 1; i++){
			printf("%8.4f ", Base[j][i]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int write_tet(vector<vector<double> > &Tet){
	for (int j = 0; j <= Tet.size() - 1; j++){
		for (int i = 0; i <= Tet[1].size() - 1; i++){
			printf("%f ", Tet[j][i]);
		}
		if (j < Tet.size() - 1)
		printf(", ");
	}
	printf("\n");
	return 0;
}

int write_pack(vector<vector<vector<double> > > &Pack){
	for (int k = 0; k <= Pack.size() - 1; k++){
		for (int j = 0; j <= Pack[1].size() - 1; j++){
			for (int i = 0; i <= Pack[1][1].size() - 1; i++){
				printf("%8.4f ", Pack[k][j][i]);
			}
//			if (j < Pack[1].size() - 1)
//			printf(", ");
		}
	printf("\n");
	}
	printf("\n");
	return 0;
}

int write_tet_face(vector<vector<vector<double> > >Face){
	for (int k = 0; k <= Face.size() - 1; k++){
		for (int j = 0; j <= Face[1].size() - 1; j++){
			for (int i = 0; i <= Face[1][1].size() - 1; i++){
				printf("%f ", Face[k][j][i]);
			}
			if (j < Face[1].size() - 1)
			printf(",");
		}
		printf("\n");
	}
	return 0;
}


