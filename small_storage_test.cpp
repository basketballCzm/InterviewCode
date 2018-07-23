 /*
小测试—— 一个简单的内存key-value 数据结构
输入：2,000,000 条记录。每条记录为(key, value)对, key为一个整数，value为一个无重复的数组。
为了简单，用简单的loop来生成数据记录即可。
	for(int i = 0; i < 2000000; i++)
		int key = i; 
		int val_size = 8; //value的长度固定为 8
		for(int j = 0; j < val_size; j++)
			int val = rand_int(1,8); // 取[1,8]之间的随机整数作为value的值，因而val可能有相同的，注意去重
请设计一个在内存中的key-value数据结构
测试1：将以上数据存储到该结构。输出：导入这2 million记录，需要的总时间。
测试2：根据key，获取相应的value。输出：查询2 million记录，需要的总时间。
说明：
1.	请用c++实现，不要使用多线程或者并行方法。
2.	虽然生成的key是从0开始连续的整数，但在key-value数据存取时，请需要忽略key值的特殊性，假设key是任意的整数。
3.	请尽可能的提高数据的存取效率，用时越短越好，空间复杂度不作为第一考虑的要素。
*/

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#define NOW_RECORD 2000000
#define MAX_HASH_RECORD 2000000
typedef unsigned long ulong;
#define CLOCKS_PER_SEC ((clock_t)1000000) 
ulong key_value[NOW_RECORD];
ulong hash_key_value[MAX_HASH_RECORD];

int find_hash_index(ulong value){
	int addr = value % MAX_HASH_RECORD;
	//the space has been used, generate conflicts
	for (int i = 0; i < MAX_HASH_RECORD && hash_key_value[addr] != -1 && hash_key_value[addr] != value; i++){
		addr = (addr+1) % MAX_HASH_RECORD;
	}
	if(addr == MAX_HASH_RECORD){
		return -1; //溢出
	}else{
		return addr;
	}
}

int rand_int(int min, int max){
	return (rand()%(max-min+1))+min;
}


int main(){
	clock_t start, end;
	double time;
	//produce dataset
	for (int i = 0; i < MAX_HASH_RECORD; i++){
		hash_key_value[i] = -1;
	}
	for(int i = 0; i < NOW_RECORD; i++){
		int key = i;
		int val_size = 8;
		ulong value =  0;
		for (int j = 0; j < val_size; j++){
			int val = rand_int(1,8);
			value = value + val*pow(10,j);
		}
		key_value[key] = value;
	}


	//storage dataset
	start = clock();
	for(int i = 0; i < NOW_RECORD; i++){
		ulong value = key_value[i];
		int addr = find_hash_index(value);
		if(-1 == addr || hash_key_value[addr] == value){
			//std::cout << "hashtable is overflow or data value has existed!" << std::endl;
		}else{
			hash_key_value[addr] = value;
		}
	}
	end = clock();
	time = (end - start); 

	std::cout << "the storage time is:" << time << "ms" << std::endl;

	//find hash_value
	start = clock();
	for (int i = 0; i < NOW_RECORD; i++)
	{
		int key = rand_int(1,NOW_RECORD-1);
		ulong value = key_value[key];
		int addr = find_hash_index(value);
		if(-1 == addr){
			std::cout << "hashtable is overflow!" << std::endl;
 		}else if(hash_key_value[addr] != value){
 			std::cout << "data value is not existed!" << std::endl;
 		}else{
 			//std::cout << "data has been found! hash_key:" << addr << "  hash_value:" << value << std::endl;
 		}
	}
 	end = clock();
 	time = double(end - start)/NOW_RECORD;
 	std::cout << "the find time is:" << time << "ms" << std::endl;
 	
 	
	return 0;
}