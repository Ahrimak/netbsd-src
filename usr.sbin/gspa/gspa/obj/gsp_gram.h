#ifndef _yy_defines_h_
#define _yy_defines_h_

#define LEFT_SHIFT 257
#define RIGHT_SHIFT 258
#define ID 259
#define STRING 260
#define NUMBER 261
#define REGISTER 262
#define UMINUS 263
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	long		y_int;
	char		*y_id;
	expr		y_expr;
	operand		y_opnd;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
