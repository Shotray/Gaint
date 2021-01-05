q = new queue();
q.push(S);
in_queue[S] = true;
while (!q.empty()) {
  u = q.pop();
  in_queue[u] = false;
  for each edge(u, v) {
    if (relax(u, v) && !in_queue[v]) {
      q.push(v);
      in_queue[v] = true;
    }
  }
}

while(!Q.empty()){
    t=Q.front();
    Q.pop();
    visited[t]=false;
    for(i=p[t];i;i=e[i].next){
        temp=e[i].to;
        if(dis[temp]>dis[t]+e[i].w){
            dis[temp]=dis[t]+e[i].w;
            if(!visited[temp]){
                Q.push(temp);
                visited[temp]=true;
                if(++in[temp]>n) return false;
            }
        }
    }
}