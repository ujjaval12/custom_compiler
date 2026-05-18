/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "1807002.y"

	#include<stdio.h>
	#include <math.h>
	#include <string.h>
	#include <stdlib.h>
	int yylex(void);
	void yyerror(const char *s);
	void open_tac_file(void);
	int cnt=1,cntt=0,val,track=0;

	/* Phase 4: TAC Generator */
	int temp_count = 0;
	int label_count = 0;
	FILE *tac_file        = NULL;   /* Phase 4 TAC output        */
	FILE *lexer_file      = NULL;   /* Phase 1 Lexer output      */
	FILE *parser_file     = NULL;   /* Phase 2 Parser output     */
	FILE *semantic_file   = NULL;   /* Phase 3 Semantic output   */

	char* new_temp() {
		char *t = (char*)malloc(16);
		sprintf(t, "t%d", temp_count++);
		return t;
	}

	char* new_label() {
		char *l = (char*)malloc(16);
		sprintf(l, "L%d", label_count++);
		return l;
	}

	/* Structured IF/ELIF/ELSE TAC helpers (needed so branch bodies don't execute unconditionally) */
	void emit_tac(const char *line);
	extern char tac_buf[256];
	typedef struct if_ctx {
		char *end;
		char *next;
	} if_ctx;
	static if_ctx if_stack[128];
	static int if_sp = -1;

	static void if_begin_tac(int cond) {
		char *l_true = new_label();
		char *l_next = new_label();
		char *l_end  = new_label();
		sprintf(tac_buf, "if %d goto %s", cond, l_true);
		emit_tac(tac_buf);
		sprintf(tac_buf, "goto %s", l_next);
		emit_tac(tac_buf);
		sprintf(tac_buf, "%s:", l_true);
		emit_tac(tac_buf);
		if_sp++;
		if_stack[if_sp].end = l_end;
		if_stack[if_sp].next = l_next;
	}

	static void elif_begin_tac(int cond) {
		/* assumes the previous branch has already emitted the fallthrough label */
		char *l_true = new_label();
		char *l_next = new_label();
		sprintf(tac_buf, "if %d goto %s", cond, l_true);
		emit_tac(tac_buf);
		sprintf(tac_buf, "goto %s", l_next);
		emit_tac(tac_buf);
		sprintf(tac_buf, "%s:", l_true);
		emit_tac(tac_buf);
		if(if_sp >= 0) {
			if_stack[if_sp].next = l_next;
		}
	}

	static void if_after_branch_tac(void) {
		if(if_sp < 0) return;
		sprintf(tac_buf, "goto %s", if_stack[if_sp].end);
		emit_tac(tac_buf);
		sprintf(tac_buf, "%s:", if_stack[if_sp].next);
		emit_tac(tac_buf);
	}

	static void if_finish_tac(void) {
		if(if_sp < 0) return;
		sprintf(tac_buf, "%s:", if_stack[if_sp].end);
		emit_tac(tac_buf);
		if_sp--;
	}

	void emit_tac(const char *line) {
		if(tac_file) fprintf(tac_file, "%s\n", line);
		printf("[TAC] %s\n", line);
	}

	void emit_parser(const char *line) {
		if(parser_file) fprintf(parser_file, "%s\n", line);
	}

	void emit_semantic(const char *line) {
		if(semantic_file) fprintf(semantic_file, "%s\n", line);
	}

	char tac_buf[256];
	typedef struct entry {
    	char *str;
    	int n;
		int isArray;
		int size;
		int arrayVal[1000];
	}vartable;
	vartable fntn[1000],f[1000],vptr[1000];
	
	int cnt2=1; 
	


		int total_Var=0;
		int is_var_exist(char *varName){
            for(int i = 0 ; i<total_Var; i++){
                if(strcmp(vptr[i].str,varName)==0){
                    return 1;
                }
            }
            return 0;
        }

        /* Get the index of variable that is called. If not found return -1. */
        int get_Var_Id(char *varName){
            for(int i = 0 ; i<total_Var; i++){
                if(strcmp(vptr[i].str,varName)==0){
                    return i;
                }
            }
            return -1;
        }
		void showExistance(char *varName){
            
            printf("%s is already Declared.\n",varName);
            
        }

		void declare_Var_table(char *varName,int val)
		{
			vptr[total_Var].str = varName;
			vptr[total_Var].n = val;
			
		}





	

