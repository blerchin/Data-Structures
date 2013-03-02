#include <stdlib.h>
#include <iostream>
#include "operator.h"

using namespace std;


int main(){
	bool check_unm = 1;

	const char* op[] = {
					"+","-","*","/","(",")","-","tan","cos","sin"
			};

	char num_ops = 10;
	char op_len[] = {	1,1,1,1,1,3,3,3};

	cout << "Testing parse_operator()" << endl
			<< "---------------------------------" << endl;

	for (int i = 0; i < num_ops; i++) 
	{
		op_code result = parse_operator (op[i], op_len[i], check_unm);
		cout << "testing " << op[i]
							<< ": " << result << endl;
	}
	cout << endl << "Testing perform_op()"<< endl
			<< "----------------------------------" << endl;

	check_unm = 1;

	operand test_vals[] = { 1, 2, 3, 14, .05, 0, 400, -1, -400 };
	int test_vals_len = 9;

	for (int i=0; i < num_ops; i++)
	{
		op_code result = parse_operator (op[i], op_len[i], check_unm);
		cout << "testing " << op[i]
							<< ": " << result << endl
							<< "--------------------------------" << endl;

		for (int j=0; j<test_vals_len-1; j++)
		{
			op_status status = OP_STATUS_GOOD;
			cout << "trying " << test_vals[j] << op[i] << test_vals[j+1]
					<< " =" << endl
					<< perform_op (test_vals[j], test_vals[j+1], result, status);
					
			cout<< endl << "status is: " << status
					<< endl << endl;
		}
	}

	return 0;
}

