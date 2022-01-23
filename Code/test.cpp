#include<iostream>
using namespace std;

double fractionSum(int u)
{
	double sum = 0;
	for (int i = 1; i <= u; ++i)
	{
		double sgn = i % 2 == 0 ? -1 : 1;
		sum += sgn * 1.0 / double(i);
	}
	return sum;
}


int main() {

	cout << fractionSum(4) << endl;
	system("pause");
	return 0;
}