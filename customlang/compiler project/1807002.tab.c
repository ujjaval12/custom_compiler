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
  YYSYMBOL_61_ = 61,                       /* '('  */
  YYSYMBOL_62_ = 62,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_program = 64,                   /* program  */
  YYSYMBOL_input_tail = 65,                /* input_tail  */
  YYSYMBOL_cstatement = 66,                /* cstatement  */
  YYSYMBOL_block = 67,                     /* block  */
  YYSYMBOL_block_items = 68,               /* block_items  */
  YYSYMBOL_func_block = 69,                /* func_block  */
  YYSYMBOL_func_call = 70,                 /* func_call  */
  YYSYMBOL_Parameter = 71,                 /* Parameter  */
  YYSYMBOL_para = 72,                      /* para  */
  YYSYMBOL_pass_Parameter = 73,            /* pass_Parameter  */
  YYSYMBOL_cdeclaration = 74,              /* cdeclaration  */
  YYSYMBOL_TYPE = 75,                      /* TYPE  */
  YYSYMBOL_ID1 = 76,                       /* ID1  */
  YYSYMBOL_ID = 77,                        /* ID  */
  YYSYMBOL_statement = 78,                 /* statement  */
  YYSYMBOL_79_1 = 79,                      /* $@1  */
  YYSYMBOL_80_2 = 80,                      /* $@2  */
  YYSYMBOL_if_tail = 81,                   /* if_tail  */
  YYSYMBOL_82_3 = 82,                      /* $@3  */
  YYSYMBOL_83_4 = 83,                      /* $@4  */
  YYSYMBOL_BASE = 84,                      /* BASE  */
  YYSYMBOL_Bas = 85,                       /* Bas  */
  YYSYMBOL_Cs = 86,                        /* Cs  */
  YYSYMBOL_Dflt = 87,                      /* Dflt  */
  YYSYMBOL_expression = 88,                /* expression  */
  YYSYMBOL_switch_expression = 89          /* switch_expression  */
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
#define YYLAST   878

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  216

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   315


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
      61,    62,     2,     2,     2,     2,     2,     2,     2,     2,
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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   187,   187,   188,   202,   205,   206,   209,   210,   211,
     212,   215,   217,   218,   221,   250,   256,   257,   258,   260,
     263,   264,   265,   269,   270,   274,   301,   303,   305,   309,
     310,   312,   341,   368,   369,   370,   376,   405,   409,   415,
     432,   458,   458,   458,   462,   480,   481,   482,   482,   482,
     487,   488,   491,   492,   495,   504,   514,   515,   522,   530,
     538,   546,   554,   567,   575,   577,   578,   580,   584,   589,
     595,   599,   604,   608,   612,   616,   620,   625,   630,   635,
     639,   643,   649,   654,   659,   664,   669,   673,   678,   690,
     692,   694,   696,   698,   708
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
  "size_of", "CALL", "PRINT", "TAKE_INPUT", "'('", "')'", "$accept",
  "program", "input_tail", "cstatement", "block", "block_items",
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

