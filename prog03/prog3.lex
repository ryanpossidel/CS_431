/* 
Written by Ryan Possidel
CS 431 Prog03
Language: Flex
Compiler: g++ and flex
*/

%option noyywrap

	int line_no = 1;
	

%%

"\n"|"\r\n"	{
		line_no++;
	}

[[:BLANK:]]+

set		{
		printf("Line %d: SET\n", line_no);
	}
	
get		{
		printf("Line %d: GET\n", line_no);
	}
	
print		{
		printf("Line %d: PRINT\n", line_no);
	}

[0-9]+		{
		printf("Line %d: INTEGER %s\n", line_no, yytext);
	}
	
[0-9]+\.[0-9]+	{
		printf("Line %d: REAL %s\n", line_no, yytext);
	}

[a-z]+ 	{
		if(yyleng > 3){
			printf("Line %d: BAD %s \n", line_no, yytext);
		}else{
			printf("Line %d: IDENTIFIER %s \n", line_no, yytext);
		}
	}
	
[a-zA-Z]{2,}	{
		printf("Line %d: BAD %s \n", line_no, yytext);
	}
	
[A-Z]+ 	{
		printf("Line %d: BAD %s \n", line_no, yytext);
	}
	
"("		{
		printf("Line %d: LPAREN\n", line_no);
	}

")"		{
		printf("Line %d: RPAREN\n", line_no);
	}

"."		{
		printf("Line %d: PERIOD\n", line_no);
	}
	
"+"		{
		printf("Line %d: PLUS\n", line_no);
	}
"-"		{
		printf("Line %d: MINUS\n", line_no);
	}
"/"		{
		printf("Line %d: DIVIDE\n", line_no);
	}
"*"		{
		printf("Line %d: MULTIPLY\n", line_no);
	}
\\		{
		printf("Line %d: RDIVIDE\n", line_no);
	}
"%"		{
		printf("Line %d: MOD\n", line_no);
	}

","		{
		printf("Line %d: COMMA\n", line_no);
	}
["]([^"\\\n]|\\(.|\n))*["]	{
		printf("Line %d: STRING %s\n", line_no, yytext);
	}
	
[']([^'\\\n]|\\(.|\n))*[']	{
		printf("Line %d: STRING %s\n", line_no, yytext);
	}

"{"[^}\r\n]*"}"? {
			printf("Line %d: COMMMENT %s\n", line_no, yytext);
	}	
.		{
		printf("Line %d: BAD %s\n", line_no, yytext);
	}

%%

int main(int argc, char *argv[]){
	yyin = fopen(argv[1], "r");
	yylex();
	fclose(yyin);
}