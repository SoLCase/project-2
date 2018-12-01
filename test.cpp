#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class Queuearray
{
	public:		
		Queuearray():capacity(10000000),front(-1),back(-1)
		{
        queue = new int[capacity];
    };
		void push(int x);
		void pop();
		int getFront();
		void morecapacity();
	private:
	    int capacity, front, back;
        int *queue;	
};
int Queuearray::getFront()
{
	return queue[front+1];
}
void Queuearray::pop()
{
	front++;
}
void Queuearray::push(int x)
{
	
	queue[++back]=x;
}
struct Vertice
{
	int visits,distance;
	int x,y;
	Vertice *up,*left,*down,*right;
	bool nd;
};
void setdistance(Vertice* start)
{

     int distance=start->distance+1;
	 cout<<endl<<distance;
     if(start->up!=NULL)
     {
		    if(start->up->distance==1)
     		{start->up->distance=distance;}
			 else 
			 {if(start->up->distance>distance){start->up->distance=distance;}}
	 }
	     if(start->left!=NULL)
     {
		    if(start->left->distance==1)
     		{start->left->distance=distance;}
			 else 
			 {if(start->left->distance>distance){start->left->distance=distance;}}
	 }
	     if(start->down!=NULL)
     {
		    if(start->down->distance==1)
     		{start->down->distance=distance;}
			 else 
			 {if(start->down->distance>distance){start->down->distance=distance;}}
	 }
	     if(start->right!=NULL)
     {
		    if(start->right->distance==1)
     		{start->right->distance=distance;}
			 else 
			 {if(start->right->distance>distance){start->right->distance=distance;}}
	 }

};
Vertice *findway(Vertice *start,int nowb)
{
	int u,d,r,l;

	u=d=r=l=100000002;
	if(start->up!=NULL&&start->up->distance<=nowb)
	{
		u=start->up->visits;
	}
	if(start->down!=NULL&&start->down->distance<=nowb)
	{
		d=start->down->visits;
	}
	if(start->right!=NULL&&start->right->distance<=nowb)
	{
		r=start->right->visits;
	}
	if(start->left!=NULL&&start->left->distance<=nowb)
	{
		l=start->left->visits;
	}
	int temp=100000000;
	if(start->up!=NULL&&start->up->distance>-1)
	{
		
		if(u<=temp)
		{
			temp=u;
		}
	}
	if(start->down!=NULL&&start->down->distance>-1)
	{
	
		if(d<=temp)
		{
			temp=d;
		}
	}
	if(start->left!=NULL&&start->left->distance>-1)
	{
		
		if(l<=temp)
		{
			temp=l;
		}
	}
	if(start->right!=NULL&&start->right->distance>-1)
	{
	
		if(r<=temp)
		{
			temp=r;
		}
	}
	if(temp==r){ return start->right;}
	else if(temp==l){return start->left;}
	else if(temp==d){return start->down;}
	else if(temp==u){ return start->up;}
};

struct Graph
{
	struct Vertice *vertices;	
};

 struct Graph* makeGraph(int size) 
{ 
	struct Graph* graph = new Graph;
	graph->vertices = new Vertice[size]; 

	return graph; 
} ;

int main(int argc,char*argv[])
{
	
	int r,c,i,j,k;

	
	int battery;	
	
	int chargepos;
	char x;
	int nv=0;
	fstream fin;
	string folderin;
    string folderout;
    string pathin,pathout;
    string start;
    folderin = "/floor.data";
    folderout = "/final.path";
    start ="./";
    pathin = start+argv[1] + folderin;
    pathout = start+argv[1] + folderout;
    fin.open(pathin,ios::in);
    if(fin.is_open()){cout<<"opened";}else{cerr<<"defail";}
    fin>>r;fin>>c;fin>>battery; 
	int size=r*c;
	int tod;
	struct Graph* graph = makeGraph(size);
	for(int i=1;i<=size;i++)
	{
		
		fin>>x;
		if(x=='0')
		{graph->vertices[i].distance=1;graph->vertices[i].visits=0;tod++;graph->vertices[i].nd=false;
		graph->vertices[i].up=NULL;	graph->vertices[i].left=NULL;graph->vertices[i].right=NULL;graph->vertices[i].down=NULL;
		nv++;}
		else if(x=='1')
		{graph->vertices[i].distance=-1;graph->vertices[i].visits=-1;}
		else if(x=='R')
		{graph->vertices[i].distance=0;graph->vertices[i].visits=0;graph->vertices[i].up=NULL;	graph->vertices[i].left=NULL;graph->vertices[i].right=NULL;graph->vertices[i].down=NULL;
		chargepos=i;}		
	}
	fin.close();
	cout<<"goconnece";
	//2D->1D a[i][j]->a[x] (i-1)*c+j=x (x-j)/c=i-1
		for(int i=1;i<=r;i++)
	{
		
          for(int j=1;j<=c;j++)
          {
          	int dpos=(i-1)*c+j;
          	int dposup=(i-2)*c+j;
          	int dposdown=i*c+j;
          	if(graph->vertices[dpos].visits==0)
          	{
          		graph->vertices[dpos].x=i-1;
          		graph->vertices[dpos].y=j-1;
          	    	if(i>1){
						  if(graph->vertices[dposup].visits==0){
				  	graph->vertices[dpos].up=&graph->vertices[(i-2)*c+j];}
				  //up
				  else{graph->vertices[dpos].up=NULL;}}
				  if(i<r){
          		if(graph->vertices[i*c+j].visits==0)
				  {
				    graph->vertices[dpos].down=&graph->vertices[i*c+j];
				  }
				  else{graph->vertices[dpos].down=NULL;}}//down
				  if(j>1){
          		if(graph->vertices[dpos-1].visits==0)
				  {
				  	graph->vertices[dpos].left=&graph->vertices[dpos-1];
				  }else{graph->vertices[dpos].left=NULL;}}//left
				  if(j<c){
          		if(graph->vertices[dpos+1].visits==0)
				  {
				  	graph->vertices[dpos].right=&graph->vertices[dpos+1];
				  }else{graph->vertices[dpos].right=NULL;}}//right 			
			
		  }}
	}
	int nowb=battery;
	Queuearray steps;
	int stepc=0;
	setdistance(&graph->vertices[chargepos]);
	cout<<"gofind";
	Vertice  *now=&graph->vertices[chargepos];
	while(nv>0)
	{
	if(now->distance==0)
	{
		nowb=battery;
	}
	nowb--;
	now=findway(now,nowb);
		if(now->visits==0)
	{
		nv--;
	}
	now->visits++;
	stepc++;
	steps.push(now->x);steps.push(now->y);
	}
    cout<<"back";
    while(now->distance>0)
    {
		nowb--;
	now=findway(now,nowb);
	stepc++;now->visits++;
	steps.push(now->x);steps.push(now->y);
	}
	cout<<"output";
	ofstream result;
result.open(pathout,ios::out);
result<<stepc<<endl;
   for(i=0;i<stepc;i++)
     {
     	result<<steps.getFront()<<" ";steps.pop();
     	result<<steps.getFront()<<endl;steps.pop();
	 }
	 delete[] &steps;
    return 0;
} 
