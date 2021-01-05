#include<iostream>
void dijkstra(int u)//主函数，参数是源点编号
{
    memset(dis,88,sizeof(dis));//把dis数组附最大值（88不是十进制的88，其实很大）
    int start=u;//先从源点搜索
    book[start]=1;//标记源点已经搜索过
    for(int i=1;i<=n;i++)
    {
        dis[i]=min(dis[i],map[start][i]);//先更新一遍
    }
    for(int i=1;i<=n-1;i++)
    {
        int minn=9999999;//谢评论区，改正一下：这里的minn不是题解上的minn，这代表的是最近点到源点的距离，start才代表最近的点、
        for(int j=1;j<=n;j++)
            if(book[j]==0 && minn>dis[j])
            {
                minn=dis[j];
                start=j;//找到离源点最近的点，然后把编号记录下来，用于搜索。
            }
        book[start]=1;        
        for(int j=1;j<=n;j++)
            dis[j]=min(dis[j],dis[start]+map[start][j]);//以新的点来更新dis。
    }
}

const int max_size=88;

void dijkstra(int u)
{
    memset(dis,max_size,sizeof(dis));
    int start=u;
    book[start]=1;
    for(int i=1;i<=n;i++)
    {
        dis[i]=min(dis[i],map[start][i]);
    }
    for(int i=1;i<=n-1;i++)
    {
        int minn=INT_MAX;
        for(int j=1;j<=n;j++)
            if(book[j]==0 && minn>dis[j])
            {
                minn=dis[j];
                start=j;。
            }
        book[start]=1;        
        for(int j=1;j<=n;j++)
            dis[j]=min(dis[j],dis[start]+map[start][j]);
    }
}

H = new heap();
H.insert(S, 0);
dis[S] = 0;
for (i = 1; i <= n; i++) {
  u = H.delete_min();
  for each edge(u, v) {
    if (relax(u, v)) {
      H.decrease_key(v, dis[v]);
    }
  }
}