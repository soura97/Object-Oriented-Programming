#include<iostream>
#include<cstdlib>
using namespace std;

class pascal
{
	int n,k;
	public:
	int binomialCoeff(int n, int k)		//function to calculate binomial coefficient
	{
	    if(k>n) return 0;
	    int res = 1;
	    if (k > n - k)
	       k = n - k;
	    for (int i = 0; i < k; ++i)
	    {
	        res *= (n - i);
	        res /= (i + 1);
	    }
	    return res;
	}
	
	void printPascal(int n)			//function to print Pascal's triangle for n rows
	{
	
	  for (int line = 0; line < n; line++)
	  {
	    	for(int j=0;j<n-1-line;j++)
		{
			cout<<" ";
		}
		for (int i = 0; i <= line; i++)
		{
			cout<<" "<<binomialCoeff(line, i);
		}      
	    printf("\n");
	  }
	}
 
};

 

int main()
{
	int c,n,k;
	pascal p;
	do {
		cout << endl << "MENU:" << endl << endl << "0 Exit" << endl
			<< "1 Display n c k" << endl
			<< "2 Print first n rows" << endl
			<< endl << "Enter operation code: ";
		cin>>c;
		switch(c) {
				case 0: cout << "Exiting program" << endl; break;
				case 1: cout<<"Enter n and k"<<endl;
					cin>>n>>k;
					printf("%d",p.binomialCoeff(n,k));break;
				case 2: cout<<"Enter n"<<endl;
					cin>>n;
					p.printPascal(n);break;
				default:break;
			}
	} while(c);
	
 	return 0;
}
