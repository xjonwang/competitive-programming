#include <bits/stdc++.h>

using namespace std;



/*
 * Complete the 'rearrangeWord' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING word as parameter.
 */

#define vt vector
#define pb push_back

string rearrangeWord(string word) {
    int l=word.size()-1, a;
    bool b=0;
    vt<int> cnt(26, 0);
    while (l>=0) {
        int ind=word[l]-'a';
        for (int i=ind+1; i<26; i++) {
            if (cnt[i]) {
                a=i;
                b=1;
                break;
            }
        }
        if (b) break;
        cnt[ind]++;
        l--;
    }
    if (!b) return "no answer";
    string ans=word.substr(0, l);
    ans.pb('a'+a);
    cnt[a]--; cnt[word[l]-'a']++;
    for (int i=0; i<26; i++) {
        for (int j=0; j<cnt[i]; j++) ans.pb('a'+i);
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string word;
    getline(cin, word);

    string result = rearrangeWord(word);

    fout << result << "\n";

    fout.close();

    return 0;
}