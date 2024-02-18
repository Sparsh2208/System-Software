#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct ESTAB
{
    char pname[7];
    char symname[7];
    char address[7];
    char length[7];
}estab[100];
int esc=0;
int searchProgEstab(char *progName)
{
    for(int i=0;i<esc;i++)
    {
        if(!strcmp(estab[esc].pname,progName))
        {
            return 1;
        }
    }
    return 0;
}

int searchSymEstab(char *symbol)
{
    for(int i=0;i<esc;i++)
    {
        if(!strcmp(estab[esc].symname,symbol))
        {
            return 1;
        }
    }
    return 0;
}

void insertestab(struct ESTAB a)
{
    strcpy(estab[esc].pname,a.pname);
    strcpy(estab[esc].symname,a.symname);
    strcpy(estab[esc].address,a.address);
    strcpy(estab[esc].length,a.length);
    esc++;
}

void display()
{
    printf("PName    \tSymbol    \tAddress    \tLength\n");
    printf("------------------------------------------------------\n");
    for(int i=0;i<esc;i++)
    {
        printf("%s  \t%s  \t%s  \t%s\n\n",estab[i].pname,estab[i].symname,estab[i].address,estab[i].length);
    }

}

int main()
{
    FILE * f1,*f2;
    f1=fopen("op.txt","r");
    f2=fopen("myestab.txt","w");
    char line[100];
    unsigned int progAddr,csAddr;
    printf("Provide OS address\n");
    scanf("%x",&progAddr);
    csAddr=progAddr;

    while(fgets(line,sizeof(line),f1)!=NULL)
    {
        if(line[0]=='H')
        {
            char progName[7],progLen[7],progAdd[7];
            strncpy(progName,line+2,6);
            strncpy(progLen,line+16,6);
            strncpy(progAdd,line+9,6);
            progName[6]='\0';
            progLen[6]='\0';
            progAdd[6]='\0';
            unsigned int cslen= strtoul(progLen,NULL,16);
            unsigned int staAddr=strtoul(progAdd,NULL,16);
            if(searchProgEstab(progName))
            {
                printf("Duplicate Program name");
            }
            else
            {
                struct ESTAB a;
                strcpy(a.pname,progName);
                strcpy(a.length,progLen);
                strcpy(a.symname,"      ");
                staAddr+=progAddr;
                sprintf(a.address,"%06X",staAddr);
                insertestab(a);
            }
            while(line[0]!='E')
            {
                fgets(line,sizeof(line),f1);
                if(line[0]=='D')
                {
                    int len=strlen(line);
                    for(int c=2;c<len-1;c+=14)
                    {
                        char dname[7],daddr[7],num2[7];
                        strncpy(dname,line+c,6);
                        strncpy(daddr,line+c+7,6);
                        dname[6]='\0';
                        daddr[6]='\0';
                        unsigned int num=strtoul(daddr,NULL,16);
                        num+=progAddr;
                        sprintf(num2,"%06X",num);
                        if(searchSymEstab(dname))
                        {
                            printf("Duplicate symbol\n");
                        }
                        else
                        {
                            struct ESTAB b;
                            strcpy(b.pname,"      ");
                            strcpy(b.length,"     ");
                            strcpy(b.address,num2);
                            strcpy(b.symname,dname);
                            printf("%s\n",b.symname);
                            insertestab(b);
                        }
                        
                    }
                    
                }
            }
            unsigned int l= strtoul(progLen,NULL,16);
            progAddr+=l;
        }
    }
    display();
    return 0;
}