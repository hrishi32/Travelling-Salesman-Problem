/*
Made by
Hrishikesh Sagar B16029
Hrishikesh Sarode B16032


*/


#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <limits>

using namespace std;

double probablity(double currentEnergy, double newEnergy, double temperature)
{
	int delta=newEnergy- currentEnergy;
	if(newEnergy<currentEnergy)
		return 1;
	else 
		return (double) 1/( (double) 1.0 + (double)exp(  (delta)/temperature ));
}


int ranFunc (int i) { return (rand()*time(0)+1) % i; }

int main(int argc, char const *argv[])
{
	/* code */
	/*********Read input  start********/
	bool eucFlag=true;
	string typ;
	cin>>typ;
	if(typ=="euclidean")
		eucFlag=true;
	else
		eucFlag=false;

	int N;
	cin>>N;

	double distance[N][N];

	double coordinates[N][2];
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			cin>>coordinates[i][j];//i is row and j is column
		}
	}
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin>>distance[i][j];//i is row and j is column
		}
	}
	/*********Read input END********/

	/**************Start initialising stuff**********/
	double temperature=100000000;
	double coolingRate=0.05;

	int n=N;

	vector<int> currState(n);

	for (int l = 0; l < n; ++l)//generatin random state
		currState[l]=l;	

	// random_shuffle(currState.begin(), currState.end(), ranFunc); 

	double currentEnergy=0;
	for (int l = 0; l < n-1; ++l)//generatin random state
		currentEnergy+=distance[currState[l]][currState[l+1]];
	currentEnergy+=distance[currState[n-1]][currState[0]];
	double newEnergy;


	double bestEnergy = currentEnergy;
	vector<int> bestState(currState);

	double delta=0;

	while(1)
	{
		temperature=	100000000;//found maximum at 10^18

						// currState=bestState;
						// currentEnergy=0;
						// for (int l = 0; l < n-1; ++l)//generatin random state
						// 	currentEnergy+=distance[currState[l]][currState[l+1]];
						// currentEnergy+=distance[currState[n-1]][currState[0]];
		/**************END initialising stuff**********/
		//[TO DO] add iterations for the whole temperature variance(from high to low)
		while(temperature>1)
		{
			
			//[TO DO] generate proper random cities
			//shifting cities in current state on indices city1 and city2
			int iterations=100*n;
			if(n>255)
				iterations=100*250;
			while(iterations--)
				{
				vector<int> newState(currState);


				


				int i=ranFunc(n);
					int j=ranFunc(n);

					while(i==j)
						i=ranFunc(n);
					int tmp=newState[i];
				newState[i]=newState[j];
				newState[j]=tmp;
					delta= distance[currState[j]][currState[(i+1)%n]] + distance[currState[(i-1+n)%n]][currState[j]] + distance[currState[i]][currState[(j+1)%n]] + distance[currState[(j-1+n)%n]][currState[i]];
					delta -= ( distance[currState[i]][currState[(i+1)%n]] + distance[currState[(i-1+n)%n]][currState[i]] + distance[currState[j]][currState[(j+1)%n]] + distance[currState[(j-1+n)%n]][currState[j]] );
					newEnergy=currentEnergy+delta;
					if(abs(i-j)==1 || i==0 || i==n-1 || j==0 || j==n-1)
					{
						// find currState length for neighbour node
						newEnergy=0;
						for (int k = 0; k < n-1; ++k)
							newEnergy+=distance[newState[k]][newState[k+1]];
						newEnergy+=distance[newState[n-1]][newState[0]];
					}
				double p=probablity(currentEnergy,newEnergy,temperature);
				if(p > (double) rand()/  (double) RAND_MAX)
				{
					// cout<<"acceptin p"<<endl;
					currState=newState;
					currentEnergy=newEnergy;
				}


				if(bestEnergy>currentEnergy)
				{
					bestState=currState;
					bestEnergy=currentEnergy;

					for (int k = 0; k < n-1; ++k)
						cout<<bestState[k]<<" ";
					cout<<bestState[n-1]<<endl;

				}
				

			}
			temperature=temperature*(1- coolingRate );//1-coolingRate
			// cout<<"new bestEnergy: "<<bestEnergy<<"Temperature: "<<temperature<<endl;
		}
}

	return 0;
}