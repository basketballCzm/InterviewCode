#include "../CString.hpp"
#include <iostream>
using namespace std;

int main()
{
	CString obj("czm");
	CString obj1(obj);
	CString obj2("hello");
	obj = obj2;
	cout << obj << endl;
	cout << obj1 << endl;
	cout << obj2 << endl;
	return 0;
}