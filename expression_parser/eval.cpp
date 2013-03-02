/** Expression parser 
		created: Ben Lerchin - 2/11/13
		modified: blerchin - 2/14/13
		-Sorry about the mess and missing error checks. I have been messing
		with this for long enough and it's time to move on.
		-Also, I promise never again to use GNU-style braces. Ever.
**/


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <ctype.h> /* includes isdigit() */

#include "operator.h"
#include "Stack.h"
#include "debug.h"

#define NUL '\0'
#define CHAR_SPACE ' '
#define CHAR_NEWLINE '\n'
#define CHAR_HASH '#'
#define CHAR_DOT '.'
#define CHAR_COMMA ','

#define PARSER_STATUS_GOOD 0
#define PARSER_STATUS_NOP 1
#define PARSER_STATUS_SYNTAX 2
#define PARSER_STATUS_FATAL 3
	
#define MAX_OP_LENGTH 3

#define DEBUG 0

/* Define global constants & variables */
Stack* op_stack;
Stack* num_stack;

/* initialize a char string with the length of the biggest operator */
const static int op_str_max = MAX_OP_LENGTH;
char op_str [op_str_max+1];
int op_str_len = 0;

/* stringstream will be used to gather digits and output a number. */
stringstream* num_stream = new stringstream();

op_status status = PARSER_STATUS_GOOD;	
bool check_unm = 1;
double last_result = 0;
bool last_term_num = 0;

void setup_parser()
{
/* Not strictly necessary, but safer in case there is some
	 gnarly syntax error.
*/
	num_stack = new Stack();
	op_stack = new Stack();
	op_stack -> push (OP_CODE_END);
	op_str_len = 0;
	check_unm = 1;
	last_term_num = 0;
	op_str[op_str_len] = NUL;
	cout << "Enter an infix expression to be evaluated" << endl;
}

void reset_parser(bool clear_cin = 1)
{
	delete op_stack;
	delete num_stack;
	if( clear_cin )
	{
		while(cin.peek() != CHAR_NEWLINE)
			cin.get();
	}
	setup_parser();
	cout << "Enter '#' to reference the last successful computation."
				<<endl;
}


/** Take a string (hopefully) containing an operator and either
		push it to the stack or eval it depending on precedence.
**/
int handle_op ( const char* op_str,
								Stack* op_stack, 
								Stack* num_stack)
{
#if DEBUG==1 
	cout << "Handling operator '" << op_str << "'." << endl;
#endif
	op_code new_op = -1;

	if (! (0 == op_str_len))
	{
		new_op = parse_operator (op_str, op_str_len, check_unm);
#if DEBUG==1
		cout << "Operator code is: " << new_op << endl;
#endif
	
		if (new_op == OP_CODE_ERR)
		{
			return PARSER_STATUS_NOP;
		}
		else
		{
#if DEBUG==1
			cout << "Comparing previous op, '" << op_stack -> top()
						<< "' with new op '" << new_op << "'." << endl;
			cout << "Precedence is: " << compare_prec (new_op,
							op_stack -> top() ) << endl;
#endif
	/* Only do if holding a low-precedence operator: */	
			while ((op_stack -> top() != OP_CODE_END) && !compare_prec (new_op, op_stack -> top()) )
			{
				double R_arg = num_stack -> top();
				num_stack -> pop();

				double L_arg = 0;
				if ( !is_unary ( op_stack -> top() ) )
				{
					if( num_stack -> empty() )
					{
						cerr << "Operations remain but not enough numbers to "
											"evaluate." << endl;
						return PARSER_STATUS_SYNTAX;
					}
#if DEBUG==1
					cout << "Operator is binary." <<endl;
#endif
					L_arg = num_stack -> top();
					num_stack -> pop();
				}

				double result = perform_op ( L_arg,
															R_arg,
															op_stack -> top(),
															status );
				last_result = result;
				op_stack -> pop();

#if DEBUG==1
				cout << "Result is: " << result << endl;
#endif
				num_stack -> push (result);
			}
	/* As long as we're not holding a right-paren */
			if (new_op != OP_CODE_RPN)
			{
#if DEBUG==1
				cout << "Pushing operator '" << new_op << "' to stack."<<endl;
#endif
				op_stack -> push( new_op );
			}
	/* only LPN has higher prec than RPN. Eliminate it. */
			else if ( OP_CODE_LPN == op_stack -> top() )
			{
				op_stack -> pop();
			}


#if DEBUG==1
			if( !op_stack -> empty() )
				cout << "Next up on stack: " << op_stack -> top() << endl;
#endif
		}
	}
	return PARSER_STATUS_GOOD;
}

