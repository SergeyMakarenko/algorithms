#include <iostream>
#include <vector>
#include <string>

using namespace std;

long long const BASE = 31;

int main()
{
	int k;
	cin >> k;
	string str;
	getline(cin, str);
	getline(cin, str);

	vector<long long> powers;
	powers.resize(str.size());

	powers[0] = 1;
	for (int i = 1; i < str.size(); i++)
		powers[i] = powers[i - 1] * BASE;

	vector<long long> hf;
	hf.resize(str.size());
	long long hash = 0;
	for (int i = 0; i < str.size(); i++)
	{
		hash += (str[i] - 'a' + 1) * powers[i];
		hf[i] = hash;
	}

	vector<long long> hb;
	hb.resize(str.size());
	hash = 0;
	for (int i = 0; i < str.size(); i++)
	{
		hash += (str[str.size() - 1 - i] - 'a' + 1) * powers[i];
		hb[i] = hash;
	}

	int cnt = 0;
	for (int i = 0; i <= str.size() - k; i++)
	{
		long long h1 = hf[i + k - 1];
		if (i > 0)
			h1 -= hf[i - 1];
		int pos2 = str.size() - i - k;
		long long h2 = hb[pos2 + k - 1];
		if(pos2 > 0)
			h2 -= hb[pos2 - 1];
		if (i < pos2)
			h1 *= powers[pos2 - i];
		else
			h2 *= powers[i - pos2];

		if (h1 == h2)
			cnt++;
	}
	
	cout << cnt << endl;

	return 0;
}