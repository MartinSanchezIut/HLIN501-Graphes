#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

const int N=20;
const int M=(N*(N-1))/2;
  
typedef struct coord{int abs; int ord;} coord;

void pointRandom(int n,coord point[]) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		point[i].abs = rand()%613 ; 
		point[i].ord = rand()%793 ; 
	}
}

int carre(int n) {	return n * n; }
float distance(coord p1,coord p2) {
	return sqrt(  carre(p1.abs - p2.abs) + carre(p1.ord - p2.ord)  ) ;
}


void voisins(int n, int dmax,coord point[], vector<int> voisin[], int &m) {
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)	{
			if ((j != i) && distance(point[i], point[j]) < dmax ) {
				voisin[i].push_back(j) ;
				m++;
			}
		}
	}
}


void voisins2arete(int n,vector<int>voisins[],int arete[][2]) {
	int count = 0;
	for (int i = 0; i < n; ++i)	{
		for (int j = 0; j < voisins[i].size(); ++j){
			arete[count][0] = i;
			arete[count][1] = voisins[i].at(j);
			count++;
		}
	}

}



void affichageGraphique(int n,int m,coord point[],int arete[][2],string name) {
	ofstream output;                           
	output.open(name + ".ps",ios::out);
	output << "%!PS-Adobe-3.0" << endl;
	output << "%%BoundingBox: 0 0 612 792" << endl;
	output << endl;

	for(int i=0;i<n;i++){
		output << point[i].abs << " " << point[i].ord << " 5 0 360 arc" <<endl;
		output << "0 setgray" <<endl;
		output << "fill" <<endl;
		output << "stroke"<<endl;
		output << endl;
	}
	output << endl;

	for(int i=0;i<m;i++){
		//cout << arete[i][0] << " " << arete[i][1] << endl;

		/*
		cout << i << " : ";
		cout << point[arete[i][0]].abs << " " << point[arete[i][0]].ord << "  ->  "  ;
		cout << point[arete[i][1]].abs << " " << point[arete[i][1]].ord << endl ;
		*/

		output << point[arete[i][0]].abs << " " << point[arete[i][0]].ord << " moveto" << endl;
		output << point[arete[i][1]].abs << " " << point[arete[i][1]].ord << " lineto" << endl;
		output << "stroke" << endl;
		output << endl;
	}
	
	output << "showpage";
	output << endl;
}



bool existe(int n,int dis[],bool traite[],int &x);

void dijkstra(int n,vector<int> voisin[],coord point[],int pere[]);

int construireArbre(int n,int arbre[][2],int pere[]);


int main() {
  int n = N;                           // Le nombre de points.
  cout << "Entrer le nombre de points: "; cout << endl;
  //cin >> n; 
  
  int dmax=50;                     // La distance jusqu'a laquelle on relie deux points.
  
  coord point[N];                  // Les coordonnees des points.
  vector<int> voisin[N];           // Les listes de voisins.          
  
  int arbre[N-1][2];               // Les aretes de l'arbre de Dijkstra.
  int pere[N];                     // La relation de filiation de l'arbre de Dijkstra.
  
  int m = 0;                           // Le nombre d'arete
  int arete[M][2];                 // Les aretes du graphe

  pointRandom(N, point) ;
  for (int i = 0; i < N; ++i)  {
  	cout << "Point " << i << " : " << point[i].abs << " - " << point[i].ord << endl;
  }

  voisins(N, dmax, point, voisin, m);
  cout << "Nombre d'arretes " << m << endl;
  for (int i = 0; i < N; ++i)  {
  	cout << "Voisins de " << i << " : " << endl;

  	for (int j = 0; j < voisin[i].size(); ++j) {
  		cout << "  & " << voisin[i].at(j) << endl;
  	}

  }


  voisins2arete(n, voisin, arete) ;
  for (int i = 0; i < m / 2; ++i)  {
  	cout << arete[i][0] << " - " << arete[i][1] << endl;	
  }

  affichageGraphique(n, m/2, point, arete , "Test") ;

  return EXIT_SUCCESS;
}