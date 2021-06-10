#include <stdio.h>
#include <stdlib.h>
int bipartiteMatch(int n, int M, int N,int visited[M],int assign[M],int graph[M][N])
{
   for (int v = 0; v < N; v++)
   {
      if(graph[n][v]==1 && !visited[v])
      {
         visited[v] = 1;
         if(assign[v] < 0 || bipartiteMatch(assign[v],M,N,visited,assign,graph))
         {
            assign[v] = n;
            return 1;
         }
      }
   }
   return 0;
}

int maxMatch(int M,int N,int graph[M][N])
{
   int assign[N];
   for(int i = 0; i<N; i++)
      assign[i] = -1;
   int Count = 0;
   for (int u = 0; u < M; u++)
   {
      int visited[N];
      for(int i = 0; i<N; i++)
          visited[i] = 0;
      if(bipartiteMatch(u,M,N,visited,assign,graph))
          Count++;
   }
   return Count;
}

int main()
{
    int num;
    scanf("%d",&num);
    int c=1;
    while(c<=num){
        int m,n;
        scanf("%d %d",&m,&n);
        int graph[m][n];
        for(int j=0;j<m;j++)
        {
            for(int k=0;k<n;k++)
                scanf("%d",&graph[j][k]);
        }
        printf("Maximum number of applicants matching for job: %d \n" ,maxMatch(m,n,graph));
        c++;

    }
}



