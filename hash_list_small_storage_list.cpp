#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#define NOW_RECORD 2000000
#define MAX_HASHTABLE_RECORD 20000
typedef unsigned long ulong;
ulong key_value[NOW_RECORD];

struct node{
	node(){m_value = 0;m_next = NULL;}
	ulong m_value;
	node *m_next;
};

//this is the head node for every list
node* hashtable_key_value[MAX_HASHTABLE_RECORD];

int rand_int(int min, int max){
	return (rand()%(max-min+1))+min;
}

node* find_hash_node(int addr, ulong value){
	node* p_tmp_node = hashtable_key_value[addr];
	while(NULL != p_tmp_node && p_tmp_node->m_value != value){
		p_tmp_node = p_tmp_node->m_next;
	}
	return p_tmp_node;
}

bool insert_hash_node(int addr, ulong value){
	node *p_new_node = new node();
	if(NULL == p_new_node){
		return false;
	}else{
		p_new_node->m_value = value;
		p_new_node->m_next = hashtable_key_value[addr];
		hashtable_key_value[addr] = p_new_node;
		return true;
	}
}


int main(){
	clock_t start, end;
	double time;
	//produce dataset
	for (int i = 0; i < MAX_HASHTABLE_RECORD; i++){
		hashtable_key_value[i] = NULL;
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

	start = clock();
	for(int i = 0; i < NOW_RECORD; i++){
		ulong value = key_value[i];
		int addr = value % MAX_HASHTABLE_RECORD;
		if(!find_hash_node(addr, value)){
			insert_hash_node(addr, value);
		}
	}
	end = clock();
	time = double(end-start);
	std::cout << "the storage time is:" << time << std::endl;

	start = clock();
	for (int i = 0; i < NOW_RECORD; i++){
		int key = rand_int(0,NOW_RECORD-1);
		ulong value = key_value[key];
		int addr = value % MAX_HASHTABLE_RECORD;
		node *p_tmp_node = find_hash_node(addr, value);
		if(p_tmp_node){
			//cout << "find date is success! the hash key is:" << addr << "the value is:" <<  p_tmp_node->m_value << std::endl; 
		}

	}
	end = clock();
	time = double(end-start)/NOW_RECORD;
	std::cout << "the find data time is:" << time << std::endl;
	return 0;
}