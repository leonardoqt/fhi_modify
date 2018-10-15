#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstring>

using namespace std;

int main()
{
	string tmp;
	double ttt;
	ifstream input;
	ofstream output;
	int num_orb, *num_coef, num_grid;
	double *rc, **v_coef;
	double rr,psi,vv;
	int index;
	const double pi=3.1415926535897932384626;


	// find psp file name
	cin>>tmp;
	input.open(tmp);
	output.open(tmp+".DAT");

	// get number of orbitals
	input>>ttt>>num_orb;
	output<<setw(13)<<setprecision(9)<<fixed<<ttt<<setw(5)<<num_orb<<endl;

	// get rc of each orbital
	rc = new double[num_orb];
	for (int t1=0; t1<num_orb; t1++)
		cin>>rc[t1];
	
	// get coefficients in dV from input file
	v_coef = new double*[num_orb];
	num_coef = new int[num_orb];
	for (int t1=0; t1<num_orb; t1++)
	{
		cin>>num_coef[t1];
		v_coef[t1] = new double[num_coef[t1]];
		for (int t2=0; t2<num_coef[t1]; t2++)
			cin>>v_coef[t1][t2];
	}

	// skip the first a few rows
	getline(input,tmp);
	for (int t1=0; t1<10; t1++)
	{
		getline(input,tmp);
		output<<tmp<<endl;
	}
	
	// read and modify psp
	for (int t1=0; t1<num_orb; t1++)
	{
		// get number of grid points
		input>>num_grid>>ttt;
		output<<setw(5)<<num_grid<<setw(25)<<setprecision(15)<<scientific<<ttt<<endl;
		for (int t2=0; t2<num_grid; t2++)
		{
			input>>index>>rr>>psi>>vv;
			getline(input,tmp);
			if (rr < rc[t1])
				for (int t3=0; t3<num_coef[t1]; t3++)
					vv += v_coef[t1][t3]*cos((t3+0.5)*rr/rc[t1]*pi);
			output<<setw(5)<<index<<setw(25)<<setprecision(15)<<scientific<<rr<<setw(25)<<setprecision(15)<<scientific<<psi<<setw(25)<<setprecision(15)<<scientific<<vv<<endl;
		}
	}

	while(!input.eof())
	{
		getline(input,tmp);
		output<<tmp<<endl;
	}
	output.close();
	input.close();
	return 0;
}
