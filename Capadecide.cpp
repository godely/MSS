#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <climits>
#include <cctype>
#include <cmath>
#include <cassert>
#include <ctime>
   
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <complex>
#include <limits>
#include <functional>
#include <numeric>

using namespace std;

#define fr(a,b,c) for(int (a) = (b); (a) < (c); ++(a))
#define rp(a,b) fr(a,0,b)
#define fre(a,b) for(int a = adj[b]; ~a; a = ant[a])
#define cl(a,b) memset((a), (b), sizeof(a))
#define sc(a) scanf("%d", &a)
#define sc2(a,b) scanf("%d%d", &a, &b)
#define sc3(a,b,c) scanf("%d%d%d", &a, &b, &c)
#define scs(s) scanf("%s", s)
#define pri(x) printf("%d\n", x)

#define iter(a) __typeof((a).begin())
#define fore(a,b) for(iter(b) a = (b).begin(); a != (b).end(); ++a)

#define st first
#define nd second
#define mp make_pair
#define pb push_back

#define db(x) cerr << #x << " == " << x << endl
#define _ << ", " <<

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector< vi > vii;

int qtdModulos, qtdAlunos;

char modulo[20][50];
char aluno[20][50];
int nota[20][20];
int prepd[1<<20][20];
int sizeGroup[20];

int pd[1<<20][20];
bool mark[1<<20][20];
int to[1<<20][20];

void bin(int n) {
	rp(i,qtdAlunos) printf("%d", (n>>i)&1);
}

int go(int mask, int group) {
	int &ret = pd[mask][group];
	if (mark[mask][group]) return ret;
	mark[mask][group] = 1;
	if (group >= qtdModulos) return 0;

	//bin(mask);
	//printf(" %d\n", group);

	int r = 0;
	int q2 = ((1<<qtdAlunos)-1) - mask;
	for (int i = q2; i > 0; i = (i-1)&q2) {
		//if (prepd[i][group] > 100000) printf("%d %d\n", i, group);
		if (__builtin_popcount(i) == sizeGroup[group]) {
			int t = prepd[i][group] + go(mask | i, group+1);
			if (t > r) {
				r = t;
				to[mask][group] = i;
			}
		}
	}
	return ret = r;
}

char line[1010], nome[1010];

map<string, int> moduloId, alunoId;

int main() {
	freopen("Capadecide.txt", "r", stdin);
	gets(line);

	int off = 0, x;
	qtdModulos = 0;

	moduloId.clear(); alunoId.clear();
	while (sscanf(line+off, "%s%n", modulo[qtdModulos], &x) == 1) {
		off += x;
		string md = modulo[qtdModulos];
		transform(md.begin(), md.end(), md.begin(), ::tolower);
		moduloId[md] = qtdModulos;
		qtdModulos++;
	}

	qtdAlunos = 0;
	while (gets(line)) {
		off = 0;
		if (sscanf(line, "%s%n", aluno[qtdAlunos], &x) != 1) continue;

		if (strcmp(aluno[qtdAlunos], "***") == 0) break;

		off +=x;

		string md = aluno[qtdAlunos];
		transform(md.begin(), md.end(), md.begin(), ::tolower);
		alunoId[md] = qtdAlunos;

		rp(i,qtdModulos) {
			sscanf(line+off, "%d%n", &nota[qtdAlunos][i], &x);
			off += x;
		}

		qtdAlunos++;
	}

	rp(i,qtdModulos) {
		scanf("%s%d", line, &x);
		string md = line;
		transform(md.begin(), md.end(), md.begin(), ::tolower);
		sizeGroup[moduloId[md]] = x;
	}

	rp(k,qtdModulos) {
		rp(i,1<<qtdAlunos) {
			int r = 0;
			rp(j,qtdAlunos) if ((i>>j)&1) {
				r += nota[j][k]*nota[j][k];
			}
			prepd[i][k] = r;
		}
	}

	scanf("%s", line);
	while (scanf("%s", line) == 1 && strcmp(line, "***") != 0) {
		string md = line;
		transform(md.begin(), md.end(), md.begin(), ::tolower);
		int id1 = alunoId[md];

		scanf("%s%d", line, &x);
		md = line;
		transform(md.begin(), md.end(), md.begin(), ::tolower);
		int id2 = alunoId[md];
		
		rp(i,1<<qtdAlunos) {
			if (((i>>id1)&1) && ((i>>id2)&1)) {
				rp(j,qtdModulos) prepd[i][j] += x;
			}
		}
	}

	cl(mark,0); cl(to, -1);
	printf("Nível de satisfação geral: %d\n", go(0,0));

	int a = 0, g = 0;
	while (to[a][g] != -1) {
		int r = to[a][g];
		printf("Módulo %s:", modulo[g]);
		rp(i,qtdAlunos) if ((r>>i)&1) {
			printf(" %s", aluno[i]);
		}
		puts("");

		a = a|r;
		g++;
	}

}