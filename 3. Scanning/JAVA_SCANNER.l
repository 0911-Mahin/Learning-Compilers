%{
#include "token.h"
%}
%%
(" "|\t|\r|\n)
"//".*
"/*"([^*]|\*+[^*/])*\*+"/"
"{"                      {return TOKEN_LBRACE;}
"}"                      {return TOKEN_RBRACE;}
"("                      {return TOKEN_LPARENTHESES;}
")"                      {return TOKEN_RPARENTHESES;}
"["                      {return TOKEN_LBRACKET;}
"]"                      {return TOKEN_RBRACKET;}
public                   {return TOKEN_PUBLIC;}
class                    {return TOKEN_CLASS;}
private                  {return TOKEN_PRIVATE;}
protected                {return TOKEN_PROTECTED;}
static                   {return TOKEN_STATIC;}
final                    {return TOKEN_FINAL;}
void                     {return TOKEN_VOID;}
if                       {return TOKEN_IF;}
else                     {return TOKEN_ELSE;}
for                      {return TOKEN_FOR;}
while                    {return TOKEN_WHILE;}
return                   {return TOKEN_RETURN;}
new                      {return TOKEN_NEW;}
false                    {return TOKEN_FALSE;}
true                     {return TOKEN_TRUE;}
null                     {return TOKEN_NULL;}
[a-zA-Z$_][a-zA-Z0-9$_]* {return TOKEN_IDENTIFIER;}
"+"                      {return TOKEN_PLUS;}
"-"                      {return TOKEN_MINUS;}
"*"                      {return TOKEN_MULTIPLY;}
"/"                      {return TOKEN_DIVIDE;}
"%"                      {return TOKEN_MODULUS;}
"="                      {return TOKEN_ASSIGNMENT;}
"=="                     {return TOKEN_EQUALS;}
"!="                     {return TOKEN_NEQUALS;}
"<"                      {return TOKEN_LESSTHAN;}
">"                      {return TOKEN_GREATERTHAN;}
"<="                     {return TOKEN_LESSTHANOREQUALS;}
">="                     {return TOKEN_GREATERTHANOREQUALS;}
"&&"                     {return TOKEN_AND;}
"||"                     {return TOKEN_OR;}
"++"                     {return TOKEN_INCREMENT;}
"--"                     {return TOKEN_DECREMENT;}
[0-9]+                   {return TOKEN_INTEGER;}
[0-9]+\.[0-9]+           {return TOKEN_FLOAT;}
\'([^\'\\\n]|\\.)\'      {return TOKEN_CHAR;}
\"([^\"\\]|\\.)*\"       {return TOKEN_STRING;}
";"                      {return TOKEN_SEMICOLON;}
","                      {return TOKEN_COMMA;}
"."                      {return TOKEN_DOT;}
.                        {return TOKEN_ERROR;}
%%
int yywrap() { return 1; }
