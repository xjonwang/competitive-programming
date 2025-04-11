#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cstdint>

using namespace std;

#define vt vector
#define ll int64_t
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
#define pb push_back

class IPrinter
{
public:
    virtual ~IPrinter() = default;
    virtual void OnMessageComplete(const std::string& message) const = 0;
};

class Printer
    : public IPrinter
{
public:
    void OnMessageComplete(const std::string& message) const override
    {
        std::cout << message << std::endl;
    }
};

struct BIT {
    vt<ll> bit;
    ll n;
    
    BIT() {}
    
    BIT(ll n) {
        this->n = n;
        bit.assign(n, 0);
    }
    
    ll sum(ll r) {
        ll ans=0;
        while (r>=0) {
            ans+=bit[r];
            r&=r+1; r--;
        }
        return ans;
    }
    
    ll sum(ll l, ll r) {
        return sum(r) - sum(l-1);
    }
    
    void add(ll i, ll x) {
        while (i<n) {
            bit[i]+=x;
            i|=i+1;
        }
    }
};

class Decoder
{
public:
    Decoder(const IPrinter& printer)
        : mPrinter(printer)
    {
        v=vt<char>(2e5+1);
    }
    
    void ProcessSample(const uint64_t sequence, const char character)
    {
        /* complete your function and call mPrinter.OnMessageComplete when completing a message */
        if (character=='-') {
            ends.insert(sequence-1);
            auto it=ends.upper_bound(sequence-1);
            if (it!=ends.end() && sequence-1>seq) {
                ll d=*it-sequence;
                if (mbit.sum(sequence, *it-1)==d) {
                    seq=sequence-1;
                    string s; s.resize(d);
                    for (int i=0; i<d; i++) s[i]=v[sequence+i];
                    mPrinter.OnMessageComplete(s);
                }
                return;
            }
            it=ends.lower_bound(sequence-1);
            if (it!=ends.begin() && *prev(it)>seq) {
                it--;
                ll d=sequence-*it-2;
                if (mbit.sum(*it+1, sequence-1)==d) {
                    seq=*it;
                    string s; s.resize(d);
                    for (int i=0; i<d; i++) s[i]=v[*it+i+1];
                    mPrinter.OnMessageComplete(s);
                } 
            }
        } else {
            v[sequence-1] = character;
            mbit.add(sequence-1, 1);
            auto it = ends.upper_bound(sequence-1);
            if (it!=ends.begin() && it!=ends.end() && *prev(it)>seq) {
                ll d=*it-*prev(it)-1;
                if (mbit.sum(*prev(it)+1, *it-1)==d) {
                    seq=*prev(it);
                    string s; s.resize(d);
                    for (int i=0; i<d; i++) s[i]=v[*prev(it)+i+1];
                    mPrinter.OnMessageComplete(s);
                }
            }
        }
    }
    
    const IPrinter& mPrinter;

private:
    vt<char> v;
    set<ll> ends;
    BIT mbit = BIT(2e5+1);
    ll seq=-1;
};

int main() {
    Printer printer;
    Decoder decoder(printer);
    
    uint64_t seqNum;
    char message;
    
    while(!std::cin.eof())
    {
        std::cin >> seqNum >> message;
        if (std::cin.eof()) break;
        decoder.ProcessSample(seqNum, message);
    }
    
    return  0;
}