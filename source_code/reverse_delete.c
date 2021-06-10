#include<stdio.h>
#include<stdlib.h>

typedef struct Edge
{
int vertex1;
int vertex2;
int weight;
}Edge;

void dfs(int n,int graph[n][n],int visited[n],int start)
{
	visited[start]=1;
	for(int i=0;i<n;i++)
	{
		if(graph[start][i]>0 && !visited[i])
		{
			dfs(n,graph,visited,i);
		}
	}
}

int is_connected(int n,int graph[n][n])
{
	int visited[n];
	for(int i=0;i<n;i++)
		visited[i] = 0;
	dfs(n,graph,visited,0);
	for(int i=0;i<n;i++)
	{
		if(visited[i] == 0)
			return 0;
	}
	return 1;
}

void reverse_delete(int n, int graph[n][n])
{
	int temp[n][n];
	int x=0;
	for(int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			temp[i][j]=0;
			if(graph[i][j]>0)
				x++;
		}
	}

	x=x/2;
	Edge edge[x];
	int y=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(graph[i][j]>0 && temp[i][j]==0)
			{
				edge[y].vertex1=i;
				edge[y].vertex2=j;
				edge[y].weight=graph[i][j];
				y++;
				temp[i][j]=1;
				temp[j][i]=1;
			}
		}
	}

	int pos;
	Edge temp1;
	for (int i=0;i<x-1;i++)
	{
		pos=i;
		for(int j=i+1;j<x;j++)
		{
			if(edge[j].weight>edge[pos].weight)
				pos=j;
		}
		if(pos!=i)
		{
			temp1=edge[i];
			edge[i]=edge[pos];
			edge[pos]=temp1;
		}
	}
	for (int i=0;i<x;i++)
	{
		graph[edge[i].vertex1][edge[i].vertex2]=0;
		graph[edge[i].vertex2][edge[i].vertex1]=0;
		if(is_connected(n,graph)==0)
		{
			graph[edge[i].vertex1][edge[i].vertex2]=edge[i].weight;
			graph[edge[i].vertex2][edge[i].vertex1]=edge[i].weight;
		}
		else
			edge[i].weight=-1;
	}
	int total=0;
	for(int i=0;i<x;i++)
	{
		if(edge[i].weight!=-1)
		{
			total=total+edge[i].weight;
			printf("%d , %d \n",edge[i].vertex1,edge[i].vertex2);
		}
	}
	printf("Total weight of the Minimum Spanning Tree :%d\n\n",total);

}

int main()
{
	int num;
	scanf("%d",&num);
	int n=1;
	while(n<=num)
	{
      int nodes;
      scanf("%d",&nodes);
      int graph[nodes][nodes];
      for(int i=0;i<nodes;i++)
      {
        for(int j=0;j<nodes;j++)
            scanf("%d",&graph[i][j]);
      }
      printf("******* Graph %d *******\n",n);
      reverse_delete(nodes,graph);
      n++;
    }

}
