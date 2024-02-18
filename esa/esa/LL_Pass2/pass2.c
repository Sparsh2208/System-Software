#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct ESTAB
{
    char pname[10];
    char symbol[100];
    char address[100];
    char length[100];
}estab[100];
unsigned int searchESTAB(char * search,FILE * f2)
{
    char line1[100];
    char key[10];
    char value[10];
    rewind(f2);
    while(fgets(line1,sizeof(line1),f2)!=NULL)
    {
        sscanf(line1,"%s %s",key,value);
        if(!strncmp(search,key,strlen(key)))
        {
            unsigned int ret= strtoul(value,NULL,16);
            return ret;
        }
    }
    return -1;
}
void memory(unsigned int stA,unsigned int csaddr,FILE *f3, char * line)
{
    char length[3];
    strncpy(length,line+9,2);
    length[2]='\0';
    char *rec=line+12;
    char rec2[100];
    int j=0;
    for(int i=0;i<strlen(rec);i++)
    {
         if(rec[i]!='^')
         {
        printf("%d\n",strlen(rec2));
         rec2[j]=rec[i];
         j++;
        if(strlen(rec2)==8)
            {
                fprintf(f3,"\t");
                printf("\t");
            }
        if(strlen(rec2)==32)
            {
                fprintf(f3,"%s\n",rec2);
                printf("%s\n",rec2);
                rec2[0]='\0';
            }
         }
        
    }
    fprintf(f3,"%s\n",rec2);
}
int main()
{
    int i=0;
    FILE *f1=fopen("op.txt","r");
    FILE *f2=fopen("estab.txt","r");
    FILE *f3=fopen("output.txt","w");
    char line[100];
    fgets(line,sizeof(line),f2);
    sscanf(line,"%s %s %s",estab[i].pname,estab[i].address,estab[i].length);
    unsigned int progaddr= strtoul(estab[i].address,NULL,16);
    unsigned int csaddr= progaddr;
    unsigned int execaddr= progaddr;
    while(fgets(line,sizeof(line),f1)!=NULL)
    {
        unsigned int cslth=strtoul(estab[i].length,NULL,16);
        while(line[0]!='E')
        {
            fgets(line,sizeof(line),f1);
            if(line[0]=='T')
            {
                char stAd[7];
                strncpy(stAd,line+2,6);
                stAd[6]='\0';
                unsigned int stA=strtoul(stAd,NULL,16);
                stA+=csaddr;
                memory(stA,csaddr,f3,line);
            }
            else if(line[0]=='M')
            {
                char *label=line+14;
                unsigned int val=searchESTAB(label,f2);
                if(val!=-1)
                {
                     
                }
                else
                {
                    printf("No symbol. !ERROR\n");
                }
            }
        }
    }

    return 0;
}