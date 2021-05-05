#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
int a[100][100];


int random(int a, int b){
	int area = 0;
	int ret = 0;
	//生成区间
	area = b - a + 1;
	ret = (int)(rand()*area / (1.0 * RAND_MAX) + a);
	return ret;
}

int connected(int n){
	int i, j, k;
	for (k = 0; k <= n; k++)
		for (i = 1; i <= n; i++)
			if (a[k][i])
				for (j = 1; j <= n; j++)
					if (a[i][k] && a[k][j]) {
						a[i][j] = 1;
					}
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			if (a[i][j] + a[j][i] == 0) {
				printf("no connected\n"); 
				return 0;
			}
		}
	printf("connected\n");
	return 1;
}

int main(){
	ofstream outfile("data.txt", ios::app);
	int size,num;
	int deg[100];
	int arc[100][100];
	cout << "please input the number of vertices and the number of graph you want to create" << endl;
	cin >> size >> num;
	for (int i = 1; i <= num; i++) {
		loop:deg[100] = { 0 };
		memset(arc, 0, sizeof(arc));
		memset(a, 0, sizeof(a));
		int maxdeghalf = (size - 1) / 3;									//图中可以存在的最大度的一半
		for (int j = 1; j <= size; j++) {
			deg[j] = 2 * random(1, maxdeghalf);								//为每个顶点赋度值，必须是偶数
		}
		//
		cout << "check degree" << endl;
		for (int j = 1; j <= size; j++) {
			cout << deg[j] << " ";
		}
		cout << endl;
		//
		for (int j = 1; j <= size; j++) {
			for (int k = j+1; k <= size; k++) {
				if (deg[j]==0)break;
				if (j == k || deg[k]==0)continue;
				if (arc[j][k] == 0){
					arc[j][k] = 1;
					arc[k][j] = 1;
					a[j][k] = 1;
					a[k][j] = 1;
					deg[j]--; deg[k]--;
				}
			}
		}
		//
		cout << "Check if there are any degree left" << endl;
		for (int j = 1; j <= size; j++) {
			cout << deg[j] << " ";
			if (deg[j] != 0) {
				cout << "the number of degree is too large" << endl;
				goto loop;
			}
		}
		cout << endl;
		//

		if (connected(size) == 0) {
			goto loop;
		}

		//
		cout << "Check the Euler matrix" << endl;
		for (int j = 1; j <= size; j++) {
			for (int k = 1; k <= size; k++) {
				cout << arc[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
		//
		for (int j = 1; j <= random(1, size/3); j++) {						//控制随机插入边的数量
			int check = 1;
			int x, y;
			while (check == 1) {
				x = random(1, size);
				y = random(1, size);
				check = arc[x][y];
			}
			arc[x][y] = 1;
			arc[y][x] = 1;
		}
		for (int j = 1; j <= size; j++) {
			arc[j][j] = 0;
		}
		//
		cout << "Check the surperEuler matrix" << endl;
		for (int j = 1; j <= size; j++) {
			for (int k = 1; k <= size; k++) {
				cout << arc[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
		//
		outfile << size << endl;
		for (int j = 1; j <= size; j++) {
			for (int k = 1; k <= size; k++) {
				outfile << arc[j][k] << " ";
			}
			outfile << endl;
		}
	}
	outfile.close();
	system("pause");
	return 0;
}
