#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100

int main(int argc, char* argv[]){
  char input_filename[SIZE], output_filename[SIZE];
  FILE *input_file1, *output_file1,*input_file2, *output_file2;
  char ch;
  int s=0;
  int i=0;
  int a=3;
  int b=0;
  int p=1;
  switch(argc){
    case 1:
    printf("Not enough Arguments");
    exit(1);//Exit with error
    break;
    //////////////////////////////////////////////////////////
    case 2:
    if(strcmp(argv[1],"--help")==0){
      printf("Usage: diff [OPTION] FILE1 FILE2\n");
      printf("Compare FILE1 and FILE2 line by line and shows the lines that are different in the two files.\n");
      printf("[OPTIONS]\n");
      printf("-s show only the lines that are identical in the two files\n");
      printf("-i ignore case differences in file contents\n");
      printf("--help display this help and exit\n");
      exit(0);//Without error
    }else{
      printf("Error");
      exit(1);
    }  
    break;
    ///////////////////////////////////////////////////////
    case 3:
    input_file1= fopen(argv[1], "r");
    if (input_file1 == NULL){
    printf("Cannot open %s for reading.", argv[1]);
    exit(1);
    }

    input_file2= fopen(argv[2], "r"); 
    if (input_file2 == NULL){
    printf("Cannot open %s for reading.", argv[2]);
    exit(1);
    }
    
    break;
    ////////////////////////////////////////////////////////
    case 4:
    input_file1= fopen(argv[2], "r");
  
    if (input_file1 == NULL){
    printf("Cannot open %s for reading.", argv[2]);
    exit(1);
    }

    input_file2= fopen(argv[3], "r");
  
    if (input_file2 == NULL){
    printf("Cannot open %s for reading.", argv[3]);
    exit(1);
    }

    if(strcmp(argv[1], "-s")==0){
      s=1;
    }else if(strcmp(argv[1], "-i")==0){
      i=1;
    }else{
      printf("Error");
      exit(1);
    }
    break;
    ////////////////////////////////////////////////////////////////////////
    case 5:
    input_file1= fopen(argv[3], "r");
  
    if (input_file1 == NULL){
    printf("Cannot open %s for reading.", argv[3]);
    exit(1);
    }

    input_file2= fopen(argv[4], "r");
  
    if (input_file2 == NULL){
    printf("Cannot open %s for reading.", argv[4]);
    exit(1);
    }

    if(strcmp(argv[1], "-s")==0||strcmp(argv[2], "-s")==0){
      s=1;
    }else if(strcmp(argv[1], "-i")==0||strcmp(argv[2], "-i")==0){
      i=1;
    }else{
      printf("Error");
      exit(1);
    }
    break;
  }//end of switch

  
  ch=getc(input_file1);
  char *line1=malloc(100);
  char *line2=malloc(100);
  size_t n;
  int uno=0;
  int hundred=0;
  float percentage=0;

  while (ch != EOF) {
    ungetc(ch, input_file1);//Checks the first character
    getline(&line1,&n,input_file1);
    getline(&line2,&n,input_file2);
    int sim=strcmp(line1, line2);//Compares both lines
    int insensitivesim=strcasecmp(line1, line2);
    
    
    if(i==1&&s==1&&insensitivesim==0){
      b++;//One more similar line
      printf("Lines %d are identical\n:",p);
      printf("  file1.txt:%s\n",line1);
      printf("  file2.txt: %s\n",line2);
      percentage=(float)b/a*100;
      
      uno++;
    }

    else if(s==1&&i==0&&sim==0){
      b++;//One more similar line
      printf("Lines %d are identical:\n",p);
      printf("  file1.txt:%s\n",line1);
      printf("  file2.txt: %s\n",line2);
      percentage=(float)b/a*100;

      if(percentage!=100){
        hundred=1;
      }
      uno++;
    }

    else if(i==1&&s==0&&insensitivesim!=0){
      b++;//One more different line
      printf("Lines %d are different:\n",p);
      printf("  file1.txt:%s\n",line1);
      printf("  file2.txt: %s\n",line2);
      percentage=(float)b/a*100;
      uno++;
      if(percentage!=100){
        hundred=1;
      }
    }

    else if(i==0&&s==0&&sim!=0){
      b++;//One more different line
      printf("Lines %d are different:\n",p);
      printf("  file1.txt:%s\n",line1);
      printf("  file2.txt: %s\n",line2);
      percentage=(float)b/a*100;
      uno++;
      if(percentage!=100){
        hundred=1;
      }
    }
    ch = getc(input_file1); //Checks if it reached the EOF
    a=3;//One more analyzed line
    ++p;
  } ;//end of while loop
  
  printf("Number of lines: %d\n",a);
  printf("%% Identical lines: %.2f %%\n",percentage);

  if(hundred==0){
    printf("Exit status 0\n");
    exit(0);
  }
  
  if(uno!=0){
    printf("Exit status 1\n");
    exit(1);
  }else{
    printf("Exit status 0\n");
    exit(0);
  }
  
}//end of Main Function
