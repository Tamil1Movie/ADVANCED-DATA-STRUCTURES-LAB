#include<iostream>
using namespace std;
int main()
{
	int size=3;
	int bits[3]={0};
	for(int j=size-1;j>=0;j--)
	{
		cout<<bits[j];
	}
	cout<<endl;
	for(int i=0;i<7;i++){
		int carry=1;
	for(int j=0;j<size&& carry==1;j++)
	{
		if(bits[j]==0)
		{
			bits[j]=1;
			carry=0;
		}
		else
		{
			bits[j]=0;
			carry=1;
		}
	}
	for(int j=size-1;j>=0;j--)
	{
		cout<<bits[j];
	}
	cout<<endl;
	}
	return 0;
}

OUTPUT:
000
001
010
011
100
101
110
111

