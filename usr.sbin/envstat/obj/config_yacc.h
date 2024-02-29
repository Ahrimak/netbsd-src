#ifndef _yy_defines_h_
#define _yy_defines_h_

#define EOL 257
#define EQUAL 258
#define LBRACE 259
#define RBRACE 260
#define STRING 261
#define NUMBER 262
#define SENSOR 263
#define SENSOR_PROP 264
#define DEVICE_PROP 265
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	char *string;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
