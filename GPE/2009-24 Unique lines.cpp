#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

struct Point{ // 結構 - 紀錄輸入的點座標 
    int x; 
    int y;
};

struct Equation{ //結構 - 紀錄兩點所形成的直線方程式的係數 ax+by=c 
    float a; 
    float b;
    float c;
};

int main(void) {
	// 變數宣告 
	Point pointRecords[1000]; // 點 array 
	Equation equations[1000]; // 線 array 
	float x1, x2, y1, y2, b_constant, e_constant, det, aa, bb, cc, ae, bd, ce, bf, af, cd;
	int i, j, h, n, sn, num, overlap_marks, k;
	float gradient[1000]; // 斜率 array 
	
	cin >> n;
	
	while (n > 0) {
		// 初始化 
		num = 0; // 直線方程式係數記數用 
		k = 0; // 斜率記數用 
		overlap_marks = 0; // 重疊記號 
		gradient[1000] = {0};
		equations[1000] = {0};
		pointRecords[1000] = {0};
		
		cin >> sn;
		
		// 輸入點座標 
		for (i = 0; i < sn; i++) {
			cin >> pointRecords[i].x >> pointRecords[i].y;
		}
		
		// 比對 
		for (i = 0; i < sn-1; i++) {
			for (j = i+1; j < sn; j++) {			
				// 斜率計算 m = (y1-y2) / (x1-x2) 	(目前無用)
				if ((pointRecords[i].x - pointRecords[j].x) != 0) {
					gradient[k] = (float)(pointRecords[i].y - pointRecords[j].y) / (pointRecords[i].x - pointRecords[j].x);
				}
				else {
					gradient[k] = 0;
				}
				// cout << k << " " << i << " " << j << " (" << pointRecords[i].x << ", " << pointRecords[i].y << ") - (" << pointRecords[j].x << ", " << pointRecords[j].y << ") ~ " << m[k] << " " << aa << "&" << bb << " - " << re << "\n";
					
				// 計算兩個點所形成的直線方程式(y=ax+b) => a*x1+(-y1)=-(b_constant*b)、 a*x2+(-y2)=-(e_constant*b)，將兩點的XY座標帶入，並求出二元一次方程式解，也就是每個直線方程式的a和b 
				x1 = pointRecords[i].x;
				b_constant = 1; 
				y1 = pointRecords[i].y;
				x2 = pointRecords[j].x;
				e_constant = 1; 
				y2 = pointRecords[j].y;
				det = x1 * e_constant - x2 * b_constant;
				
				if (det == 0) { // 分母為0
					if (x1 == x2 && y1 != y2) { // 兩點所形成與X軸垂直的直線，aa*x+bb*y=cc => x=x1 
						aa = 1;
						bb = 0;
						cc = x1; 
					}
					else { // 分母為0，並沒其他特例 
						aa = 0;
						bb = 0;
						cc = 0;
					}
				}
				else { // 正常情況 
					aa = (y1 * e_constant - y2 * b_constant) / det;
					bb = -1; // 原始值 
					cc = -((-x2 * y1 + x1 * y2) / det);
				}
				// cout << aa << "x + (" << bb << "y) = " << cc << endl;
				
				// 上方所形成的直線方程式 aa * x + bb * y = cc(新)，dd * x + ee * y = ff(既有的，已符合唯一條件的直線方程式) 
				// 判斷兩線是否為共線、平行或有交點 
			  	if (i != 0 || j != 1) { // 如果不是第一條線 
			  		for (h = 0; h < num; h++) {
						ae = aa * equations[h].b;
					  	bd = bb * equations[h].a;
					  	ce = cc * equations[h].b;
					  	bf = bb * equations[h].c;
					  	af = aa * equations[h].c;
					  	cd = cc * equations[h].a;
					  	
					  	if (ae - bd == 0) 
					  	{
						    if (ce - bf == 0 && bb != 0 && equations[h].b != 0) { // 兩線重疊  
						    	// printf("Two lines overlap\n");
						    	overlap_marks = 1;
						    	break;
							}
						    else { // 兩線是並行的  
						    	// printf("Two lines are parallel.\n");
							}
					    }
					    else { //兩線有交點 
					    	// int x = (ce - bf)/(ae - bd);
					  		// int y = (af - cd)/(ae - bd);
					    	// printf("The intersection %lf, %lf.\n", x, y); 
						}
					    	
					}
				}
			  	
			  	if (overlap_marks == 0) { // 兩線並未重疊，記錄此直線方程式係數 
					equations[num].a = aa;
					equations[num].b = bb;
					equations[num].c = cc;
					// cout << "++" << num << endl;
					num++;
				}
								
				overlap_marks = 0;
				k++;
			}
			// cout << "===================================" << endl;
		}
		
		// 輸出共有多少條不重複的直線 
		cout << num << endl;
		
		n -= 1;
	}
	
	return 0;
}


