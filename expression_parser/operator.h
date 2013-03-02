/** Operator Function **/

typedef int op_code; 
typedef double operand;
typedef int op_status;

/* Status codes, probably just for perform_op() */
#define OP_STATUS_GOOD 0
#define OP_STATUS_WTF 1

/* Internal representation for operators */
#define OP_CODE_ERR -1
#define OP_CODE_ADD 0
#define OP_CODE_SUB 1
#define OP_CODE_MUL 2
#define OP_CODE_DIV 3
#define OP_CODE_LPN 4
#define OP_CODE_RPN 5
#define OP_CODE_TAN 6
#define OP_CODE_COS 7
#define OP_CODE_SIN 8
#define OP_CODE_EXP 9
#define OP_CODE_UNM 10
#define OP_CODE_END 11

/* Precedence table for comparing operators */
const static char PREC_DIM_IN = 11;
const static char PREC_DIM_OUT = 12;

const static bool unary_table[PREC_DIM_OUT] ={
	/*         ADD SUB MUL DIV LPN RPN TAN COS SIN EXP UNM END */
							 0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1
};
const static bool op_prec_table[PREC_DIM_IN][PREC_DIM_OUT] = { 
	/*         ADD SUB MUL DIV LPN RPN TAN COS SIN EXP UNM END */
  {/* ADD */   0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  1   },
	{/* SUB */   0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  1   },
	{/* MUL */   1,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  1   },
	{/* DIV */   1,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  1   },
	{/* LPN */	 1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1   },
	{/* RPN */   0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  1   },
	{/* TAN */	 1,  1,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1   },
	{/* COS */	 1,  1,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1   },
	{/* SIN */   1,  1,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1   },
	{/* EXP */   1,  1,  0,  0,  1,  0,  0,  0,  0,  0,  1,  1   },
	{/* UNM */   1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1   }
};

/** Operator Parser
    Take char[] input of any length and save first operator found.
		Note that there is NO error-checking of multiple operators in
		input.  Third arg is a pass-by-reference bool which is true
    if the current op could be unary minus.
**/

op_code
parse_operator (const char* op, int op_len, bool& check_unm);

/** Perform a mathematical (or pseudo-math) operation according to the
		opcode given.  If the operation is unary, L_arg will be ignored.
		This isn't really logical, but is really convenient.
**/
operand
perform_op (operand L_arg, operand R_arg, op_code op, op_status& status);

/** Returns true if arg0 has a greater precedence than arg1.
**/
operand
compare_prec (op_code new_op, op_code stack_op);

bool
is_unary (op_code op);
