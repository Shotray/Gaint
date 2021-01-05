#include <iostream>
#include <vector>
using namespace std;

void floyd(vector<vector<int>>& dis){
    int n=dis.size();
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(dis[i][j]>dis[i][k]+dis[k][j])
                    dis[i][j]=dis[i][k]+dis[k][j];
}

int main(void) {
    for(int i=0;i<n;i++){
        for(int j=0;i<n;j++){
            if(dis[i][j]>dis[i][0]+dis[0][j])
                dis[i][j]=dis[i][0]+dis[0][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(dis[i][j]>dis[i][1]+dis[1][j])
                dis[i][j]=dis[i][1]+dis[1][j];
        }
    }
}