#line 222 "1807002.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "1807002.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FUNC_NUM = 3,                   /* FUNC_NUM  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_VAR = 5,                        /* VAR  */
  YYSYMBOL_FUNC_STR = 6,                   /* FUNC_STR  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_ELIF = 8,                       /* ELIF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_MAIN = 10,                      /* MAIN  */
  YYSYMBOL_INT = 11,                       /* INT  */
  YYSYMBOL_FLOAT = 12,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 13,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 14,                      /* CHAR  */
  YYSYMBOL_LP = 15,                        /* LP  */
  YYSYMBOL_RP = 16,                        /* RP  */
  YYSYMBOL_LB = 17,                        /* LB  */
  YYSYMBOL_RB = 18,                        /* RB  */
  YYSYMBOL_CM = 19,                        /* CM  */
  YYSYMBOL_SM = 20,                        /* SM  */
  YYSYMBOL_PLUS = 21,                      /* PLUS  */
  YYSYMBOL_MINUS = 22,                     /* MINUS  */
  YYSYMBOL_MULT = 23,                      /* MULT  */
  YYSYMBOL_DIV = 24,                       /* DIV  */
  YYSYMBOL_POW = 25,                       /* POW  */
  YYSYMBOL_ASSIGN = 26,                    /* ASSIGN  */
  YYSYMBOL_COL = 27,                       /* COL  */
  YYSYMBOL_WHILE = 28,                     /* WHILE  */
  YYSYMBOL_WHILE_END = 29,                 /* WHILE_END  */
  YYSYMBOL_BREAK = 30,                     /* BREAK  */
  YYSYMBOL_DEFAULT = 31,                   /* DEFAULT  */
  YYSYMBOL_CASE = 32,                      /* CASE  */
  YYSYMBOL_SWITCH = 33,                    /* SWITCH  */
  YYSYMBOL_SWITCH_END = 34,                /* SWITCH_END  */
  YYSYMBOL_inc = 35,                       /* inc  */
  YYSYMBOL_dec = 36,                       /* dec  */
  YYSYMBOL_MOD = 37,                       /* MOD  */
  YYSYMBOL_LT = 38,                        /* LT  */
  YYSYMBOL_GT = 39,                        /* GT  */
  YYSYMBOL_LTE = 40,                       /* LTE  */
  YYSYMBOL_GTE = 41,                       /* GTE  */
  YYSYMBOL_EEQL = 42,                      /* EEQL  */
  YYSYMBOL_NEQL = 43,                      /* NEQL  */
  YYSYMBOL_AND = 44,                       /* AND  */
  YYSYMBOL_OR = 45,                        /* OR  */
  YYSYMBOL_NOT = 46,                       /* NOT  */
  YYSYMBOL_XOR = 47,                       /* XOR  */
  YYSYMBOL_SIN = 48,                       /* SIN  */
  YYSYMBOL_COS = 49,                       /* COS  */
  YYSYMBOL_TAN = 50,                       /* TAN  */
  YYSYMBOL_SQRT = 51,                      /* SQRT  */
  YYSYMBOL_LOG = 52,                       /* LOG  */
  YYSYMBOL_LOG2 = 53,                      /* LOG2  */
  YYSYMBOL_LN = 54,                        /* LN  */
  YYSYMBOL_FACTORIAL = 55,                 /* FACTORIAL  */
  YYSYMBOL_ARRAY = 56,                     /* ARRAY  */
  YYSYMBOL_size_of = 57,                   /* size_of  */
  YYSYMBOL_CALL = 58,                      /* CALL  */
  YYSYMBOL_PRINT = 59,                     /* PRINT  */
  YYSYMBOL_TAKE_INPUT = 60,                /* TAKE_INPUT  */
  YYSYMBOL_STRING_LITERAL = 61,            /* STRING_LITERAL  */
  YYSYMBOL_62_ = 62,                       /* '('  */
  YYSYMBOL_63_ = 63,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 64,                  /* $accept  */
  YYSYMBOL_program = 65,                   /* program  */
  YYSYMBOL_input_tail = 66,                /* input_tail  */
  YYSYMBOL_cstatement = 67,                /* cstatement  */
  YYSYMBOL_block = 68,                     /* block  */
  YYSYMBOL_block_items = 69,               /* block_items  */
  YYSYMBOL_func_block = 70,                /* func_block  */
  YYSYMBOL_func_call = 71,                 /* func_call  */
  YYSYMBOL_Parameter = 72,                 /* Parameter  */
  YYSYMBOL_para = 73,                      /* para  */
  YYSYMBOL_pass_Parameter = 74,            /* pass_Parameter  */
  YYSYMBOL_cdeclaration = 75,              /* cdeclaration  */
  YYSYMBOL_TYPE = 76,                      /* TYPE  */
  YYSYMBOL_ID1 = 77,                       /* ID1  */
  YYSYMBOL_ID = 78,                        /* ID  */
  YYSYMBOL_statement = 79,                 /* statement  */
  YYSYMBOL_80_1 = 80,                      /* $@1  */
  YYSYMBOL_81_2 = 81,                      /* $@2  */
  YYSYMBOL_if_tail = 82,                   /* if_tail  */
  YYSYMBOL_83_3 = 83,                      /* $@3  */
  YYSYMBOL_84_4 = 84,                      /* $@4  */
  YYSYMBOL_BASE = 85,                      /* BASE  */
  YYSYMBOL_Bas = 86,                       /* Bas  */
  YYSYMBOL_Cs = 87,                        /* Cs  */
  YYSYMBOL_Dflt = 88,                      /* Dflt  */
  YYSYMBOL_expression = 89,                /* expression  */
  YYSYMBOL_switch_expression = 90          /* switch_expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   917

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  95
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  218

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      62,    63,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   187,   187,   188,   202,   205,   206,   209,   210,   211,
     212,   215,   217,   218,   221,   250,   256,   257,   258,   260,
     263,   264,   265,   269,   270,   274,   301,   303,   305,   309,
     310,   312,   341,   368,   369,   370,   376,   382,   411,   415,
     421,   438,   464,   464,   464,   468,   486,   487,   488,   488,
     488,   493,   494,   497,   498,   501,   510,   520,   521,   528,
     536,   544,   552,   560,   573,   581,   583,   584,   586,   590,
     595,   601,   605,   610,   614,   618,   622,   626,   631,   636,
     641,   645,   649,   655,   660,   665,   670,   675,   679,   684,
     696,   698,   700,   702,   704,   714
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "FUNC_NUM", "NUM",
  "VAR", "FUNC_STR", "IF", "ELIF", "ELSE", "MAIN", "INT", "FLOAT",
  "DOUBLE", "CHAR", "LP", "RP", "LB", "RB", "CM", "SM", "PLUS", "MINUS",
  "MULT", "DIV", "POW", "ASSIGN", "COL", "WHILE", "WHILE_END", "BREAK",
  "DEFAULT", "CASE", "SWITCH", "SWITCH_END", "inc", "dec", "MOD", "LT",
  "GT", "LTE", "GTE", "EEQL", "NEQL", "AND", "OR", "NOT", "XOR", "SIN",
  "COS", "TAN", "SQRT", "LOG", "LOG2", "LN", "FACTORIAL", "ARRAY",
  "size_of", "CALL", "PRINT", "TAKE_INPUT", "STRING_LITERAL", "'('", "')'",
  "$accept", "program", "input_tail", "cstatement", "block", "block_items",
  "func_block", "func_call", "Parameter", "para", "pass_Parameter",
  "cdeclaration", "TYPE", "ID1", "ID", "statement", "$@1", "$@2",
  "if_tail", "$@3", "$@4", "BASE", "Bas", "Cs", "Dflt", "expression",
  "switch_expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-162)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,     4,    10,    21,     2,    16,  -162,  -162,  -162,    -1,
      69,  -162,  -162,  -162,     3,  -162,    30,  -162,    -9,    36,
     263,  -162,  -162,   263,   263,    60,    67,   263,    23,    24,
      34,    37,    38,    39,    41,    68,    87,    93,   212,    99,
     263,  -162,    -1,  -162,   668,    88,    -1,  -162,   102,   263,
     263,    92,   535,   104,   246,   246,   263,   105,   835,   263,
     263,   263,   263,   263,   263,   263,    -1,    90,    96,    94,
     696,   110,   297,   107,  -162,   263,   263,   263,   263,   263,
    -162,  -162,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,  -162,   193,  -162,    97,   724,   570,   112,  -162,
    -162,   605,  -162,    56,   326,   355,   384,   413,   442,   471,
     500,   108,  -162,   128,  -162,  -162,  -162,  -162,   109,    18,
    -162,   246,   246,   251,   251,   -21,   835,   862,   862,   862,
     862,   862,   862,   835,   835,   835,   115,   111,  -162,  -162,
     118,   119,   106,   105,   105,   105,   105,   105,  -162,  -162,
    -162,  -162,  -162,  -162,  -162,   124,  -162,     9,   263,   107,
    -162,  -162,   263,   119,  -162,  -162,   114,   127,    70,    70,
     116,   116,  -162,   141,   130,   144,   835,  -162,   752,  -162,
     142,  -162,  -162,   135,  -162,  -162,  -162,    45,  -162,  -162,
     134,    29,   148,   139,   119,  -162,  -162,   129,   151,  -162,
    -162,   138,   263,  -162,   263,   132,  -162,   640,   780,   263,
    -162,  -162,   808,   119,  -162,  -162,    45,  -162
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     0,     2,     0,     7,     1,     4,    16,
      23,    26,    27,    28,     0,    18,     0,    57,    58,     0,
       0,     5,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     9,     8,     0,     0,     0,    19,     0,     0,
       0,    58,     0,     3,    68,    69,     0,     0,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    38,     0,     0,     0,     0,     0,
      66,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,     0,    17,     0,     0,     0,     0,    65,
       6,     0,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    39,    20,    36,    35,    37,    81,    32,     0,
      30,    60,    61,    62,    63,    64,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,     0,    59,    40,    42,
       0,     0,     0,     0,     0,     0,     0,     0,    82,    83,
      84,    88,    85,    86,    87,     0,    22,     0,     0,     0,
      24,    14,     0,     0,    59,    12,     0,     0,    91,    92,
      93,    94,    95,     0,     0,     0,    31,    29,     0,    43,
       0,    45,    53,     0,    15,    21,    41,    46,    11,    13,
       0,    51,     0,     0,     0,    44,    34,     0,     0,    54,
      52,     0,     0,    47,     0,     0,    25,     0,     0,     0,
      48,    56,     0,     0,    55,    49,    46,    50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -162,   157,  -162,  -162,  -161,  -162,  -162,  -162,  -162,   120,
    -162,  -162,   -34,  -162,     6,   -92,  -162,  -162,   -49,  -162,
    -162,  -162,  -162,  -162,  -162,   -20,   -97
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,    53,    10,   166,   180,     4,    41,    14,    15,
     157,    42,    16,   119,   120,    43,   163,   187,   195,   213,
     216,   190,   191,   199,   200,    44,   103
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      52,   136,   179,    54,    55,     1,    48,    58,    73,     5,
      11,    12,     2,    13,    80,    81,    82,    49,    70,    45,
      72,     7,    46,    89,    90,   174,    91,     6,   175,    96,
      97,     9,   111,   203,    92,    47,   101,   159,   160,   104,
     105,   106,   107,   108,   109,   110,   168,   169,   170,   171,
     172,    50,   215,   193,   194,   121,   122,   123,   124,   125,
     197,   198,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   142,    17,    18,    56,    19,   143,   144,   145,
     146,   147,    57,    66,    20,    59,    60,    21,   189,    22,
      23,    24,    67,   145,   146,   147,    61,    25,    68,    62,
      63,    64,    26,    65,    71,    93,    95,    98,   100,   102,
     112,   113,   118,   137,   114,    27,   140,    28,    29,    30,
      31,    32,    33,    34,   155,    35,    36,    37,    38,    39,
     116,    40,   156,   161,   164,   158,   165,   162,   176,   173,
     167,   147,   178,   181,   182,   183,    17,    18,   185,    19,
     184,   192,   196,   201,   202,   205,   204,    20,   206,   209,
     188,     8,    22,    23,    24,   177,    94,   217,     0,     0,
      25,     0,     0,     0,     0,    26,     0,     0,     0,     0,
       0,     0,   207,     0,   208,     0,     0,     0,    27,   212,
      28,    29,    30,    31,    32,    33,    34,    17,    18,    36,
      19,    38,    39,     0,    40,     0,     0,     0,    20,     0,
       0,     0,     0,    22,    23,    24,    17,    51,     0,     0,
       0,    25,     0,     0,     0,     0,    26,    20,     0,     0,
       0,     0,     0,    23,    24,     0,     0,     0,     0,    27,
       0,    28,    29,    30,    31,    32,    33,    34,     0,     0,
      36,     0,    38,    39,     0,    40,     0,     0,    27,     0,
      28,    29,    30,    31,    32,    33,    34,    17,    51,    77,
      78,    79,     0,    69,    40,     0,    79,     0,    20,     0,
       0,    80,    81,    82,    23,    24,    80,    81,    82,     0,
      89,    90,     0,    91,     0,    89,    90,     0,    91,     0,
       0,    92,     0,     0,     0,     0,    92,     0,     0,    27,
       0,    28,    29,    30,    31,    32,    33,    34,    75,    76,
      77,    78,    79,     0,     0,    40,     0,     0,     0,     0,
       0,     0,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,     0,    91,     0,     0,    75,    76,    77,
      78,    79,    92,     0,     0,     0,     0,     0,     0,     0,
     117,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,     0,    91,     0,     0,    75,    76,    77,    78,
      79,    92,     0,     0,     0,     0,     0,     0,     0,   148,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,    91,     0,     0,    75,    76,    77,    78,    79,
      92,     0,     0,     0,     0,     0,     0,     0,   149,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
       0,    91,     0,     0,    75,    76,    77,    78,    79,    92,
       0,     0,     0,     0,     0,     0,     0,   150,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,     0,
      91,     0,     0,    75,    76,    77,    78,    79,    92,     0,
       0,     0,     0,     0,     0,     0,   151,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,     0,    91,
       0,     0,    75,    76,    77,    78,    79,    92,     0,     0,
       0,     0,     0,     0,     0,   152,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,     0,    91,     0,
       0,    75,    76,    77,    78,    79,    92,     0,     0,     0,
       0,     0,     0,     0,   153,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,     0,    91,     0,     0,
       0,    99,     0,     0,     0,    92,    75,    76,    77,    78,
      79,     0,     0,   154,     0,     0,     0,     0,     0,     0,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,    91,     0,     0,     0,   139,     0,     0,     0,
      92,    75,    76,    77,    78,    79,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,     0,    91,     0,     0,
       0,   141,     0,     0,     0,    92,    75,    76,    77,    78,
      79,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,    91,     0,     0,     0,   210,     0,     0,     0,
      92,    75,    76,    77,    78,    79,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,     0,    91,    74,    75,
      76,    77,    78,    79,     0,    92,     0,     0,     0,     0,
       0,     0,     0,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,     0,    91,   115,    75,    76,    77,
      78,    79,     0,    92,     0,     0,     0,     0,     0,     0,
       0,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,     0,    91,   138,    75,    76,    77,    78,    79,
       0,    92,     0,     0,     0,     0,     0,     0,     0,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
       0,    91,   186,    75,    76,    77,    78,    79,     0,    92,
       0,     0,     0,     0,     0,     0,     0,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,     0,    91,
     211,    75,    76,    77,    78,    79,     0,    92,     0,     0,
       0,     0,     0,     0,     0,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,     0,    91,   214,    75,
      76,    77,    78,    79,     0,    92,     0,     0,     0,     0,
       0,     0,     0,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,     0,    91,    75,    76,    77,    78,
      79,     0,     0,    92,     0,     0,     0,     0,     0,     0,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,    91,    75,    76,    77,    78,    79,     0,     0,
      92,     0,     0,     0,     0,     0,     0,    80,    81,    82,
       0,     0,     0,     0,     0,     0,    89,    90,     0,    91,
       0,     0,     0,     0,     0,     0,     0,    92
};

static const yytype_int16 yycheck[] =
{
      20,    93,   163,    23,    24,     3,    15,    27,    42,     5,
      11,    12,    10,    14,    35,    36,    37,    26,    38,    16,
      40,     0,    19,    44,    45,    16,    47,    17,    19,    49,
      50,    15,    66,   194,    55,     5,    56,    19,    20,    59,
      60,    61,    62,    63,    64,    65,   143,   144,   145,   146,
     147,    15,   213,     8,     9,    75,    76,    77,    78,    79,
      31,    32,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    16,     4,     5,    15,     7,    21,    22,    23,
      24,    25,    15,    15,    15,    62,    62,    18,   180,    20,
      21,    22,     5,    23,    24,    25,    62,    28,     5,    62,
      62,    62,    33,    62,     5,    17,     4,    15,     4,     4,
      20,    15,     5,    16,    20,    46,     4,    48,    49,    50,
      51,    52,    53,    54,    16,    56,    57,    58,    59,    60,
      20,    62,     4,    18,    16,    26,    17,    26,   158,    15,
      34,    25,   162,    29,    17,     4,     4,     5,     4,     7,
      20,    16,    18,     5,    15,     4,    27,    15,    20,    27,
      18,     4,    20,    21,    22,   159,    46,   216,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,   202,    -1,   204,    -1,    -1,    -1,    46,   209,
      48,    49,    50,    51,    52,    53,    54,     4,     5,    57,
       7,    59,    60,    -1,    62,    -1,    -1,    -1,    15,    -1,
      -1,    -1,    -1,    20,    21,    22,     4,     5,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    33,    15,    -1,    -1,
      -1,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    46,
      -1,    48,    49,    50,    51,    52,    53,    54,    -1,    -1,
      57,    -1,    59,    60,    -1,    62,    -1,    -1,    46,    -1,
      48,    49,    50,    51,    52,    53,    54,     4,     5,    23,
      24,    25,    -1,    61,    62,    -1,    25,    -1,    15,    -1,
      -1,    35,    36,    37,    21,    22,    35,    36,    37,    -1,
      44,    45,    -1,    47,    -1,    44,    45,    -1,    47,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    55,    -1,    -1,    46,
      -1,    48,    49,    50,    51,    52,    53,    54,    21,    22,
      23,    24,    25,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    -1,    47,    -1,    -1,    21,    22,    23,
      24,    25,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    -1,    -1,    21,    22,    23,    24,
      25,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    -1,    -1,    21,    22,    23,    24,    25,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    -1,    -1,    21,    22,    23,    24,    25,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      47,    -1,    -1,    21,    22,    23,    24,    25,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      -1,    -1,    21,    22,    23,    24,    25,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    -1,    47,    -1,
      -1,    21,    22,    23,    24,    25,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    -1,    -1,
      -1,    16,    -1,    -1,    -1,    55,    21,    22,    23,    24,
      25,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    -1,    -1,    -1,    16,    -1,    -1,    -1,
      55,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    -1,    -1,
      -1,    16,    -1,    -1,    -1,    55,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    -1,    -1,    -1,    16,    -1,    -1,    -1,
      55,    21,    22,    23,    24,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    20,    21,
      22,    23,    24,    25,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    20,    21,    22,    23,
      24,    25,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    20,    21,    22,    23,    24,    25,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    20,    21,    22,    23,    24,    25,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      20,    21,    22,    23,    24,    25,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    20,    21,
      22,    23,    24,    25,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    21,    22,    23,    24,
      25,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    -1,    47,    21,    22,    23,    24,    25,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    10,    65,    70,     5,    17,     0,    65,    15,
      67,    11,    12,    14,    72,    73,    76,     4,     5,     7,
      15,    18,    20,    21,    22,    28,    33,    46,    48,    49,
      50,    51,    52,    53,    54,    56,    57,    58,    59,    60,
      62,    71,    75,    79,    89,    16,    19,     5,    15,    26,
      15,     5,    89,    66,    89,    89,    15,    15,    89,    62,
      62,    62,    62,    62,    62,    62,    15,     5,     5,    61,
      89,     5,    89,    76,    20,    21,    22,    23,    24,    25,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    47,    55,    17,    73,     4,    89,    89,    15,    16,
       4,    89,     4,    90,    89,    89,    89,    89,    89,    89,
      89,    76,    20,    15,    20,    20,    20,    63,     5,    77,
      78,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    79,    16,    20,    16,
       4,    16,    16,    21,    22,    23,    24,    25,    63,    63,
      63,    63,    63,    63,    63,    16,     4,    74,    26,    19,
      20,    18,    26,    80,    16,    17,    68,    34,    90,    90,
      90,    90,    90,    15,    16,    19,    89,    78,    89,    68,
      69,    29,    17,     4,    20,     4,    20,    81,    18,    79,
      85,    86,    16,     8,     9,    82,    18,    31,    32,    87,
      88,     5,    15,    68,    27,     4,    20,    89,    89,    27,
      16,    20,    89,    83,    20,    68,    84,    82
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    65,    65,    65,    66,    66,    67,    67,    67,
      67,    68,    69,    69,    70,    71,    72,    72,    72,    73,
      74,    74,    74,    75,    75,    75,    76,    76,    76,    77,
      77,    78,    78,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    80,    81,    79,    79,    82,    82,    83,    84,
      82,    85,    85,    86,    86,    87,    88,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      90,    90,    90,    90,    90,    90
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     5,     2,     0,     2,     0,     2,     2,
       2,     3,     0,     2,     8,     6,     0,     3,     1,     2,
       0,     3,     1,     0,     4,     9,     1,     1,     1,     3,
       1,     3,     1,     1,     8,     3,     3,     3,     2,     3,
       4,     7,     0,     0,     8,     6,     0,     2,     0,     0,
       8,     1,     2,     0,     2,     5,     4,     1,     1,     4,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     3,     4,     4,     4,     4,     4,     4,     4,     2,
       1,     3,     3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* program: MAIN LB cstatement RB input_tail  */
