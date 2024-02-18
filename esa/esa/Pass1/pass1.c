#include<stdio.h>
struct Token
{
    char label[10];
    char opcode[10];
    char operand[10];
}token[100];
struct symTab
{
    char symbol[10];
    char value[10];
}symtab[100];
int syc=0;
int searchSymbol(char *ssym)
{
    for(int j=0;j<syc;j++)
    {
        if(strcmp(symtab[j].symbol,ssym)==0)
            return 1;
    }
    return 0;
}
void insertSymbol(struct symTab a)
{
    strcpy(symtab[syc].symbol,a.symbol);
    strcpy(symtab[syc].value,a.value);
    syc++;
}
char * searchOpcode(FILE *f4, char *opc) {
    static char nm[10];
    char line1[15];
    while (fgets(line1, sizeof(line1), f4) != NULL) {
        char op[5], nm_temp[5];
        int y = sscanf(line1, "%s %s", op, nm_temp);
        if (strcmp(op, opc) == 0) {
            strcpy(nm, nm_temp);
            return nm;
        }
    }
    return NULL;
}
void putFile(FILE *f3)
{
    for(int j=0;j<syc;j++)
    {
        printf("%s\t %s\n",symtab[j].symbol,symtab[j].value);
        fprintf(f3,"%s\t %s\n",symtab[j].symbol,symtab[j].value);
    }
}
int main()
{
    FILE *f1,*f2,*f3,*f4;
    f1=fopen("input.txt","r");
    f3=fopen("symtabNew.txt","w");
    f4=fopen("optab.txt","r");
    f2=fopen("intermediate.txt","w");
    char line[100];
    fgets(line,sizeof(line),f1);
    int i=0;
    printf("Intermediate file\n");
    printf("-----------------------------------------------\n");
    unsigned int locctr;
    int x=sscanf(line,"%s %s %s",token[i].label,token[i].opcode,token[i].operand);
    if(strcmp(token[i].opcode,"START")==0)
    {
        unsigned int y=strtoul(token[i].operand,NULL,16);
        locctr=y;
        fprintf(f2,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
    }
    else
       locctr=0000;
    while(strcmp(token[i].opcode,"END")!=0&&strcmp(token[i].label,"END")!=0)
    {

      if(x==3)
      {
          int search=searchSymbol(token[i].label);
          if(search==1)
           {
                printf("Duplicate symbol\n");
               goto input;
           }
          else
          {
              char s[5];
              sprintf(s,"%04x",locctr);
              struct symTab a;
              strcpy(a.symbol,token[i].label);
              strcpy(a.value,s);
              insertSymbol(a);
          }
      }
      if(x==2)
      {
        strcpy(token[i].operand,token[i].opcode);
        strcpy(token[i].opcode,token[i].label);
        strcpy(token[i].label,"     ");
      }
      if(x==1)
      {
        strcpy(token[i].opcode,token[i].label);
        strcpy(token[i].label,"     ");
        strcpy(token[i].operand,"     ");
      }
       char * m=searchOpcode(f4,token[i].opcode);
       rewind(f4);
       if(m!=NULL)
       {
           fprintf(f2,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
           printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
           locctr+=3;
       }
       else if(strcmp(token[i].opcode,"RESW")==0)
       {
           unsigned int y=strtoul(token[i].operand,NULL,10);
           fprintf(f2,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
           printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
           locctr+=3*y;
       }
        else if(strcmp(token[i].opcode,"RESB")==0)
       {
           unsigned int y=strtoul(token[i].operand,NULL,10);
           fprintf(f2,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
           printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
           locctr+=y;
       }
        else if(strcmp(token[i].opcode,"BYTE")==0)
       {
           int len=strlen(token[i].operand);
           fprintf(f2,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
           printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
           len-=3;
           if(token[i].operand[0]=='X')
           {
               if(len%2!=0)
                {printf("----------------->Error! X can't be odd \n");goto input;}
               len=len/2;
           }
           locctr+=len;
       }
        else if(strcmp(token[i].opcode,"WORD")==0)
          {
           fprintf(f2,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
           printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
          locctr+=3;
          }
        else{
            if(strcmp(token[i].opcode,"START")!=0)
            {
                printf("Invalid Opcode !! Error\n");
                goto input;
            }
        }
      input:
      i++;
      fgets(line,sizeof(line),f1);
      x=sscanf(line,"%s %s %s",token[i].label,token[i].opcode,token[i].operand);
    }
     fprintf(f2,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
     printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
     printf("\n\nSymbol Table\n");
     printf("-----------------------------------------------\n");
     putFile(f3);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    return 0;
}