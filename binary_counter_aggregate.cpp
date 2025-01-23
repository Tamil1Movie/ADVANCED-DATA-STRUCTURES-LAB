
#include<iostream>
using namespace std;
int main()
{
	int size;
	int limit;
	cout<<"Enter number of bits and limit:";
	cin>>size>>limit;
	int bits[size]={0};
	int cost=0;
	cout<<"Binary"<<"  "<<"Cost"<<endl;
	for(int i=0;i<=limit;i++)
	{
	    for(int j=size-1;j>=0;j--)
	    {
		    cout<<bits[j];
	    }
	    cout<<"    "<<"Cost:"<<cost;
	    cout<<endl;
		int carry=1;
	    for(int j=0;j<size,carry==1;j++)
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
	}
	cout<<"Amortized cost="<<cost-1;
	return 0;
}