#line 188 "1807002.y"
                                           {
		emit_parser("Rule matched: program -> MAIN LB cstatement RB");
		printf("\nSuccessful compilation\n");
		printf("\n--- Output files generated ---\n");
		printf("  Phase 1 (Lexer)    -> phase1_lexer.txt\n");
		printf("  Phase 2 (Parser)   -> phase2_parser.txt\n");
		printf("  Phase 3 (Semantic) -> phase3_semantic.txt\n");
		printf("  Phase 4 (TAC)      -> phase4_tac.txt\n");
		printf("  Phase 5 (Optimized)-> phase5_optimized.txt (run optimizer.exe)\n");
		if(lexer_file)    fclose(lexer_file);
		if(parser_file)   fclose(parser_file);
		if(semantic_file) fclose(semantic_file);
		if(tac_file)      fclose(tac_file);
	}
#line 1591 "1807002.tab.c"
    break;

  case 5: /* input_tail: %empty  */
#line 205 "1807002.y"
                        { (yyval.number) = 0; }
#line 1597 "1807002.tab.c"
    break;

  case 6: /* input_tail: input_tail NUM  */
#line 206 "1807002.y"
                         { (yyval.number) = (yyvsp[-1].number); }
#line 1603 "1807002.tab.c"
    break;

  case 11: /* block: LB block_items RB  */
