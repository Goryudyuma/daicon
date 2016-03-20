// daicon.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"

#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

//#include <bits/stdc++.h>
using namespace std;
vector<vector<int>>D;
typedef pair<int, int> pos;

#define maxsize 30

int nummax;

vector<pos> maxpoint() {
	int num = nummax;
	vector<pos> ret;
	while( 1 ) {
		for( size_t i = 0; i < maxsize; i++ ) {
			for( size_t j = 0; j < maxsize; j++ ) {
				if( num == D[i][j] ) {
					ret.emplace_back( make_pair( i, j ) );
				}
			}
		}
		if( ret.size() == 0 ) {
			num--;
			if( num == 0 ) {
				return ret;
			}
			continue;
		} else {
			break;
		}
	}
	nummax = num;

	return ret;
}

int dx[] = { 0,-1,0,1 };
int dy[] = { 1,0,-1,0 };

vector<pos> saiki( int point, pos now ) {
	vector<pos>ret, ret2;
	ret.emplace_back( now );
	for( size_t i = 0; i < 4; i++ ) {
		auto next = now;
		next.first += dx[i];
		next.second += dy[i];
		if( 0 <= next.first&&next.first < maxsize && 0 <= next.second&&next.second < maxsize ) {
			if( D[next.first][next.second] && D[next.first][next.second] == point - 1 ) {
				auto saikiret = saiki( point - 1, next );
				if( saikiret.size() > ret2.size() ) {
					ret2 = saikiret;
				} else if( saikiret.size() == ret2.size() && rand() % 2 ) {
					ret2 = saikiret;
				}
			}
		}
	}
	ret.resize( ret2.size() + 1 );
	ret[0] = now;
	copy( ret2.begin(), ret2.end(), ret.begin() + 1 );
	return ret;
}
/*
int main() {
for( size_t i = 0; i < 30; i++ ) {
for( size_t j = 0; j < 30; j++ ) {
cout << rand() % 100 << " ";
}
cout << endl;
}
}
*/

int main() {
	srand( ( unsigned int )time( NULL ) );
	D.resize( maxsize, vector<int>( maxsize ) );
	for( size_t i = 0; i < maxsize; i++ ) {
		for( size_t j = 0; j < maxsize; j++ ) {
			cin >> D[i][j];
			nummax = max( D[i][j], nummax );
		}
	}
	vector<pos> now;
	while( now = maxpoint(), now.size() ) {
		vector<pos>retsaiki;
		for( size_t i = 0; i < now.size(); i++ ) {
			int nowp = D[now[i].first][now[i].second];
			auto retsaikin = saiki( nowp, now[i] );
			if( retsaiki.size() < retsaikin.size() ) {
				retsaiki = retsaikin;
			}
		}
		for( auto x : retsaiki ) {
			cout << x.first + 1 << " " << x.second + 1 << endl;
			D[x.first][x.second]--;
		}
	}

}