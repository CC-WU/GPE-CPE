#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

struct Point{ // ���c - ������J���I�y�� 
    int x; 
    int y;
};

struct Equation{ //���c - �������I�ҧΦ������u��{�����Y�� ax+by=c 
    float a; 
    float b;
    float c;
};

int main(void) {
	// �ܼƫŧi 
	Point pointRecords[1000]; // �I array 
	Equation equations[1000]; // �u array 
	float x1, x2, y1, y2, b_constant, e_constant, det, aa, bb, cc, ae, bd, ce, bf, af, cd;
	int i, j, h, n, sn, num, overlap_marks, k;
	float gradient[1000]; // �ײv array 
	
	cin >> n;
	
	while (n > 0) {
		// ��l�� 
		num = 0; // ���u��{���Y�ưO�ƥ� 
		k = 0; // �ײv�O�ƥ� 
		overlap_marks = 0; // ���|�O�� 
		gradient[1000] = {0};
		equations[1000] = {0};
		pointRecords[1000] = {0};
		
		cin >> sn;
		
		// ��J�I�y�� 
		for (i = 0; i < sn; i++) {
			cin >> pointRecords[i].x >> pointRecords[i].y;
		}
		
		// ��� 
		for (i = 0; i < sn-1; i++) {
			for (j = i+1; j < sn; j++) {			
				// �ײv�p�� m = (y1-y2) / (x1-x2) 	(�ثe�L��)
				if ((pointRecords[i].x - pointRecords[j].x) != 0) {
					gradient[k] = (float)(pointRecords[i].y - pointRecords[j].y) / (pointRecords[i].x - pointRecords[j].x);
				}
				else {
					gradient[k] = 0;
				}
				// cout << k << " " << i << " " << j << " (" << pointRecords[i].x << ", " << pointRecords[i].y << ") - (" << pointRecords[j].x << ", " << pointRecords[j].y << ") ~ " << m[k] << " " << aa << "&" << bb << " - " << re << "\n";
					
				// �p�����I�ҧΦ������u��{��(y=ax+b) => a*x1+(-y1)=-(b_constant*b)�B a*x2+(-y2)=-(e_constant*b)�A�N���I��XY�y�бa�J�A�èD�X�G���@����{���ѡA�]�N�O�C�Ӫ��u��{����a�Mb 
				x1 = pointRecords[i].x;
				b_constant = 1; 
				y1 = pointRecords[i].y;
				x2 = pointRecords[j].x;
				e_constant = 1; 
				y2 = pointRecords[j].y;
				det = x1 * e_constant - x2 * b_constant;
				
				if (det == 0) { // ������0
					if (x1 == x2 && y1 != y2) { // ���I�ҧΦ��PX�b���������u�Aaa*x+bb*y=cc => x=x1 
						aa = 1;
						bb = 0;
						cc = x1; 
					}
					else { // ������0�A�èS��L�S�� 
						aa = 0;
						bb = 0;
						cc = 0;
					}
				}
				else { // ���`���p 
					aa = (y1 * e_constant - y2 * b_constant) / det;
					bb = -1; // ��l�� 
					cc = -((-x2 * y1 + x1 * y2) / det);
				}
				// cout << aa << "x + (" << bb << "y) = " << cc << endl;
				
				// �W��ҧΦ������u��{�� aa * x + bb * y = cc(�s)�Add * x + ee * y = ff(�J�����A�w�ŦX�ߤ@���󪺪��u��{��) 
				// �P�_��u�O�_���@�u�B����Φ����I 
			  	if (i != 0 || j != 1) { // �p�G���O�Ĥ@���u 
			  		for (h = 0; h < num; h++) {
						ae = aa * equations[h].b;
					  	bd = bb * equations[h].a;
					  	ce = cc * equations[h].b;
					  	bf = bb * equations[h].c;
					  	af = aa * equations[h].c;
					  	cd = cc * equations[h].a;
					  	
					  	if (ae - bd == 0) 
					  	{
						    if (ce - bf == 0 && bb != 0 && equations[h].b != 0) { // ��u���|  
						    	// printf("Two lines overlap\n");
						    	overlap_marks = 1;
						    	break;
							}
						    else { // ��u�O�æ檺  
						    	// printf("Two lines are parallel.\n");
							}
					    }
					    else { //��u�����I 
					    	// int x = (ce - bf)/(ae - bd);
					  		// int y = (af - cd)/(ae - bd);
					    	// printf("The intersection %lf, %lf.\n", x, y); 
						}
					    	
					}
				}
			  	
			  	if (overlap_marks == 0) { // ��u�å����|�A�O�������u��{���Y�� 
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
		
		// ��X�@���h�ֱ������ƪ����u 
		cout << num << endl;
		
		n -= 1;
	}
	
	return 0;
}


