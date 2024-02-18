#include<stdio.h>
struct Token{
  char address[10];
  char label[10];
  char opcode[10];
  char operand[10];
}token[100];
char * searchOpcode(FILE *f4,char *search)
{
    static char nm[5];
    char mm[5],opc[5];
    char line1[15];
  while(fgets(line1,sizeof(line1),f4)!=NULL)
  {
     int y=sscanf(line1,"%s %s",opc,mm);
     if(strcmp(opc,search)==0)
     {
         strcpy(nm,mm);
         return nm;
     }
  }
  return NULL;
}
char * searchSymbol(FILE *f5,char *search)
{

    static char nm[10];
    char mm[10],opc[10];
    char line1[25];
  while(fgets(line1,sizeof(line1),f5)!=NULL)
    {
     int y=sscanf(line1,"%s %s",opc,mm);
     if(strcmp(opc,search)==0)
     {
         strcpy(nm,mm);
         return nm;
     }
}

  return NULL;
}
int main()
{
    FILE *f1,*f2;
    FILE *f5=fopen("symtabNew.txt","r");
    FILE *f4=fopen("optab.txt","r");
    f2=fopen("Length.txt","r");
    FILE *f3=fopen("ObjectNew2.txt","w");
    char lenn[7];
    fgets(lenn,sizeof(lenn),f2);
    f1=fopen("intermediate.txt","r");
    FILE *f11=fopen("intermediate.txt","r");
    char line2[100];
    fgets(line2,sizeof(line2),f11);
    fgets(line2,sizeof(line2),f11);
    unsigned int loc=0;
    char line[100];
    fgets(line,sizeof(line),f1);
    int x,i=0;
    x=sscanf(line,"%s %s %s %s",token[i].address,token[i].label,token[i].opcode,token[i].operand);
    char stAd[7];
    strcpy(stAd,token[i].operand);
    printf("%s %s %s %s\n",token[i].address,token[i].label,token[i].opcode,token[i].operand);
    char header[25];
    char text[100];
    if(strcmp(token[i].opcode,"START")==0)
    {
        sprintf(header,"H^%06s^%06s^%06s\n",token[i].label,token[i].address,lenn);
        fprintf(f3,"%s",header);
    }
    else
       {
           fprintf(f3,"%s",header);
           sprintf(header,"H^%06s^%06s^%06s^\n","","000000",lenn);
       }
               printf("%s\n",header);

       sprintf(text,"T^%06s^",token[i].address);
 char opcode1[80];
                          strcpy(opcode1,"");
       while(strcmp(token[i].opcode,"END")!=0&&strcmp(token[i].label,"END")!=0)
       {

           if(x==3)
           {
               strcpy(token[i].operand,token[i].opcode);
               strcpy(token[i].opcode,token[i].label);
               strcpy(token[i].label,"");
           }
           if(x==2)
           {
               strcpy(token[i].opcode,token[i].label);
               strcpy(token[i].label,"");
               strcpy(token[i].operand,"");
           }
           int yes=0;
           char *op=searchOpcode(f4,token[i].opcode);
           rewind(f4);
           if(op!=NULL)
           {
               char op1[8];

               if(strcmp(token[i].operand,"")!=0)

               {
                   strcat(opcode1,"^");
                   strcat(opcode1,op);
                  int l=strlen(token[i].operand);
                  for(int k=0;k<l;k++)
                  {

                      if(token[i].operand[k]!=',')
                      {
                         op1[k]= token[i].operand[k];
                      }
                      else
                      {
                          op1[k]='\0';
                          yes=1;
                          break;
                      }
                  }
                  char *sym;
                  if(yes==1)
                   {
                       sym=searchSymbol(f5,op1);
                       if(sym[0]=='0')
                        sym[0]='8';
                       else if(sym[0]=='1')
                        sym[0]='9';
                        else if(sym[0]=='2')
                        sym[0]='a';
                        else if(sym[0]=='3')
                        sym[0]='b';
                        else if(sym[0]=='4')
                        sym[0]='c';
                        else if(sym[0]=='5')
                        sym[0]='d';
                        else if(sym[0]=='6')
                        sym[0]='e';
                        else if(sym[0]=='7')
                        sym[0]='f';


                   }
                 else
                   sym=searchSymbol(f5,token[i].operand);
                  if(sym!=NULL)
                  {

                      strcat(opcode1,sym);
                  }
                  else
                  {
                      strcat(opcode1,"0000");
                      printf("Error! symbol not found\n");
                  }
                  rewind(f5);
               }
               else
               {
                   strcat(opcode1,"^");strcat(opcode1,op);
                   strcat(opcode1,"0000");
               }
               loc+=3;
           }
           if(strcmp(token[i].opcode,"BYTE")==0)
           {
               int l=strlen(token[i].operand);
               char n[l-2];
               strncpy(n,token[i].operand+2,l-3);
               n[l-3]='\0';
               if(token[i].operand[0]=='C')
               {  int k=0;
                   strcat(opcode1,"^");
                   while(k<l-3)
                   {
                            int m=(int)n[k];
                           unsigned int u=(unsigned int)m;
                           char z[3];
                           sprintf(z,"%02x",u);
                           strcat(opcode1,z);
                           k++;
                   }
                   unsigned int v=(unsigned int)l-3;
                   loc=loc+v;
               }
                if(token[i].operand[0]=='X')

               {
                   strcat(opcode1,"^");
                   strcat(opcode1,n);
                   unsigned int v =(unsigned int)l-3;
                   loc=loc+v/2;
               }
           }
           if(strcmp(token[i].opcode,"WORD")==0)
           {
               unsigned int u=strtoul(token[i].operand,NULL,0);
               char f[10];
               sprintf(f,"%06x",u);
               strcat(opcode1,"^");
               strcat(opcode1,f);
               loc=loc+3;
           }
           if(strcmp(token[i].opcode,"RESB")==0||strcmp(token[i].opcode,"RESW")==0)
           {
               char za[7],zz[7],zaa[7];
                   sscanf(line2,"%06s %06s %06s",zz,zaa,za);

              if(strcmp(za,"RESB")!=0&&strcmp(za,"RESW")!=0)
               {
                   char loc1[3];
                   sprintf(loc1,"%02x",loc);
                   strcat(text,loc1);
                  strcat(text,opcode1);
                  loc=0;
                   }
               int lp=strlen(text);
               if(lp>10)
               {
                   if(strcmp(za,"RESW")!=0&&strcmp(za,"RESB")!=0)
               {printf("%s\n",text);
               strcpy(text,"");
               strcpy(opcode1,"");
 char zz[7];
              sscanf(line2,"%06s ",zz);
               sprintf(text,"T^%06s^",zz);
               }}
           }
           int length=strlen(opcode1);

           if(loc>=0x1e||loc>=0x1d||loc>=0x1c)
           {
               char loc1[3];

                   sprintf(loc1,"%02x",loc);
                   loc=0;
                   strcat(text,loc1);
               strcat(text,opcode1);
               int lp=strlen(text);
               if(lp>10)
               {
               char za[7],zz[7],zaa[7];
                   sscanf(line2,"%06s %06s %06s",zz,zaa,za);
                   if(strcmp(za,"RESW")!=0&&strcmp(za,"RESB")!=0)
               {printf("%s\n",text);
               strcpy(text,"");
               strcpy(opcode1,"");
             char zz[7];
              sscanf(line2,"%06s ",zz);
               sprintf(text,"T^%06s^",zz);
               }
               }
           }
               fgets(line2,sizeof(line2),f11);
           fgets(line,sizeof(line),f1);
           x=sscanf(line,"%s %s %s %s",token[i].address,token[i].label,token[i].opcode,token[i].operand);
       }
        char loc1[3];

                   sprintf(loc1,"%02x",loc);
                                      loc=0;
                   strcat(text,loc1);
               strcat(text,opcode1);

       strcat(text,opcode1);
 printf("%s\n",text);
        printf("E^%06s",stAd);

}