#include "Triangle_collusion.h"
int main()
{
double PS[10000][3][3];
double QS[10000][3][3];
double EPS[10000][2][3];
double EQS[10000][2][3];

	int i;
	int j;
	int k;
	int t_1 = clock();
	srand(t_1);
	for(i=0; i<10000; i++){
		for(j=0; j<3; j++){
			for(k=0; k<3; k++){
				PS[i][j][k] =  drand48();
				QS[i][j][k] = drand48();
			}
		}
		for(j=0; j<2; j++){
			for(k=0; k<3; k++){
				EPS[i][j][k] = PS[i][j+1][k] - PS[i][0][k];
				EQS[i][j][k] = QS[i][j+1][k] - PS[i][0][k];
			}
		}
	}
//	double sum=0;
	int t0 = clock();
	int sums[100]={0};
for(j=0; j<1000; j++)
	for(i=0; i<10000; i++){
		int res = tr_tri_intersect3D(PS[i][0],EPS[i][0],EPS[i][1],
							QS[j][0],EQS[j][0],EQS[j][1]);
		sums[res]++;
	}
	int t1 = clock();
	printf(" time %d %d\n",t0-t_1,t1-t0);
	for(i=0; i<100; i++){
		if(sums[i]!=0)printf("%d %d\n",i,sums[i]);
	}
	return 0;
}
