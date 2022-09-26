#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

void removeDuplicates(vector<int> &v)
{
    vector<int>::iterator itr = v.begin();
    unordered_set<int> s;
    for (int & c : v) {
        if (s.insert(c).second) {
            *itr++ = c;
        }
    }
    v.erase(itr, v.end());
}

void allSums (vector <int> &sum, const vector<int> &v){
    for (int i = 0; i < v.size()-1; i++){
        for (int j = i+1; j< v.size();j++){
            sum.push_back(v[i] + v[j]);
        }
    }
    sort(sum.begin(),sum.end());
    removeDuplicates(sum);
}

int main() {
    int n, q;
    vector<int> conj, sum;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        conj.push_back(s);
    }
    allSums(sum, conj);
    n = sum.size();

    cin >> q;
    for (int i = 0; i < q; i++) {
        int p;
        cin >> p;

        if (p <= sum[0]) {
            cout << sum[0] << endl;
            continue;
        } else if (p >= sum[n - 1]) {
            cout << sum[n - 1] << endl;
            continue;
        }

        int right = 0, left = n, mid = 0;
        while (right < left) {
            mid = (right + left) / 2;
            if (sum[mid] == p) {
                cout << sum[mid] << endl;
                break;
            } else if (sum[mid] > p) {
                if (mid > 0 && p > sum[mid - 1]) {
                    if(abs(p - sum[mid - 1]) == abs(p-sum[mid]))
                        cout << sum[mid - 1] << " " << sum[mid] << endl;
                    else if (abs(p - sum[mid - 1]) < abs(p - sum[mid]))
                        cout << sum[mid - 1] << endl;
                    else
                        cout << sum[mid] << endl;
                    break;
                }
                left = mid;
            } else {
                if (mid < n - 1 && p < sum[mid + 1]) {
                    if (abs(p - sum[mid]) == abs(p - sum[mid + 1]))
                        cout << sum[mid] << " " << sum[mid + 1] << endl;
                    else if (abs(p - sum[mid]) < abs(p - sum[mid + 1]))
                        cout << sum[mid] << endl;
                    else
                        cout << sum[mid + 1] << endl;
                    break;
                }
                right = mid + 1;
            }
        }
    }
}