#line 215 "1807002.y"
                         { (yyval.number) = (yyvsp[-1].number); }
#line 1609 "1807002.tab.c"
    break;

  case 12: /* block_items: %empty  */
#line 217 "1807002.y"
                         { (yyval.number) = 0; }
#line 1615 "1807002.tab.c"
    break;

  case 13: /* block_items: block_items statement  */
#line 218 "1807002.y"
                                { (yyval.number) = (yyvsp[0].number); }
#line 1621 "1807002.tab.c"
    break;

  case 14: /* func_block: FUNC_NUM VAR LP Parameter RP LB statement RB  */
#line 222 "1807002.y"
                {
			{
				int id = get_Var_Id((yyvsp[-6].string));
            
            
            	if(id!=-1)
            	{
                	printf("already declared\n");
            	}
            	else
            	{
                	vptr[total_Var].str=(yyvsp[-6].string);
					printf("func save %s\n",(yyvsp[-6].string));
                	vptr[total_Var].n= (yyvsp[-1].number);
					printf("%d func output %d\n",total_Var,(yyvsp[-1].number));
                	total_Var++;
            	}

				


			}
			
			
			printf("Function name : %s\n",(yyvsp[-6].string));
	
		}
#line 1653 "1807002.tab.c"
    break;

  case 15: /* func_call: CALL VAR LP pass_Parameter RP SM  */