#define YYPACT_NINF (-160)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,     4,    10,    21,     2,    16,  -160,  -160,  -160,    -1,
      68,  -160,  -160,  -160,     3,  -160,    30,  -160,    -9,    36,
     210,  -160,  -160,   210,   210,    38,    59,   210,    23,    24,
      34,    37,    39,    41,    42,    76,    92,    94,   210,    99,
     210,  -160,    -1,  -160,   608,    88,    -1,  -160,   102,   210,
     210,    93,   475,   103,   808,   808,   210,   105,   775,   210,
     210,   210,   210,   210,   210,   210,    -1,    90,    96,   636,
      95,   244,   107,  -160,   210,   210,   210,   210,   210,  -160,
    -160,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,  -160,   191,  -160,    97,   664,   510,   119,  -160,  -160,
     545,  -160,    55,   272,   300,   328,   356,   384,   412,   440,
     114,  -160,   127,  -160,  -160,  -160,   106,    18,  -160,   808,
     808,   823,   823,   -21,   775,   802,   802,   802,   802,   802,
     802,   775,   775,   775,   115,   108,  -160,  -160,   121,   118,
     104,   105,   105,   105,   105,   105,  -160,  -160,  -160,  -160,
    -160,  -160,  -160,   124,  -160,     9,   210,   107,  -160,  -160,
     210,   118,  -160,  -160,   112,   125,    69,    69,   123,   123,
    -160,   139,   126,   145,   775,  -160,   692,  -160,   140,  -160,
    -160,   134,  -160,  -160,  -160,    51,  -160,  -160,   133,    50,
     147,   138,   118,  -160,  -160,   129,   150,  -160,  -160,   137,
     210,  -160,   210,   132,  -160,   580,   720,   210,  -160,  -160,
     748,   118,  -160,  -160,    51,  -160
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     0,     2,     0,     7,     1,     4,    16,
      23,    26,    27,    28,     0,    18,     0,    56,    57,     0,
       0,     5,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     9,     8,     0,     0,     0,    19,     0,     0,
       0,    57,     0,     3,    67,    68,     0,     0,    79,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    37,     0,     0,     0,     0,     0,    65,
      66,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    88,     0,    17,     0,     0,     0,     0,    64,     6,
       0,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    38,    20,    35,    36,    80,    32,     0,    30,    59,
      60,    61,    62,    63,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,     0,    58,    39,    41,     0,     0,
       0,     0,     0,     0,     0,     0,    81,    82,    83,    87,
      84,    85,    86,     0,    22,     0,     0,     0,    24,    14,
       0,     0,    58,    12,     0,     0,    90,    91,    92,    93,
      94,     0,     0,     0,    31,    29,     0,    42,     0,    44,
      52,     0,    15,    21,    40,    45,    11,    13,     0,    50,
       0,     0,     0,    43,    34,     0,     0,    53,    51,     0,
       0,    46,     0,     0,    25,     0,     0,     0,    47,    55,
       0,     0,    54,    48,    45,    49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -160,   159,  -160,  -160,  -159,  -160,  -160,  -160,  -160,   120,
    -160,  -160,   -34,  -160,     7,   -91,  -160,  -160,   -49,  -160,
    -160,  -160,  -160,  -160,  -160,   -20,   -95
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,    53,    10,   164,   178,     4,    41,    14,    15,
     155,    42,    16,   117,   118,    43,   161,   185,   193,   211,
     214,   188,   189,   197,   198,    44,   102
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      52,   134,   177,    54,    55,     1,    48,    58,    72,     5,
      11,    12,     2,    13,    79,    80,    81,    49,    69,    45,
      71,     7,    46,    88,    89,   172,    90,     6,   173,    95,
      96,     9,   110,   201,    91,    47,   100,   157,   158,   103,
     104,   105,   106,   107,   108,   109,   166,   167,   168,   169,
     170,    50,   213,    56,   119,   120,   121,   122,   123,   191,
     192,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   140,    17,    18,    57,    19,   141,   142,   143,   144,
     145,   195,   196,    20,    59,    60,    21,   187,    22,    23,
      24,    66,   143,   144,   145,    61,    25,    67,    62,    68,
      63,    26,    64,    65,    70,    92,    94,    99,    97,   101,
     111,   112,   116,   135,    27,   114,    28,    29,    30,    31,
      32,    33,    34,   138,    35,    36,    37,    38,    39,    40,
     153,   154,   156,   159,   160,   163,   174,   162,   165,   171,
     176,   179,   180,   181,    17,    18,   182,    19,   145,   183,
     190,   194,   199,   200,   203,    20,   202,   204,   186,   207,
      22,    23,    24,     8,   175,   215,    93,     0,    25,     0,
       0,     0,     0,    26,     0,     0,     0,     0,     0,     0,
     205,     0,   206,     0,     0,     0,    27,   210,    28,    29,
      30,    31,    32,    33,    34,    17,    18,    36,    19,    38,
      39,    40,     0,     0,     0,     0,    20,     0,     0,     0,
       0,    22,    23,    24,    17,    51,     0,     0,     0,    25,
       0,     0,     0,     0,    26,    20,     0,     0,     0,     0,
       0,    23,    24,     0,     0,     0,     0,    27,     0,    28,
      29,    30,    31,    32,    33,    34,     0,     0,    36,     0,
      38,    39,    40,     0,     0,     0,    27,     0,    28,    29,
      30,    31,    32,    33,    34,    74,    75,    76,    77,    78,
       0,    40,     0,     0,     0,     0,     0,     0,     0,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
       0,    90,     0,    74,    75,    76,    77,    78,     0,    91,
       0,     0,     0,     0,     0,     0,   115,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,    90,
       0,    74,    75,    76,    77,    78,     0,    91,     0,     0,
       0,     0,     0,     0,   146,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,    90,     0,    74,
      75,    76,    77,    78,     0,    91,     0,     0,     0,     0,
       0,     0,   147,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     0,    90,     0,    74,    75,    76,
      77,    78,     0,    91,     0,     0,     0,     0,     0,     0,
     148,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,     0,    90,     0,    74,    75,    76,    77,    78,
       0,    91,     0,     0,     0,     0,     0,     0,   149,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
       0,    90,     0,    74,    75,    76,    77,    78,     0,    91,
       0,     0,     0,     0,     0,     0,   150,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,    90,
       0,    74,    75,    76,    77,    78,     0,    91,     0,     0,
       0,     0,     0,     0,   151,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,    90,     0,     0,
       0,    98,     0,     0,     0,    91,    74,    75,    76,    77,
      78,     0,   152,     0,     0,     0,     0,     0,     0,     0,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,     0,    90,     0,     0,     0,   137,     0,     0,     0,
      91,    74,    75,    76,    77,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,    90,     0,     0,
       0,   139,     0,     0,     0,    91,    74,    75,    76,    77,
      78,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,     0,    90,     0,     0,     0,   208,     0,     0,     0,
      91,    74,    75,    76,    77,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,    90,    73,    74,
      75,    76,    77,    78,     0,    91,     0,     0,     0,     0,
       0,     0,     0,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     0,    90,   113,    74,    75,    76,
      77,    78,     0,    91,     0,     0,     0,     0,     0,     0,
       0,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,     0,    90,   136,    74,    75,    76,    77,    78,
       0,    91,     0,     0,     0,     0,     0,     0,     0,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
       0,    90,   184,    74,    75,    76,    77,    78,     0,    91,
       0,     0,     0,     0,     0,     0,     0,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,    90,
     209,    74,    75,    76,    77,    78,     0,    91,     0,     0,
       0,     0,     0,     0,     0,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,    90,   212,    74,
      75,    76,    77,    78,     0,    91,     0,     0,     0,     0,
       0,     0,     0,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     0,    90,    74,    75,    76,    77,
      78,     0,     0,    91,     0,     0,     0,     0,     0,     0,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,     0,    90,    74,    75,    76,    77,    78,     0,     0,
      91,    76,    77,    78,     0,     0,     0,    79,    80,    81,
       0,     0,     0,    79,    80,    81,    88,    89,    78,    90,
       0,     0,    88,    89,     0,    90,     0,    91,    79,    80,
      81,     0,     0,    91,     0,     0,     0,    88,    89,     0,
      90,     0,     0,     0,     0,     0,     0,     0,    91
};

