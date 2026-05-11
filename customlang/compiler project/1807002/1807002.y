/* last shondha */
%{
	#include<stdio.h>
	#include <math.h>
	#include <stdlib.h>
	void open_tac_file(void);
	int cnt=1,cntt=0,val,track=0;

	/* Phase 4: TAC Generator */
	int temp_count = 0;
	int label_count = 0;
	FILE *tac_file = NULL;

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

	void emit_tac(const char *line) {
		if(tac_file) fprintf(tac_file, "%s\n", line);
		printf("[TAC] %s\n", line);
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
%token<string> IF ELIF ELSE MAIN INT FLOAT DOUBLE CHAR LP RP LB RB CM SM PLUS MINUS MULT DIV POW ASSIGN FOR FOR_END COL WHILE WHILE_END BREAK DEFAULT CASE SWITCH SWITCH_END inc dec MOD LTE GTE EEQL NEQL AND OR NOT XOR
%token<string> SIN COS TAN SQRT LOG LOG2 LN FACTORIAL ARRAY size_of CALL
%type <string> para
%type <string> TYPE
%type <string> statement 
 
%type <number> expression
%type <number> switch_expression
%nonassoc ELIF
%nonassoc ELSE
%expect 184
%left LT GT LTE GTE EEQL NEQL
%left PLUS MINUS
%left MULT DIV
%left POW

/* Simple grammar rules */

%%

program: 
        | MAIN LB cstatement RB {
		printf("\nSuccessful compilation\n");
		printf("\n--- TAC Generation Complete. See tac_output.txt ---\n");
		if(tac_file) fclose(tac_file);
	}
		| func_block program
	 ;

cstatement: /* empty */

	| cstatement statement
	
	| cdeclaration
	
	
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
                	vptr[total_Var].n= $7;
                	total_Var++;
            	}

				


			}
			
			
			printf("Function name : %s\n",$2);
	
		}
 

Parameter :
		| Parameter CM para		
		|	para					
		;
para : TYPE VAR						{printf("Parameter %s: %s\n",$1,$2);}
		;
cdeclaration:	
				| cdeclaration TYPE ID1 SM	{ printf("\nvalid declaration\n"); }
				| cdeclaration	ARRAY LP TYPE RP LP NUM RP VAR SM 	{
					/*
					int id = get_Var_Id($9);

            
            		if(id!=-1)
            		{	
                		printf("already declared\n");
            		}
            		else
            		{
                		vptr[total_Var].isArray = 1;
                		vptr[total_Var].size = $7;
                		total_Var++;
            		}
					*/
					printf("Array declaration Successful\n")
 
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
            	}
            	else
            	{
                	vptr[total_Var].str=$1;
                	vptr[total_Var].n=0;
                	total_Var++;
            	}

				


			}
	

     ;


statement: SM
	| SWITCH LP switch_expression RP SWITCH_END LB BASE RB    {printf("SWITCH case.\n");val=$3;} 

	| expression SM 			{
								$$ = $1 
								printf("\nvalue of expression: %d\n", ($1)); }

	| size_of VAR SM				{
									int id = get_Var_Id($2);
									printf("%d \n",vptr[id].size);}
	
	

    | VAR ASSIGN expression	SM		
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

				sprintf(tac_buf, "%s = %d", $1, $3);
				emit_tac(tac_buf);

				/*
				for(int i=0;i<total_Var;i++)
				{
					printf("%s",vptr[i].str);
					printf(" %d\n",vptr[i].n);
				}
				*/ 

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

	| IF LP expression RP LB statement RB {
		if($3) {
			printf("\nTrue conditioin. IF executes : %d\n",($6));
			char *l = new_label();
			sprintf(tac_buf, "if (%d) goto %s", $3, l);
			emit_tac(tac_buf);
		} else {
			printf("\nFalse condition.If not executes\n");
			emit_tac("if condition false, skip");
		}
	}

	| IF LP expression RP LB statement RB ELSE LB statement RB {
		if($3) {
			printf("\nTrue conditioin. IF executes : %d\n",$6);
			char *l = new_label();
			sprintf(tac_buf, "if (%d) goto %s", $3, l);
			emit_tac(tac_buf);
		} else {
			printf("\nFalse condition. Else executes %d\n",$10);
			emit_tac("else branch");
		}
	}
	| FOR LP NUM COL NUM RP FOR_END LB expression RB     {
	   printf("For Loop :\n");
	   int i;
	   for(i=$3;i<$5;i++){
	   printf("Iteration no : %d and expression or statement value : %d\n",i,$9);
	   }
	}
	/*while loop starts*/

	| WHILE LP expression RP WHILE_END LB statement RB {
		int condition = $3;
		printf("repeat loop executed, condition was: %d\n", condition);
		if(condition){
			printf("Loop body value: %d\n", $7);
		}
		$$ = $7;
		
		char *l_start = new_label();
		char *l_exit = new_label();
		sprintf(tac_buf, "%s:", l_start);
		emit_tac(tac_buf);
		sprintf(tac_buf, "if (%d) goto %s", condition, l_exit);
		emit_tac(tac_buf);
		sprintf(tac_buf, "goto %s", l_start);
		emit_tac(tac_buf);
		sprintf(tac_buf, "%s:", l_exit);
		emit_tac(tac_buf);
	}

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
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d + %d", t, $1, $3);
		emit_tac(tac_buf);
	}

	| expression MINUS expression	{
		$$ = $1 - $3;
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d - %d", t, $1, $3);
		emit_tac(tac_buf);
	}

	| expression MULT expression	{
		$$ = $1 * $3;
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d * %d", t, $1, $3);
		emit_tac(tac_buf);
	}

	| expression DIV expression	{
		if($3) {
			$$ = $1 / $3;
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
		char *t = new_temp();
		sprintf(tac_buf, "%s = %d ^ %d", t, $1, $3);
		emit_tac(tac_buf);
	}


	| expression LT expression	{ $$ = $1 < $3; }

	| expression GT expression	{ $$ = $1 > $3; }

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
    }
    | expression OR expression          
    {
        $$ = ($1 || $3);
    }
    | expression XOR expression         
    {
        $$ = ((int)$1 ^ (int)$3);
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

    }
    | COS '(' expression ')'      
    {
        $$ = cos($3);
    }
    | TAN '(' expression ')'      
    {
        $$ = tan($3);
    }
    | LOG '(' expression ')'      
    {
        $$ = log10($3);
    }
    | LOG2 '(' expression ')'     
    {
        $$ = log2($3);
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
	tac_file = fopen("tac_output.txt", "w");
	if(tac_file) {
		fprintf(tac_file, "=== THREE ADDRESS CODE (TAC) ===\n\n");
	}
}


yyerror(char *s){
	printf( "%s\n", s);
}