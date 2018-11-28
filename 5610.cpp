#include<iostream>
using namespace std;
struct Vertice
{
	int visits,distance;
	int x,y;
	Vertice *up,*left,*down,*right;
	char zz;
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

void setdistance(Vertice* start)
{
     int distance=start->distance+1;
     if(start->up!=NULL)
     {
     	if(distance<=start->up->distance)
     	{
     		start->up->distance=distance;
     		setdistance(start->up);
		 }
	 }
	      if(start->right!=NULL)
     {
     	if(distance<=start->right->distance)
     	{
     		start->right->distance=distance;
     		setdistance(start->right);
		 }
	 }
	      if(start->down!=NULL)
     {
     	if(distance<=start->down->distance)
     	{
     		start->down->distance=distance;
     		setdistance(start->down);
		 }
	 }
	      if(start->left!=NULL)
     {
     	if(distance<=start->left->distance)
     	{
     		start->left->distance=distance;
     		setdistance(start->left);
		 }
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
int main()
{
	int r,c,i,j,k;
    cin>>r>>c;
    int array[r][c];
	int size=r*c;
	struct Graph* graph = makeGraph(size);
	int battery;	
	cin>>battery;
	int chargepos;
	char x;
	int nv=0;
	for(int i=1;i<=size;i++)
	{
		cin>>x;
		if(x=='0')
		{graph->vertices[i].distance=battery/2;graph->vertices[i].visits=0;
		graph->vertices[i].up=NULL;	graph->vertices[i].left=NULL;graph->vertices[i].right=NULL;graph->vertices[i].down=NULL;graph->vertices[i].zz='0';
		nv++;}//最遠距離應小於一半的電量，不然走不回來。 
		else if(x=='1')
		{graph->vertices[i].distance=-1;graph->vertices[i].visits=-1;graph->vertices[i].zz='1';}
		else if(x=='R')
		{graph->vertices[i].distance=0;graph->vertices[i].visits=0;graph->vertices[i].up=NULL;	graph->vertices[i].left=NULL;graph->vertices[i].right=NULL;graph->vertices[i].down=NULL;
		chargepos=i;nv++;graph->vertices[i].zz='R';}		
	}
	int connecting=0;
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
          		if(graph->vertices[dpos].distance==battery/2)
          	    {
				  if(graph->vertices[(i-2)*c+j].visits==0)
				  {
				  	graph->vertices[dpos].up=&graph->vertices[(i-2)*c+j];
				  }//up
          		if(graph->vertices[i*c+j].visits==0)
				  {
				    graph->vertices[dpos].down=&graph->vertices[i*c+j];
				  }//down
          		if(graph->vertices[dpos-1].visits==0)
				  {
				  	graph->vertices[dpos].left=&graph->vertices[dpos-1];
				  }//left
          		if(graph->vertices[dpos+1].visits==0)
				  {
				  	graph->vertices[dpos].right=&graph->vertices[dpos+1];
				  }//right 換行時一定不會進迴圈，所以不用擔心 
			}
			   
			   
			   else if(graph->vertices[dpos].distance==0){
			   	  if(j==1)//left
			   	  {
			   	  	graph->vertices[dpos].right=&graph->vertices[dpos+1];
			      } 
			      else if(j==c)//right
			      {
			      	graph->vertices[dpos].left=&graph->vertices[dpos-1];
				  }
				  else if(i==1)//top
				  {
				  	graph->vertices[dpos].down=&graph->vertices[i*c+j];
				  }
				  else if(i==r)//bott
				  {
				  	graph->vertices[dpos].up=&graph->vertices[(i-2)*c+j];
				  }
			   }
			}
		  }
	}
	int nowb=battery;
	
	setdistance(&graph->vertices[chargepos]);
	
	
	Vertice  *now=&graph->vertices[chargepos];
	while(nv>0)
	{
	if(now->distance==0)
	{
		nowb=battery;
	}
	
	if(now->visits==0)
	{
		nv--;
	}
	now->visits++;
	
	
	nowb--;
	now->zz='C';
	now=findway(now,nowb);
	//cout<<now->x<<"  "<<now->y<<endl;
	
    }
    while(nv==0)
    {
    
	nowb--;
	now=findway(now,nowb);
	//cout<<now->x<<"  "<<now->y<<endl;
	if(now==&graph->vertices[chargepos])
	{
		break;
	}
	}
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++)
		{
			int dpos=(i-1)*c+j;
			cout<<graph->vertices[dpos].zz<<"  ";
		}
		cout<<endl;
	}
    
} 
