#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50004;
int prec[N][10];
vector<int> pos[10];
int n,q;
string s;
const ll BASE = 137;
const int lmod = 179426081;
int powBASE[N+3];
vector<int> hsh[11];
ll invs[11];
int SA[N],AS[N];
ll modpow(ll a, ll b, ll m)
{
	if(b==0)
		return 1%m;
	ll f = modpow(a,b/2,m);
	f = (f*f)%m;
	if(b&1)
		f = (f*a)%m;
	return f;
}
inline int gethash(int i, int j, int d)
{
	int dig = j-i+1;
	ll v1 = ((ll)hsh[d][i]*powBASE[dig])%lmod;
	ll v2 = hsh[d][j+1];
	v2=(v2-v1)%lmod;
	return v2;
}
inline int getTruehash(int x, int y)
{
	ll hh = 0;
	for(int i=1; i<=10; i++)
	{
		if(prec[x][i-1]!=-1)
		{
			int j = prec[x][i-1] + 1;
			ll v = gethash(x,y,i);
			v = (v*j)%lmod;
			hh = hh+v;
		}
	}
	hh%=lmod;
	if(hh<0)
		hh+=lmod;
	return hh;
}
inline bool sufCmp(int i, int j)
{
	int lo = 1, hi = min(n - i, n - j);
	while (lo <= hi)
	{
		int mid = (lo + hi) >> 1;
		if (getTruehash(i, i+mid-1) == getTruehash(j, j+mid-1))
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	if((i+hi)==n&&(j+hi)==n)
		return false;
	if((i+hi)==n)
		return true;
	if((j+hi)==n)
		return false;
	return prec[i][s[i + hi]-'a'] < prec[j][s[j + hi]-'a'];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	powBASE[0] = 1;
	for(int i=1; i<=(N); i++)
		powBASE[i] = (powBASE[i-1]*BASE)%lmod;
	for(int i=1; i<=10; i++)
		invs[i] = modpow(i,lmod-2,lmod);
	cin>>n>>q;
	cin>>s;
	for(int i=0; i<n; i++)
		pos[s[i]-'a'].push_back(i);
	for(int i=0; i<n; i++)
	{
		vector<int> done(10,0);
		for(int j=0; j<10; j++)
			prec[i][j] = -1;
		for(int j=0; j<10; j++)
		{
			int minval = n+1, minpos = -1;
			for(int k=0; k<10; k++)
			{
				if(done[k]==0)
				{
					auto posk = lower_bound(pos[k].begin(), pos[k].end(),i);
					if(posk!=pos[k].end())
					{
						if((*posk)<minval)
						{
							minval = *posk;
							minpos = k;
						}
					}
				}
			}
			if(minpos!=-1)
			{
				prec[i][minpos] = j;
				done[minpos] = 1;
			}
		}
	}
	for(int i=1; i<=10; i++)
		hsh[i].push_back(0);
	for(int i=0; i<n; i++)
	{
		for(int j=1; j<=10; j++)
		{
			hsh[j].push_back((BASE*hsh[j][i] + (s[i]==(j+'a'-1)?1:0))%lmod);
		}
	}
	for(int i=0; i<n; i++)
		SA[i] = i;
	stable_sort(SA,SA+n,sufCmp);

	for(int i=0;i<n;i++)
		AS[SA[i]] = i;
	
	while(q--)
	{
		int l,r;
		cin>>l>>r;
		l--,r--;
		int ans = -1;
		int len=r-l;
		int hm = getTruehash(l,r);
		int p1 = AS[l];
		int st=0, en=p1;
		while(st<en)
		{
			int pos = (st+en)/2;
			int x = SA[pos];
			int y = x+len;
			int ht=-1;
			if(y<n)
				ht = getTruehash(x,y);
			if(ht!=hm)
				st=pos+1;
			else
				en=pos;
		}
		int fo = en;
		st=p1,en=n;
		while(st<en)
		{
			int pos = (st+en)/2;
			int x = SA[pos];
			int y = x+len;
			int ht=-1;
			if(y<n)
				ht = getTruehash(x,y);
			if(ht==hm)
				st=pos+1;
			else
				en=pos;
		}
		int lo = st;
		ans = lo-fo;
		cout<<ans<<"\n";
	}
}	