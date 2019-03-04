#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <bits/stdc++.h> 
#define PI 3.1415
using namespace cv;
using namespace std;

struct point	//used for storing points
{
	int x;
	int y;
	int ang;
};



Mat img = imread("Test1.png", 1);	//Test Image
Mat vis(img.rows,img.cols,CV_8UC1,Scalar(0));	//for storing if pixel visited
//for storing distance.Initialised at greater than possible in the image
float dist[1080][1080];
queue<point> qu;	//queue for implementing bfs
// 2-d array of vectors storing points for shortest path
vector<point> sp[1080][1080]; 

void binary();
int isValid(point p);
void add_qu(point p);
void djik(point p);
point centre(int chnl);
void path(point p);


int main()
{	
	point src, dest;
	
	src= centre(1);
	
	for (int i = 0; i < img.rows; ++i)
	{
			for (int j = 0; j < img.cols; ++j)
			{
				dist[i][j]=(img.rows*img.cols)+200;
			}
	}
	dist[src.x][src.y]=0;	// initial distance of src set to 0
	sp[src.x][src.y].push_back({src.x,src.y});	//shortest path for src plugged
	point curr={src.x,src.y};
	qu.push(curr);
	
	dest = centre(2);
	
	while(!qu.empty() && vis.at<uchar>(dest.x,dest.y)==0)
	{
		curr=qu.front();
		qu.pop();
		djik(curr);
		add_qu(curr);
	}
	
	path(dest);
	return 0;
}

void binary()
{
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols; ++j)
		{
			if(img.at<Vec3b>(i,j)[0]>100 && img.at<Vec3b>(i,j)[1]>100 && img.at<Vec3b>(i,j)[2]>100)
				img.at<Vec3b>(i,j)={255,255,255};
			if(img.at<Vec3b>(i,j)[0]<100 && img.at<Vec3b>(i,j)[1]<100 && img.at<Vec3b>(i,j)[2]<100)
				img.at<Vec3b>(i,j)={0,0,0};
		}
	}
}


int isValid(point p)	
{
	point a={p.x-4,p.y-9};
	for (int ang = 0; ang >-31; ang-=10)
	{
		int flag=0;
		for (int i = 0; i <10; i+=9)
		{
			for (int j = 0; j < 19; ++j)
			{
				int nx=(j-10)*sin((p.ang+ang)*PI/180)+(i-5)*cos((p.ang+ang)*PI/180) +15;
				int ny=(j-10)*cos((p.ang+ang)*PI/180)-(i-5)*sin((p.ang+ang)*PI/180) +30;
				if(a.x+nx<0||p.y+ny<0||a.x+nx>=img.rows||p.y+ny>=img.cols)
				{	
					flag=1;
					break;
				}
				if(img.at<Vec3b>(a.x+nx,p.y+ny)[0]==255 && img.at<Vec3b>(a.x+nx,p.y+ny)[1]==255 && img.at<Vec3b>(a.x+nx,p.y+ny)[2]==255)
				{
					flag=1;
					break;
				}

			}
			if (flag==1)
				break;

		}
		if(flag==1)
			continue;

		for (int j = 0; j <20; j+=19)
		{
			for (int i = 0; i < 9; ++i)
			{
				int nx=(j-10)*sin((p.ang+ang)*PI/180)+(i-5)*cos((p.ang+ang)*PI/180) +15;
				int ny=(j-10)*cos((p.ang+ang)*PI/180)-(i-5)*sin((p.ang+ang)*PI/180) +30;
				if(a.x+nx<0||p.y+ny<0||a.x+nx>=img.rows||p.y+ny>=img.cols)
				{	
					flag=1;
					break;
				}
				if(img.at<Vec3b>(a.x+nx,p.y+ny)[0]==255 && img.at<Vec3b>(a.x+nx,p.y+ny)[1]==255 && img.at<Vec3b>(a.x+nx,p.y+ny)[2]==255)
				{
					flag=1;
					break;
				}
			}
			if(flag==1)
				break;		
		}
		if(flag==0)
			return (p.ang+ang);
		

	}
	for (int ang = 0; ang <31; ang+=10)
	{
		int flag=0;
		for (int i = 0; i <10; i+=9)
		{
			for (int j = 0; j < 19; ++j)
			{
				int nx=(j-10)*sin((p.ang+ang)*PI/180)+(i-5)*cos((p.ang+ang)*PI/180) +15;
				int ny=(j-10)*cos((p.ang+ang)*PI/180)-(i-5)*sin((p.ang+ang)*PI/180) +30;
				if(a.x+nx<0||p.y+ny<0||a.x+nx>=img.rows||p.y+ny>=img.cols)
				{	
					flag=1;
					break;
				}
				if(img.at<Vec3b>(a.x+nx,p.y+ny)[0]==255 && img.at<Vec3b>(a.x+nx,p.y+ny)[1]==255 && img.at<Vec3b>(a.x+nx,p.y+ny)[2]==255)
				{
					flag=1;
					break;
				}

			}
			if (flag==1)	break;
		}
		if(flag==1)	continue;

		for (int j = 0; j <20; j+=19)
		{
			for (int i = 0; i < 9; ++i)
			{
				int nx=(j-10)*sin((p.ang+ang)*PI/180)+(i-5)*cos((p.ang+ang)*PI/180) +15;
				int ny=(j-10)*cos((p.ang+ang)*PI/180)-(i-5)*sin((p.ang+ang)*PI/180) +30;
				if(a.x+nx<0||p.y+ny<0||a.x+nx>=img.rows||p.y+ny>=img.cols)
				{	
					flag=1;
					break;
				}
				if(img.at<Vec3b>(a.x+nx,p.y+ny)[0]==255 && img.at<Vec3b>(a.x+nx,p.y+ny)[1]==255 && img.at<Vec3b>(a.x+nx,p.y+ny)[2]==255)
				{
					flag=1;
					break;
				}
			}
			if(flag==1)	break;		
		}
		if(flag==0)	return (p.ang+ang);
	}
	return -1;
}



