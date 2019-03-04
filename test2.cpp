#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <bits/stdc++.h> 

using namespace cv;
using namespace std;

struct point	//used for storing points
{
	int x;
	int y;
};



Mat img = imread("Test1.png", 1);	//Test Image
Mat vis(img.rows,img.cols,CV_8UC1,Scalar(0));	//for storing if pixel visited
//for storing distance.Initialised at greater than possible in the image
float dist[1080][1080];
queue<point> qu;	//queue for implementing bfs
// 2-d array of vectors storing points for shortest path
vector<point> sp[1080][1080]; 

void binary();
bool isValid(point p);
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


bool isValid(point p)	
{
	for (int a = -4; a <16; ++a)
	{
		for (int b = -9; b <10; ++b)
		{
			if(p.x+a<0||p.y+b<0||p.x+a>=img.rows||p.y+b>=img.cols)
				return 0;
			if(img.at<Vec3b>(p.x+a,p.y+b)[0]==255 && img.at<Vec3b>(p.x+a,p.y+b)[1]==255 && img.at<Vec3b>(p.x+a,p.y+b)[2]==255)
				return 0;
		}
	}
	return 1;
}



void add_qu(point p)
{
	for (int a = -1; a < 2; a++)
	{
		for (int b = -1; b < 2; b++)
		{
			// for only selectig the adjacent 4 valid pixels
			if (isValid({p.x+a,p.y+b}) && vis.at<uchar>(p.x+a,p.y+b)==0)
			{
				point tmp={p.x+a,p.y+b};
				qu.push(tmp);
				vis.at<uchar>(p.x+a,p.y+b)=255;
			}
		}
	}
}



void djik(point p)
{
	static int ctr=0;
	ctr++;
	if (ctr%45==0)
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
			if(isValid({p.x+a,p.y+b}))
			{
				if((abs(a+b)==1) && (dist[p.x][p.y] + 1< dist[p.x+a][p.y+b]))
				{
					dist[p.x+a][p.y+b]=dist[p.x][p.y] + 1;	//distance is updated
					sp[p.x+a][p.y+b]={};	//vector is cleared out
					//shortest path for (p.x,p.y) appended to sp for (p.x+a,p.y)
					sp[p.x+a][p.y+b].insert(sp[p.x+a][p.y+b].begin(),sp[p.x][p.y].begin(),sp[p.x][p.y].end());
					//finally (p.x+a,p.y) appended to the vector
					sp[p.x+a][p.y+b].push_back({p.x+a,p.y+b});
				}
				else if (abs(a*b)==1 && (dist[p.x][p.y] + 1.414< dist[p.x+a][p.y+b]))
				{
					dist[p.x+a][p.y+b]=dist[p.x][p.y] + 1.414;	//distance is updated
					sp[p.x+a][p.y+b]={};	//vector is cleared out
					//shortest path for (p.x,p.y) appended to sp for (p.x+a,p.y)
					sp[p.x+a][p.y+b].insert(sp[p.x+a][p.y+b].begin(),sp[p.x][p.y].begin(),sp[p.x][p.y].end());
					//finally (p.x+a,p.y) appended to the vector
					sp[p.x+a][p.y+b].push_back({p.x+a,p.y+b});
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
