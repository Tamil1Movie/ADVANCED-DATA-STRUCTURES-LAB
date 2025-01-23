#include<iostream>
using namespace std;
int main()
{
    int size;
    int limit;
    cout << "Enter number of bits and limit: ";
    cin >> size >> limit;
	int bits[4]={0};
	int cost=0;
	 int amortizedCost = 0;
    int potentialBefore = 0, potentialAfter = 0;
    int potentialDifference=0;
	cout<<"Binary"<<"\t\t"<<"Acutal Cost"<<"\tfi(Di)"<<"\t\tfi(Di-1)"<<"\tPotentialDifference"<<"\t\t\tAmortized cost"<<endl;
	for (int j = size - 1; j >= 0; j--) 
	{
        cout << bits[j];
    }
    cout << "\t\t0 flips" << "\t\t"<<potentialBefore
         << "\t\t"<<potentialAfter
         << "\t\t"<<potentialDifference
         << "\t\t\t\t\t\t" <<amortizedCost
         << endl;
	for(int i=0;i<limit;i++){
		int carry=1;
		int cost=0;
	for(int j=0;j<size&&carry==1;j++)
	{
		if(bits[j]==0)
		{
			bits[j]=1;
			carry=0;
			cost++;
		}
		else
		{
			bits[j]=0;
			carry=1;
			cost++;
		}
	}
	 potentialBefore = potentialAfter;
	  potentialAfter = 0;
        for (int j = 0; j < size; j++) {
            if (bits[j] == 1) {
                potentialAfter++;
            }
        }
    int potentialDifference = potentialAfter - potentialBefore;
        amortizedCost = cost + potentialDifference;
	for(int j=size-1;j>=0;j--)
	{
		cout<<bits[j];
	}
	cout<<"\t\t"<<cost<<" flips"
             << "\t\t" << potentialAfter
             << "\t\t" << potentialBefore
             << "\t\t" << potentialDifference
             << "\t\t\t\t\t\t"<<amortizedCost
             << endl;
	cout<<endl;
	}
	cout<<"Amortized cost="<<amortizedCost*limit<<endl;
	return 0;
}
