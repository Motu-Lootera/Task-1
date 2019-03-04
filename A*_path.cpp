#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <bits/stdc++.h> 

using namespace cv;
using namespace std;

struct pairs	//used for storing points
{
	Point p;
	Point par;
	float fn;
	bool operator<(const pairs& rhs) const
    {
        return fn > rhs.fn;
    }
};


Mat img = imread("Test1.png", 1);	//Test Image
Mat vis(img.rows,img.cols,CV_8UC1,Scalar(0));	//for storing if pixel visited
//for storing distance.Initialised at greater than possible in the image
float gn[1080][1080];
priority_queue<pairs> open;
stack<pairs> close;


void binary();
bool isValid(Point p);
float hn(Point a,Point b);
void a_star(Point src,Point p,Point dest);
Point centre(int chnl);
void path(Point src,Point dest);


int main()
{	
	binary();	
	Point src, dest;	
	src= centre(1);
	dest = centre(2);
	
	for (int i = 0; i < img.rows; ++i)
	{
			for (int j = 0; j < img.cols; ++j)
			{
				gn[i][j]=(img.rows*img.cols)+200;
			}
	}
	gn[src.x][src.y]=0;	// initial distance of src set to 0
	// sp[src.x][src.y].push_back({src.x,src.y});	//shortest path for src plugged

	open.push({src,src,hn(src,dest)});
	
	
	while(!open.empty() && vis.at<uchar>(dest.x,dest.y)==0)
	{
		// cout<<"a\n";
		pairs curr=open.top();
		a_star(src,curr.p,dest);
		vis.at<uchar>(curr.p.x,curr.p.y)=255;
		close.push(curr);
		open.pop();
	}
	path(src,dest);
	
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

bool isValid(Point p)	
{
	if(p.x<0||p.y<0||p.x>=img.rows||p.y>=img.cols)
		return 0;
	if(img.at<Vec3b>(p.x,p.y)[0]==255 && img.at<Vec3b>(p.x,p.y)[1]==255 && img.at<Vec3b>(p.x,p.y)[2]==255)
		return 0;
	return 1;
}

float hn(Point a,Point b)
{
	int dx=abs(a.x-b.x);
	int dy=abs(a.y-b.y);
	float d= (dx+dy)-(0.586*(dx<dy ? dx:dy));
	return d;
}

void a_star(Point src,Point p,Point dest)
{
	namedWindow("Image",WINDOW_NORMAL);
	imshow("Image",vis);

	for (int i = -1; i < 2; ++i)
	{
		for (int j = -1; j < 2; ++j)
		{
			if (isValid({p.x+i,p.y+j}) && vis.at<uchar>(p.x+i,p.y+j)==0)
			{
				if((abs(i+j)==1) && (gn[p.x][p.y] + 1< gn[p.x+i][p.y+j]))
				{
					Point a={p.x+i,p.y+j};
					gn[a.x][a.y]= gn[p.x][p.y] + 1;
					float fn=  gn[a.x][a.y] + hn(a,dest);
					open.push({a,p,fn});
				}
				if((abs(i*j)==1) && (gn[p.x][p.y] + 1.414< gn[p.x+i][p.y+j]))
				{
					Point a={p.x+i,p.y+j};
					gn[a.x][a.y]= gn[p.x][p.y] + 1.414;
					float fn=  gn[a.x][a.y] + hn(a,dest);
					open.push({a,p,fn});
				}

			}
		}
	}
	
}

Point centre(int chnl)
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
	Point centre = {sumx/ctr, sumy/ctr};
	return centre;
}

void path(Point src,Point dest)
{
	Mat img1=img.clone();
	namedWindow("Path",WINDOW_NORMAL);
	//tmp is now the dest pt. since dest was added to stack close last
	Point tmp=close.top().p;
	//par is the parent of dest;
	Point par=close.top().par;
	close.pop();
	while(!close.empty() && (tmp.x!=src.x || tmp.y!=src.y))
	{
		pairs a=close.top();
		img1.at<Vec3b>(tmp.x,tmp.y)[1]=255;
		imshow("Path",img1);
		if(a.p.x==par.x && a.p.y==par.y)
		{
			tmp=par;
			par=a.par;
		}
		close.pop();
	}

	// printf("Disance b/w src & dest(TH)= %.3f\n", gn(src,dest));
	printf("Distance b/w src & dest(EXP)= %.3f\n", gn[dest.x][dest.y]);
	waitKey(0);
}
