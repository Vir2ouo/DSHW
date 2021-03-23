
#include <iostream>
using namespace std;

#define MAX_TERMS 10

typedef struct{
	int coef;
	int expo;
} polynomialTerm;

void clear(polynomialTerm t[]) 
{
	for ( int i = 0; i < MAX_TERMS; i++ ) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void printArrayBasedPoly(polynomialTerm t[])
{
	if ( t[0].coef == 0 ) 
		return;

	if ( t[0].expo == 0 )
		cout << t[0].coef;
	else
		cout << t[0].coef << "X^" << t[0].expo;

	for ( int i = 1; i < MAX_TERMS; i++ ) {
		if ( t[i].coef == 0 ) 
			return;

		if ( t[i].expo == 0 )
			cout << " + " << t[i].coef;
		else
			cout << " + "<< t[i].coef  << "X^" << t[i].expo;
	}
}

void inputTerm(polynomialTerm t[], int coef, int expo)
{
	if (coef == 0 && expo != 0)
	{
		return;
	}
	if (t[0].coef == 0 && t[0].expo == 0)  //若首項為空 直接放入
	{
		t[0].coef = coef;
		t[0].expo = expo;
		return;
	}
	for (int i = 0; i < MAX_TERMS; i++)
	{
		if (t[i].expo == expo && t[i].coef!=0) //重複次方項覆蓋(加上係數判斷以區別初始0值)
		{
			t[i].coef = coef;
			break;
		}
		else if (t[i].expo < expo && expo!=0) //插入不為常數的項
		{
			for (int j = MAX_TERMS - 2; j >= i; j--)
			{
				t[j + 1].coef = t[j].coef;
				t[j + 1].expo = t[j].expo;
			}
			t[i].coef = coef;
			t[i].expo = expo;
			return;
		}
	}
	if (coef != 0 && expo == 0) //放入常數項
	{
		for (int i = 0; i < MAX_TERMS; i++)
		{
			if (t[i].coef == 0 && t[i].expo == 0)
			{
				t[i].coef = coef;
				break;
			}
		}
	}
	return;
}

void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{
	//條件:遇到同次方數要加減
	int i = 0;
	int j = 0;
	int k = 0;
	while (k < MAX_TERMS)
	{
		if (a[i].coef == 0 && a[i].expo == 0 && b[j].coef == 0&& b[j].expo == 0)
		{
			break;
		}
		else if (a[i].expo == b[j].expo)
		{
			if (a[i].coef + b[j].coef != 0)
			{
				d[k].coef = a[i].coef + b[j].coef;
				d[k].expo = a[i].expo;
				i++;
				j++;
				k++;
			}
			else
			{
				i++;
				j++;
			}
		}
		else if (a[i].expo > b[j].expo)
		{
			d[k].coef = a[i].coef;
			d[k].expo = a[i].expo;
			i++;
			k++;
		}
		else if(a[i].expo < b[j].expo)
		{
			d[k].coef = b[j].coef;
			d[k].expo = b[j].expo;
			j++;
			k++;
		}
	}
	return;
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	int coef, expo;

	while (1) {
		clear( a ); clear( b ); clear( d );

		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerm( a, coef, expo );
		}

		cout << "\n\na = ";
		printArrayBasedPoly( a );
		cout << "\n";
		
		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerm( b, coef, expo );
		}

		cout << "\n\nb = ";
		printArrayBasedPoly( b );
		cout << "\n";

		// d =a + b, where a, b, and d are polynomials
		addArrayBasedPoly( a, b, d );
		cout << "\na + b = ";
		printArrayBasedPoly( d );
		cout << "\n";
	}

	return 0;
}
