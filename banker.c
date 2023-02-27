#include <stdio.h>
#include <stdbool.h>

struct processes
{
    int m[10];
    int allc[10];
    int n[10];
};

int nop,nor;
void input(struct processes p[nop],int avail[nor])
{
    for(int i=0;i<nop;i++)
    {
      printf("Enter p[%d]'s max need\n",i);
      for(int j=0;j<nor;j++)
      {
        scanf("%d",&p[i].m[j]);
      }
      printf("Enter no. of resources allocated for process: ");
      for(int j=0;j<nor;j++)
      {
        scanf("%d",&p[i].allc[j]); 
        p[i].n[j]= p[i].m[j] - p[i].allc[j];
      }
    }
    printf("Enter resources: ");
    for(int i=0;i<nor;i++)
    {
      scanf("%d",&avail[i]);
    }
}
void showTheInfo(struct processes p[nop])
{
    printf("\nPID\tMax\t\tAlloc\tNeed\n");
    for(int i=0;i<nop;i++)
    {
        printf("P[%d]\t",i);
        for(int j=0;j<nor;j++)
           printf("%d ",p[i].m[j]);
        printf("\t\t");
        for(int j=0;j<nor;j++)
           printf("%d ",p[i].allc[j]); 
        printf("\t\t");
        for(int j=0;j<nor;j++)
           printf("%d ",p[i].n[j]);
        printf("\n");

    }
}
bool safety(struct processes p[nop],int avail[nor],int safe[nop])
{
   bool finish[nop];
   int work[nor];  
   for(int i=0;i<nor;i++)
   {
      work[i]=avail[i];      
   }
   for(int i=0;i<nop;i++)
     finish[i]=false;    
   bool result=true;
   int k=0;
   while(result)
   {
     result=false;
     for(int i=0;i<nop;i++)
     {    
         bool flag=true;
         if(finish[i]==false)
         {
           
           for(int j=0;j<nor;j++)
           {
             if(p[i].n[j] <= work[j])
             {
               continue;
             }
             else
             {
               flag=false;
               break;
             }
           }
           if(flag==false)
             continue;
          for(int j=0;j<nor;j++)   
            work[j]=work[j]+ p[i].allc[j];
          finish[i]=true;
          safe[k++]=i;
          result=true;
          
         }
       }

     }

     int i;
     for( i=0;i<nop&&finish[i]==true;i++)
     {
       continue;
     }
     if(i==nop)
      return true;
     else
      return false;
}
bool safestate(struct processes p[nop],int avail[nor],int safe[nop])
{
     
    if(safety(p,avail,safe)==true)
    return true;
    return false;
   
}
int main()
{
    printf("Enter no. of process\n");
    scanf("%d",&nop);
    printf("Enter no. of resources\n");
    scanf("%d",&nor);
    int avail[nor];
    int safe[nop];
    struct processes p[nop];
    input(p,avail); 
    showTheInfo(p);
    if(safestate(p,avail,safe))
    {
        printf("\nSystem in SAFE STATE\n");
        printf("Safe Sequence is: ");
        for(int i=0;i<nop;i++)
            printf("P[%d] ",safe[i]);
        printf("1");
    }
    else
        printf("0");    
    return 0;
}