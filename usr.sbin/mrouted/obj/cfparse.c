/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#undef YYBTYACC
#define YYBTYACC 0
#define YYDEBUGSTR YYPREFIX "debug"
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
/*	$NetBSD: cfparse.y,v 1.16 2009/04/17 16:05:43 lukem Exp $	*/

/*
 * Configuration file parser for mrouted.
 *
 * Written by Bill Fenner, NRL, 1994
 * Copyright (c) 1994
 * Naval Research Laboratory (NRL/CCS)
 *                    and the
 * Defense Advanced Research Projects Agency (DARPA)
 *
 * All Rights Reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright notice and
 * this permission notice appear in all copies of the software, derivative
 * works or modified versions, and any portions thereof, and that both notices
 * appear in supporting documentation.
 *
 * NRL AND DARPA ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION AND
 * DISCLAIM ANY LIABILITY OF ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING FROM
 * THE USE OF THIS SOFTWARE.
 */
#include <stdio.h>
#include <stdarg.h>
#include "defs.h"
#include <netdb.h>
#include <ifaddrs.h>

/*
 * Local function declarations
 */
static void		fatal(const char *fmt, ...)
    __attribute__((__format__(__printf__, 1, 2)));
static void		warn(const char *fmt, ...)
        __attribute__((__format__(__printf__, 1, 2)));
static void		yyerror(const char *s);
static char *		next_word(void);
static int		yylex(void);
static u_int32_t	valid_if(char *s);
static const char *	ifconfaddr(u_int32_t a);
int			yyparse(void);

static FILE *f __attribute__((__unused__));	/* XXX egcs */
extern int udp_socket;
const char *configfilename = _PATH_MROUTED_CONF;

extern int cache_lifetime;
extern int max_prune_lifetime;

static int lineno;

static struct uvif *v;

static int order;

struct addrmask {
	u_int32_t	addr;
	int	mask;
};

struct boundnam {
	char		*name;
	struct addrmask	 bound;
};

#define MAXBOUNDS 20

struct boundnam boundlist[MAXBOUNDS];	/* Max. of 20 named boundaries */
int numbounds = 0;			/* Number of named boundaries */

