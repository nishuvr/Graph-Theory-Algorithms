#include<stdio.h>
void dfs(int n,int graph[n][n],int visited[n],int start,int count)
{
	visited[start]=count;
	count++;
	for(int i=0;i<n;i++)
	{
		if(graph[start][i]==1 && !visited[i])
		{
			dfs(n,graph,visited,i,count);
		}
	}
}

void tarjan(int n, int graph[n][n])
{
	int neighbours[n];
	int low_link[n];
	for(int i=0;i<n;i++)
	{
		neighbours[i]=0;
		low_link[i]=0;
	}
	dfs(n,graph,neighbours,0,1);
	int visit[n];
	int vertices[n];
	for (int i=0;i<n;i++)
	{
		vertices[0]=i;
		int temp=1;
		int min=neighbours[i];
		for (int j=0;j<n;j++)
			visit[j]=-1;
		visit[i]=1;
		while(temp)
		{
			temp--;
			int temp2=vertices[temp];
			if(neighbours[temp2]<min)
				min=neighbours[temp2];
			for(int m=0;m<n;m++)
			{
				if(graph[temp2][m]==1 && visit[m]==-1)
				{
					vertices[temp]=m;
					temp++;
					visit[m]=1;
				}
			}
		}
		low_link[i]=min;
	}
	for (int j=0;j<n;j++)
		visit[j]=-1;
	for (int i=0;i<n;i++)
	{
		if(visit[i]== -1)
		{
			for(int j=0;j<n;j++)
		   {
                if(low_link[i]==low_link[j] && visit[j]==-1)
                {
                    visit[j]=1;
                    printf("%d ",j);
                }
           }
		 printf("\n");
		}
	}
}
int main()
{
    int num;
    scanf("%d",&num);
    int n=0;
    while(n<num)
    {
        int nodes;
        scanf("%d",&nodes);
        int graph[nodes][nodes];
        for(int j=0;j<nodes;j++)
        {
            for(int k=0;k<nodes;k++)
                scanf("%d",&graph[j][k]);
        }
        printf("****** Graph %d ******\n",c);
        printf("Strongly connected components :\n");
        tarjan(nodes,graph);
        printf("\n");
        n++;

    }
}
