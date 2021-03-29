#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

typedef struct{
	int coef;
	int expo;
} polynomialTerm;

typedef struct linkedTerm {
	int coef;
	int expo;
	linkedTerm *nextTermPtr;
} linkedPolynomialTerm;

void clear(polynomialTerm t[]) 
{
	for ( int i = 0; i < MAX_TERMS; i++ ) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void clear(linkedPolynomialTerm *&polynomialTermPtr) 
{
	linkedPolynomialTerm *tmpPtr;

	while ( polynomialTermPtr != nullptr ) {
		tmpPtr = polynomialTermPtr;
		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		delete tmpPtr;
	}
}

void inputTerms(polynomialTerm terms[], int coef, int expo)
{
	int door = 1;
	if (coef == 0 && expo == 0)
	{
		return;
	}
	if (terms[0].coef == 0 && terms[0].expo == 0 && coef != 0)
	{
		terms[0].coef = coef;
		terms[0].expo = expo;
		return;
	}
	for (int i = 0; i < MAX_TERMS; i++)
	{
		if (terms[i].expo == expo) 
		{
			if (coef == 0) 
			{
				for (int j = i; j < MAX_TERMS - 1 ; j++)
				{
					terms[j].coef = terms[j + 1].coef;
					terms[j].expo = terms[j + 1].expo;
				}
			}
			else
			{
				terms[i].coef = coef;
				door = 0;
			}
			break;
		}
		else if (terms[i].expo < expo && terms[i].coef != 0 && coef != 0)
		{
			for (int j = MAX_TERMS - 2; j >= i; j--)
			{
				terms[j + 1].coef = terms[j].coef;
				terms[j + 1].expo = terms[j].expo;
			}
			terms[i].coef = coef;
			terms[i].expo = expo;
			door = 0;
			break;
		}
	}
	if (coef != 0 && door==1)
	{
		for (int i = 0; i < MAX_TERMS; i++)
		{
			if (terms[i].coef == 0 && terms[i].expo == 0)
			{
				terms[i].coef = coef;
				terms[i].expo = expo;
				break;
			}
		}
	}
	return;
}

void inputLinkTerms(linkedPolynomialTerm *&polyPtr, int coef, int expo)
{
	linkedPolynomialTerm *tmpPtr, *head, *current, *prePtr, *diePtr;
	
	tmpPtr = new linkedPolynomialTerm;
	tmpPtr->coef = coef ;
	tmpPtr->expo = expo;
	tmpPtr->nextTermPtr = nullptr;

	if (polyPtr == nullptr && coef != 0)
	{
		polyPtr = tmpPtr;
	}
	else if (polyPtr != nullptr)
	{
		head = polyPtr; //保留第一個位置
		current = polyPtr; //跑動仔
		prePtr = polyPtr; //跑動仔的媽
		int door = 1;

		if (head->expo == expo) //第一項就是要更動的節點
		{
			if (coef == 0) //覆蓋後係數為0則刪除該節點
			{
				polyPtr = polyPtr->nextTermPtr;
				delete head;
				door = 0;
			}
			else
			{
				polyPtr->coef = tmpPtr->coef;
				door = 0;
			}
		}
		else if (head->expo < expo) //插頭
		{
			tmpPtr->nextTermPtr = polyPtr;
			polyPtr = tmpPtr;
			door = 0;
		}
		while (door == 1 && current != nullptr)
		{
			if (current->expo == expo) //中間項覆蓋
			{
				if (coef == 0)
				{
					if (current->nextTermPtr == nullptr) //覆蓋最後一項
					{
						delete current;
						prePtr->nextTermPtr = nullptr;
						door = 0;
					}
					else
					{
						diePtr = current;
						prePtr->nextTermPtr = current->nextTermPtr;
						current = current->nextTermPtr;
						delete diePtr;
						door = 0;
					}
				}
				else
				{
					current->coef = coef;
					prePtr = current;
					current = current->nextTermPtr;
					door = 0;
				}
			}
			else if (current->expo < expo) //中間項插入
			{
				tmpPtr->nextTermPtr = current;
				prePtr->nextTermPtr = tmpPtr;
				prePtr = current;
				current = current->nextTermPtr;
				door = 0;
			}
			else
			{
				prePtr = current;
				current = current->nextTermPtr;
			}
		}
		if (door == 1)
		{
			current = tmpPtr;
			prePtr->nextTermPtr = current;
		}
	}
		return;
}


void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < MAX_TERMS && j< MAX_TERMS)
	{
		if (a[i].coef == 0 && a[i].expo == 0 && b[j].coef == 0 && b[j].expo == 0) //兩陣列為空
		{
			return;
		}
		if (a[i].expo == b[j].expo)
		{
			d[k].coef = a[i].coef + b[j].coef;
			if (d[k].coef == 0)
			{
				i++;
				j++;
			}
			else
			{
				d[k].expo = a[i].expo;
				i++;
				j++;
				k++;
			}
		}
		else if(a[i].expo > b[j].expo)
		{
			d[k].coef = a[i].coef;
			d[k].expo = a[i].expo;
			i++;
			k++;
		}
		else
		{
			d[k].coef = b[j].coef;
			d[k].expo = b[j].expo;
			j++;
			k++;
		}
	}
	while (i < MAX_TERMS)
	{
		if (a[i].coef == 0 && a[i].expo == 0)
		{
			break;
		}
		else
		{
			d[k].coef = a[i].coef;
			d[k].expo = a[i].expo;
			i++;
			k++;
		}
	}
	while (j < MAX_TERMS)
	{
		if (b[j].coef == 0 && b[j].expo == 0)
		{
			break;
		}
		else
		{
			d[k].coef = b[j].coef;
			d[k].expo = b[j].expo;
			j++;
			k++;
		}
	}
	return;
}