#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 75 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
typedef union
{
	int num;
	char *ptr;
	struct addrmask addrmask;
	u_int32_t addr;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 110 "cfparse.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define CACHE_LIFETIME 257
#define PRUNING 258
#define PHYINT 259
#define TUNNEL 260
#define NAME 261
#define DISABLE 262
#define IGMPV1 263
#define SRCRT 264
#define METRIC 265
#define THRESHOLD 266
#define RATE_LIMIT 267
#define BOUNDARY 268
#define NETMASK 269
#define ALTNET 270
#define SYSNAM 271
#define SYSCONTACT 272
#define SYSVERSION 273
#define SYSLOCATION 274
#define BOOLEAN 275
#define NUMBER 276
#define STRING 277
#define ADDRMASK 278
#define ADDR 279
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    6,    6,    7,    9,    7,   11,    7,    7,    7,
    7,    7,    7,    7,    7,   10,   10,   12,   12,    8,
    8,   14,   14,   14,   14,   14,   14,   14,   13,   13,
   13,   13,   13,   13,   13,   13,    1,    1,    2,    2,
    3,    3,    4,    5,    5,
};
static const YYINT yylen[] = {                            2,
    1,    0,    2,    1,    0,    4,    0,    5,    2,    2,
    3,    2,    2,    2,    2,    0,    2,    1,    1,    0,
    2,    1,    1,    1,    2,    1,    2,    1,    2,    1,
    2,    1,    2,    1,    2,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         2,
    0,    0,    4,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    3,   10,    9,   38,   37,    5,    0,    0,
   12,   13,   14,   15,   20,   40,   39,    7,   43,   11,
    0,   16,   23,   24,    0,    0,    0,    0,    0,    0,
   22,   21,    0,   31,   29,   33,   42,   35,   41,   25,
   44,   45,   27,   19,   17,   18,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  281,  287,  256,  257,  258,  259,  260,  261,  271,  272,
  273,  274,  288,  276,  275,  277,  279,  282,  282,  277,
  277,  277,  277,  277,  290,  277,  279,  283,  278,  285,
  289,  292,  262,  263,  265,  266,  267,  268,  269,  270,
  294,  295,  291,  276,  276,  276,  277,  284,  285,  283,
  278,  279,  286,  264,  293,  294,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          1,
   18,   28,   48,   30,   53,    2,   13,   31,   25,   43,
   32,   55,   41,   42,
};
static const YYINT yysindex[] = {                         0,
    0, -250,    0, -272, -256, -277, -277, -241, -240, -239,
 -236, -235,    0,    0,    0,    0,    0,    0, -274, -251,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -237,    0,    0,    0, -233, -232, -231, -260, -274, -244,
    0,    0, -252,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,   40,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  115,    0,    0,    0,    1,   20,   39,   58,   77,   96,
    0,    0,  121,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
#if YYBTYACC
static const YYINT yycindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
   41,    7,    0,    9,    0,    0,    0,    0,    0,    0,
    0,    0,    6,    0,
};
#define YYTABLESIZE 395
static const YYINT yytable[] = {                         16,
   32,   17,   26,   14,   27,    3,    4,    5,    6,    7,
    8,   54,   35,   36,   37,   38,   47,   29,   15,   30,
    9,   10,   11,   12,   33,   34,   29,   35,   36,   37,
   38,   39,   40,   51,   52,   20,   21,   22,   34,    1,
   23,   24,   44,   45,   46,   50,   49,   19,   56,    0,
    0,    0,    0,    0,    0,    0,    0,   36,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   26,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   28,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    6,    0,    0,    0,    0,    0,
    8,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   32,   32,   32,   32,
   32,   32,   32,   32,   32,   32,   32,   32,   32,   32,
   32,   32,   32,   32,   32,   30,   30,   30,   30,   30,
   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
   30,   30,   30,   30,   34,   34,   34,   34,   34,   34,
   34,   34,   34,   34,   34,   34,   34,   34,   34,   34,
   34,   34,   34,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   26,   26,   26,   26,   26,   26,   26,   26,
    0,   26,   26,   26,   26,   26,   26,   26,   26,   26,
   26,   28,   28,   28,   28,   28,   28,   28,   28,    0,
   28,   28,   28,   28,   28,   28,   28,   28,   28,   28,
    6,    6,    6,    6,    6,    6,    8,    8,    8,    8,
    8,    8,    0,    0,    0,    6,    6,    6,    6,    0,
    0,    8,    8,    8,    8,
};
static const YYINT yycheck[] = {                        277,
    0,  279,  277,  276,  279,  256,  257,  258,  259,  260,
  261,  264,  265,  266,  267,  268,  277,  278,  275,    0,
  271,  272,  273,  274,  262,  263,  278,  265,  266,  267,
  268,  269,  270,  278,  279,  277,  277,  277,    0,    0,
  277,  277,  276,  276,  276,   39,   38,    7,   43,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,    0,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,   -1,   -1,
    0,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  256,  257,  258,  259,
  260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,  272,  273,  274,  256,  257,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  256,  257,  258,  259,  260,  261,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
  272,  273,  274,  256,  257,  258,  259,  260,  261,  262,
  263,  264,  265,  266,  267,  268,  269,  270,  271,  272,
  273,  274,  256,  257,  258,  259,  260,  261,  262,  263,
   -1,  265,  266,  267,  268,  269,  270,  271,  272,  273,
  274,  256,  257,  258,  259,  260,  261,  262,  263,   -1,
  265,  266,  267,  268,  269,  270,  271,  272,  273,  274,
  256,  257,  258,  259,  260,  261,  256,  257,  258,  259,
  260,  261,   -1,   -1,   -1,  271,  272,  273,  274,   -1,
   -1,  271,  272,  273,  274,
};
#if YYBTYACC
static const YYINT yyctable[] = {                        -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 279
#define YYUNDFTOKEN 296
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"$end",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"error","CACHE_LIFETIME","PRUNING",
"PHYINT","TUNNEL","NAME","DISABLE","IGMPV1","SRCRT","METRIC","THRESHOLD",
"RATE_LIMIT","BOUNDARY","NETMASK","ALTNET","SYSNAM","SYSCONTACT","SYSVERSION",
"SYSLOCATION","BOOLEAN","NUMBER","STRING","ADDRMASK","ADDR","$accept","conf",
"interface","addrname","bound","boundary","addrmask","stmts","stmt","ifmods",
"$$1","tunnelmods","$$2","tunnelmod","mod","ifmod","illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : conf",
"conf : stmts",
"stmts :",
"stmts : stmts stmt",
"stmt : error",
"$$1 :",
"stmt : PHYINT interface $$1 ifmods",
"$$2 :",
"stmt : TUNNEL interface addrname $$2 tunnelmods",
"stmt : PRUNING BOOLEAN",
"stmt : CACHE_LIFETIME NUMBER",
"stmt : NAME STRING boundary",
"stmt : SYSNAM STRING",
"stmt : SYSCONTACT STRING",
"stmt : SYSVERSION STRING",
"stmt : SYSLOCATION STRING",
"tunnelmods :",
"tunnelmods : tunnelmods tunnelmod",
"tunnelmod : mod",
"tunnelmod : SRCRT",
"ifmods :",
"ifmods : ifmods ifmod",
"ifmod : mod",
"ifmod : DISABLE",
"ifmod : IGMPV1",
"ifmod : NETMASK addrname",
"ifmod : NETMASK",
"ifmod : ALTNET addrmask",
"ifmod : ALTNET",
"mod : THRESHOLD NUMBER",
"mod : THRESHOLD",
"mod : METRIC NUMBER",
"mod : METRIC",
"mod : RATE_LIMIT NUMBER",
"mod : RATE_LIMIT",
"mod : BOUNDARY bound",
"mod : BOUNDARY",
"interface : ADDR",
"interface : STRING",
"addrname : ADDR",
"addrname : STRING",
"bound : boundary",
"bound : STRING",
"boundary : ADDRMASK",
"addrmask : ADDRMASK",
"addrmask : ADDR",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
YYLTYPE  yyloc; /* position returned by actions */
YYLTYPE  yylloc; /* position from the lexer */
#endif

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(loc, rhs, n) \
do \
{ \
    if (n == 0) \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 0).last_line; \
        (loc).first_column = YYRHSLOC(rhs, 0).last_column; \
        (loc).last_line    = YYRHSLOC(rhs, 0).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, 0).last_column; \
    } \
    else \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 1).first_line; \
        (loc).first_column = YYRHSLOC(rhs, 1).first_column; \
        (loc).last_line    = YYRHSLOC(rhs, n).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, n).last_column; \
    } \
} while (0)
#endif /* YYLLOC_DEFAULT */
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#if YYBTYACC

#ifndef YYLVQUEUEGROWTH
#define YYLVQUEUEGROWTH 32
#endif
#endif /* YYBTYACC */

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#ifndef YYINITSTACKSIZE
#define YYINITSTACKSIZE 200
#endif

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  *p_base;
    YYLTYPE  *p_mark;
#endif
} YYSTACKDATA;
#if YYBTYACC

struct YYParseState_s
{
    struct YYParseState_s *save;    /* Previously saved parser state */
    YYSTACKDATA            yystack; /* saved parser stack */
    int                    state;   /* saved parser state */
    int                    errflag; /* saved error recovery status */
    int                    lexeme;  /* saved index of the conflict lexeme in the lexical queue */
    YYINT                  ctry;    /* saved index in yyctable[] for this conflict */
};
typedef struct YYParseState_s YYParseState;
#endif /* YYBTYACC */
/* variables for the parser stack */
static YYSTACKDATA yystack;
#if YYBTYACC

/* Current parser state */
static YYParseState *yyps = 0;

