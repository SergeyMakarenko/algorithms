#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> z_function(string const& str)
{
	vector<int> Z(str.size());
	Z[0] = 0;

	int l = 1;
	int r = 0;
	int pos = 1;
	for (; pos < str.size(); pos++)
		if (str[pos] != str[pos - 1])
			break;

	Z[1] = pos - 1;
	if (Z[1] > 0)
		r = pos - 1;

	for (int k = 2; k < str.size(); k++)
	{
		if (k > r)
		{
			int i = k;
			for (; i < str.size(); i++)
				if (str[i] != str[i - k])
					break;

			Z[k] = i - k;

			if (Z[k] > 0)
			{
				l = k;
				r = i - 1;
			}
		}
		else
		{
			int k1 = k - l;
			int b = r - k + 1;

			if (Z[k1] < b)
			{
				Z[k] = Z[k1];
			}
			else if (Z[k1] > b)
			{
				Z[k] = b;
			}
			else
			{
				int q = r + 1;
				for (; q < str.size(); q++)
					if (str[q] != str[b + q - r - 1])
						break;

				Z[k] = q - k;
				l = k;
				r = q - 1;
			}
		}
	}

	return Z;
}

int main()
{
	string str("ababaa");
	vector<int> z = z_function(str);
	return 0;
}