linkedPolynomialTerm *addLinkBasedPoly(linkedPolynomialTerm *aPtr, linkedPolynomialTerm *bPtr)
{
	linkedPolynomialTerm* curra, * currb,  *currd, *tmpPtr , *head;
	linkedPolynomialTerm* dPtr = nullptr;
	curra = aPtr;
	currb = bPtr;
	currd = dPtr;
	while (curra != nullptr && currb != nullptr)
	{
		int door = 1;

		tmpPtr = new linkedPolynomialTerm;
		tmpPtr->coef = 0;
		tmpPtr->expo = 0;
		tmpPtr->nextTermPtr = nullptr;
		if (curra->expo == currb->expo)
		{
			if (curra->coef + currb->coef == 0)
			{
				door = 0;
				curra = curra->nextTermPtr;
				currb = currb->nextTermPtr;

			}
			else
			{
				tmpPtr->coef = curra->coef + currb->coef;
				tmpPtr->expo = curra->expo;
				curra = curra->nextTermPtr;
				currb = currb->nextTermPtr;
			}
		}
		else if (curra->expo > currb->expo)
		{
			tmpPtr->coef = curra->coef;
			tmpPtr->expo = curra->expo;
			curra = curra->nextTermPtr;
		}
		else
		{
			tmpPtr->coef = currb->coef;
			tmpPtr->expo = currb->expo;
			currb = currb->nextTermPtr;
		
		}

		if (dPtr == nullptr&&door==1)
		{
			dPtr = new linkedPolynomialTerm;
			dPtr = tmpPtr;
			currd = dPtr;
		}
		else if(door==1)
		{
			currd->nextTermPtr = tmpPtr;
			currd = currd->nextTermPtr;
		}
	}
	while (curra != nullptr)
	{
		tmpPtr = new linkedPolynomialTerm;
		tmpPtr->coef = curra->coef;
		tmpPtr->expo = curra->expo;
		tmpPtr->nextTermPtr = nullptr;

		if (dPtr == nullptr)
		{
			dPtr = new linkedPolynomialTerm;
			dPtr = tmpPtr;
			currd = dPtr;
			curra = curra->nextTermPtr;
		}
		else
		{
			currd->nextTermPtr = tmpPtr;
			currd = currd->nextTermPtr;
			curra = curra->nextTermPtr;
		}
	}
	while (currb != nullptr)
	{
		tmpPtr = new linkedPolynomialTerm;
		tmpPtr->coef = currb->coef;
		tmpPtr->expo = currb->expo;
		tmpPtr->nextTermPtr = nullptr;

		if (dPtr == nullptr)
		{
			dPtr = new linkedPolynomialTerm;
			dPtr = tmpPtr;
			currd = dPtr;
			currb = currb->nextTermPtr;
		}
		else
		{
			currd->nextTermPtr = tmpPtr;
			currd = currd->nextTermPtr;
			currb = currb->nextTermPtr;
		}
	}
	return dPtr;
}

void printArrayBasedPoly(polynomialTerm terms[])
{
	if ( terms[0].coef == 0 ) 
		return;

	if ( terms[0].expo == 0 )
		cout << terms[0].coef;
	else
		cout << terms[0].coef << "X^" << terms[0].expo;

	for ( int i = 1; i < MAX_TERMS; i++ ) {
		if ( terms[i].coef == 0 ) 
			return;

		if ( terms[i].expo == 0 )
			cout << " + " << terms[i].coef;
		else
			cout << " + "<< terms[i].coef  << "X^" << terms[i].expo;
	}
}

void printLinkBasedPoly(linkedPolynomialTerm *polyPtr)
{
	linkedPolynomialTerm *termPtr =  polyPtr;

	if ( termPtr  == nullptr )
			return;

	if ( termPtr->expo == 0 )
		cout << termPtr->coef;
	else
		cout << termPtr->coef << "X^" << termPtr->expo;

	termPtr  = termPtr->nextTermPtr;
	
	while ( termPtr  != nullptr ) {
		if ( termPtr->coef == 0 ) 
			return;

		if ( termPtr->expo == 0 )
			cout << " + " << termPtr->coef;
		else
			cout << " + "<< termPtr->coef  << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;
	}
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	linkedPolynomialTerm *aPtr, *bPtr, *dPtr;

	int coef, expo;

	aPtr = bPtr = dPtr = nullptr;

	while (1) {
		clear( a ); clear( b ); clear( d );
		clear( aPtr ); clear( bPtr ); clear( dPtr );

		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerms( a, coef, expo );
			inputLinkTerms( aPtr, coef, expo );
		}

		cout << "\n\na = ";
		printArrayBasedPoly( a );
		cout << "\na = ";
		printLinkBasedPoly( aPtr );
		cout << "\n";
		
		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerms( b, coef, expo );
			inputLinkTerms( bPtr, coef, expo );
		}

		cout << "\n\nb = ";
		printArrayBasedPoly( b );

		cout << "\nb = ";
		printLinkBasedPoly( bPtr );

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		addArrayBasedPoly( a, b, d );
		cout << "\na + b = ";
		printArrayBasedPoly( d );
		
		dPtr = addLinkBasedPoly( aPtr, bPtr );
		cout << "\na + b = ";
		printLinkBasedPoly( dPtr );

		cout << "\n";
	}
	return 0;
}
 