/* yypath != NULL: do the full parse, starting at *yypath parser state. */
static YYParseState *yypath = 0;

/* Base of the lexical value queue */
static YYSTYPE *yylvals = 0;

/* Current position at lexical value queue */
static YYSTYPE *yylvp = 0;

/* End position of lexical value queue */
static YYSTYPE *yylve = 0;

/* The last allocated position at the lexical value queue */
static YYSTYPE *yylvlim = 0;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
/* Base of the lexical position queue */
static YYLTYPE *yylpsns = 0;

/* Current position at lexical position queue */
static YYLTYPE *yylpp = 0;

/* End position of lexical position queue */
static YYLTYPE *yylpe = 0;

/* The last allocated position at the lexical position queue */
static YYLTYPE *yylplim = 0;
#endif

/* Current position at lexical token queue */
static YYINT  *yylexp = 0;

static YYINT  *yylexemes = 0;
#endif /* YYBTYACC */
#line 392 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
static void
fatal(const char *fmt, ...)
{
	va_list ap;
	char buf[200];

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	logit(LOG_ERR,0,"%s: %s near line %d", configfilename, buf, lineno);
}

static void
warn(const char *fmt, ...)
{
	va_list ap;
	char buf[200];

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	logit(LOG_WARNING,0,"%s: %s near line %d", configfilename, buf, lineno);
}

static void
yyerror(s)
const char *s;
{
	logit(LOG_ERR, 0, "%s: %s near line %d", configfilename, s, lineno);
}

static char *
next_word()
{
	static char buf[1024];
	static char *p=NULL;
	extern FILE *f;
	char *q;

	while (1) {
	    if (!p || !*p) {
		lineno++;
		if (fgets(buf, sizeof(buf), f) == NULL)
		    return NULL;
		p = buf;
	    }
	    while (*p && (*p == ' ' || *p == '\t'))	/* skip whitespace */
		p++;
	    if (*p == '#') {
		p = NULL;		/* skip comments */
		continue;
	    }
	    q = p;
#ifdef SNMP
       if (*p == '"') {
          p++;
	       while (*p && *p != '"' && *p != '\n')
		      p++;		/* find next whitespace */
          if (*p == '"')
             p++;
       } else
#endif
	    while (*p && *p != ' ' && *p != '\t' && *p != '\n')
		p++;		/* find next whitespace */
	    *p++ = '\0';	/* null-terminate string */

	    if (!*q) {
		p = NULL;
		continue;	/* if 0-length string, read another line */
	    }

	    return q;
	}
}

static int
yylex()
{
	int n;
	u_int32_t addr;
	char *q;
	char c;

	if ((q = next_word()) == NULL) {
		return 0;
	}

	if (!strcmp(q,"cache_lifetime"))
		return CACHE_LIFETIME;
	if (!strcmp(q,"pruning"))
		return PRUNING;
	if (!strcmp(q,"phyint"))
		return PHYINT;
	if (!strcmp(q,"tunnel"))
		return TUNNEL;
	if (!strcmp(q,"disable"))
		return DISABLE;
	if (!strcmp(q,"metric"))
		return METRIC;
	if (!strcmp(q,"threshold"))
		return THRESHOLD;
	if (!strcmp(q,"rate_limit"))
		return RATE_LIMIT;
	if (!strcmp(q,"srcrt") || !strcmp(q,"sourceroute"))
		return SRCRT;
	if (!strcmp(q,"boundary"))
		return BOUNDARY;
	if (!strcmp(q,"netmask"))
		return NETMASK;
	if (!strcmp(q,"igmpv1"))
		return IGMPV1;
	if (!strcmp(q,"altnet"))
		return ALTNET;
	if (!strcmp(q,"name"))
		return NAME;
	if (!strcmp(q,"on") || !strcmp(q,"yes")) {
		yylval.num = 1;
		return BOOLEAN;
	}
	if (!strcmp(q,"off") || !strcmp(q,"no")) {
		yylval.num = 0;
		return BOOLEAN;
	}
	if ((addr = inet_parse(q, &n)) != 0xffffffff) {
		yylval.addrmask.mask = n;
		yylval.addrmask.addr = addr;
		return ADDRMASK;
	}
	if ((addr = inet_parse(q,0)) != 0xffffffff &&
	    inet_valid_host(addr)) { 
		yylval.addr = addr;
		return ADDR;
	}
	if (sscanf(q,"0x%8x%c",&n,&c) == 1) {
		yylval.addr = n;
		return ADDR;
	}
	if (sscanf(q,"%d%c",&n,&c) == 1) {
		yylval.num = n;
		return NUMBER;
	}
#ifdef SNMP
	if (!strcmp(q,"sysName"))
		return SYSNAM;
	if (!strcmp(q,"sysContact"))
		return SYSCONTACT;
	if (!strcmp(q,"sysVersion"))
		return SYSVERSION;
	if (!strcmp(q,"sysLocation"))
		return SYSLOCATION;
   if (*q=='"') {
      if (q[ strlen(q)-1 ]=='"')
         q[ strlen(q)-1 ]='\0'; /* trash trailing quote */
      yylval.ptr = q+1;
      return STRING;
   }
#endif
	yylval.ptr = q;
	return STRING;
}

void
config_vifs_from_file()
{
	extern FILE *f;

	order = 0;
	numbounds = 0;
	lineno = 0;

	if ((f = fopen(configfilename, "r")) == NULL) {
	    if (errno != ENOENT)
		logit(LOG_ERR, errno, "can't open %s", configfilename);
	    return;
	}

	yyparse();

	fclose(f);
}

static u_int32_t
valid_if(s)
char *s;
{
	vifi_t vifi;
	struct uvif *uv;

	for (vifi=0, uv=uvifs; vifi<numvifs; vifi++, uv++)
	    if (!strcmp(uv->uv_name, s))
		return uv->uv_lcl_addr;

	return 0;
}

