#include<stdio.h>
struct Estab{
 char progName[7];
 char symbol[7];
 char startAddr[7];
 char length[7];
};
int n=0;
struct Estab estab[100];
int searchProgEstab(char *prog)
{
    for(int i=0;i<n;i++)
    {
        if(strcmp(estab[i].progName,prog)==0)
            return 1;
    }
    return 0;
}
int searchSymEstab(char *sym)
{
    for(int i=0;i<n;i++)
    {
        if(strcmp(estab[i].symbol,sym)==0)
            return 1;
    }
    return 0;
}
void display()
{
    printf("PName    \tSymbol    \tAddress    \tLength\n");
    printf("------------------------------------------------------\n");
    for(int i=0;i<n;i++)
    {
        printf("%s  \t%s  \t%s  \t%s\n\n",estab[i].progName,estab[i].symbol,estab[i].startAddr,estab[i].length);
    }

}
void insertEstab(struct Estab a)
{
    strcpy(estab[n].progName,a.progName);
    strcpy(estab[n].symbol,a.symbol);
    strcpy(estab[n].startAddr,a.startAddr);
    strcpy(estab[n].length,a.length);
    n++;
}
int main()
{
    FILE *f1=fopen("op.txt","r");
    char line[100];
    printf("Provide OS address\n");
    unsigned int progAddr,csAddr;
    scanf("%x",&progAddr);
    csAddr=progAddr;

    while(fgets(line,sizeof(line),f1)!=NULL)
    {
        if(line[0]=='H')
        {
            char progN[7];
            strncpy(progN,line+2,6);
            progN[6]='\0';
            char progL[7],startA[7];
            strncpy(progL,line+16,6);
            strncpy(startA,line+9,6);
            startA[6]='\0';
            progL[6]='\0';
            unsigned int csa=strtoul(progL,NULL,16);
            unsigned int sta=strtoul(startA,NULL,16);
            int search=searchProgEstab(progN);
            if(search==1)
                printf("Found\n");
            else
            {

                struct Estab a;
                strcpy(a.progName,progN);
                strcpy(a.length,progL);
                sta=sta+progAddr;
                char len[7];
                sprintf(len,"%06X",sta);
                strcpy(a.startAddr,len);
                strcpy(a.symbol,"      ");
                insertEstab(a);
            }
            while(line[0]!='E')
            {
                fgets(line,sizeof(line),f1);
                if(line[0]=='D')
                {
                    int len=strlen(line);
                    for(int c=2;c<len-1;c=c+14)
                    {
                        char dname[7],num[7],num2[7];
                        strncpy(dname,line+c,6);
                        strncpy(num,line+c+7,6);
                        dname[6]='\0';
                        num[6]='\0';
                        unsigned int num1=strtoul(num,NULL,16);
                        num1=num1+progAddr;
                        sprintf(num2,"%06X",num1);
                        int searchSym=searchSymEstab(dname);
                        if(searchSym==1)
                            printf("Found!!Duplicate symbol\n");
                        else
                        {
                          struct Estab a;
                          strcpy(a.progName,"      ");
                          strcpy(a.length,"      ");
                          strcpy(a.startAddr,num2);
                          strcpy(a.symbol,dname);
                          insertEstab(a);
                        }
                    }
                }
            }
            unsigned int l=strtoul(progL,NULL,16);
            progAddr=progAddr+l;
        }
    }

    display();
    return 0;
}