#line 251 "1807002.y"
                {
			int id = get_Var_Id((yyvsp[-4].string));
			printf("%s Fuction called\n",(yyvsp[-4].string));
			printf("output of fuction : %d\n",vptr[id].n);									}
#line 1662 "1807002.tab.c"
    break;

  case 19: /* para: TYPE VAR  */
#line 260 "1807002.y"
                                                        {printf("Parameter %s: %s\n",(yyvsp[-1].string),(yyvsp[0].string));}
#line 1668 "1807002.tab.c"
    break;

  case 24: /* cdeclaration: cdeclaration TYPE ID1 SM  */
#line 270 "1807002.y"
                                                                {
		printf("\nvalid declaration\n");
		emit_parser("Rule matched: TYPE ID1 SM -> variable declaration");
	}
#line 1677 "1807002.tab.c"
    break;

  case 25: /* cdeclaration: ARRAY LP TYPE RP LP NUM RP VAR SM  */
#line 274 "1807002.y"
                                                                        {
					
					int id = get_Var_Id((yyvsp[-1].string));

            
            		if(id!=-1)
            		{	
                		printf("already declared\n");
            		}
            		else
            		{
                		vptr[total_Var].isArray = 1;
						vptr[total_Var].str = (yyvsp[-1].string) ;
                		vptr[total_Var].size = (yyvsp[-3].number);
                		total_Var++;
            		}
					
					printf("Array declaration Successful\n");
		emit_parser("Rule matched: ARRAY declaration");
					printf("Printing table\n");
					for(int i = 0 ; i<total_Var; i++){
                		printf("%d %s\n",i,vptr[i].str);
                	}
            
 
				}
#line 1708 "1807002.tab.c"
    break;

  case 26: /* TYPE: INT  */
#line 301 "1807002.y"
                        { (yyval.string) = (yyvsp[0].string);  }
#line 1714 "1807002.tab.c"
    break;

  case 27: /* TYPE: FLOAT  */
#line 303 "1807002.y"
                { (yyval.string) = (yyvsp[0].string);  }
#line 1720 "1807002.tab.c"
    break;

  case 28: /* TYPE: CHAR  */
#line 305 "1807002.y"
                        { (yyval.string) = (yyvsp[0].string);  }
#line 1726 "1807002.tab.c"
    break;

  case 29: /* ID1: ID1 CM ID  */
#line 309 "1807002.y"
                                {}
#line 1732 "1807002.tab.c"
    break;

  case 30: /* ID1: ID  */
#line 310 "1807002.y"
                                        {}
#line 1738 "1807002.tab.c"
    break;

  case 31: /* ID: VAR ASSIGN expression  */
#line 313 "1807002.y"
                        {
				int id = get_Var_Id((yyvsp[-2].string));
				
            	if(id==-1)
            	{

					vptr[total_Var].str=(yyvsp[-2].string);
                	vptr[total_Var].n=(yyvsp[0].number);
                	total_Var++;

                	
            	}
            	else
            	{
                	vptr[id].str=(yyvsp[-2].string);
                	vptr[id].n=(yyvsp[0].number);
            	}

				/*
				for(int i=0;i<total_Var;i++)
				{
					printf("%s",vptr[i].str);
					printf(" %d\n",vptr[i].n);
				}
				*/


			}
#line 1771 "1807002.tab.c"
    break;

  case 32: /* ID: VAR  */
#line 343 "1807002.y"
                        {
				int id = get_Var_Id((yyvsp[0].string));
            
            
            	if(id!=-1)
            	{
                	printf("already declared\n");
				emit_semantic("ERROR: duplicate variable declaration");
            	}
            	else
            	{
                	vptr[total_Var].str=(yyvsp[0].string);
                	vptr[total_Var].n=0;
                	total_Var++;
            	}

				


			}
#line 1796 "1807002.tab.c"
    break;

  case 33: /* statement: SM  */