static const char *
ifconfaddr(a)
    u_int32_t a;
{
    static char ifname[IFNAMSIZ];
    struct ifaddrs *ifap, *ifa;

    if (getifaddrs(&ifap) != 0)
	return (NULL);

    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
	if (ifa->ifa_addr->sa_family == AF_INET &&
	    ((struct sockaddr_in *)ifa->ifa_addr)->sin_addr.s_addr == a) {
	    strlcpy(ifname, ifa->ifa_name, sizeof(ifname));
	    freeifaddrs(ifap);
	    return (ifname);
	}
    }

    freeifaddrs(ifap);
    return (NULL);
}
#line 788 "cfparse.c"

/* For use in generated program */
#define yydepth (int)(yystack.s_mark - yystack.s_base)
#if YYBTYACC
#define yytrial (yyps->save)
#endif /* YYBTYACC */

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == 0)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    free(data->p_base);
#endif
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif /* YYPURE || defined(YY_NO_LEAKS) */
#if YYBTYACC

static YYParseState *
yyNewState(unsigned size)
{
    YYParseState *p = (YYParseState *) malloc(sizeof(YYParseState));
    if (p == NULL) return NULL;

    p->yystack.stacksize = size;
    if (size == 0)
    {
        p->yystack.s_base = NULL;
        p->yystack.l_base = NULL;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        p->yystack.p_base = NULL;
#endif
        return p;
    }
    p->yystack.s_base    = (YYINT *) malloc(size * sizeof(YYINT));
    if (p->yystack.s_base == NULL) return NULL;
    p->yystack.l_base    = (YYSTYPE *) malloc(size * sizeof(YYSTYPE));
    if (p->yystack.l_base == NULL) return NULL;
    memset(p->yystack.l_base, 0, size * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    p->yystack.p_base    = (YYLTYPE *) malloc(size * sizeof(YYLTYPE));
    if (p->yystack.p_base == NULL) return NULL;
    memset(p->yystack.p_base, 0, size * sizeof(YYLTYPE));
#endif

    return p;
}

static void
yyFreeState(YYParseState *p)
{
    yyfreestack(&p->yystack);
    free(p);
}
#endif /* YYBTYACC */

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab
#if YYBTYACC
#define YYVALID        do { if (yyps->save)            goto yyvalid; } while(0)
#define YYVALID_NESTED do { if (yyps->save && \
                                yyps->save->save == 0) goto yyvalid; } while(0)
#endif /* YYBTYACC */

int
YYPARSE_DECL()
{
    int yym, yyn, yystate, yyresult;
#if YYBTYACC
    int yynewerrflag;
    YYParseState *yyerrctx = NULL;
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyerror_loc_range[3]; /* position of error start/end (0 unused) */
#endif
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
    if (yydebug)
        fprintf(stderr, "%sdebug[<# of symbols on state stack>]\n", YYPREFIX);
#endif
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(yyerror_loc_range, 0, sizeof(yyerror_loc_range));
#endif

#if YYBTYACC
    yyps = yyNewState(0); if (yyps == 0) goto yyenomem;
    yyps->save = 0;
#endif /* YYBTYACC */
    yym = 0;
    yyn = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base;
#endif
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
#if YYBTYACC
        do {
        if (yylvp < yylve)
        {
            /* we're currently re-reading tokens */
            yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc = *yylpp++;
#endif
            yychar = *yylexp++;
            break;
        }
        if (yyps->save)
        {
            /* in trial mode; save scanner results for future parse attempts */
            if (yylvp == yylvlim)
            {   /* Enlarge lexical value queue */
                size_t p = (size_t) (yylvp - yylvals);
                size_t s = (size_t) (yylvlim - yylvals);

                s += YYLVQUEUEGROWTH;
                if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL) goto yyenomem;
                if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL) goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL) goto yyenomem;
#endif
                yylvp   = yylve = yylvals + p;
                yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp   = yylpe = yylpsns + p;
                yylplim = yylpsns + s;
#endif
                yylexp  = yylexemes + p;
            }
            *yylexp = (YYINT) YYLEX;
            *yylvp++ = yylval;
            yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *yylpp++ = yylloc;
            yylpe++;
#endif
            yychar = *yylexp++;
            break;
        }
        /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
        yychar = YYLEX;
#if YYBTYACC
        } while (0);
#endif /* YYBTYACC */
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, " <%s>", YYSTYPE_TOSTRING(yychar, yylval));
#endif
            fputc('\n', stderr);
        }
#endif
    }
