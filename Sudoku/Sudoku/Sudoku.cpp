/************嵌入式项目设计*********/
/************解数独C++实现*********/
/************Saxon*****************/

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include<cstdio> 
#include <math.h>
#include <random>



	
	int k,flag;
	clock_t start;
	clock_t finish;
	int sudo_result[9][9];


	 int highestOneBit(int i) {
		// 例如1000
		i |= (i >> 1); // 使前2位变为1，相当于i = i | (i >> 1); i = 1000 | 0100 = 1100
		i |= (i >> 2); // 使前4位变为1，由于上一步确保了前两位都是1，所以这一次移动两位，1111
		i |= (i >> 4); // 使前8位变为1，1111
		i |= (i >> 8); // 使前16位变为1，1111
		i |= (i >> 16); // 使前32位变为1，1111
		return i - (i >> 1); // i >>> 1 无符号右移，使最高位为0，其余位为1，相减即得出结果，1111 - 0111 = 1000 
	}
	 int bitCount(int n)
	{
		int count = 0;
		while (n){
			count++;  //只要n不为0则其至少有一个1
			n = n & (n - 1);
		}
		return count;
	}


	 void smallPosition(int *res, int(*data)[9]) {
		//res[2] = { 0 };
		int flag = 0;
		int smallCount = 10;
		for (int i = 0; i < 9; i++) {
			if (flag == 1){ break; }
			for (int j = 0; j < 9; j++) {
				int bitcount = bitCount(data[i][j]);

				if (bitcount == 2) {
					res[0] = i;
					res[1] = j;
					flag = 1;
					break;



				}
				else if (bitcount != 1) {
					if (smallCount > bitcount) {
						smallCount = bitcount;
						res[0] = i;
						res[1] = j;

					}
				}
			}
		}

	}


	 void copyData(int(*copy)[9], int(*data)[9]) {


		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				copy[i][j] = data[i][j];
			}
		}

	}

 int check(int(*data)[9]) {
		for (int i = 0; i < 9; i++) {
			int row = 0;
			int col = 0;
			int block = 0;
			for (int j = 0; j < 9; j++) {
				if (bitCount(data[i][j]) > 1) {
					return 1;
				}
				row |= data[i][j];
				col |= data[j][i];
			}

			for (int h = i / 3 * 3; h < i / 3 * 3 + 3; h++) {
				for (int l = i % 3 * 3; l < i % 3 * 3 + 3; l++) {
					block |= data[h][l];
				}
			}
			if (row != 0x1ff || col != 0x1ff || block != 0x1ff) {
				return -1;
			}
		}
		return 0;
	}


	 bool tryReduce(int(*data)[9], int m, int n, int v) {
		int old = data[m][n];
		data[m][n] = old & v;
		return data[m][n] != old;
	}

	 void  init(int(*data)[9]){
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if (data[i][j] != 0){
					data[i][j] = 1 << (data[i][j] - 1);
				}
				else{
					data[i][j] = 0x1ff;
				}
			}

		}
	}
	int getV9(int v) {
		// 使用switch与使用Math.log时间效率差不多
		switch (v) {
		case 1:
			return 1;
		case 2:
			return 2;
		case 4:
			return 3;
		case 8:
			return 4;
		case 16:
			return 5;
		case 32:
			return 6;
		case 64:
			return 7;
		case 128:
			return 8;
		case 256:
			return 9;
		default:
			break;
		}
		return -1;
	}


 void print(int(*data)[9]){
		for (int m = 0; m < 9; m++){

			for (int n = 0; n < 9; n++){
				int v = getV9(data[m][n]);
				if (v != -1){
					std::cout << v << " ";
				}
				else{
					std::cout << '_' << " ";
				}
			}
			std::cout << std::endl;

		}
	}
 bool setMaybe(int(*data)[9], int m, int n){
		if (bitCount(data[m][n]) == 1) {
			return false;
		}
		int row = 0;// 行已确定值集合
		int col = 0;// 列已确定值集合
		int block = 0; // 宫格已确定值集合

		for (int i = 0; i < 9; i++) {
			if (bitCount(data[m][i]) == 1) {
				row += data[m][i];
			}
			if (bitCount(data[i][n]) == 1) {
				col += data[i][n];
			}
		}

		for (int i = m / 3 * 3; i < m / 3 * 3 + 3; i++) {
			for (int j = n / 3 * 3; j < n / 3 * 3 + 3; j++) {
				if (bitCount(data[i][j]) == 1) {
					block += data[i][j];
				}
			}
		}

		int have = row | col | block;// 不可能的值
		int left = 0x1ff ^ have;// 候选数
		
		return tryReduce(data, m, n, left);
	}



	 bool reduce(int(*data)[9]){
		bool changed = false;
		for (int m = 0; m < 9; m++) {
			for (int n = 0; n < 9; n++) {
				if (bitCount(data[m][n]) != 1) {
					if (setMaybe(data, m, n)) {
						changed = true;
					}
				}
			}
		}
		return changed;

	}
   // 候选值删选
	 void analyse(int(*data)[9]){     
		bool changed = false;
		changed = reduce(data);
		if (changed){
			analyse(data);
		}
	}

	 void solve(int(*data)[9]){
		analyse(data);

		int result = check(data);


		if (result == 1) {
			int position[2] = { 0 };
			/*int  *position;
			position = new int[2];*/
			smallPosition(position, data);

			int pv = data[position[0]][position[1]];

			int pvcount = bitCount(pv);
			for (int i = 0; i < pvcount; i++) {
				int testv = 1 << ((int)(log(highestOneBit(pv)) / log(2)));

				pv ^= testv;


				int copy[9][9];
				copyData(copy, data);
				copy[position[0]][position[1]] = testv;

				solve(copy);
			}
		}
		else if (result == 0) {
			finish = clock();
			flag = 1;
			std::cout << "------------------------------用时：---------------------"
				<< (double)(finish - start) / CLOCKS_PER_SEC << "second" << std::endl;
			start = clock();
			print(data);
			

		}

	}




	 int main(){
		 flag = 0;

		 start = clock();
		 int data[9][9] = { { 8 }, { 0, 7, 0, 0, 9, 0, 2 }, { 0, 0, 3, 6 }, { 0, 5, 0, 0, 0, 7 }, { 0, 0, 0, 0, 4, 5, 7 }, { 0, 0, 0, 1, 0, 0, 0, 3 }, { 0, 0, 1, 0, 0, 0, 0, 6, 8 }, { 0, 0, 8, 5, 0, 0, 0, 1, 0 }, { 0, 9, 0, 0, 0, 0, 4 } };
		 //int data[9][9] = { 0 };
		 init(data);
		 print(data);
		 solve(data);
		 system("pause");
		 /*finish = clock();

		 std::cout << "------------------------------------总用时：---------------------"
		 << (double)(finish - start) / CLOCKS_PER_SEC << "second" << std::endl;*/


		/* int a = 15;

		 for (int i = 0; i < a; i++){
			 std::random_device rd;
			 std::mt19937  gen(rd());
			 std::uniform_int_distribution<> dis(0, 80);



			 sudo_result[dis(gen) / 9][dis(gen) % 9] = 0x1ff;



		 }
		 print(sudo_result);
		 solve(data);*/

	 }
	 	





	//	system("pause");

	//}
