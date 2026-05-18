/* final */

%{
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





	
%}
%union 
{
        int number;
        char *string;
}
/* BISON Declarations */

%token FUNC_NUM
%token<number> NUM 
%token<string> VAR FUNC_STR
%token<string> IF ELIF ELSE MAIN INT FLOAT DOUBLE CHAR LP RP LB RB CM SM PLUS MINUS MULT DIV POW ASSIGN COL WHILE WHILE_END BREAK DEFAULT CASE SWITCH SWITCH_END inc dec MOD LT GT LTE GTE EEQL NEQL AND OR NOT XOR
%token<string> SIN COS TAN SQRT LOG LOG2 LN FACTORIAL ARRAY size_of CALL PRINT TAKE_INPUT STRING_LITERAL
%expect 208
%type <string> para
%type <string> TYPE
%type <number> statement 
 
%type <number> expression
%type <number> block
%type <number> block_items
%type <number> if_tail
%type <number> input_tail
%type <number> switch_expression
%nonassoc ELIF
%nonassoc ELSE
%left LT GT LTE GTE EEQL NEQL
%left PLUS MINUS
%left MULT DIV
%left POW

/* Simple grammar rules */

%%

program: 
        | MAIN LB cstatement RB input_tail {
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
		| func_block program
	 ;

input_tail: /* empty */ { $$ = 0; }
	| input_tail NUM { $$ = $1; }
	;

cstatement: /* empty */
	| cstatement statement
	| cstatement cdeclaration
	| cstatement func_call
	;

block: LB block_items RB { $$ = $2; };

block_items: /* empty */ { $$ = 0; }
	| block_items statement { $$ = $2; }
	;

func_block: FUNC_NUM VAR LP Parameter RP LB statement RB
		{
			{
				int id = get_Var_Id($2);
            
            
            	if(id!=-1)
            	{
                	printf("already declared\n");
            	}
            	else
            	{
                	vptr[total_Var].str=$2;
					printf("func save %s\n",$2);
                	vptr[total_Var].n= $7;
					printf("%d func output %d\n",total_Var,$7);
                	total_Var++;
            	}

				


			}
			
			
			printf("Function name : %s\n",$2);
	
		}
 
func_call: CALL VAR LP pass_Parameter RP SM		
		{
			int id = get_Var_Id($2);
			printf("%s Fuction called\n",$2);
			printf("output of fuction : %d\n",vptr[id].n);									}

Parameter :
		| Parameter CM para		
		|	para					
		;
para : TYPE VAR						{printf("Parameter %s: %s\n",$1,$2);}
		;

pass_Parameter :
		| pass_Parameter CM NUM		
		| NUM					
		;


cdeclaration:	
				| cdeclaration TYPE ID1 SM	{
		printf("\nvalid declaration\n");
		emit_parser("Rule matched: TYPE ID1 SM -> variable declaration");
	}
				| ARRAY LP TYPE RP LP NUM RP VAR SM 	{
					
					int id = get_Var_Id($8);

            
            		if(id!=-1)
            		{	
                		printf("already declared\n");
            		}
            		else
            		{
                		vptr[total_Var].isArray = 1;
						vptr[total_Var].str = $8 ;
                		vptr[total_Var].size = $6;
                		total_Var++;
            		}
					
					printf("Array declaration Successful\n");
		emit_parser("Rule matched: ARRAY declaration");
					printf("Printing table\n");
					for(int i = 0 ; i<total_Var; i++){
                		printf("%d %s\n",i,vptr[i].str);
                	}
            
 
				}

TYPE : INT		{ $$ = $1;  }

     | FLOAT	{ $$ = $1;  }

     | CHAR		{ $$ = $1;  }
     ;


ID1  : ID1 CM ID		{}
		| ID			{}
		;
ID	: VAR ASSIGN expression			
			{
				int id = get_Var_Id($1);
				
            	if(id==-1)
            	{

					vptr[total_Var].str=$1;
                	vptr[total_Var].n=$3;
                	total_Var++;

                	
            	}
            	else
            	{
                	vptr[id].str=$1;
                	vptr[id].n=$3;
            	}

				/*
				for(int i=0;i<total_Var;i++)
				{
					printf("%s",vptr[i].str);
					printf(" %d\n",vptr[i].n);
				}
				*/


			}
	| VAR

			{
				int id = get_Var_Id($1);
            
            
            	if(id!=-1)
            	{
                	printf("already declared\n");
				emit_semantic("ERROR: duplicate variable declaration");
            	}
            	else
            	{
                	vptr[total_Var].str=$1;
                	vptr[total_Var].n=0;
                	total_Var++;
            	}

				


			}
	

     ;


statement: SM { $$ = 0; }
	| SWITCH LP switch_expression RP SWITCH_END LB BASE RB    {printf("SWITCH case.\n");val=$3;} 
	| PRINT expression SM       {
		printf("print: %d\n", $2);
		sprintf(tac_buf, "print %d", $2);
		emit_tac(tac_buf);
		$$ = 0;
	}
	| PRINT STRING_LITERAL SM {
		printf("print_str: %s\n", $2);
		sprintf(tac_buf, "print_str %s", $2);
		emit_tac(tac_buf);
		$$ = 0;
	}
	| TAKE_INPUT VAR SM         {
							int id = get_Var_Id($2);
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
											printf("take_input: %s = %d\n", $2, input_val);
											sprintf(tac_buf, "%s = %d  /* take_input */", $2, input_val);
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
								printf("Error: variable %s not declared\n", $2);
							}
							$$ = 0;
						}
	| expression SM 			{
								$$ = $1;
								printf("\nvalue of expression: %d\n", ($1)); }

	| size_of VAR SM				{
									int id = get_Var_Id($2);
									printf("total size of %s is %d \n",$2,vptr[id].size);}
	
	

    | VAR ASSIGN expression	SM		
			{
				int id = get_Var_Id($1);
				if(id==-1) {
					vptr[total_Var].str=$1;
                	vptr[total_Var].n=$3;
                	total_Var++;
            	} else {
                	vptr[id].str=$1;
                	vptr[id].n=$3;
            	}
            	sprintf(tac_buf, "%s = %d", $1, $3);
            	emit_tac(tac_buf);
		sprintf(tac_buf, "%-20s | %-10s | %-10d | %-10d", $1, "number", $3, 0);
		emit_semantic(tac_buf);
			}  
	
	| VAR LP NUM RP ASSIGN expression	SM		
			{
				int id = get_Var_Id($1);
				
            	if(id==-1)
            	{

					/* error */

                	
            	}
            	else
            	{
                	vptr[id].arrayVal[$3] = $6;
            	}

				/*
				for(int i=0;i<total_Var;i++)
				{
					printf("%s",vptr[i].str);
					printf(" %d\n",vptr[i].n);
				}
				*/ 

			}  

	| IF LP expression RP { if_begin_tac($3); } block { if_after_branch_tac(); } if_tail { $$ = 0; }

	/*while loop starts*/

	| WHILE LP expression RP block WHILE_END {
		char *l_start = new_label();
		char *l_end   = new_label();
		sprintf(tac_buf, "%s:", l_start);
		emit_tac(tac_buf);
		sprintf(tac_buf, "if NOT %d goto %s", $3, l_end);
		emit_tac(tac_buf);
		sprintf(tac_buf, "  body = %d", $5);
		emit_tac(tac_buf);
		sprintf(tac_buf, "%s:", l_end);
		emit_tac(tac_buf);
		int condition = $3;
		printf("repeat loop executed, condition was: %d\n", condition);
		if(condition) printf("Loop body value: %d\n", $5);
		$$ = $5;
	}

