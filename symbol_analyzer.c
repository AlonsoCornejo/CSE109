//Course:System Software
//Professor: Houria Oudghiri
//July 20,2020
//This program simulates a finite state machine(FSM) enviroment and returns the different states of inputs

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 100

//Declaring the structure
typedef enum{ START, IDENTIFIER, NUMBER,
BUILDING_IDENTIFIER, BUILDING_NUMBER
} state;  

//Declaring function headings
state transition(state a,char b);
int find_key(char *item);

//Main Function
int main(int argc, char* argv[]){
  //Some important variables for the program
  char input_filename[SIZE], output_filename[SIZE];
  FILE *input_file1, *output_file1;
  char ch;
  int num_identifier=0;
  int num_number=0;
  int num_keyword=0;

  //Check the correctness of the command line arguments
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
  //Check every item in file text
  while(current_char != EOF){
  current_state = transition(current_state, current_char);
  
  //Create a string from joined characters
  if(!isspace(current_char)){
    item[index++]=current_char;
  }

  //Check the state to print it
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
    index=0;//Make string blank again
  }
  
  if (current_state == NUMBER){
    num_number++;
    item[index]='\0';
    printf("%s: Number\n",item);
    current_state = START;
    index=0;//Make string blank again
  }
  current_char = getc(input_file1);

  }//end of while loop
  //Print number of each state
  printf("Number of identifiers: %d\n",num_identifier);
  printf("Number of keyword: %d\n",num_keyword);
  printf("Number of numbers: %d\n",num_number);
}//end of main

//Function to check the state the item is present
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

//Function to find if an item is a keyword or Identifier
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
