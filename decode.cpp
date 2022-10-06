#include<bits/stdc++.h>
using namespace std;

#define p 39916801

class frac {
public:
	int num, den;

	frac(int n, int d): num(n), den(d) {}			#Member Initializer List 

	void reduce_frac(frac & f) {
		int gcd = __gcd(f.num, f.den);
		f.num /= gcd;
		f.num %= p;
		f.den /= gcd;
		f.den %= p;
	}

	frac operator * (frac f) {
		frac temp((num * f.num) % p, (den * f.den) % p);
		reduce_frac(temp);
		return temp;
	}

	frac operator + (frac f) {
		frac temp((num * f.den + den * f.num) % p,
		          (den * f.den) % p);

		reduce_frac(temp);
		return temp;
	}
};

bitset < 10 > decode(vector < pair < int, int >> points) {
	frac ans(0, 1);

	for (int i = 0; i < points.size(); ++i) {
		frac l(points[i].second, 1);
		for (int j = 0; j < points.size(); ++j)
			if (i != j) {
				frac temp(-1 * points[j].first, points[i].first - points[j].first);
				l = l * temp;
			}

		ans = ans + l;
	}

	return static_cast < bitset < 10 >> (ans.num % p);
}

int main()
{
	cout<<"Enter number of parts to input\n";
	int k;
	cin >> k;
	vector < pair < int, int >> minimalPoints;
	
	cout<<"Enter keys/parts in format x<space>y:\n";
	for (int j = 0; j < k; ++j)
	{
		int x, y;
		cin >> x >> y;
		minimalPoints.push_back({x, y});
	}

	cout <<"Secret is " << decode(minimalPoints) << endl;
	return 0;
}