#if YYBTYACC

    /* Do we have a conflict? */
    if (((yyn = yycindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        YYINT ctry;

        if (yypath)
        {
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: CONFLICT in state %d: following successful trial parse\n",
                                YYDEBUGSTR, yydepth, yystate);
#endif
            /* Switch to the next conflict context */
            save = yypath;
            yypath = save->save;
            save->save = NULL;
            ctry = save->ctry;
            if (save->state != yystate) YYABORT;
            yyFreeState(save);

        }
        else
        {

            /* Unresolved conflict - start/continue trial parse */
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
            {
                fprintf(stderr, "%s[%d]: CONFLICT in state %d. ", YYDEBUGSTR, yydepth, yystate);
                if (yyps->save)
                    fputs("ALREADY in conflict, continuing trial parse.\n", stderr);
                else
                    fputs("Starting trial parse.\n", stderr);
            }
#endif
            save                  = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (save == NULL) goto yyenomem;
            save->save            = yyps->save;
            save->state           = yystate;
            save->errflag         = yyerrflag;
            save->yystack.s_mark  = save->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (save->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            save->yystack.l_mark  = save->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (save->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            save->yystack.p_mark  = save->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (save->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            ctry                  = yytable[yyn];
            if (yyctable[ctry] == -1)
            {
#if YYDEBUG
                if (yydebug && yychar >= YYEOF)
                    fprintf(stderr, "%s[%d]: backtracking 1 token\n", YYDEBUGSTR, yydepth);
#endif
                ctry++;
            }
            save->ctry = ctry;
            if (yyps->save == NULL)
            {
                /* If this is a first conflict in the stack, start saving lexemes */
                if (!yylexemes)
                {
                    yylexemes = (YYINT *) malloc((YYLVQUEUEGROWTH) * sizeof(YYINT));
                    if (yylexemes == NULL) goto yyenomem;
                    yylvals   = (YYSTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYSTYPE));
                    if (yylvals == NULL) goto yyenomem;
                    yylvlim   = yylvals + YYLVQUEUEGROWTH;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpsns   = (YYLTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYLTYPE));
                    if (yylpsns == NULL) goto yyenomem;
                    yylplim   = yylpsns + YYLVQUEUEGROWTH;
#endif
                }
                if (yylvp == yylve)
                {
                    yylvp  = yylve = yylvals;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp  = yylpe = yylpsns;
#endif
                    yylexp = yylexemes;
                    if (yychar >= YYEOF)
                    {
                        *yylve++ = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                        *yylpe++ = yylloc;
#endif
                        *yylexp  = (YYINT) yychar;
                        yychar   = YYEMPTY;
                    }
                }
            }
            if (yychar >= YYEOF)
            {
                yylvp--;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp--;
#endif
                yylexp--;
                yychar = YYEMPTY;
            }
            save->lexeme = (int) (yylvp - yylvals);
            yyps->save   = save;
        }
        if (yytable[yyn] == ctry)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                                YYDEBUGSTR, yydepth, yystate, yyctable[ctry]);
#endif
            if (yychar < 0)
            {
                yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp++;
#endif
                yylexp++;
            }
            if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                goto yyoverflow;
            yystate = yyctable[ctry];
            *++yystack.s_mark = (YYINT) yystate;
            *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *++yystack.p_mark = yylloc;
#endif
            yychar  = YYEMPTY;
            if (yyerrflag > 0) --yyerrflag;
            goto yyloop;
        }
        else
        {
            yyn = yyctable[ctry];
            goto yyreduce;
        }
    } /* End of code dealing with conflicts */
#endif /* YYBTYACC */
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                            YYDEBUGSTR, yydepth, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yylloc;
#endif
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;
#if YYBTYACC

    yynewerrflag = 1;
    goto yyerrhandler;
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */

yyerrlab:
    /* explicit YYERROR from an action -- pop the rhs of the rule reduced
     * before looking for error recovery */
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif

    yynewerrflag = 0;
yyerrhandler:
    while (yyps->save)
    {
        int ctry;
        YYParseState *save = yyps->save;
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: ERROR in state %d, CONFLICT BACKTRACKING to state %d, %d tokens\n",
                            YYDEBUGSTR, yydepth, yystate, yyps->save->state,
                    (int)(yylvp - yylvals - yyps->save->lexeme));
#endif
        /* Memorize most forward-looking error state in case it's really an error. */
        if (yyerrctx == NULL || yyerrctx->lexeme < yylvp - yylvals)
        {
            /* Free old saved error context state */
            if (yyerrctx) yyFreeState(yyerrctx);
            /* Create and fill out new saved error context state */
            yyerrctx                 = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (yyerrctx == NULL) goto yyenomem;
            yyerrctx->save           = yyps->save;
            yyerrctx->state          = yystate;
            yyerrctx->errflag        = yyerrflag;
            yyerrctx->yystack.s_mark = yyerrctx->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (yyerrctx->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yyerrctx->yystack.l_mark = yyerrctx->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (yyerrctx->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yyerrctx->yystack.p_mark = yyerrctx->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (yyerrctx->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yyerrctx->lexeme         = (int) (yylvp - yylvals);
        }
        yylvp          = yylvals   + save->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yylpp          = yylpsns   + save->lexeme;
#endif
        yylexp         = yylexemes + save->lexeme;
        yychar         = YYEMPTY;
        yystack.s_mark = yystack.s_base + (save->yystack.s_mark - save->yystack.s_base);
        memcpy (yystack.s_base, save->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
        yystack.l_mark = yystack.l_base + (save->yystack.l_mark - save->yystack.l_base);
        memcpy (yystack.l_base, save->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yystack.p_mark = yystack.p_base + (save->yystack.p_mark - save->yystack.p_base);
        memcpy (yystack.p_base, save->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
        ctry           = ++save->ctry;
        yystate        = save->state;
        /* We tried shift, try reduce now */
        if ((yyn = yyctable[ctry]) >= 0) goto yyreduce;
        yyps->save     = save->save;
        save->save     = NULL;
        yyFreeState(save);

        /* Nothing left on the stack -- error */
        if (!yyps->save)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%sdebug[%d,trial]: trial parse FAILED, entering ERROR mode\n",
                                YYPREFIX, yydepth);
#endif
            /* Restore state as it was in the most forward-advanced error */
            yylvp          = yylvals   + yyerrctx->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylpp          = yylpsns   + yyerrctx->lexeme;
#endif
            yylexp         = yylexemes + yyerrctx->lexeme;
            yychar         = yylexp[-1];
            yylval         = yylvp[-1];
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc         = yylpp[-1];
#endif
            yystack.s_mark = yystack.s_base + (yyerrctx->yystack.s_mark - yyerrctx->yystack.s_base);
            memcpy (yystack.s_base, yyerrctx->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yystack.l_mark = yystack.l_base + (yyerrctx->yystack.l_mark - yyerrctx->yystack.l_base);
            memcpy (yystack.l_base, yyerrctx->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yystack.p_mark = yystack.p_base + (yyerrctx->yystack.p_mark - yyerrctx->yystack.p_base);
            memcpy (yystack.p_base, yyerrctx->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yystate        = yyerrctx->state;
            yyFreeState(yyerrctx);
            yyerrctx       = NULL;
        }
        yynewerrflag = 1;
    }
    if (yynewerrflag == 0) goto yyinrecovery;
#endif /* YYBTYACC */

    YYERROR_CALL("syntax error");
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yyerror_loc_range[1] = yylloc; /* lookahead position is error start position */
#endif

#if !YYBTYACC
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
#endif
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: state %d, error recovery shifting to state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* lookahead position is error end position */
                yyerror_loc_range[2] = yylloc;
                YYLLOC_DEFAULT(yyloc, yyerror_loc_range, 2); /* position of error span */
                *++yystack.p_mark = yyloc;
#endif
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: error recovery discarding state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* the current TOS position is the error start position */
                yyerror_loc_range[1] = *yystack.p_mark;
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
                if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark, yystack.p_mark);
#else
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
                --yystack.s_mark;
                --yystack.l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                --yystack.p_mark;
#endif
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, error recovery discarding token %d (%s)\n",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
        }
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval, &yylloc);
#else
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
    yym = yylen[yyn];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: state %d, reducing by rule %d (%s)",
                        YYDEBUGSTR, yydepth, yystate, yyn, yyrule[yyn]);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            if (yym > 0)
            {
                int i;
                fputc('<', stderr);
                for (i = yym; i > 0; i--)
                {
                    if (i != yym) fputs(", ", stderr);
                    fputs(YYSTYPE_TOSTRING(yystos[yystack.s_mark[1-i]],
                                           yystack.l_mark[1-i]), stderr);
                }
                fputc('>', stderr);
            }
#endif
        fputc('\n', stderr);
    }
#endif
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)

    /* Perform position reduction */
    memset(&yyloc, 0, sizeof(yyloc));
