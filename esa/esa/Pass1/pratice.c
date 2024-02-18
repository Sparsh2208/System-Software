#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct SYMTAB
{
    char name[10];
    char value[10];
}symtab[100];
int symc=0;
struct TOKEN
{
    char label[10];
    char opcode[10];
    char operand[10];
}token[100];

int searchSymbol(char *sym)
{
    for(int j=0;j<symc;j++)
    {
        if(strcmp(sym,symtab[j].name)==0)
        {
            return 1;
        }
    }
    return 0;
}

void insertSymbol(struct SYMTAB a)
{
    strcpy(symtab[symc].name,a.name);
    strcpy(symtab[symc].value,a.value);
    symc++;
}

char * searchOpcode(FILE *f2, char *opc) {
    static char nm[10];
    char line1[15];
    while (fgets(line1, sizeof(line1), f2) != NULL) {
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
    for(int j=0;j<symc;j++)
    {
        printf("%s\t %s\n",symtab[j].name,symtab[j].value);
        fprintf(f3,"%s\t %s\n",symtab[j].name,symtab[j].value);
    }
}
int main()
{
    FILE *f1,*f2,*f3,*f4,*f5;
    f1=fopen("input.txt","r");
    f2=fopen("optab.txt","r");
    f3=fopen("symtab.txt","w");
    f4=fopen("intermediate_test.txt","w");
    f5=fopen("intermediate_test2.txt","w");
    char line[100];
    fgets(line,sizeof(line),f1);
    int i=0;
    printf("--------Intermidiate file----------\n");
    unsigned int locctr,startAddr;
    int x=sscanf(line,"%s %s %s",token[i].label,token[i].opcode,token[i].operand);
    if(!strcmp(token[i].opcode,"START"))
    {
        startAddr=strtoul(token[i].operand,NULL,16);
        locctr=startAddr;
        fprintf(f4,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
    }
    else
    {
        startAddr=0000;
        locctr=startAddr;
    }
    while(strcmp(token[i].opcode,"END")!=0&&strcmp(token[i].label,"END")!=0)
    {
        if(x==3)
        {
            if(searchSymbol(token[i].label))
           {
                printf("Duplicate symbol\n");
               goto input;
           }
          else
          {
              char s[5];
              sprintf(s,"%04x",locctr);
              struct SYMTAB a;
              strcpy(a.name,token[i].label);
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
       char * m=searchOpcode(f2,token[i].opcode);
       rewind(f2);
       if(m!=NULL)
      {
        fprintf(f4,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        locctr+=3;
      }
      else if(strcmp(token[i].opcode,"RESW")==0)
      {
        unsigned int y= strtoul(token[i].operand,NULL,10);
        fprintf(f4,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        locctr+=3*y;
      }
      else if(strcmp(token[i].opcode,"RESB")==0)
      {
        unsigned int y= strtoul(token[i].operand,NULL,10);
        fprintf(f4,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        locctr+=y;
      }
      else if(strcmp(token[i].opcode,"WORD")==0)
      {
        fprintf(f4,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        locctr+=3;
      }
      else if(strcmp(token[i].opcode,"BYTE")==0)
      {
        unsigned int len=strlen(token[i].operand);
        len-=3;
        if(token[i].operand[0]=='X')
           {
               if(len%2!=0)
                {
                    printf("----------------->Error! X can't be odd \n");goto input;
                }
                len/=2;
           }
        fprintf(f4,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
        locctr+=len;
      }
      else
      {
        printf("Invalid Opcode\n");
      }
    input:
      i++;
      fgets(line,sizeof(line),f1);
      x=sscanf(line,"%s %s %s",token[i].label,token[i].opcode,token[i].operand);
    }
fprintf(f4,"%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
printf("%04x\t %s\t %s\t %s\n",locctr,token[i].label,token[i].opcode,token[i].operand);
printf("--------------------\n Program length=%04X\n",locctr-startAddr);
printf("---------------------\nSymbol Table\n");
putFile(f3);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    return 0;
}