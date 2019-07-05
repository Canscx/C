#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib> 
using namespace std;
const double PRECISION = 1E-6;
int COUNT_OF_NUMBER = 4;
int NUMBER_TO_BE_CAL = 24;

double srcdata[][7] = {
	{1, 114514,			},
	{2, 1, 14514,		},
	{2, 11, 4514,		},
	{2, 114, 514,		},
	{2, 1145, 14,		},
	{2, 11451, 4,		},
	{3, 1, 1, 4514,		},
	{3, 1, 14, 514,		},
	{3, 1, 145, 14,		},
	{3, 1, 1451, 4,		},
	{3, 11, 4, 514,		},
	{3, 11, 45, 14,		},
	{3, 11, 451, 4,		},
	{3, 114, 5, 14,		},
	{3, 114, 51, 4,		},
	{3, 1145, 1, 4,		},
	{4, 1, 1, 4, 514,	},
	{4, 1, 1, 45, 14,	},
	{4, 1, 1, 451, 4,	},
	{4, 1, 14, 5, 14,	},
	{4, 1, 14, 51, 4,	},
	{4, 1, 145, 1, 4,	},
	{4, 11, 4, 5, 14,	},
	{4, 11, 4, 51, 4,	},
	{4, 11, 45, 1, 4,	},
	{4, 114, 5, 1, 4,	},
	{5, 11, 4, 5, 1, 4,	},
	{5, 1, 14, 5, 1, 4,	},
	{5, 1, 1, 45, 1, 4,	},
	{5, 1, 1, 4, 51, 4,	},
	{5, 1, 1, 4, 5, 14,	},
	{6, 1, 1, 4, 5, 1, 4},
};
string srcstr[][6] = {
	{"114514",					 },
	{"1", "14514",				 },
	{"11", "4514",				 },
	{"114", "514",				 },
	{"1145", "14",				 },
	{"11451", "4",				 },
	{"1", "1", "4514",			 },
	{"1", "14", "514",			 },
	{"1", "145", "14",			 },
	{"1", "1451", "4",			 },
	{"11", "4", "514",			 },
	{"11", "45", "14",			 },
	{"11", "451", "4",			 },
	{"114", "5", "14",			 },
	{"114", "51", "4",			 },
	{"1145", "1", "4",			 },
	{"1", "1", "4", "514",		 },
	{"1", "1", "45", "14",		 },
	{"1", "1", "451", "4",		 },
	{"1", "14", "5", "14",		 },
	{"1", "14", "51", "4",		 },
	{"1", "145", "1", "4",		 },
	{"11", "4", "5", "14",		 },
	{"11", "4", "51", "4",		 },
	{"11", "45", "1", "4",		 },
	{"114", "5", "1", "4",		 },
	{"11", "4", "5", "1", "4",	 },
	{"1", "14", "5", "1", "4",	 },
	{"1", "1", "45", "1", "4",	 },
	{"1", "1", "4", "51", "4",	 },
	{"1", "1", "4", "5", "14",	 },
	{"1", "1", "4", "5", "1", "4"},
};

bool Search(int n, int limit, double number[], string expression[])
{
	if (n == 1)
	{
		if (fabs(number[0] - limit) < PRECISION)
		{
			cout << limit << " = " << expression[0] << endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	for (int i = 0; i < n - 1; i++)
	{
		int j = i + 1;
		double a, b;
		int k;
		string expa, expb;
		a = number[i];
		b = number[j];
		expa = expression[i];
		expb = expression[j];
		for (k = j; k < n - 1; k++)
		{
			number[k] = number[k + 1];
			expression[k] = expression[k + 1];
		}

		expression[i] = '(' + expa + '+' + expb + ')';
		number[i] = a + b;
		if (Search(n - 1, limit, number, expression))
		{
			return true;
		}

		expression[i] = '(' + expa + '-' + expb + ')';
		number[i] = a - b;
		if (Search(n - 1, limit, number, expression))
		{
			return true;
		}

		expression[i] = "(-" + expa + '+' + expb + ')';
		number[i] = b - a;
		if (Search(n - 1, limit, number, expression))
		{
			return true;
		}

		expression[i] = '(' + expa + '*' + expb + ')';
		number[i] = a * b;
		if (Search(n - 1, limit, number, expression))
		{
			return true;
		}

		expression[i] = '(' + expa + "*(-" + expb + "))";
		number[i] = a * -b;
		if (Search(n - 1, limit, number, expression))
		{
			return true;
		}

		if (b != 0)
		{
			expression[i] = '(' + expa + '/' + expb + ')';
			number[i] = a / b;
			if (Search(n - 1, limit, number, expression))
			{
				return true;
			}

			expression[i] = '(' + expa + "/(-" + expb + "))";
			number[i] = a / -b;
			if (Search(n - 1, limit, number, expression))
			{
				return true;
			}
		}

		expression[i] = '(' + expa + '^' + expb + ')';
		number[i] = powf(a, b);
		if (Search(n - 1, limit, number, expression))
		{
			return true;
		}

		expression[i] = '(' + expa + "^-(" + expb + "))";
		number[i] = powf(a, -b);
		if (Search(n - 1, limit, number, expression))
		{
			return true;
		}

		expression[i] = "((" + expa + ")^-" + expb + ')';
		number[i] = powf(-a, b);
		if (Search(n - 1, limit, number, expression))
		{
			return true;
		}

		expression[i] = "((" + expa + ")^-(" + expb + "))";
		number[i] = powf(-a, -b);
		if (Search(n - 1, limit, number, expression))
		{
			return true;
		}

		for (k = n - 1; k >= j; k--)
		{
			number[k] = number[k - 1];
			expression[k] = expression[k - 1];
		}
		number[i] = a;
		number[j] = b;
		expression[i] = expa;
		expression[j] = expb;
	}
	return false;
}

void resetdata(double *number, double *tmp, string *expression, string *tmps, int n)
{
	for (int i = 0; i < n; i++)
	{
		number[i] = tmp[i];
		expression[i] = tmps[i];
	}
}

int main()
{
	COUNT_OF_NUMBER = 6;
	int i;
	double *number = new double[COUNT_OF_NUMBER];
	double *tmp = new double[COUNT_OF_NUMBER];
	string *expression = new string[COUNT_OF_NUMBER];
	string *tmps = new string[COUNT_OF_NUMBER];
	bool flag = true;

	for (NUMBER_TO_BE_CAL = 0; NUMBER_TO_BE_CAL <= 161; NUMBER_TO_BE_CAL++)
	{
		for (i = 0; i < 32; i++)
		{
			resetdata(number, &srcdata[i][1], expression, srcstr[i], srcdata[i][0]);
			if (Search(srcdata[i][0], NUMBER_TO_BE_CAL, number, expression))
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			cout << NUMBER_TO_BE_CAL << "无解" << endl;
		}
		flag = true;
	}
	delete[]tmp;
	delete[]number;
	delete[]tmps;
	delete[]expression;
	return 0;
}