#if YYBTYACC
    if (!yytrial)
#endif /* YYBTYACC */
    {
        YYLLOC_DEFAULT(yyloc, &yystack.p_mark[-yym], yym);
        /* just in case YYERROR is invoked within the action, save
           the start of the rhs as the error start position */
        yyerror_loc_range[1] = yystack.p_mark[1-yym];
    }
#endif

    switch (yyn)
    {
case 5:
#line 109 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{

			vifi_t vifi;

			if (order)
			    fatal("phyints must appear before tunnels");

			for (vifi = 0, v = uvifs;
			     vifi < numvifs;
			     ++vifi, ++v)
			    if (!(v->uv_flags & VIFF_TUNNEL) &&
				yystack.l_mark[0].addr == v->uv_lcl_addr)
				break;
			
			if (vifi == numvifs)
			    fatal("%s is not a configured interface",
				inet_fmt(yystack.l_mark[0].addr));

					}
#line 1 ""
break;
case 7:
#line 129 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{
			const char *ifname;
			struct ifreq ffr;
			vifi_t vifi;

			order++;

			ifname = ifconfaddr(yystack.l_mark[-1].addr);
			if (ifname == 0)
			    fatal("Tunnel local address %s is not mine",
				inet_fmt(yystack.l_mark[-1].addr));

			strncpy(ffr.ifr_name, ifname, sizeof(ffr.ifr_name));
			if (ioctl(udp_socket, SIOCGIFFLAGS, (char *)&ffr)<0)
			    fatal("ioctl SIOCGIFFLAGS on %s",ffr.ifr_name);
			if (ffr.ifr_flags & IFF_LOOPBACK)
			    fatal("Tunnel local address %s is a loopback interface",
				inet_fmt(yystack.l_mark[-1].addr));

			if (ifconfaddr(yystack.l_mark[0].addr) != 0)
			    fatal("Tunnel remote address %s is one of mine",
				inet_fmt(yystack.l_mark[0].addr));

			for (vifi = 0, v = uvifs;
			     vifi < numvifs;
			     ++vifi, ++v)
			    if (v->uv_flags & VIFF_TUNNEL) {
				if (yystack.l_mark[0].addr == v->uv_rmt_addr)
				    fatal("Duplicate tunnel to %s",
					inet_fmt(yystack.l_mark[0].addr));
			    } else if (!(v->uv_flags & VIFF_DISABLED)) {
				if ((yystack.l_mark[0].addr & v->uv_subnetmask) == v->uv_subnet)
				    fatal("Unnecessary tunnel to %s",
					inet_fmt(yystack.l_mark[0].addr));
			    }

			if (numvifs == MAXVIFS)
			    fatal("too many vifs");

			v = &uvifs[numvifs];
			v->uv_flags	= VIFF_TUNNEL;
			v->uv_metric	= DEFAULT_METRIC;
			v->uv_rate_limit= DEFAULT_TUN_RATE_LIMIT;
			v->uv_threshold	= DEFAULT_THRESHOLD;
			v->uv_lcl_addr	= yystack.l_mark[-1].addr;
			v->uv_rmt_addr	= yystack.l_mark[0].addr;
			v->uv_subnet	= 0;
			v->uv_subnetmask= 0;
			v->uv_subnetbcast= 0;
			strncpy(v->uv_name, ffr.ifr_name, IFNAMSIZ);
			v->uv_groups	= NULL;
			v->uv_neighbors	= NULL;
			v->uv_acl	= NULL;
			v->uv_addrs	= NULL;

			if (!(ffr.ifr_flags & IFF_UP)) {
			    v->uv_flags |= VIFF_DOWN;
			    vifs_down = TRUE;
			}
					}
#line 1 ""
break;
case 8:
#line 190 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{
			logit(LOG_INFO, 0,
			    "installing tunnel from %s to %s as vif #%u - rate=%d",
			    inet_fmt(yystack.l_mark[-3].addr),
			    inet_fmt(yystack.l_mark[-2].addr),
			    numvifs, v->uv_rate_limit);

			++numvifs;
					}
#line 1 ""
break;
case 9:
#line 199 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ pruning = yystack.l_mark[0].num; }
#line 1 ""
break;
case 10:
#line 200 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ cache_lifetime = yystack.l_mark[0].num;
				      max_prune_lifetime = cache_lifetime * 2;
				    }
#line 1 ""
break;
case 11:
#line 203 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ if (numbounds >= MAXBOUNDS) {
					fatal("Too many named boundaries (max %d)", MAXBOUNDS);
				      }

				      boundlist[numbounds].name = strdup(yystack.l_mark[-1].ptr);
				      boundlist[numbounds++].bound = yystack.l_mark[0].addrmask;
				    }