static const yytype_int16 yycheck[] =
{
      20,    92,   161,    23,    24,     3,    15,    27,    42,     5,
      11,    12,    10,    14,    35,    36,    37,    26,    38,    16,
      40,     0,    19,    44,    45,    16,    47,    17,    19,    49,
      50,    15,    66,   192,    55,     5,    56,    19,    20,    59,
      60,    61,    62,    63,    64,    65,   141,   142,   143,   144,
     145,    15,   211,    15,    74,    75,    76,    77,    78,     8,
       9,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    16,     4,     5,    15,     7,    21,    22,    23,    24,
      25,    31,    32,    15,    61,    61,    18,   178,    20,    21,
      22,    15,    23,    24,    25,    61,    28,     5,    61,     5,
      61,    33,    61,    61,     5,    17,     4,     4,    15,     4,
      20,    15,     5,    16,    46,    20,    48,    49,    50,    51,
      52,    53,    54,     4,    56,    57,    58,    59,    60,    61,
      16,     4,    26,    18,    26,    17,   156,    16,    34,    15,
     160,    29,    17,     4,     4,     5,    20,     7,    25,     4,
      16,    18,     5,    15,     4,    15,    27,    20,    18,    27,
      20,    21,    22,     4,   157,   214,    46,    -1,    28,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,
     200,    -1,   202,    -1,    -1,    -1,    46,   207,    48,    49,
      50,    51,    52,    53,    54,     4,     5,    57,     7,    59,
      60,    61,    -1,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    20,    21,    22,     4,     5,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    33,    15,    -1,    -1,    -1,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    46,    -1,    48,
      49,    50,    51,    52,    53,    54,    -1,    -1,    57,    -1,
      59,    60,    61,    -1,    -1,    -1,    46,    -1,    48,    49,
      50,    51,    52,    53,    54,    21,    22,    23,    24,    25,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    -1,    21,    22,    23,    24,    25,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      -1,    21,    22,    23,    24,    25,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    -1,    21,
      22,    23,    24,    25,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    47,    -1,    21,    22,    23,
      24,    25,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    47,    -1,    21,    22,    23,    24,    25,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    62,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      -1,    47,    -1,    21,    22,    23,    24,    25,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    -1,    47,
      -1,    21,    22,    23,    24,    25,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    -1,    47,    -1,    -1,
      -1,    16,    -1,    -1,    -1,    55,    21,    22,    23,    24,
      25,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      55,    23,    24,    25,    -1,    -1,    -1,    35,    36,    37,
      -1,    -1,    -1,    35,    36,    37,    44,    45,    25,    47,
      -1,    -1,    44,    45,    -1,    47,    -1,    55,    35,    36,
      37,    -1,    -1,    55,    -1,    -1,    -1,    44,    45,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    10,    64,    69,     5,    17,     0,    64,    15,
      66,    11,    12,    14,    71,    72,    75,     4,     5,     7,
      15,    18,    20,    21,    22,    28,    33,    46,    48,    49,
      50,    51,    52,    53,    54,    56,    57,    58,    59,    60,
      61,    70,    74,    78,    88,    16,    19,     5,    15,    26,
      15,     5,    88,    65,    88,    88,    15,    15,    88,    61,
      61,    61,    61,    61,    61,    61,    15,     5,     5,    88,
       5,    88,    75,    20,    21,    22,    23,    24,    25,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      47,    55,    17,    72,     4,    88,    88,    15,    16,     4,
      88,     4,    89,    88,    88,    88,    88,    88,    88,    88,
      75,    20,    15,    20,    20,    62,     5,    76,    77,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    78,    16,    20,    16,     4,    16,
      16,    21,    22,    23,    24,    25,    62,    62,    62,    62,
      62,    62,    62,    16,     4,    73,    26,    19,    20,    18,
      26,    79,    16,    17,    67,    34,    89,    89,    89,    89,
      89,    15,    16,    19,    88,    77,    88,    67,    68,    29,
      17,     4,    20,     4,    20,    80,    18,    78,    84,    85,
      16,     8,     9,    81,    18,    31,    32,    86,    87,     5,
      15,    67,    27,     4,    20,    88,    88,    27,    16,    20,
      88,    82,    20,    67,    83,    81
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    64,    64,    65,    65,    66,    66,    66,
      66,    67,    68,    68,    69,    70,    71,    71,    71,    72,
      73,    73,    73,    74,    74,    74,    75,    75,    75,    76,
      76,    77,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    79,    80,    78,    78,    81,    81,    82,    83,    81,
      84,    84,    85,    85,    86,    87,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    89,
      89,    89,    89,    89,    89
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     5,     2,     0,     2,     0,     2,     2,
       2,     3,     0,     2,     8,     6,     0,     3,     1,     2,
       0,     3,     1,     0,     4,     9,     1,     1,     1,     3,
       1,     3,     1,     1,     8,     3,     3,     2,     3,     4,
       7,     0,     0,     8,     6,     0,     2,     0,     0,     8,
       1,     2,     0,     2,     5,     4,     1,     1,     4,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     4,     4,     4,     4,     4,     4,     4,     2,     1,
       3,     3,     3,     3,     3
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
#line 1582 "1807002.tab.c"
    break;

  case 5: /* input_tail: %empty  */
#line 205 "1807002.y"
                        { (yyval.number) = 0; }
#line 1588 "1807002.tab.c"
    break;

  case 6: /* input_tail: input_tail NUM  */
#line 206 "1807002.y"
                         { (yyval.number) = (yyvsp[-1].number); }
#line 1594 "1807002.tab.c"
    break;

  case 11: /* block: LB block_items RB  */
#line 215 "1807002.y"
                         { (yyval.number) = (yyvsp[-1].number); }
#line 1600 "1807002.tab.c"
    break;

  case 12: /* block_items: %empty  */
#line 217 "1807002.y"
                         { (yyval.number) = 0; }
#line 1606 "1807002.tab.c"
    break;

  case 13: /* block_items: block_items statement  */
#line 218 "1807002.y"
                                { (yyval.number) = (yyvsp[0].number); }
#line 1612 "1807002.tab.c"
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
#line 1644 "1807002.tab.c"
    break;

  case 15: /* func_call: CALL VAR LP pass_Parameter RP SM  */
#line 251 "1807002.y"
                {
			int id = get_Var_Id((yyvsp[-4].string));
			printf("%s Fuction called\n",(yyvsp[-4].string));
			printf("output of fuction : %d\n",vptr[id].n);									}
#line 1653 "1807002.tab.c"
    break;

  case 19: /* para: TYPE VAR  */
#line 260 "1807002.y"
                                                        {printf("Parameter %s: %s\n",(yyvsp[-1].string),(yyvsp[0].string));}
#line 1659 "1807002.tab.c"
    break;

  case 24: /* cdeclaration: cdeclaration TYPE ID1 SM  */
#line 270 "1807002.y"
                                                                {
		printf("\nvalid declaration\n");
		emit_parser("Rule matched: TYPE ID1 SM -> variable declaration");
	}
#line 1668 "1807002.tab.c"
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
#line 1699 "1807002.tab.c"
    break;

  case 26: /* TYPE: INT  */
#line 301 "1807002.y"
                        { (yyval.string) = (yyvsp[0].string);  }
#line 1705 "1807002.tab.c"
    break;

  case 27: /* TYPE: FLOAT  */
#line 303 "1807002.y"
                { (yyval.string) = (yyvsp[0].string);  }
#line 1711 "1807002.tab.c"
    break;

  case 28: /* TYPE: CHAR  */
#line 305 "1807002.y"
                        { (yyval.string) = (yyvsp[0].string);  }
#line 1717 "1807002.tab.c"
    break;

  case 29: /* ID1: ID1 CM ID  */
#line 309 "1807002.y"
                                {}
#line 1723 "1807002.tab.c"
    break;

  case 30: /* ID1: ID  */
#line 310 "1807002.y"
                                        {}
#line 1729 "1807002.tab.c"
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
#line 1762 "1807002.tab.c"
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
#line 1787 "1807002.tab.c"
    break;

  case 33: /* statement: SM  */
#line 368 "1807002.y"
              { (yyval.number) = 0; }
#line 1793 "1807002.tab.c"
    break;

  case 34: /* statement: SWITCH LP switch_expression RP SWITCH_END LB BASE RB  */
#line 369 "1807002.y"
                                                                  {printf("SWITCH case.\n");val=(yyvsp[-5].number);}
#line 1799 "1807002.tab.c"
    break;

  case 35: /* statement: PRINT expression SM  */
#line 370 "1807002.y"
                                    {
		printf("print: %d\n", (yyvsp[-1].number));
		sprintf(tac_buf, "print %d", (yyvsp[-1].number));
		emit_tac(tac_buf);
		(yyval.number) = (yyvsp[-1].number);
	}
#line 1810 "1807002.tab.c"
    break;

  case 36: /* statement: TAKE_INPUT VAR SM  */
#line 376 "1807002.y"
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
#line 1844 "1807002.tab.c"
    break;

  case 37: /* statement: expression SM  */
#line 405 "1807002.y"
                                                {
								(yyval.number) = (yyvsp[-1].number);
								printf("\nvalue of expression: %d\n", ((yyvsp[-1].number))); }
#line 1852 "1807002.tab.c"
    break;

  case 38: /* statement: size_of VAR SM  */
#line 409 "1807002.y"
                                                        {
									int id = get_Var_Id((yyvsp[-1].string));
									printf("total size of %s is %d \n",(yyvsp[-1].string),vptr[id].size);}
#line 1860 "1807002.tab.c"
    break;

  case 39: /* statement: VAR ASSIGN expression SM  */
#line 416 "1807002.y"
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
#line 1880 "1807002.tab.c"
    break;

  case 40: /* statement: VAR LP NUM RP ASSIGN expression SM  */
#line 433 "1807002.y"
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
#line 1909 "1807002.tab.c"
    break;

  case 41: /* $@1: %empty  */
#line 458 "1807002.y"
                              { if_begin_tac((yyvsp[-1].number)); }
#line 1915 "1807002.tab.c"
    break;

  case 42: /* $@2: %empty  */
#line 458 "1807002.y"
                                                          { if_after_branch_tac(); }
#line 1921 "1807002.tab.c"
    break;

  case 43: /* statement: IF LP expression RP $@1 block $@2 if_tail  */
#line 458 "1807002.y"
                                                                                             { (yyval.number) = 0; }
#line 1927 "1807002.tab.c"
    break;

  case 44: /* statement: WHILE LP expression RP block WHILE_END  */
#line 462 "1807002.y"
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
#line 1948 "1807002.tab.c"
    break;

  case 45: /* if_tail: %empty  */
#line 480 "1807002.y"
                      { if_finish_tac(); (yyval.number) = 0; }
#line 1954 "1807002.tab.c"
    break;

  case 46: /* if_tail: ELSE block  */
#line 481 "1807002.y"
                     { if_finish_tac(); (yyval.number) = 0; }
#line 1960 "1807002.tab.c"
    break;

  case 47: /* $@3: %empty  */
#line 482 "1807002.y"
                                { elif_begin_tac((yyvsp[-1].number)); }
#line 1966 "1807002.tab.c"
    break;

  case 48: /* $@4: %empty  */
#line 482 "1807002.y"
                                                              { if_after_branch_tac(); }
#line 1972 "1807002.tab.c"
    break;

  case 49: /* if_tail: ELIF LP expression RP $@3 block $@4 if_tail  */
#line 482 "1807002.y"
                                                                                                 { (yyval.number) = 0; }
#line 1978 "1807002.tab.c"
    break;

  case 54: /* Cs: CASE NUM COL expression SM  */
#line 495 "1807002.y"
                                                             {
						
						if(val==(yyvsp[-3].number)){
							  track=1;
							  printf("\nCase No : %d  and Result :  %d\n",(yyvsp[-3].number),(yyvsp[-1].number));
						}
					}
#line 1990 "1807002.tab.c"
    break;

  case 55: /* Dflt: DEFAULT COL expression SM  */
#line 504 "1807002.y"
                                                               {
						if(track!=1){
							printf("\nResult in default Value is :  %d\n",(yyvsp[-1].number));
						}
						track=0;
					}
#line 2001 "1807002.tab.c"
    break;

  case 56: /* expression: NUM  */
#line 514 "1807002.y"
                                        { (yyval.number) = (yyvsp[0].number); 	}
#line 2007 "1807002.tab.c"
    break;

  case 57: /* expression: VAR  */
#line 516 "1807002.y"
                        {
				int id = get_Var_Id((yyvsp[0].string));
            	(yyval.number) = vptr[id].n;

			}
#line 2017 "1807002.tab.c"
    break;

  case 58: /* expression: VAR LP NUM RP  */
#line 523 "1807002.y"
                        {
				int id = get_Var_Id((yyvsp[-3].string));
            	(yyval.number) = vptr[id].arrayVal[(yyvsp[-1].number)];

			}
#line 2027 "1807002.tab.c"
    break;

  case 59: /* expression: expression PLUS expression  */
#line 530 "1807002.y"
                                        {
		(yyval.number) = (yyvsp[-2].number) + (yyvsp[0].number);
		printf("%d + %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d + %d", t, (yyvsp[-2].number), (yyvsp[0].number));
		emit_tac(tac_buf);
	}
#line 2039 "1807002.tab.c"
    break;

  case 60: /* expression: expression MINUS expression  */
#line 538 "1807002.y"
                                        {
		(yyval.number) = (yyvsp[-2].number) - (yyvsp[0].number);
		printf("%d - %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d - %d", t, (yyvsp[-2].number), (yyvsp[0].number));
		emit_tac(tac_buf);
	}
#line 2051 "1807002.tab.c"
    break;

  case 61: /* expression: expression MULT expression  */
#line 546 "1807002.y"
                                        {
		(yyval.number) = (yyvsp[-2].number) * (yyvsp[0].number);
		printf("%d * %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d * %d", t, (yyvsp[-2].number), (yyvsp[0].number));
		emit_tac(tac_buf);
	}
#line 2063 "1807002.tab.c"
    break;

  case 62: /* expression: expression DIV expression  */
#line 554 "1807002.y"
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
#line 2081 "1807002.tab.c"
    break;

  case 63: /* expression: expression POW expression  */
#line 567 "1807002.y"
                                    {
		(yyval.number) = pow((yyvsp[-2].number),(yyvsp[0].number));
		printf("%d ^ %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d ^ %d", t, (yyvsp[-2].number), (yyvsp[0].number));
		emit_tac(tac_buf);
	}
#line 2093 "1807002.tab.c"
    break;

  case 64: /* expression: LP expression RP  */
#line 575 "1807002.y"
                                        { (yyval.number) = (yyvsp[-1].number);	}
#line 2099 "1807002.tab.c"
    break;

  case 65: /* expression: expression inc  */
#line 577 "1807002.y"
                                 { (yyval.number)=(yyvsp[-1].number)+1; printf("inc: %d\n",(yyval.number));}
#line 2105 "1807002.tab.c"
    break;

  case 66: /* expression: expression dec  */
#line 578 "1807002.y"
                                 { (yyval.number)=(yyvsp[-1].number)-1; printf("dec: %d\n",(yyval.number));}
#line 2111 "1807002.tab.c"
    break;

  case 67: /* expression: PLUS expression  */
#line 581 "1807002.y"
    {
        (yyval.number) = (yyvsp[0].number);
    }
#line 2119 "1807002.tab.c"
    break;

  case 68: /* expression: MINUS expression  */
#line 585 "1807002.y"
    {
        (yyval.number) = -(yyvsp[0].number);
    }
#line 2127 "1807002.tab.c"
    break;

  case 69: /* expression: expression MOD expression  */
#line 590 "1807002.y"
    {

        (yyval.number) = (int)(yyvsp[-2].number) % (int)(yyvsp[0].number);
    }
#line 2136 "1807002.tab.c"
    break;

  case 70: /* expression: expression LT expression  */
#line 596 "1807002.y"
        {
		(yyval.number) = ((yyvsp[-2].number) < (yyvsp[0].number));
	}
#line 2144 "1807002.tab.c"
    break;

  case 71: /* expression: expression GT expression  */
#line 600 "1807002.y"
        {
		(yyval.number) = ((yyvsp[-2].number) > (yyvsp[0].number));
	}
#line 2152 "1807002.tab.c"
    break;

  case 72: /* expression: expression LTE expression  */
#line 605 "1807002.y"
    {
        (yyval.number) = ((yyvsp[-2].number) <= (yyvsp[0].number));
    }
#line 2160 "1807002.tab.c"
    break;

  case 73: /* expression: expression GTE expression  */
#line 609 "1807002.y"
    {
        (yyval.number) = ((yyvsp[-2].number) >= (yyvsp[0].number));
    }
#line 2168 "1807002.tab.c"
    break;

  case 74: /* expression: expression EEQL expression  */
#line 613 "1807002.y"
    {
        (yyval.number) = ((yyvsp[-2].number) == (yyvsp[0].number));
    }
#line 2176 "1807002.tab.c"
    break;

  case 75: /* expression: expression NEQL expression  */
#line 617 "1807002.y"
    {
        (yyval.number) = ((yyvsp[-2].number) != (yyvsp[0].number));
    }
#line 2184 "1807002.tab.c"
    break;

  case 76: /* expression: expression AND expression  */
#line 621 "1807002.y"
    {
        (yyval.number) = ( (yyvsp[-2].number) && (yyvsp[0].number));
		printf("%d AND %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
    }
#line 2193 "1807002.tab.c"
    break;

  case 77: /* expression: expression OR expression  */
#line 626 "1807002.y"
    {
        (yyval.number) = ((yyvsp[-2].number) || (yyvsp[0].number));
		printf("%d OR %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
    }
#line 2202 "1807002.tab.c"
    break;

  case 78: /* expression: expression XOR expression  */
#line 631 "1807002.y"
    {
        (yyval.number) = ((int)(yyvsp[-2].number) ^ (int)(yyvsp[0].number));
		printf("%d XOR %d : \n",(yyvsp[-2].number),(yyvsp[0].number));
    }
#line 2211 "1807002.tab.c"
    break;

  case 79: /* expression: NOT expression  */
#line 636 "1807002.y"
    {
        (yyval.number) = !(yyvsp[0].number);
    }
#line 2219 "1807002.tab.c"
    break;

  case 80: /* expression: '(' expression ')'  */
#line 640 "1807002.y"
    {
        (yyval.number) = (yyvsp[-1].number);
    }
#line 2227 "1807002.tab.c"
    break;

  case 81: /* expression: SIN '(' expression ')'  */
#line 644 "1807002.y"
    {
        (yyval.number) = sin((yyvsp[-1].number));
		printf("sin( %d ) : \n",(yyvsp[-1].number));

    }
#line 2237 "1807002.tab.c"
    break;

  case 82: /* expression: COS '(' expression ')'  */
#line 650 "1807002.y"
    {
        (yyval.number) = cos((yyvsp[-1].number));
		printf("cos( %d ) : \n",(yyvsp[-1].number));
    }
#line 2246 "1807002.tab.c"
    break;

  case 83: /* expression: TAN '(' expression ')'  */
#line 655 "1807002.y"
    {
        (yyval.number) = tan((yyvsp[-1].number));
		printf("tan( %d ) : \n",(yyvsp[-1].number));
    }
#line 2255 "1807002.tab.c"
    break;

  case 84: /* expression: LOG '(' expression ')'  */
#line 660 "1807002.y"
    {
        (yyval.number) = log10((yyvsp[-1].number));
		printf("log10( %d ) : \n",(yyvsp[-1].number));
    }
#line 2264 "1807002.tab.c"
    break;

  case 85: /* expression: LOG2 '(' expression ')'  */
#line 665 "1807002.y"
    {
        (yyval.number) = log2((yyvsp[-1].number));
		printf("log2( %d ) : \n",(yyvsp[-1].number));
    }
#line 2273 "1807002.tab.c"
    break;

  case 86: /* expression: LN '(' expression ')'  */
#line 670 "1807002.y"
    {
        (yyval.number) = log((yyvsp[-1].number));
    }
#line 2281 "1807002.tab.c"
    break;

  case 87: /* expression: SQRT '(' expression ')'  */
#line 674 "1807002.y"
    {
    	(yyval.number) = sqrt((yyvsp[-1].number));
		
    }
#line 2290 "1807002.tab.c"
    break;

  case 88: /* expression: expression FACTORIAL  */
#line 679 "1807002.y"
                {
                    long long x = 1;
                	for(long long i=1;i<=(yyvsp[-1].number);i++)
					 	x*=i;
                    (yyval.number) = x;
                    
                }
#line 2302 "1807002.tab.c"
    break;

  case 89: /* switch_expression: NUM  */
#line 690 "1807002.y"
                                                        { (yyval.number) = (yyvsp[0].number); val = (yyval.number);	}
#line 2308 "1807002.tab.c"
    break;

  case 90: /* switch_expression: switch_expression PLUS switch_expression  */
#line 692 "1807002.y"
                                                        { (yyval.number) = (yyvsp[-2].number) + (yyvsp[0].number); val = (yyval.number); }
#line 2314 "1807002.tab.c"
    break;

  case 91: /* switch_expression: switch_expression MINUS switch_expression  */
#line 694 "1807002.y"
                                                        { (yyval.number) = (yyvsp[-2].number) - (yyvsp[0].number); val = (yyval.number); }
#line 2320 "1807002.tab.c"
    break;

  case 92: /* switch_expression: switch_expression MULT switch_expression  */
#line 696 "1807002.y"
                                                        { (yyval.number) = (yyvsp[-2].number) * (yyvsp[0].number);  val = (yyval.number);}
#line 2326 "1807002.tab.c"
    break;

  case 93: /* switch_expression: switch_expression DIV switch_expression  */
#line 698 "1807002.y"
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
#line 2341 "1807002.tab.c"
    break;

  case 94: /* switch_expression: switch_expression POW switch_expression  */
#line 708 "1807002.y"
                                                  { (yyval.number) = pow((yyvsp[-2].number),(yyvsp[0].number));  val = (yyval.number);}
#line 2347 "1807002.tab.c"
    break;


#line 2351 "1807002.tab.c"

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

#line 712 "1807002.y"





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
