/* final */
%{
	#include<stdio.h>
	#include <string.h>
	#include "1807002.tab.h"
	#include<stdlib.h>
	int yyparse(void);
	void yyerror(const char *s);
	void open_tac_file(void);
	void emit_parser(const char *line);
	void emit_semantic(const char *line);
	extern FILE *lexer_file;

	int step_counter = 1;
	void trace(const char *token) {
		printf("%-5d | %-20s | %-20s\n", step_counter++, yytext, token);
		if(lexer_file) fprintf(lexer_file, "%-5d | %-20s | %-20s\n", step_counter, yytext, token);
	}
%}

var [a-zA-Z_][a-zA-Z0-9_]*
comment [/][-][-](.*|\n)[-][-][/]
digit [0-9]+

/*RE and Action*/

%%

{comment} { trace("COMMENT"); }
"#get*<"{var}">" { trace("HEADER_INCLUSION"); }

"++" { trace("inc"); return inc; }
"--" { trace("dec"); return dec; }
"{" { trace("LB"); return LB; }
"}" { trace("RB"); return RB; }
"break" { trace("BREAK"); return BREAK; }

"number" { trace("INT"); yylval.string=strdup(yytext); return INT; }
"decimal" { trace("FLOAT"); yylval.string=strdup(yytext); return FLOAT; }
"symbol" { trace("CHAR"); yylval.string=strdup(yytext); return CHAR; }
"arr" { trace("ARRAY"); yylval.string=strdup(yytext); return ARRAY; }
"sizeof" { trace("size_of"); return size_of; }
"call" { trace("CALL"); return CALL; }

{digit} {
	trace("NUM");
	yylval.number = atoi(yytext);
	return NUM;
}

"case" { trace("CASE"); return CASE; }
"switch" { trace("SWITCH"); return SWITCH; }
"switch_end" { trace("SWITCH_END"); return SWITCH_END; }
"default" { trace("DEFAULT"); return DEFAULT; }
":" { trace("COL"); return COL; }

"repeat" { trace("WHILE"); return WHILE; }
"until" { trace("WHILE_END"); return WHILE_END; }
"(" { trace("LP"); return LP; }
")" { trace("RP"); return RP; }

"," { trace("CM"); return CM; }
";" { trace("SM"); return SM; }

"+" { trace("PLUS"); return PLUS; }
"-" { trace("MINUS"); return MINUS; }
"*" { trace("MULT"); return MULT; }
"/" { trace("DIV"); return DIV; }
"%" { trace("MOD"); return MOD; }
"^" { trace("POW"); return POW; }
"=" { trace("ASSIGN"); return ASSIGN; }

">" { trace("GT"); return GT; }
">="  { trace("GTE"); return GTE; }
"<" { trace("LT"); return LT; }
"<=" { trace("LTE"); return LTE; }
"==" { trace("EEQL"); return EEQL; }
"!=" { trace("NEQL"); return NEQL; }

"XOR" { trace("XOR"); return XOR; }
"AND" { trace("AND"); return AND; }
"OR" { trace("OR"); return OR; }
"NOT" { trace("NOT"); return NOT; }
"SIN" { trace("SIN"); return SIN; }
"COS" { trace("COS"); return COS; }
"TAN" { trace("TAN"); return TAN; }
"SQRT" { trace("SQRT"); return SQRT; }
"log" { trace("LOG"); return LOG; }
"log2" { trace("LOG2"); return LOG2; }
"ln" { trace("LN"); return LN; }
"FACT" { trace("FACTORIAL"); return FACTORIAL; }

"if" { trace("IF"); return IF; }
"elif" { trace("ELIF"); return ELIF; }
"else" { trace("ELSE"); return ELSE; }
"start()" { trace("MAIN"); return MAIN; }
"func" {
	trace("FUNC_NUM");
	printf("Function declared with return type : INTERGER\n");
	return FUNC_NUM;
}
"def->T-symbol" { trace("FUNC_STR"); return FUNC_STR; }

"print"      { trace("PRINT");      return PRINT;      }
"take_input" { trace("TAKE_INPUT"); return TAKE_INPUT; }

{var} {
	trace("VAR");
	yylval.string=strdup(yytext);
	return VAR;
}

[ \t\n]*

. {
	yyerror("Unknown Character.\n");
}
%%

/* user subroutines */

int main()
{
	open_tac_file();
	yyout = freopen("output.txt","w",stdout);
	yyparse();
}
