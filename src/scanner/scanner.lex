
%{
#include <stdio>
#include <parse.hh>

/* For logging */
#define RETURN(x) return(x);

%}

/************************************************************************/
/* Regular Definitions													*/
/************************************************************************/
DELIM	[ \t\n]
WS		{DELIM}+




/************************************************************************/
/* Rules																*/
/************************************************************************/
%%

{WS}		{ /* no action and no return */ }

auto		{ RETURN(AUTO_TK); }
break		{ RETURN(BREAK_TK); }
case		{ RETURN(CASE_TK); }
char		{ RETURN(CHAR_TK); }
const		{ RETURN(CONST_TK); }
continue	{ RETURN(CONTINUE_TK); }
default		{ RETURN(DEFAULT_TK); }
do			{ RETURN(DO_TK); }
double		{ RETURN(DOUBLE_TK); }
else		{ RETURN(ELSE_TK); }
enum		{ RETURN(ENUM_TK); }
extern		{ RETURN(EXTERN_TK); }
float		{ RETURN(FLOAT_TK); }
for			{ RETURN(FOR_TK); }
goto		{ RETURN(GOTO_TK); }
if			{ RETURN(IF_TK); }
int			{ RETURN(INT_TK); }
long		{ RETURN(LONG_TK); }
register	{ RETURN(REGISTER_TK); }
return		{ RETURN(RETURN_TK); }
short		{ RETURN(SHORT_TK); }
signed		{ RETURN(SIGNED_TK); }
sizeof		{ RETURN(SIZEOF_TK); }
static		{ RETURN(STATIC_TK); }
struct		{ RETURN(STRUCT_TK); }
switch		{ RETURN(SWITCH_TK); }
typedef		{ RETURN(TYPEDEF_TK); }
union		{ RETURN(UNION_TK); }
unsigned	{ RETURN(UNSIGNED_TK); }
void		{ RETURN(VOID_TK); }
volatile	{ RETURN(VOLATILE_TK); }
while		{ RETURN(WHILE_TK); }

%%

/************************************************************************/
/* User Code															*/
/************************************************************************/
scanner() {

	yyparse();
	
}
