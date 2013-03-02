/** Operator Functions **/

#include <math.h>

#include "operator.h"
#include "debug.h"

op_code
parse_operator(
        const char* op_str,
        int op_len,
        bool& check_unm
        )
{
  char c = op_str[0];
	/* retain starting value of unm */
	bool unm = check_unm;
	/* default 1. 0 after '(' */
	check_unm = 1;

  switch (c)
	{
    case '+':
      return OP_CODE_ADD;

    case '-':
      if(!unm)
			{
        return OP_CODE_SUB;
			}
      else
			{
/* This is necessary in case of -- */
        return OP_CODE_UNM; 
			}
    
    case '*':
      return OP_CODE_MUL;

    case '/':
      return OP_CODE_DIV;
		
		case '(':
			return OP_CODE_LPN;

		case ')':
			check_unm = 0;
			return OP_CODE_RPN;

    case 't':
      if(   
          op_str[1] == 'a'
          && op_str[2] == 'n'
        )
      {
        return OP_CODE_TAN;
      }
      else
        return OP_CODE_ERR;

    case 's':
        if( 
            op_str[1] == 'i'
            && op_str[2] == 'n'
          )
          return OP_CODE_SIN;
        else
          return OP_CODE_ERR;
    case 'c':
        if(
            op_str[1] == 'o'
            && op_str[2] == 's'
          )
          return OP_CODE_COS;
        else
          return OP_CODE_ERR;
    case 'e':
        if(
            op_str[1] == 'x'
            && op_str[2] == 'p'
          )
          return OP_CODE_EXP;
        else
          return OP_CODE_ERR;

    default:
        return OP_CODE_ERR;
			}

}


operand
perform_op (operand L_arg, operand R_arg, op_code op, op_status& s)
{
	switch (op)
	{
		case OP_CODE_ADD:
			return L_arg + R_arg;

		case OP_CODE_SUB:
			return L_arg - R_arg;

		case OP_CODE_MUL:
			return L_arg * R_arg;

		case OP_CODE_DIV:
			return L_arg / R_arg;

		case OP_CODE_TAN:
			return tan ( R_arg );
		
		case OP_CODE_COS:
			return cos ( R_arg );

		case OP_CODE_SIN:
			return sin ( R_arg );
		case OP_CODE_EXP:
			return exp ( R_arg );
			

		case OP_CODE_UNM:
			return 0 - R_arg;
		case OP_CODE_LPN:
			return L_arg * R_arg;
/* This makes no sense, but does no harm. */
		case OP_CODE_RPN:
			return R_arg;
		

		default:
			cerr << "WTF did you do????";
			s = OP_STATUS_WTF;
			return 0;
	}
}

operand
compare_prec (op_code new_op, op_code stack_op)
{
	return op_prec_table[new_op][stack_op];
}

bool
is_unary (op_code op)
{
	return unary_table[op];

}