#line 368 "1807002.y"
              { (yyval.number) = 0; }
#line 1802 "1807002.tab.c"
    break;

  case 34: /* statement: SWITCH LP switch_expression RP SWITCH_END LB BASE RB  */
#line 369 "1807002.y"
                                                                  {printf("SWITCH case.\n");val=(yyvsp[-5].number);}
#line 1808 "1807002.tab.c"
    break;

  case 35: /* statement: PRINT expression SM  */
#line 370 "1807002.y"
                                    {
		printf("print: %d\n", (yyvsp[-1].number));
		sprintf(tac_buf, "print %d", (yyvsp[-1].number));
		emit_tac(tac_buf);
		(yyval.number) = 0;
	}
#line 1819 "1807002.tab.c"
    break;

  case 36: /* statement: PRINT STRING_LITERAL SM  */
#line 376 "1807002.y"
                                  {
		printf("print_str: %s\n", (yyvsp[-1].string));
		sprintf(tac_buf, "print_str %s", (yyvsp[-1].string));
		emit_tac(tac_buf);
		(yyval.number) = 0;
	}
#line 1830 "1807002.tab.c"
    break;

  case 37: /* statement: TAKE_INPUT VAR SM  */
#line 382 "1807002.y"
                                    {
							int id = get_Var_Id((yyvsp[-1].string));
							if(id != -1){
								int input_val;
								FILE *inp = fopen("runtime_input.txt", "r");
								if(inp){
									static int read_pos = 0;
									int num, count = 0;
									while(fscanf(inp, "%d", &num) == 1){
										if(count == read_pos){
											input_val = num;
											vptr[id].n = input_val;
											printf("take_input: %s = %d\n", (yyvsp[-1].string), input_val);
											sprintf(tac_buf, "%s = %d  /* take_input */", (yyvsp[-1].string), input_val);
											emit_tac(tac_buf);
											read_pos++;
											break;
										}
										count++;
									}
									fclose(inp);
								} else {
									printf("Error: runtime_input.txt not found\n");
								}
							} else {
								printf("Error: variable %s not declared\n", (yyvsp[-1].string));
							}
							(yyval.number) = 0;
						}
#line 1864 "1807002.tab.c"
    break;

  case 38: /* statement: expression SM  */
#line 411 "1807002.y"
                                                {
								(yyval.number) = (yyvsp[-1].number);
								printf("\nvalue of expression: %d\n", ((yyvsp[-1].number))); }
#line 1872 "1807002.tab.c"
    break;

  case 39: /* statement: size_of VAR SM  */
#line 415 "1807002.y"
                                                        {
									int id = get_Var_Id((yyvsp[-1].string));
									printf("total size of %s is %d \n",(yyvsp[-1].string),vptr[id].size);}
#line 1880 "1807002.tab.c"
    break;

  case 40: /* statement: VAR ASSIGN expression SM  */
#line 422 "1807002.y"
                        {
				int id = get_Var_Id((yyvsp[-3].string));
				if(id==-1) {
					vptr[total_Var].str=(yyvsp[-3].string);
                	vptr[total_Var].n=(yyvsp[-1].number);
                	total_Var++;
            	} else {
                	vptr[id].str=(yyvsp[-3].string);
                	vptr[id].n=(yyvsp[-1].number);
            	}
            	sprintf(tac_buf, "%s = %d", (yyvsp[-3].string), (yyvsp[-1].number));
            	emit_tac(tac_buf);
		sprintf(tac_buf, "%-20s | %-10s | %-10d | %-10d", (yyvsp[-3].string), "number", (yyvsp[-1].number), 0);
		emit_semantic(tac_buf);
			}
#line 1900 "1807002.tab.c"
    break;

  case 41: /* statement: VAR LP NUM RP ASSIGN expression SM  */
#line 439 "1807002.y"
                        {
				int id = get_Var_Id((yyvsp[-6].string));
				
            	if(id==-1)
            	{

					/* error */

                	
            	}
            	else
            	{
                	vptr[id].arrayVal[(yyvsp[-4].number)] = (yyvsp[-1].number);
            	}

				/*
				for(int i=0;i<total_Var;i++)
				{
					printf("%s",vptr[i].str);
					printf(" %d\n",vptr[i].n);
				}
				*/ 

			}
#line 1929 "1807002.tab.c"
    break;

  case 42: /* $@1: %empty  */
#line 464 "1807002.y"
                              { if_begin_tac((yyvsp[-1].number)); }
#line 1935 "1807002.tab.c"
    break;

  case 43: /* $@2: %empty  */
#line 464 "1807002.y"
                                                          { if_after_branch_tac(); }
#line 1941 "1807002.tab.c"
    break;

  case 44: /* statement: IF LP expression RP $@1 block $@2 if_tail  */
#line 464 "1807002.y"
                                                                                             { (yyval.number) = 0; }
#line 1947 "1807002.tab.c"
    break;

  case 45: /* statement: WHILE LP expression RP block WHILE_END  */
#line 468 "1807002.y"
                                                 {
		char *l_start = new_label();
		char *l_end   = new_label();
		sprintf(tac_buf, "%s:", l_start);
		emit_tac(tac_buf);
		sprintf(tac_buf, "if NOT %d goto %s", (yyvsp[-3].number), l_end);
		emit_tac(tac_buf);
		sprintf(tac_buf, "  body = %d", (yyvsp[-1].number));
		emit_tac(tac_buf);
		sprintf(tac_buf, "%s:", l_end);
		emit_tac(tac_buf);
		int condition = (yyvsp[-3].number);
		printf("repeat loop executed, condition was: %d\n", condition);
		if(condition) printf("Loop body value: %d\n", (yyvsp[-1].number));
		(yyval.number) = (yyvsp[-1].number);
	}
#line 1968 "1807002.tab.c"
    break;

  case 46: /* if_tail: %empty  */
#line 486 "1807002.y"
                      { if_finish_tac(); (yyval.number) = 0; }
#line 1974 "1807002.tab.c"
    break;

  case 47: /* if_tail: ELSE block  */
#line 487 "1807002.y"
                     { if_finish_tac(); (yyval.number) = 0; }
#line 1980 "1807002.tab.c"
    break;

  case 48: /* $@3: %empty  */
#line 488 "1807002.y"
                                { elif_begin_tac((yyvsp[-1].number)); }
#line 1986 "1807002.tab.c"
    break;

  case 49: /* $@4: %empty  */
#line 488 "1807002.y"
                                                              { if_after_branch_tac(); }
#line 1992 "1807002.tab.c"
    break;

  case 50: /* if_tail: ELIF LP expression RP $@3 block $@4 if_tail  */
