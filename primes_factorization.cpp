#include <iostream>
#include <vector>

using namespace std;
const int MAX = 1000000;

vector<int> primes;
int lp[MAX];

void init()
{
	for (int i = 2; i < MAX; i++)
	{
		if (lp[i] == 0)
		{
			primes.push_back(i);
			lp[i] = i;
		}

		for (size_t j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] < MAX; j++)
			lp[i * primes[j]] = primes[j];
	}
}

int main()
{
	init();

	return 0;
}