#line 1 ""
break;
case 12:
#line 210 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{
#ifdef SNMP
			    set_sysName(yystack.l_mark[0].ptr);
#endif /* SNMP */
			    }
#line 1 ""
break;
case 13:
#line 215 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{
#ifdef SNMP
			    set_sysContact(yystack.l_mark[0].ptr);
#endif /* SNMP */
			    }
#line 1 ""
break;
case 14:
#line 220 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{
#ifdef SNMP
			    set_sysVersion(yystack.l_mark[0].ptr);
#endif /* SNMP */
			    }
#line 1 ""
break;
case 15:
#line 225 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{
#ifdef SNMP
			    set_sysLocation(yystack.l_mark[0].ptr);
#endif /* SNMP */
			    }
#line 1 ""
break;
case 19:
#line 237 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ fatal("Source-route tunnels not supported"); }
#line 1 ""
break;
case 23:
#line 245 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ v->uv_flags |= VIFF_DISABLED; }
#line 1 ""
break;
case 24:
#line 246 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ v->uv_flags |= VIFF_IGMPV1; }
#line 1 ""
break;
case 25:
#line 247 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{
				  u_int32_t subnet, mask;

				  mask = yystack.l_mark[0].addr;
				  subnet = v->uv_lcl_addr & mask;
				  if (!inet_valid_subnet(subnet, mask))
					fatal("Invalid netmask");
				  v->uv_subnet = subnet;
				  v->uv_subnetmask = mask;
				  v->uv_subnetbcast = subnet | ~mask;
				}
#line 1 ""
break;
case 26:
#line 258 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{

		    warn("Expected address after netmask keyword, ignored");

				}
#line 1 ""
break;
case 27:
#line 263 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{

		    struct phaddr *ph;

		    ph = (struct phaddr *)malloc(sizeof(struct phaddr));
		    if (ph == NULL)
			fatal("out of memory");
		    if (yystack.l_mark[0].addrmask.mask) {
			VAL_TO_MASK(ph->pa_subnetmask, yystack.l_mark[0].addrmask.mask);
		    } else
			ph->pa_subnetmask = v->uv_subnetmask;
		    ph->pa_subnet = yystack.l_mark[0].addrmask.addr & ph->pa_subnetmask;
		    ph->pa_subnetbcast = ph->pa_subnet | ~ph->pa_subnetmask;
		    if (yystack.l_mark[0].addrmask.addr & ~ph->pa_subnetmask)
			warn("Extra subnet %s/%d has host bits set",
				inet_fmt(yystack.l_mark[0].addrmask.addr), yystack.l_mark[0].addrmask.mask);
		    ph->pa_next = v->uv_addrs;
		    v->uv_addrs = ph;

				}
#line 1 ""
break;
case 28:
#line 283 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{

		    warn("Expected address after altnet keyword, ignored");

				}
#line 1 ""
break;
case 29:
#line 290 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ if (yystack.l_mark[0].num < 1 || yystack.l_mark[0].num > 255)
				    fatal("Invalid threshold %d",yystack.l_mark[0].num);
				  v->uv_threshold = yystack.l_mark[0].num;
				}
#line 1 ""
break;
case 30:
#line 294 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{

		    warn("Expected number after threshold keyword, ignored");

				}
#line 1 ""
break;
case 31:
#line 299 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ if (yystack.l_mark[0].num < 1 || yystack.l_mark[0].num > UNREACHABLE)
				    fatal("Invalid metric %d",yystack.l_mark[0].num);
				  v->uv_metric = yystack.l_mark[0].num;
				}
#line 1 ""
break;
case 32:
#line 303 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{

		    warn("Expected number after metric keyword, ignored");

				}
#line 1 ""
break;
case 33:
#line 308 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ if (yystack.l_mark[0].num > MAX_RATE_LIMIT)
				    fatal("Invalid rate_limit %d",yystack.l_mark[0].num);
				  v->uv_rate_limit = yystack.l_mark[0].num;
				}
#line 1 ""
break;
case 34:
#line 312 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{

		    warn("Expected number after rate_limit keyword, ignored");

				}
#line 1 ""
break;
case 35:
#line 317 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{

		    struct vif_acl *v_acl;

		    v_acl = (struct vif_acl *)malloc(sizeof(struct vif_acl));
		    if (v_acl == NULL)
			fatal("out of memory");
		    VAL_TO_MASK(v_acl->acl_mask, yystack.l_mark[0].addrmask.mask);
		    v_acl->acl_addr = yystack.l_mark[0].addrmask.addr & v_acl->acl_mask;
		    if (yystack.l_mark[0].addrmask.addr & ~v_acl->acl_mask)
			warn("Boundary spec %s/%d has host bits set",
				inet_fmt(yystack.l_mark[0].addrmask.addr),yystack.l_mark[0].addrmask.mask);
		    v_acl->acl_next = v->uv_acl;
		    v->uv_acl = v_acl;

				}
#line 1 ""
break;
case 36:
#line 333 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{

		warn("Expected boundary spec after boundary keyword, ignored");

				}
#line 1 ""
break;
case 37:
#line 340 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ yyval.addr = yystack.l_mark[0].addr; }
#line 1 ""
break;
case 38:
#line 341 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{
				  yyval.addr = valid_if(yystack.l_mark[0].ptr);
				  if (yyval.addr == 0)
					fatal("Invalid interface name %s",yystack.l_mark[0].ptr);
				}
#line 1 ""
break;
case 39:
#line 348 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ yyval.addr = yystack.l_mark[0].addr; }
#line 1 ""
break;
case 40:
#line 349 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ struct hostent *hp;

				  if ((hp = gethostbyname(yystack.l_mark[0].ptr)) == NULL)
				    fatal("No such host %s", yystack.l_mark[0].ptr);

				  if (hp->h_addr_list[1])
				    fatal("Hostname %s does not %s",
					yystack.l_mark[0].ptr, "map to a unique address");

				  bcopy(hp->h_addr_list[0], &yyval.addr,
					    hp->h_length);
				}
