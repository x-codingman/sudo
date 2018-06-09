/**********Éú³ÉÊı¶À********/
/**********saxon***********/

#include<stdio.h>
#include <iostream>
#include <list>
#include <stdlib.h>
typedef std::list< int > list_t;


int insert(int k,int value);
int check(int i, int j,int(*data)[9]);
void solve(int(*data)[9]);
void print(int(*data)[9]);
static int end;
void copyData(int(*copy)[9], int(*data)[9]) {


	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			copy[i][j] = data[i][j];
		}
	}

}

int main(){
	 int data[9][9] = { 0 };
	
	

	
		solve(data);
		
	
	printf("\n");
	print(data);
	system("pause");
}




	
void solve(int(*data)[9]){
	int result = check(data);

		


	
	//printf("sss");
		
	}



 int check(int i, int j,int(*data)[9]) {
		int flag = 0;
		int count = 0;
		for (int n = 0; n < 9; n++){
			if (data[i][j] == data[i][n] )
				count++;
			if (data[i][j] == data[n][j]){
				count++;
			}


		}
		for (int h = i / 3 * 3; h < i / 3 * 3 + 3; h++) {
			for (int l = i % 3 * 3; l < i % 3 * 3 + 3; l++) {
				if (data[i][j] == data[h][l])
					count++;
			}
		}
		if (count == 3){
			flag = 1;
			printf("aaa");
		}
		
		return  flag;
	}

 void print(int(*data)[9]){
	 for (int m = 0; m < 9; m++){

		 for (int n = 0; n < 9; n++){

			 std::cout << data[m][n] << " ";
		 }
			
		 std::cout << std::endl;

	 }
 }