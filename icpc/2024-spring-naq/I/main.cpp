#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t; cin>>t;
	while(t--){
		string s; cin>>s;
		int n=(int)s.length();
		vector<string> ans;
		for(int k=1; k<=5; k++){ // length
			if(k>n) break;
			string cur; // first val
			for(int i=0; i<k; i++){
				cur+=s[i];
			}
			string fval=cur;
			string lastval=cur;
			int sindex=k;
			string wantnext=to_string(stoi(cur)+1);

			vector<string> mistakes;
			bool impossible=false;
			//cout<<"cur is "<<cur<<endl;
			while(true){
				string here;
				if(sindex==n) break;
				for(int i=sindex; i<min(n, sindex+(int)wantnext.length()); i++){
					here+=s[i];
				}
				//cout<<"at starting index "<<sindex<<endl;
				//cout<<"here is "<<here<<endl;
				string trynext;
				for(int i=sindex; i<min(n, sindex+(int)to_string((stoi(wantnext)+1)).length()); i++){
					trynext+=s[i];
				}

				//cout<<"trynext is "<<trynext<<endl;

				if(here.empty() or (int)mistakes.size()>=2){
					impossible=true; break;
				}
				
				if(here!=wantnext and stoi(wantnext)+1 != stoi(here)){
					//cout<<"setting impossible = true becuase "<<wantnext<<" + 1 != "<<here<<endl;
					if(stoi(trynext)==stoi(wantnext)+1){
						mistakes.push_back(wantnext);
					}
					else{ impossible=true; break; }
				}

				if(here!=wantnext and stoi(wantnext)+1==stoi(here)){
					mistakes.push_back(wantnext);
				}

				if(here==wantnext){
					lastval=here;
					wantnext=to_string(stoi(here)+1);
					sindex+=(int)here.length();
				}
				else{
					lastval=trynext;
					wantnext=to_string(stoi(trynext)+1);
					sindex+=(int)trynext.length();
				}
			}
			//cout<<"at k = "<<k<<" mistkaes size is "<<(int)mistakes.size()<<endl;
			//for(string i:mistakes) cout<<i<<" "; cout<<endl;
			//cout<<"impossible is "<<impossible<<endl;
			if((int)mistakes.size()==1 and !impossible){
				//cout<<"for k = "<<k<<" 1 mistake of "<<mistakes[0]<<endl;
				ans.push_back(mistakes[0]);
			}
			if((int)mistakes.size()==0 and !impossible){
				//cout<<"for k = "<<k<<" 0 mistakes "<<endl;
				ans.push_back(to_string(stoi(fval)-1));
				ans.push_back(to_string(stoi(lastval)+1));
			}
		}
		//cout<<"answer start :"<<endl;

		vector<int> realans;
		for(string i:ans){
			if(stoi(i)>=1 and stoi(i)<=99999){
				realans.push_back(stoi(i));
			}
		}
		
		sort(realans.begin(), realans.end());
		cout<<(int)realans.size()<<endl;
		for(int i=0; i<(int)realans.size()-1; i++){
			cout<<realans[i]<<" ";
		}
		cout<<realans.back()<<endl;
		//cout<<"answer end"<<endl;
	}
}