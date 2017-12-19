#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>

#define DEG 100	//for polynomials of max degree = 99

int main()
{
	std::string str;
	std::cout << "      Enter a polynomial without like terms\n";
	std::cout << "(use the letter x. for ex.: -x+4.5x^3+2x^4-3.1)\n";
	std::cout << "\nEnter: ";
	std::cin >> str;
	if(str == "") return 1;
	int strSize = str.size();
	
//	How many monomials has the polynomial?
	int k = 1;
	for(int i = 1; i < strSize; ++i)
		if(str[i] == '+' || str[i] == '-')
			k++;
 	int monoms = k ;
 	
//	Signs "+" are necessary for the string parsing 
	if(isdigit(str[0])) str.insert(0, "+");
	if(str[0] == 'x') str.insert(0, "+");
	str.append("+");
	strSize = str.size();
	
//	Extracting the monomials as monomStr
	k = 0;
	int j = 0;
	std::string monomStr[DEG];
	for(int i = 1; i < strSize; ++i)
		if(str[i] == '+' || str[i] == '-')
		{
			monomStr[k++] = str.substr(j, i - j);
			j = i;
		}

//  Monomials' formatting i.e. to have all the same form: coefficientX^exponent
	for(int i = 0; i < monoms; ++i)
	{
		if(monomStr[i][1] == 'x')	//x is after the +/- sign 
			monomStr[i].insert(1, "1");	//& gets 1 as coefficient
		bool flag = false;	// assuming that x is not present
		int len = monomStr[i].size();
		for(int j = 1; j < len; ++j)
			if(monomStr[i][j] == 'x')	//but we test this
			{
				flag = true;	//& if x is present
				if(j == len - 1)	//& is the last 
					monomStr[i].append("^1");	//it gets exponent 1
				break;	//& exit from j_loop
			}
		if(!flag)	//if x is not present: we have a constant term
			monomStr[i].append("x^0");	//who gets "formatting"
	}
	
//	Extracting the coefficients and exponents as numbers
	int expon[DEG] = {0};
	double coeff[DEG] = {0.};
	for(int i = 0; i < monoms; ++i)
	{
		int monomSize = monomStr[i].size();
		for(int j = 0; j < monomSize; ++j)
		{
			if(monomStr[i][j] == '^')
			{
				expon[i] = stoi(monomStr[i].substr(j + 1, monomSize - j));
				coeff[i] = stod(monomStr[i].substr(0, j));
				break;
			}
		}	
	}
//	Looking for the max of exponents	
	int maxExponent = 0;
	for(int k : expon)
		if(k >= maxExponent) maxExponent = k;

//	Generating the monomials of the null polynomial having degree = maxEponent
	std::string newMonom[DEG];
	for(int i = maxExponent; i >= 0; i--)
		newMonom[i] = "+0x^" + std::to_string(i);
		
//	Mixing the two polynomials: given & null		
	for(int i = monoms; i >= 0; i--)
		newMonom[expon[i]] = monomStr[i];
		
//	Creating the final(complete) form of the polynomial as finalStr	
	std::string finalStr;
	for(int i = maxExponent; i >=0; i--)
		finalStr += newMonom[i];
	std::cout << "\nComplete: " << finalStr << '\n';
	
//	Extracting( at last!..) the coefficients & exponents
//	from the final form of the given polynomial		
	int finalSize = finalStr.size();
	int start[DEG] = {0};
	int stop[DEG] = {0};
	k = 0; 
	for(int i = 0; i < finalSize; ++i)
	{
		if(finalStr.substr(i, 1) == "+" || finalStr.substr(i, 1) == "-") 
			start[k] = i;
		if(finalStr.substr(i, 1) == "x")
			stop[k++] = i;
	}
	
	std::cout << "\nCoefficients  Exponents\n";
	std::cout << "-----------------------\n";
	for(int i = 0; i < k; ++i)
	{
		coeff[i] = stod(finalStr.substr(start[i], stop[i] - start[i]));
		expon[i] = maxExponent - i;
		std::cout << std::setw(6) << coeff[i] << std::setw(13) << expon[i] << '\n' ;
		std::cout << "-----------------------\n";
	}
	std::cout << '\n';
		
	return 0;
}
