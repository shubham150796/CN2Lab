#include<stdio.h>
#include<stdlib.h>
int n,a[10][10],d[10],p[10];
void bellmann(int s)
{
    int i,u,v;
    for(i=1;i<n;i++)
        for(u=0;u<n;u++)
            for(v=0;v<n;v++)
            if(d[v]>d[u]+a[u][v])
            {
                d[v]=d[u]+a[u][v];
                p[v]=u;
            }
            
        
   

    for(u=0;u<n;u++){
        for(v=0;v<n;v++){
        if(d[v]>d[u]+a[u][v])
            printf("\nnegative edge present");
        }
    }
}

int main()
{
int i,j;
int source;
printf("\nEnter no. of node");
scanf("%d",&n);
printf("\nEnter the adjacency matrix");
for(i=0;i<n;i++)
for(j=0;j<n;j++)
scanf("%d",&a[i][j]);

for(source=0;source<n;source++)
{
    for(i=0;i<n;i++)
    {
    d[i]=999;
    p[i]=-1;
    }
    d[source]=0;
    bellmann(source);
    
    printf("\nRouter %d\n",source);
    for(i=0;i<n;i++)
    {
    if(i!=source)
    {
        j=i;
        while(p[j]!=-1)
    {
        printf("%d<-",j);
        j=p[j];
    }
    }
  printf("%d\t\tcost %d\n",source,d[i]);
}
}
return 0;
}