#line 488 "1807002.y"
                                                                                                 { (yyval.number) = 0; }
#line 1998 "1807002.tab.c"
    break;

  case 55: /* Cs: CASE NUM COL expression SM  */
#line 501 "1807002.y"
                                                             {
						
						if(val==(yyvsp[-3].number)){
							  track=1;
							  printf("\nCase No : %d  and Result :  %d\n",(yyvsp[-3].number),(yyvsp[-1].number));
						}
					}
#line 2010 "1807002.tab.c"
    break;

  case 56: /* Dflt: DEFAULT COL expression SM  */
#line 510 "1807002.y"
                                                               {
						if(track!=1){
							printf("\nResult in default Value is :  %d\n",(yyvsp[-1].number));
						}
						track=0;
					}
#line 2021 "1807002.tab.c"
    break;

  case 57: /* expression: NUM  */
#line 520 "1807002.y"
                                        { (yyval.number) = (yyvsp[0].number); 	}
#line 2027 "1807002.tab.c"
    break;

  case 58: /* expression: VAR  */
#line 522 "1807002.y"
                        {
				int id = get_Var_Id((yyvsp[0].string));
            	(yyval.number) = vptr[id].n;

			}
#line 2037 "1807002.tab.c"
    break;

  case 59: /* expression: VAR LP NUM RP  */
#line 529 "1807002.y"
                        {
				int id = get_Var_Id((yyvsp[-3].string));
            	(yyval.number) = vptr[id].arrayVal[(yyvsp[-1].number)];

			}
#line 2047 "1807002.tab.c"
    break;

  case 60: /* expression: expression PLUS expression  */
#line 536 "1807002.y"
                                        {
		(yyval.number) = (yyvsp[-2].number) + (yyvsp[0].number);
		printf("%d + %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d + %d", t, (yyvsp[-2].number), (yyvsp[0].number));
		emit_tac(tac_buf);
	}
#line 2059 "1807002.tab.c"
    break;

  case 61: /* expression: expression MINUS expression  */
#line 544 "1807002.y"
                                        {
		(yyval.number) = (yyvsp[-2].number) - (yyvsp[0].number);
		printf("%d - %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d - %d", t, (yyvsp[-2].number), (yyvsp[0].number));
		emit_tac(tac_buf);
	}
#line 2071 "1807002.tab.c"
    break;

  case 62: /* expression: expression MULT expression  */
#line 552 "1807002.y"
                                        {
		(yyval.number) = (yyvsp[-2].number) * (yyvsp[0].number);
		printf("%d * %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d * %d", t, (yyvsp[-2].number), (yyvsp[0].number));
		emit_tac(tac_buf);
	}
#line 2083 "1807002.tab.c"
    break;

  case 63: /* expression: expression DIV expression  */