void flush_stack (){
/* sending a right-paren until only op left is OP_CODE_END. */
	while( op_stack -> top() != OP_CODE_END )
	{
			op_str_len = 1;
			status = handle_op (")", op_stack, num_stack);
	}
	op_str_len = 0;
}


int main( int argc, char* argv[] ) {
	setup_parser();
	char new_char = 0;
	double new_num = 0;
	bool first_char = 1;

	while(cin.get(new_char)){
			if(first_char && CHAR_NEWLINE == new_char)
				break;
			first_char=0;
#if DEBUG==1
		cout << "Parser Status: " << status << endl;
#endif

/* N.B.: cin >> double does weird things like eating operators.
	 Do not want!
*/
		
		if ( isdigit (new_char) || CHAR_DOT == new_char || CHAR_COMMA == new_char)
		{
#if DEBUG==1
			cout << "Found digit '" << new_char << "' " <<endl;
#endif
			num_stream -> put(new_char);
			
			if ( !isdigit (cin.peek()) && cin.peek() != CHAR_COMMA 
						&& cin.peek()	!= CHAR_DOT ){
/* If next digit is not a number, we are clear to stop parsing and
	 push it to the stack.
 */
#if DEBUG==1
				cout << "last_term_num: " << last_term_num << endl;
#endif
				if( last_term_num )
				{
					cerr << "Two consecutive numbers with no operator in between." 
						<< endl;
					status = PARSER_STATUS_SYNTAX;
				} 
					(*num_stream) >> new_num;
					num_stack -> push( new_num);
					check_unm = 0;
					last_term_num = 1;
					num_stream -> clear();

			}
		}
		else if ( CHAR_NEWLINE == new_char)
		{
			flush_stack();	
			cout << "Result: " << num_stack -> top() << endl;
			reset_parser(0);
		}
		else if ( CHAR_HASH == new_char)
		{
			num_stack -> push (last_result);
			check_unm = 0;
		}
		else if ( CHAR_SPACE != new_char)
		{
#if DEBUG==1
			cout << "Got " << new_char << " off stream." << endl;
#endif
			if (op_str_len < op_str_max)
			{
/* Push operator tokens out to string, to be flushed when 
 we hit next number.
*/
				op_str [op_str_len] = new_char;
				op_str_len++;
#if DEBUG==1
				cout << "op_str_len: " << op_str_len << endl;
#endif
				op_str [op_str_len] = NUL;
#if DEBUG==1
				cout << "Found operator token '" << op_str [op_str_len-1]
					<< "' " << endl;

				cout << "Sending " << op_str << " to handler." << endl;
#endif
/* Keep trying with each new char found. Won't do anything if 
 * op_str is not a valid operator.
 */
				status = handle_op (op_str, op_stack, num_stack);
				if (status == PARSER_STATUS_GOOD)
				{
					last_term_num = 0;
					op_str_len = 0;
					op_str[0] = NUL;
				}
/* If next char is part of a number and we still haven't found anything,
 * throw a Syntax Error;
 */
				else if ( isdigit (cin.peek()) || CHAR_DOT == cin.peek() ||
						CHAR_COMMA == cin.peek() && status == PARSER_STATUS_NOP) {
					cerr << "Found a token that is not a number or operator." << endl;
					status = PARSER_STATUS_SYNTAX;

				}
			}
			else
			{
				cerr << "Operator '" << op_str << "...' is longer than"
							"	max allowed " << op_str_max << " chars." <<endl;
				status = PARSER_STATUS_SYNTAX;
			}
		} /* /operator detection */
	
/* Alert for syntax errors. Hopefully there is a description printed at
 * site of error.
 */
		if (status == PARSER_STATUS_SYNTAX)
		{
			cerr << "Syntax Error." << endl;
			reset_parser();
			cout ;

		}
/* Break out of the loop and end execution if there is a fatal error. 
*/
		if(status == PARSER_STATUS_FATAL)
		{
			cerr << "Fatal Error!" << endl;
			break;
		}
	}
}


