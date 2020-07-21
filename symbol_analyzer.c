#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 100

typedef enum{ START, IDENTIFIER, NUMBER,
BUILDING_IDENTIFIER, BUILDING_NUMBER
} state;  

state transition(state a,char b);
int find_key(char *item);

int main(int argc, char* argv[]){
  char input_filename[SIZE], output_filename[SIZE];
  FILE *input_file1, *output_file1;
  char ch;
  int num_identifier=0;
  int num_number=0;
  int num_keyword=0;

  switch(argc){
    case 1:
      printf("Error,not enough arguments");
      exit(1);
      break;
    case 2:
      input_file1= fopen(argv[1], "r");
      if (input_file1 == NULL){
        printf("Cannot open %s for reading.", argv[1]);
        exit(1);
      }  
      break;
  
    default:
      printf("Error, too much arguments");
      exit(1);
      break;
  }//end of switch

  //Transition
  state current_state = START;
  char current_char = getc(input_file1);
  char item[30];
  int index=0;
  while(current_char != EOF){
  current_state = transition(current_state, current_char);
  
  if(!isspace(current_char)){
    item[index++]=current_char;
  }
  if(current_state == IDENTIFIER){  
    item[index]='\0';
    if(find_key(item)==1){
      num_keyword++;
      printf("%s: KeyWord\n",item);
    }else{
       num_identifier++;
      printf("%s:Identifier\n",item);
    }
    current_state = START;// move to new data item
    index=0;
  }
  
  if (current_state == NUMBER){
    num_number++;
    item[index]='\0';
    printf("%s: Number\n",item);
    current_state = START;
    index=0;
  }
  current_char = getc(input_file1);//read the next character from the input file
  }//end of while loop
  printf("Number of identifiers: %d\n",num_identifier);
  printf("Number of keyword: %d\n",num_keyword);
  printf("Number of numbers: %d\n",num_number);
}//end of main

state transition(state a,char b){
  state next_state;
  if(a==START&&isspace(b)){//START
    next_state=START;
  }else if(a==START&&isalpha(b)){
    next_state=BUILDING_IDENTIFIER;
  }else if(a==START&&isdigit(b)){
    next_state=BUILDING_NUMBER;
  }else if(a==BUILDING_IDENTIFIER&&isspace(b)){//Building Identifier
    next_state=IDENTIFIER;
  }else if(a==BUILDING_IDENTIFIER&&isalpha(b)){
    next_state=BUILDING_IDENTIFIER;
  }else if(a==BUILDING_IDENTIFIER&&isdigit(b)){
    next_state=BUILDING_IDENTIFIER;
  }else if(a==BUILDING_IDENTIFIER&&b=='_'){
    next_state=BUILDING_IDENTIFIER;
  }else if(a==BUILDING_NUMBER&&isspace(b)){//BUILDING_NUMBER
    next_state=NUMBER;
  }else if(a==BUILDING_NUMBER&&isdigit(b)){//BUILDING_NUMBER
    next_state=BUILDING_NUMBER;
  }else if(a==NUMBER||a==IDENTIFIER){
    next_state=START;
  }else{
    printf("Invalid response.");
    exit(1);
  }
  return next_state;
}//end of function

int find_key(char *item){
  char charr[32][10]={
    "auto", "break","case", "char", "const", "continue",
    "default", "do","double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
  };
  int a=0;
  for(int i=0;i<32;i++){
    if(strcmp(charr[i],item)==0){
      return 1;
    }
  }
  return -1;
}
