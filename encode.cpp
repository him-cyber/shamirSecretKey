#include<bits/stdc++.h>

using namespace std;

#define p 39916801

class shamirSecretSharing {
    int n;
    int k;
    vector < bitset < 10 >> s;
    vector < vector < pair < int, int >>> points;

    int y(int x,
          const vector < int > & coeff) {
        int y = 0;
        for (int i = 0; i < coeff.size(); ++i)
            y += pow(x, i) * coeff[i];
        return y % p;
    }

public:
    shamirSecretSharing(vector < bitset < 10 >> & _s, int _n, int _k): s(_s), k(_k), n(_n) {
        for (int j = 0; j < s.size(); ++j) {
            vector < int > coeff(k);
            coeff[0] = s[j].to_ulong();
            for (int i = 1; i < k; ++i) {
                srand(time(NULL) + i + j);
                coeff[i] = rand() % 1000 + 1;
            }

            vector < pair < int, int >> ds(n);
            for (int i = 0; i < ds.size(); ++i) {
                auto && [_x, _y] = ds[i];
                _x = i + 1;
                _y = y(_x, coeff);
            }
            points.push_back(ds);
        }
    }

    vector < vector < pair < int, int >>> getAllSecrets() {
        return points;
    }
};

int main() {
    int n;
    int k;
    // input #keydiv & #minkeys
    cout<<"Enter number of total parts to divide secret in\n";
    cin >> n; 
    cout<<"Enter number of minimum required parts to recreate secret\n";
    cin >> k;

    // input secret
    cout<<"Enter secret\n";
    vector < bitset < 10 >> s(1);
    for (auto && ele : s) {
        for (int i = 7; i >= 0; --i) {
            bool in ;
            cin >> in ;
            ele.set(i, in );
        }
    }

    auto allSecrets = (new shamirSecretSharing(s, n, k)) -> getAllSecrets();

    cout<<"Following are the parts (kindly save these keys for future use): \n";
    for (auto && vp : allSecrets) {
        for (auto && [x, y] : vp)
            cout << x << " " << y << endl;
        cout << endl;
    }

    return 0;
}
