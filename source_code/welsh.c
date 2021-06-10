#include<stdio.h>
#include<stdlib.h>
int welshpowell(int n,int graph[n][n])
{
	int arr[n][2];
	for(int i=0;i<n;i++)
		arr[i][1]=0;
	for (int i=0;i<n;i++)
	{
		arr[i][0]=i;
		for (int j=0;j<n;j++)
		{
			if(graph[i][j]==1)
				arr[i][1]++;
		}
	}
	int ele;
	int var1;
	int var2;
	//sort
	for (int i=0;i<n;i++)
	{
		ele=i;
		for(int j=i+1;j<n;j++)
		{
			if(arr[ele][1]<arr[j][1])
				ele=j;
		}
		if(ele!=i)
		{
			var1=arr[i][0];
			var2=arr[i][1];
			arr[i][0]=arr[ele][0];
			arr[i][1]=arr[ele][1];
			arr[ele][0]=var1;
			arr[ele][1]=var2;
		}
	}
	for(int i=0;i<n;i++)
	{
		printf("Vertex : %d",arr[i][0]);
		printf(" Degree : %d \n",arr[i][1]);
	}
	printf("\n");
	int count=0;
	for (int i=0;i<n;i++)
	{
		if(arr[i][0]!=-1)
		{
			count++;
			for(int j=0;j<n;j++)
			{
				if(graph[arr[i][0]][j]<1)
					arr[j][0]=-1;
			}
		}
	}
	return count;
}

int main()
{
    int num;
    scanf("%d",&num);
    int n=1;
    while(n<=num){
        int nodes;
        scanf("%d",&nodes);
        int graph[nodes][nodes];
        for(int j=0;j<nodes;j++)
        {
            for(int k=0;k<nodes;k++)
                scanf("%d",&graph[j][k]);
        }
        printf("Chromatic number of graph %d : %d \n \n",n,welshpowell(nodes,graph));
        n++;

    }
}
