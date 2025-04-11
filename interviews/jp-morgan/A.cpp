#include <bits/stdc++.h>

using namespace std;


/*
 * Complete the 'longestEvenWord' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING sentence as parameter.
 */

#define vt vector
#define ll long long
#define pb push_back

string longestEvenWord(string sentence) {
    vt<string> v;
    int start, end=-1;
    do {
        start=end+1;
        end=sentence.find(' ', start);
        v.pb(sentence.substr(start, end-start));
    } while (end!=-1);
    int l=v.size()-1;
    ll m=0;
    string ans="00";
    while (l>=0) {
        if (v[l].size()%2==0) {
            if (v[l].size()>=m) ans=v[l];
            m=max(m, (ll) v[l].size());
        }
        l--;
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string sentence;
    getline(cin, sentence);

    string result = longestEvenWord(sentence);

    fout << result << "\n";

    fout.close();

    return 0;
}