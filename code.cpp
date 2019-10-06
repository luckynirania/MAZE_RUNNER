#include<iostream>
#include <list>
#include <limits.h> 
#include <stdio.h>

#define INFINITY 9999
#define V 225
#define max 225

using namespace std;

list<int> PATH;

struct box {
    int number;
    bool up,down,left,right;
    box() {
        up = down = left = right = false;
    }
    void set_up(bool val) {
        up = val;
    }
    void set_down(bool val) {
        down = val;
    }
    void set_left(bool val) {
        left = val;
    }
    void set_right(bool val) {
        right = val;
    }
    void set_number(int q) {
        number = q;
    }
    void operator=(box a) {
        this->up = a.up;
        this->down = a.down;
        this->left = a.left;
        this->right = a.right;
    }
};

struct MAZE {
    box block[15][15];
    MAZE() {
        for(int i = 0;i < 15;i++) {
            for(int j = 0;j < 15;j++) {
                block[i][j].set_number(15*i+j);
            }
        }
    }
    // block[0][0].up = false;
    list<int> match(box a) {
        list<int> matching_boxes;
        for(int i = 0;i < 15;i++) {
            for(int j = 0;j < 15;j++) {
                if((a.up == block[i][j].up) && (a.down == block[i][j].down) && (a.left == block[i][j].left) && (a.right == block[i][j].right)) {
                    matching_boxes.push_back(block[i][j].number);
                }
            }
        }
        return matching_boxes;
    }
    box get_box() {
        box temp;
        return temp;
    }
};

int minDistance(int dist[], bool sptSet[]) 
{ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 

int printSolution(int dist[]) { 
    printf("Vertex \t\t Distance from Source\n"); 
    for (int i = 0; i < V; i++) 
        printf("%d \t\t %d\n", i, dist[i]); 
} 
 void dijkstra(int G[max][max],int n,int startnode,int destination) {
   int cost[max][max],distance[max],pred[max];
   int visited[max],count,mindistance,nextnode,i,j;
   for(i=0;i<n;i++)
      for(j=0;j<n;j++)
   if(G[i][j]==0)
      cost[i][j]=INFINITY;
   else
      cost[i][j]=G[i][j];
   for(i=0;i<n;i++) {
      distance[i]=cost[startnode][i];
      pred[i]=startnode;
      visited[i]=0;
   }
   distance[startnode]=0;
   visited[startnode]=1;
   count=1;
   while(count<n-1) {
      mindistance=INFINITY;
      for(i=0;i<n;i++)
         if(distance[i]<mindistance&&!visited[i]) {
         mindistance=distance[i];
         nextnode=i;
      }
      visited[nextnode]=1;
      for(i=0;i<n;i++)
         if(!visited[i])
      if(mindistance+cost[nextnode][i]<distance[i]) {
         distance[i]=mindistance+cost[nextnode][i];
         pred[i]=nextnode;
      }
      count++;
   }
   for(i=0;i<n;i++)
   if(i!=startnode) {
      cout<<"\nDistance of node"<<i<<"="<<distance[i];
      cout<<"\nPath="<<i;
      if(i==destination) PATH.push_back(i);
      j=i;
      do {
         j=pred[j];
         cout<<"<-"<<j;
         if(i==destination) PATH.push_back(j);
      }while(j!=startnode);
   }
}

int main() {
    int destination = 45;
    MAZE maze;
    list<int> possible_matches;
    box my_box;
    my_box = maze.get_box();
    possible_matches = maze.match(my_box);
    while(possible_matches.size() != 1) {
        if(my_box.up == true) my_box = maze.block[my_box.number / 15][my_box.number % 15];
        possible_matches.clear();
        possible_matches = maze.match(my_box);
    }
    int graph[V][V];
    for(int i = 0;i < V;i++) {
        for(int j = 0;j < V;j++) {
            graph[i][j] = 0;
        }
    }
    for(int i = 0;i < 15;i++) {
        for(int j = 0;j < 15;j++) {
            graph[15*i+j][15*i+j] = 0;
            if(maze.block[i][j].up == true) graph[15*i+j][15*i+j+15] = 1;
            if(maze.block[i][j].down == true) graph[15*i+j][15*i+j-15] = 1;
            if(maze.block[i][j].left == true) graph[15*i+j][15*i+j-1] = 1;
            if(maze.block[i][j].right == true) graph[15*i+j][15*i+j+1] = 1;
        }
    }
    dijkstra(graph,225,my_box.number,destination);
}