if_tail
	: /* empty */ { if_finish_tac(); $$ = 0; }
	| ELSE block { if_finish_tac(); $$ = 0; }
	| ELIF LP expression RP { elif_begin_tac($3); } block { if_after_branch_tac(); } if_tail { $$ = 0; }
	;

///////////////////////
	
			BASE : Bas   
				 | Bas Dflt 
				 ;

			Bas   : /*NULL*/
				 | Bas Cs     
				 ;

			Cs    : CASE NUM COL expression SM   {
						
						if(val==$2){
							  track=1;
							  printf("\nCase No : %d  and Result :  %d\n",$2,$4);
						}
					}
				 ;

			Dflt    : DEFAULT COL expression SM    {
						if(track!=1){
							printf("\nResult in default Value is :  %d\n",$3);
						}
						track=0;
					}
				 ;    
	/////////////////////////////
	
	
expression: NUM				{ $$ = $1; 	}
	| VAR
			{
				int id = get_Var_Id($1);
            	$$ = vptr[id].n;

			}

	| VAR LP NUM RP
			{
				int id = get_Var_Id($1);
            	$$ = vptr[id].arrayVal[$3];

			}
	

	| expression PLUS expression	{
		$$ = $1 + $3;
		printf("%d + %d : \n",$1,$3);
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d + %d", t, $1, $3);
		emit_tac(tac_buf);
	}

	| expression MINUS expression	{
		$$ = $1 - $3;
		printf("%d - %d : \n",$1,$3);
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d - %d", t, $1, $3);
		emit_tac(tac_buf);
	}

	| expression MULT expression	{
		$$ = $1 * $3;
		printf("%d * %d : \n",$1,$3);
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d * %d", t, $1, $3);
		emit_tac(tac_buf);
	}

	| expression DIV expression	{
		if($3) {
			$$ = $1 / $3;
			printf("%d / %d : \n",$1,$3);
			char *t = new_temp();
			sprintf(tac_buf, "%s = %d / %d", t, $1, $3);
			emit_tac(tac_buf);
		} else {
			$$ = 0;
			printf("\ndivision by zero error\t");
			emit_tac("ERROR: division by zero");
		}
	}
	| expression POW expression {
		$$ = pow($1,$3);
		printf("%d ^ %d : \n",$1,$3);
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d ^ %d", t, $1, $3);
		emit_tac(tac_buf);
	}

	| LP expression RP		{ $$ = $2;	}
	
	| expression inc         { $$=$1+1; printf("inc: %d\n",$$);}
	| expression dec         { $$=$1-1; printf("dec: %d\n",$$);}

	| PLUS expression
    {
        $$ = $2;
    }
    | MINUS expression
    {
        $$ = -$2;
    }
            
    | expression MOD expression         
    {

        $$ = (int)$1 % (int)$3;
    }
			
	| expression LT expression        
	{
		$$ = ($1 < $3);
	}
	| expression GT expression        
	{
		$$ = ($1 > $3);
	}
            
    | expression LTE expression        
    {
        $$ = ($1 <= $3);
    }
    | expression GTE expression        
    {
        $$ = ($1 >= $3);
    }
    | expression EEQL expression         
    {
        $$ = ($1 == $3);
    }
	| expression NEQL expression        
    {
        $$ = ($1 != $3);
    }
    | expression AND expression         
    {
        $$ = ( $1 && $3);
		printf("%d AND %d : \n",$1,$3);
    }
    | expression OR expression          
    {
        $$ = ($1 || $3);
		printf("%d OR %d : \n",$1,$3);
    }
    | expression XOR expression         
    {
        $$ = ((int)$1 ^ (int)$3);
		printf("%d XOR %d : \n",$1,$3);
    }
	| NOT expression              
    {
        $$ = !$2;
    }
    | '(' expression ')'          
    {
        $$ = $2;
    }
    | SIN '(' expression ')'      
    {
        $$ = sin($3);
		printf("sin( %d ) : \n",$3);

    }
    | COS '(' expression ')'      
    {
        $$ = cos($3);
		printf("cos( %d ) : \n",$3);
    }
    | TAN '(' expression ')'      
    {
        $$ = tan($3);
		printf("tan( %d ) : \n",$3);
    }
    | LOG '(' expression ')'      
    {
        $$ = log10($3);
		printf("log10( %d ) : \n",$3);
    }
    | LOG2 '(' expression ')'     
    {
        $$ = log2($3);
		printf("log2( %d ) : \n",$3);
    }
    | LN '(' expression ')'       
    {
        $$ = log($3);
    }
    | SQRT '(' expression ')'     
    {
    	$$ = sqrt($3);
		
    }
	| expression FACTORIAL   
                {
                    long long x = 1;
                	for(long long i=1;i<=$1;i++)
					 	x*=i;
                    $$ = x;
                    
                }

	
	;
	///////////////////////////////////////
	switch_expression: NUM				{ $$ = $1; val = $$;	}

	| switch_expression PLUS switch_expression	{ $$ = $1 + $3; val = $$; }

	| switch_expression MINUS switch_expression	{ $$ = $1 - $3; val = $$; }

	| switch_expression MULT switch_expression	{ $$ = $1 * $3;  val = $$;}

	| switch_expression DIV switch_expression	{ 	if($3) 
				  		{
				     			$$ = $1 / $3; val = $$;
				  		}
				  		else
				  		{
							$$ = 0;
							 val = $$;
				  		} 	
				    	}
	| switch_expression POW switch_expression { $$ = pow($1,$3);  val = $$;}

	
	;
%%




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