void add_qu(point p)
{
	for (int a = -1; a < 2; a++)
	{
		for (int b = -1; b < 2; b++)
		{
			// for only selectig the adjacent 4 valid pixels
			int c=isValid({p.x+a,p.y+b});
			if ((c!=-1) && vis.at<uchar>(p.x+a,p.y+b)==0)
			{
				point tmp={p.x+a,p.y+b,c};
				qu.push(tmp);
				// vis.at<uchar>(p.x+a,p.y+b)=255;
			}
		}
	}
}



void djik(point p)
{
	static int ctr=0;
	ctr++;
	if (ctr%150==0)
	{
		namedWindow("Image",WINDOW_NORMAL);
		imshow("Image",vis);
		waitKey(1);
	}
	vis.at<uchar>(p.x,p.y)=255;
	// cout << "djik " << p.x << " " << p.y << endl;
	
	//Main Code
	for (int a = -1; a < 2; ++a)
	{
		for (int b = -1; b < 2; ++b)
		{
			int c=isValid({p.x+a,p.y+b});
			if(c!=-1)
			{
				if((abs(a+b)==1) && (dist[p.x][p.y] + 1< dist[p.x+a][p.y+b]))
				{
					dist[p.x+a][p.y+b]=dist[p.x][p.y] + 1;	//distance is updated
					sp[p.x+a][p.y+b]={};	//vector is cleared out
					//shortest path for (p.x,p.y) appended to sp for (p.x+a,p.y)
					sp[p.x+a][p.y+b].insert(sp[p.x+a][p.y+b].begin(),sp[p.x][p.y].begin(),sp[p.x][p.y].end());
					//finally (p.x+a,p.y) appended to the vector
					sp[p.x+a][p.y+b].push_back({p.x+a,p.y+b,c});
				}
				else if (abs(a*b)==1 && (dist[p.x][p.y] + 1.414< dist[p.x+a][p.y+b]))
				{
					dist[p.x+a][p.y+b]=dist[p.x][p.y] + 1.414;	//distance is updated
					sp[p.x+a][p.y+b]={};	//vector is cleared out
					//shortest path for (p.x,p.y) appended to sp for (p.x+a,p.y)
					sp[p.x+a][p.y+b].insert(sp[p.x+a][p.y+b].begin(),sp[p.x][p.y].begin(),sp[p.x][p.y].end());
					//finally (p.x+a,p.y) appended to the vector
					sp[p.x+a][p.y+b].push_back({p.x+a,p.y+b,c});
				}
			}
		}
	}
}


point centre(int chnl)
{
	Mat img2=img.clone();
	int sumx=0, sumy=0, ctr=0;
	for(int i=0; i<img.rows; i++)
	{
		for(int j=0; j<img.cols; j++)
		{
			if(img.at<Vec3b>(i,j)[chnl]>=220 && img.at<Vec3b>(i,j)[(chnl+1)%3]<220 && img.at<Vec3b>(i,j)[(chnl+2)%3]<220)
			{
				sumx += i;
				sumy += j;
				ctr++;
			}
		}
	}	
	point centre = {sumx/ctr, sumy/ctr};
	return centre;
}

void path(point p)
{
	Mat img1=img.clone();
	namedWindow("Path",WINDOW_NORMAL);
	point a;
	int i=0;
	// a=sp[x][y][i];
	// cout << sp[x][y].size() << endl;
	cout << "Path" << endl;
	while(a.x!=p.x || a.y!=p.y)
	{
		a=sp[p.x][p.y][i];
		cout << a.x << " " << a.y << endl;
		imshow("Path",img1);
		img1.at<Vec3b>(a.x,a.y)[1]=255;
		i++;
		waitKey(1);		
	}
	img1.at<Vec3b>(p.x,p.y)[1]=255;
			imshow("Path",img1);

	printf("Distance b/w src & dest= %f\n",dist[p.x][p.y]);
	waitKey(0);
}
