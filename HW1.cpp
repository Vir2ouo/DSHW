
#include <iostream>
#include <string>

using namespace std;

void input(string sMessage, string &sInputString)
{
	cout << sMessage << endl;
	cin >> sInputString;

	return;
}

void writeBackwardI(string s)
{
	int length = s.size();

	if ( length == 0 )  // base case 
		return;

	for ( int i = length - 1; i >= 0; i-- )
		cout << s[i];
}

void writeBackwardR1(string s)
{
	int length = s.size();

	if ( length == 0 )  // base case 
		return;

	cout << s[length - 1];
	writeBackwardR1( s.substr( 0, length - 1 ) );
}

void writeBackwardR2(string s)
{
	int length = s.size();

	if ( length == 0 )  // base case 
		return;

	writeBackwardR2( s.substr( 1, length - 1 ) );
	cout << s[0];
}


int countI(string s, char c)
{
	int length = s.size();
	int i, tol = 0;
	for (i = 0; i < length - 1; i++)
	{
		if (s[i] == c)
		{
			tol++;
		}
	}

	return tol;
}

int countR(string s, char c)
{
	int length = s.size();
	if (length == 0)
	{
		return 0;	
	}
	else 
	{
		if (s[length - 1] == c)
		{
			return 1 + countR(s.substr(0, length - 1), c);
		}
		else 
			return countR(s.substr(0, length - 1), c);
	}
	
}

unsigned char findI(string s)
{
	int length = s.size();
	char min;
	int i;
	min = s[0];
	for (i = 0; i < length - 1; i++)
	{
		if (s[i] < min)
		{
			min = s[i];
		}
	}
	s[0] = min;
	return s[0];
}

char findR(string s)
{
	char c;
	int length = s.size();
	if (length == 1)
	{
		return s[0];
	}
	else
	{
		c = findR(s.substr(1, length - 1));
		if (s[0] < c)
		{
			return s[0];
		}
		else
		{
			return c;
		}
	}
}

string removeI(string s)
{
	int length = s.size();
	string str = "";
	if (length < 2)
	{
		return s;
	}
	for (int i = 0; i < length; i++)
	{
		if (s[i] != ' ')
		{
			str += s[i];
			if (s[i] == s[i + 1])
			{
				s[i + 1] = ' ';
			}
		}
	}
	return str;
}

string removeR(string s)
{
	string t;
	int length = s.size();
	
	if (length == 1)
	{
		return s;
	}

	t = removeR(s.substr(1, length - 1));
	if (t[0] == s[0])
	{
		return t;
	}
	else
	{
		return s[0] + t;
	}
	
}

int TI( int m, int n)
{
	int tol = 0;
	
	if (m == 0 || n == 0)
	{
		return 0;
	}
	else if (m > n)
	{
		for (int i = 1; i <= n; i++)
		{
			tol += m;
		}
	}
	else
	{
		for (int i = 1; i <= m; i++)
		{
			tol += n;
		}
	}
	return tol;
	
/* 
	T(m, n) = 0, if m = 0 or n = 0
	T(m, n) = m + ... + m (n times), if m > n
	T(m, n) =  n + ... + n (m times), otherwise
*/
}

int TR( int m, int n)
{
	
	if (m == 0 || n == 0)
	{
		return 0;
	}
	else if (m > n)
	{
		if (n == 1)
		{
			return m;
		}
		else
		{
			return m + TR(m, n - 1);
		}
	}
	else
	{
		if (m == 1)
		{
			return n;
		}
		else
		{
			return n + TR(m-1, n);
		}
	}
/*
	T(m, n) = 0, if m = 0 or n = 0
	T(m, n) = m + T( m, n - 1 ), if m > n
	T(m, n) =  n + T( m - 1, n ), otherwise
*/
}

int main()
{
	string commandStr;	
	string inputStr, appendStr;
	char inputChr;
	int m, n;

	while (1) {
		input( "\nEnter command: "
			"\n I to input a string, A to append a string, B to write the string backward, "
			"\n C to count the given character , F to find the smallest character,"
			"\n R to remove the repeated characters, T to compute, and X to Exit", commandStr );
	
		if ( commandStr == "I"  || commandStr == "i" ) {
			cout << "\nInput the string: ";
			cin >> inputStr;
		} 
		else if ( commandStr == "A"  || commandStr == "a" ) {
			cout << "\nInput the string: ";
			cin >> appendStr;
			inputStr += appendStr;
			cout << "\nThe new string: " << inputStr << endl;
		} 
		else if ( commandStr == "B" || commandStr == "b" ) {
			if ( inputStr.length() > 0 ) {
				cout << endl;
				writeBackwardI( inputStr );
				cout << endl;
				writeBackwardR1( inputStr );
				cout << endl;
				writeBackwardR2( inputStr );
				cout << endl;
			}
		}
		else	if ( commandStr == "C"  || commandStr == "c" ) {
			if ( inputStr != "" ) {
				cout << "\nInput the character: ";
				cin >> inputChr;
				cout << "\nCount of " << inputChr <<": " << countI( inputStr, inputChr );
				cout << "\nCount of " << inputChr <<": " << countR( inputStr, inputChr ) << endl;
			}
		}
		else if ( commandStr == "R" || commandStr == "r" ) {
			if ( inputStr != "" ) {
				cout << endl << "Repeated characters removed: " << removeI( inputStr ) ;
				cout << endl << "Repeated characters removed: " << removeR( inputStr ) << endl;;
			}
		}
		else if ( commandStr == "F" || commandStr == "f" ) {
			if ( inputStr != "" ) {
				cout << endl << "Smallest character found: " << findI( inputStr );
				cout << endl << "Smallest character found: " << findR( inputStr ) << endl;
			}
		}
		else  if ( commandStr == "T" || commandStr == "t" ) 
		{
			cout << "\nInput two values, m and n: ";
			cin >> m >> n;
			cout << endl << "The result is " << TI( m, n );
			cout << endl << "The result is " << TR( m, n ) << endl;
		}
		else  if ( commandStr == "X" || commandStr == "x" ) 
			return 0;	
		else
			cout << "\nUnknown command!";
	}
  	return 0;
}