#line 560 "1807002.y"
                                        {
		if((yyvsp[0].number)) {
			(yyval.number) = (yyvsp[-2].number) / (yyvsp[0].number);
			printf("%d / %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
			char *t = new_temp();
			sprintf(tac_buf, "%s = %d / %d", t, (yyvsp[-2].number), (yyvsp[0].number));
			emit_tac(tac_buf);
		} else {
			(yyval.number) = 0;
			printf("\ndivision by zero error\t");
			emit_tac("ERROR: division by zero");
		}
	}
#line 2101 "1807002.tab.c"
    break;

  case 64: /* expression: expression POW expression  */
#line 573 "1807002.y"
                                    {
		(yyval.number) = pow((yyvsp[-2].number),(yyvsp[0].number));
		printf("%d ^ %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d ^ %d", t, (yyvsp[-2].number), (yyvsp[0].number));
		emit_tac(tac_buf);
	}
#line 2113 "1807002.tab.c"
    break;

  case 65: /* expression: LP expression RP  */
#line 581 "1807002.y"
                                        { (yyval.number) = (yyvsp[-1].number);	}
#line 2119 "1807002.tab.c"
    break;

  case 66: /* expression: expression inc  */
#line 583 "1807002.y"
                                 { (yyval.number)=(yyvsp[-1].number)+1; printf("inc: %d\n",(yyval.number));}
#line 2125 "1807002.tab.c"
    break;

  case 67: /* expression: expression dec  */
#line 584 "1807002.y"
                                 { (yyval.number)=(yyvsp[-1].number)-1; printf("dec: %d\n",(yyval.number));}
#line 2131 "1807002.tab.c"
    break;

  case 68: /* expression: PLUS expression  */
#line 587 "1807002.y"
    {
        (yyval.number) = (yyvsp[0].number);
    }
#line 2139 "1807002.tab.c"
    break;

  case 69: /* expression: MINUS expression  */
#line 591 "1807002.y"
    {
        (yyval.number) = -(yyvsp[0].number);
    }
#line 2147 "1807002.tab.c"
    break;

  case 70: /* expression: expression MOD expression  */
#line 596 "1807002.y"
    {

        (yyval.number) = (int)(yyvsp[-2].number) % (int)(yyvsp[0].number);
    }
#line 2156 "1807002.tab.c"
    break;

  case 71: /* expression: expression LT expression  */
#line 602 "1807002.y"
        {
		(yyval.number) = ((yyvsp[-2].number) < (yyvsp[0].number));
	}
#line 2164 "1807002.tab.c"
    break;

  case 72: /* expression: expression GT expression  */
#line 606 "1807002.y"
        {
		(yyval.number) = ((yyvsp[-2].number) > (yyvsp[0].number));
	}
#line 2172 "1807002.tab.c"
    break;

  case 73: /* expression: expression LTE expression  */
#line 611 "1807002.y"
    {
        (yyval.number) = ((yyvsp[-2].number) <= (yyvsp[0].number));
    }
#line 2180 "1807002.tab.c"
    break;

  case 74: /* expression: expression GTE expression  */
#line 615 "1807002.y"
    {
        (yyval.number) = ((yyvsp[-2].number) >= (yyvsp[0].number));
    }
#line 2188 "1807002.tab.c"
    break;

  case 75: /* expression: expression EEQL expression  */
#line 619 "1807002.y"
    {
        (yyval.number) = ((yyvsp[-2].number) == (yyvsp[0].number));
    }
#line 2196 "1807002.tab.c"
    break;

  case 76: /* expression: expression NEQL expression  */
#line 623 "1807002.y"
    {
        (yyval.number) = ((yyvsp[-2].number) != (yyvsp[0].number));
    }
#line 2204 "1807002.tab.c"
    break;

  case 77: /* expression: expression AND expression  */
#line 627 "1807002.y"
    {
        (yyval.number) = ( (yyvsp[-2].number) && (yyvsp[0].number));
		printf("%d AND %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
    }
#line 2213 "1807002.tab.c"
    break;

  case 78: /* expression: expression OR expression  */
#line 632 "1807002.y"
    {
        (yyval.number) = ((yyvsp[-2].number) || (yyvsp[0].number));
		printf("%d OR %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
    }
#line 2222 "1807002.tab.c"
    break;

  case 79: /* expression: expression XOR expression  */
#line 637 "1807002.y"
    {
        (yyval.number) = ((int)(yyvsp[-2].number) ^ (int)(yyvsp[0].number));
		printf("%d XOR %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
    }
#line 2231 "1807002.tab.c"
    break;

  case 80: /* expression: NOT expression  */
#line 642 "1807002.y"
    {
        (yyval.number) = !(yyvsp[0].number);
    }
#line 2239 "1807002.tab.c"
    break;

  case 81: /* expression: '(' expression ')'  */
#line 646 "1807002.y"
    {
        (yyval.number) = (yyvsp[-1].number);
    }
#line 2247 "1807002.tab.c"
    break;

  case 82: /* expression: SIN '(' expression ')'  */
#line 650 "1807002.y"
    {
        (yyval.number) = sin((yyvsp[-1].number));
		printf("sin( %d ) : \n",(yyvsp[-1].number));

    }
#line 2257 "1807002.tab.c"
    break;

  case 83: /* expression: COS '(' expression ')'  */
#line 656 "1807002.y"
    {
        (yyval.number) = cos((yyvsp[-1].number));
		printf("cos( %d ) : \n",(yyvsp[-1].number));
    }
#line 2266 "1807002.tab.c"
    break;

  case 84: /* expression: TAN '(' expression ')'  */
#line 661 "1807002.y"
    {
        (yyval.number) = tan((yyvsp[-1].number));
		printf("tan( %d ) : \n",(yyvsp[-1].number));
    }
#line 2275 "1807002.tab.c"
    break;

  case 85: /* expression: LOG '(' expression ')'  */
#line 666 "1807002.y"
    {
        (yyval.number) = log10((yyvsp[-1].number));
		printf("log10( %d ) : \n",(yyvsp[-1].number));
    }
#line 2284 "1807002.tab.c"
    break;

  case 86: /* expression: LOG2 '(' expression ')'  */
#line 671 "1807002.y"
    {
        (yyval.number) = log2((yyvsp[-1].number));
		printf("log2( %d ) : \n",(yyvsp[-1].number));
    }
#line 2293 "1807002.tab.c"
    break;

  case 87: /* expression: LN '(' expression ')'  */
#line 676 "1807002.y"
    {
        (yyval.number) = log((yyvsp[-1].number));
    }
#line 2301 "1807002.tab.c"
    break;

  case 88: /* expression: SQRT '(' expression ')'  */
#line 680 "1807002.y"
    {
    	(yyval.number) = sqrt((yyvsp[-1].number));
		
    }
#line 2310 "1807002.tab.c"
    break;

  case 89: /* expression: expression FACTORIAL  */
#line 685 "1807002.y"
                {
                    long long x = 1;
                	for(long long i=1;i<=(yyvsp[-1].number);i++)
					 	x*=i;
                    (yyval.number) = x;
                    
                }
#line 2322 "1807002.tab.c"
    break;

  case 90: /* switch_expression: NUM  */
#line 696 "1807002.y"
                                                        { (yyval.number) = (yyvsp[0].number); val = (yyval.number);	}
#line 2328 "1807002.tab.c"
    break;

  case 91: /* switch_expression: switch_expression PLUS switch_expression  */
#line 698 "1807002.y"
                                                        { (yyval.number) = (yyvsp[-2].number) + (yyvsp[0].number); val = (yyval.number); }
#line 2334 "1807002.tab.c"
    break;

  case 92: /* switch_expression: switch_expression MINUS switch_expression  */
#line 700 "1807002.y"
                                                        { (yyval.number) = (yyvsp[-2].number) - (yyvsp[0].number); val = (yyval.number); }
#line 2340 "1807002.tab.c"
    break;

  case 93: /* switch_expression: switch_expression MULT switch_expression  */
#line 702 "1807002.y"
                                                        { (yyval.number) = (yyvsp[-2].number) * (yyvsp[0].number);  val = (yyval.number);}
#line 2346 "1807002.tab.c"
    break;

  case 94: /* switch_expression: switch_expression DIV switch_expression  */
#line 704 "1807002.y"
                                                        { 	if((yyvsp[0].number)) 
				  		{
				     			(yyval.number) = (yyvsp[-2].number) / (yyvsp[0].number); val = (yyval.number);
				  		}
				  		else
				  		{
							(yyval.number) = 0;
							 val = (yyval.number);
				  		} 	
				    	}
#line 2361 "1807002.tab.c"
    break;

  case 95: /* switch_expression: switch_expression POW switch_expression  */
#line 714 "1807002.y"
                                                  { (yyval.number) = pow((yyvsp[-2].number),(yyvsp[0].number));  val = (yyval.number);}
#line 2367 "1807002.tab.c"
    break;


#line 2371 "1807002.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 718 "1807002.y"





int yywrap()
{
return 1;
}

void open_tac_file() {
	/* Phase 1 — Lexer output (token trace already goes to output.txt via trace()) */
	lexer_file = fopen("phase1_lexer.txt", "w");
	if(lexer_file) {
		fprintf(lexer_file, "=== PHASE 1: LEXICAL ANALYSIS ===\n");
		fprintf(lexer_file, "%-5s | %-20s | %-20s\n", "Step", "Token Text", "Token Type");
		fprintf(lexer_file, "------------------------------------------------------\n");
	}

	/* Phase 2 — Parser output */
	parser_file = fopen("phase2_parser.txt", "w");
	if(parser_file) {
		fprintf(parser_file, "=== PHASE 2: SYNTAX ANALYSIS ===\n\n");
	}

	/* Phase 3 — Semantic output */
	semantic_file = fopen("phase3_semantic.txt", "w");
	if(semantic_file) {
		fprintf(semantic_file, "=== PHASE 3: SEMANTIC ANALYSIS ===\n\n");
		fprintf(semantic_file, "%-20s | %-10s | %-10s | %-10s\n", "Variable", "Type", "Value", "isArray");
		fprintf(semantic_file, "------------------------------------------------------\n");
	}

	/* Phase 4 — TAC output */
	tac_file = fopen("phase4_tac.txt", "w");
	if(tac_file) {
		fprintf(tac_file, "=== PHASE 4: THREE ADDRESS CODE (TAC) ===\n\n");
	}
}


void yyerror(const char *s){
	printf( "%s\n", s);
}