#line 1 ""
break;
case 41:
#line 362 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ yyval.addrmask = yystack.l_mark[0].addrmask; }
#line 1 ""
break;
case 42:
#line 363 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ int i;

				  for (i=0; i < numbounds; i++) {
				    if (!strcmp(boundlist[i].name, yystack.l_mark[0].ptr)) {
					yyval.addrmask = boundlist[i].bound;
					break;
				    }
				  }
				  if (i == numbounds) {
				    fatal("Invalid boundary name %s",yystack.l_mark[0].ptr);
				  }
				}
#line 1 ""
break;
case 43:
#line 377 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{

			if ((ntohl(yystack.l_mark[0].addrmask.addr) & 0xff000000) != 0xef000000) {
			    fatal("Boundaries must be 239.x.x.x, not %s/%d",
				inet_fmt(yystack.l_mark[0].addrmask.addr), yystack.l_mark[0].addrmask.mask);
			}
			yyval.addrmask = yystack.l_mark[0].addrmask;

				}
#line 1 ""
break;
case 44:
#line 388 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ yyval.addrmask = yystack.l_mark[0].addrmask; }
#line 1 ""
break;
case 45:
#line 389 "/home/elily008/netbsd-src/usr.sbin/mrouted/cfparse.y"
	{ yyval.addrmask.addr = yystack.l_mark[0].addr; yyval.addrmask.mask = 0; }
#line 1 ""
break;
#line 1848 "cfparse.c"
    default:
        break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
        {
            fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[YYFINAL], yyval));
#endif
            fprintf(stderr, "shifting from state 0 to final state %d\n", YYFINAL);
        }
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yyloc;
#endif
        if (yychar < 0)
        {
#if YYBTYACC
            do {
            if (yylvp < yylve)
            {
                /* we're currently re-reading tokens */
                yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylloc = *yylpp++;
#endif
                yychar = *yylexp++;
                break;
            }
            if (yyps->save)
            {
                /* in trial mode; save scanner results for future parse attempts */
                if (yylvp == yylvlim)
                {   /* Enlarge lexical value queue */
                    size_t p = (size_t) (yylvp - yylvals);
                    size_t s = (size_t) (yylvlim - yylvals);

                    s += YYLVQUEUEGROWTH;
                    if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL)
                        goto yyenomem;
                    if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL)
                        goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL)
                        goto yyenomem;
#endif
                    yylvp   = yylve = yylvals + p;
                    yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp   = yylpe = yylpsns + p;
                    yylplim = yylpsns + s;
#endif
                    yylexp  = yylexemes + p;
                }
                *yylexp = (YYINT) YYLEX;
                *yylvp++ = yylval;
                yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                *yylpp++ = yylloc;
                yylpe++;
#endif
                yychar = *yylexp++;
                break;
            }
            /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
            yychar = YYLEX;
#if YYBTYACC
            } while (0);
#endif /* YYBTYACC */
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)\n",
                                YYDEBUGSTR, yydepth, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[yystate], yyval));
#endif
        fprintf(stderr, "shifting from state %d to state %d\n", *yystack.s_mark, yystate);
    }
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    *++yystack.p_mark = yyloc;
#endif
    goto yyloop;
#if YYBTYACC

    /* Reduction declares that this path is valid. Set yypath and do a full parse */
yyvalid:
    if (yypath) YYABORT;
    while (yyps->save)
    {
        YYParseState *save = yyps->save;
        yyps->save = save->save;
        save->save = yypath;
        yypath = save;
    }
#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%s[%d]: state %d, CONFLICT trial successful, backtracking to state %d, %d tokens\n",
                        YYDEBUGSTR, yydepth, yystate, yypath->state, (int)(yylvp - yylvals - yypath->lexeme));
#endif
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    yylvp          = yylvals + yypath->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yylpp          = yylpsns + yypath->lexeme;
#endif
    yylexp         = yylexemes + yypath->lexeme;
    yychar         = YYEMPTY;
    yystack.s_mark = yystack.s_base + (yypath->yystack.s_mark - yypath->yystack.s_base);
    memcpy (yystack.s_base, yypath->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
    yystack.l_mark = yystack.l_base + (yypath->yystack.l_mark - yypath->yystack.l_base);
    memcpy (yystack.l_base, yypath->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base + (yypath->yystack.p_mark - yypath->yystack.p_base);
    memcpy (yystack.p_base, yypath->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
    yystate        = yypath->state;
    goto yyloop;
#endif /* YYBTYACC */

yyoverflow:
    YYERROR_CALL("yacc stack overflow");
#if YYBTYACC
    goto yyabort_nomem;
yyenomem:
    YYERROR_CALL("memory exhausted");
yyabort_nomem:
#endif /* YYBTYACC */
    yyresult = 2;
    goto yyreturn;

yyabort:
    yyresult = 1;
    goto yyreturn;

yyaccept:
#if YYBTYACC
    if (yyps->save) goto yyvalid;
#endif /* YYBTYACC */
    yyresult = 0;

yyreturn:
#if defined(YYDESTRUCT_CALL)
    if (yychar != YYEOF && yychar != YYEMPTY)
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval, &yylloc);
#else
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */

    {
        YYSTYPE *pv;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYLTYPE *pp;

        for (pv = yystack.l_base, pp = yystack.p_base; pv <= yystack.l_mark; ++pv, ++pp)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv, pp);
#else
        for (pv = yystack.l_base; pv <= yystack.l_mark; ++pv)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
    }
#endif /* defined(YYDESTRUCT_CALL) */

#if YYBTYACC
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    while (yyps)
    {
        YYParseState *save = yyps;
        yyps = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
    while (yypath)
    {
        YYParseState *save = yypath;
        yypath = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
#endif /* YYBTYACC */
    yyfreestack(&yystack);
    return (yyresult);
}
