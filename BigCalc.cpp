//Clayton Arndt
//CS201
//12/6/2020
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
using std::string;
using std::endl;
using std::vector;
using std::istream;
using std::cin;
using std::ostream;
using std::max;
using std::cout;


#define FOR(i,l,r) for (int i=l;i<=r;i++)
#define FORD(i,r,l) for (int i=r;i>=l;i--)

const int base = 1e9;
typedef vector<int> BigInteger;

void Set(BigInteger &bint) {
	while (bint.size() > 1 && bint.back() == 0) bint.pop_back();
}

void Print(BigInteger bint) {
	Set(bint);
	printf("%d", (bint.size() == 0) ? 0 : bint.back());
	FORD(i, bint.size() - 2, 0) printf("%09d", bint[i]); printf("\n");
}

BigInteger Integer(string s) {
	BigInteger ans;
	if (s[0] == '-') return ans;
	if (s.size() == 0) { ans.push_back(0); return ans; }
	while (s.size() % 9 != 0) s = '0' + s;
	for (int i = 0; i < s.size(); i += 9) {
		int v = 0;
		for (int j = i; j < i + 9; j++) v = v * 10 + (s[j] - '0');
		ans.insert(ans.begin(), v);
	}
	Set(ans);
	return ans;
}

BigInteger Integer(long long lint) {
	string s = "";
	while (lint > 0) s = char(lint % 10 + '0') + s, lint /= 10;
	return Integer(s);
}

BigInteger Integer(int x) {
	return Integer((long long)x);
}


bool operator < (BigInteger a, BigInteger b) {
	Set(a);
	Set(b);
	if (a.size() != b.size()) return (a.size() < b.size());
	FORD(i, a.size() - 1, 0)
		if (a[i] != b[i]) return (a[i] < b[i]);
	return false;
}

void operator >> (istream &in, BigInteger &a) {
	string s;
	getline(cin, s);
	a = Integer(s);
}

void operator << (ostream &out, BigInteger a) {
	Print(a);
}


BigInteger operator + (BigInteger a, BigInteger b) {
	Set(a);
	Set(b);
	BigInteger ans;
	int carry = 0;
	FOR(i, 0, max(a.size(), b.size()) - 1) {
		if (i < a.size()) carry += a[i];
		if (i < b.size()) carry += b[i];
		ans.push_back(carry%base);
		carry /= base;
	}
	if (carry) ans.push_back(carry);
	Set(ans);
	return ans;
}

BigInteger operator + (BigInteger a, int b) {
	return a + Integer(b);
}

BigInteger operator - (BigInteger a, BigInteger b) {
	Set(a);
	Set(b);
	BigInteger ans;
	int carry = 0;
	FOR(i, 0, a.size() - 1) {
		carry += a[i] - (i < b.size() ? b[i] : 0);
		if (carry < 0) ans.push_back(carry + base), carry = -1;
		else ans.push_back(carry), carry = 0;
	}
	Set(ans);
	return ans;
}

BigInteger operator - (BigInteger a, int b) {
	return a - Integer(b);
}

BigInteger operator * (BigInteger a, BigInteger b) {
	Set(a);
	Set(b);
	BigInteger ans;
	ans.assign(a.size() + b.size(), 0);
	FOR(i, 0, a.size() - 1) {
		long long carry = 0ll;
		for (int j = 0; j < b.size() || carry > 0; j++) {
			long long s = ans[i + j] + carry + (long long)a[i] * (j < b.size() ? (long long)b[j] : 0ll);
			ans[i + j] = s%base;
			carry = s / base;
		}
	}
	Set(ans);
	return ans;
}

BigInteger operator * (BigInteger a, int b) {
	return a * Integer(b);
}
BigInteger operator / (BigInteger a, BigInteger b) {
	Set(a);
	Set(b);
	if (b == Integer(0)) return Integer("-1");
	BigInteger ans, cur;
	FORD(i, a.size() - 1, 0) {
		cur.insert(cur.begin(), a[i]);
		int x = 0, L = 0, R = base;
		while (L <= R) {
			int mid = (L + R) >> 1;
			if (b*Integer(mid) > cur) {
				x = mid;
				R = mid - 1;
			}
			else
				L = mid + 1;
		}
		cur = cur - Integer(x - 1)*b;
		ans.insert(ans.begin(), x - 1);
	}
	Set(ans);
	return ans;
}

BigInteger operator / (BigInteger a, int b) {
	Set(a);
	BigInteger ans;
	long long cur = 0ll;
	FORD(i, a.size() - 1, 0) {
		cur = (cur*(long long)base + (long long)a[i]);
		ans.insert(ans.begin(), cur / b);
		cur %= b;
	}
	Set(ans);
	return ans;
}


BigInteger operator % (BigInteger a, BigInteger b) {
	Set(a);
	Set(b);
	if (b == Integer(0)) return Integer("-1");
	BigInteger ans;
	FORD(i, a.size() - 1, 0) {
		ans.insert(ans.begin(), a[i]);
		int x = 0, L = 0, R = base;
		while (L <= R) {
			int mid = (L + R) >> 1;
			if (b*Integer(mid) > ans) {
				x = mid;
				R = mid - 1;
			}
			else
				L = mid + 1;
		}
		ans = ans - Integer(x - 1)*b;
	}
	Set(ans);
	return ans;
}

int operator % (BigInteger a, int b) {
	Set(a);
	if (b == 0) return -1;
	int ans = 0;
	FORD(i, a.size() - 1, 0)
		ans = (ans*(base%b) + a[i] % b) % b;
	return ans;
}

int main()
{

	BigInteger A;  cout << "BigInteger Input A:\n";  cin >> A;
	BigInteger B;  cout << "BigInteger Input B:\n";  cin >> B;
	cout << "BigInteger Result A+B=:\n" << A + B;
	cout << "BigInteger Result A-B=:\n" << A - B;
	cout << "BigInteger Result A*B=:\n" << A * B;
	cout << "BigInteger Result A/B=:\n" << A / B;
	cout << "BigInteger Result A%B=:\n" << A % B;

	return 0;
}

