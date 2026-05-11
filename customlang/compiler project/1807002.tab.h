/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_1807002_TAB_H_INCLUDED
# define YY_YY_1807002_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    FUNC_NUM = 258,                /* FUNC_NUM  */
    NUM = 259,                     /* NUM  */
    VAR = 260,                     /* VAR  */
    FUNC_STR = 261,                /* FUNC_STR  */
    IF = 262,                      /* IF  */
    ELIF = 263,                    /* ELIF  */
    ELSE = 264,                    /* ELSE  */
    MAIN = 265,                    /* MAIN  */
    INT = 266,                     /* INT  */
    FLOAT = 267,                   /* FLOAT  */
    DOUBLE = 268,                  /* DOUBLE  */
    CHAR = 269,                    /* CHAR  */
    LP = 270,                      /* LP  */
    RP = 271,                      /* RP  */
    LB = 272,                      /* LB  */
    RB = 273,                      /* RB  */
    CM = 274,                      /* CM  */
    SM = 275,                      /* SM  */
    PLUS = 276,                    /* PLUS  */
    MINUS = 277,                   /* MINUS  */
    MULT = 278,                    /* MULT  */
    DIV = 279,                     /* DIV  */
    POW = 280,                     /* POW  */
    ASSIGN = 281,                  /* ASSIGN  */
    COL = 282,                     /* COL  */
    WHILE = 283,                   /* WHILE  */
    WHILE_END = 284,               /* WHILE_END  */
    BREAK = 285,                   /* BREAK  */
    DEFAULT = 286,                 /* DEFAULT  */
    CASE = 287,                    /* CASE  */
    SWITCH = 288,                  /* SWITCH  */
    SWITCH_END = 289,              /* SWITCH_END  */
    inc = 290,                     /* inc  */
    dec = 291,                     /* dec  */
    MOD = 292,                     /* MOD  */
    LT = 293,                      /* LT  */
    GT = 294,                      /* GT  */
    LTE = 295,                     /* LTE  */
    GTE = 296,                     /* GTE  */
    EEQL = 297,                    /* EEQL  */
    NEQL = 298,                    /* NEQL  */
    AND = 299,                     /* AND  */
    OR = 300,                      /* OR  */
    NOT = 301,                     /* NOT  */
    XOR = 302,                     /* XOR  */
    SIN = 303,                     /* SIN  */
    COS = 304,                     /* COS  */
    TAN = 305,                     /* TAN  */
    SQRT = 306,                    /* SQRT  */
    LOG = 307,                     /* LOG  */
    LOG2 = 308,                    /* LOG2  */
    LN = 309,                      /* LN  */
    FACTORIAL = 310,               /* FACTORIAL  */
    ARRAY = 311,                   /* ARRAY  */
    size_of = 312,                 /* size_of  */
    CALL = 313,                    /* CALL  */
    PRINT = 314,                   /* PRINT  */
    TAKE_INPUT = 315               /* TAKE_INPUT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 154 "1807002.y"

        int number;
        char *string;

#line 129 "1807002.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_1807002_TAB_H_INCLUDED  */
