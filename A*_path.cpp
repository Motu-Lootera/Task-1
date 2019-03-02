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
// float dist[1080][1080];
queue<point> qu;	//queue for implementing bfs
// 2-d array of vectors storing points for shortest path
// vector<point> sp[1080][1080]; 
vector<point> sp;



bool isValid(int i,int j)	
{
	if(i<0||j<0||i>=img.rows||j>=img.cols)
		return 0;
	if(img.at<Vec3b>(i,j)[0]==255 && img.at<Vec3b>(i,j)[1]==255 && img.at<Vec3b>(i,j)[2]==255)
		return 0;
	return 1;
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

float dist(point a,point b)
{
	int dx=abs(a.x-b.x);
	int dy=abs(a.y-b.y);
	float d= sqrt(dx*dx + dy*dy);
	return d;
}

void heur(point src,point p,point dest)
{
	vis.at<uchar>(p.x,p.y)=255;
	namedWindow("Image",WINDOW_NORMAL);
	imshow("Image",vis);
	waitKey(1);
	float min= 100000;
	point tmp,push;
	for (int a = -1; a < 2; a++)
	{
		for (int b = -1; b < 2; b++)
		{
			// for only selectig the adjacent 4 valid pixels
			if (isValid(p.x+a,p.y+b) && vis.at<uchar>(p.x+a,p.y+b)==0)
			{
				tmp={p.x+a,p.y+b};
				float fn= dist(src,tmp) + dist(tmp,dest);
				if (fn<min)
				{
					min=fn;
					push=tmp;
				}			
			}
		}
	} 
	qu.push(push);
	sp.push_back(push);
	// qu.push(tmp);
}


point centre(int chnl)
{
	Mat img2=img.clone();
	int sumx=0, sumy=0, ctr=0;
	for(int i=0; i<img.rows; i++){
		for(int j=0; j<img.cols; j++){
			if(img.at<Vec3b>(i,j)[0]>=220 && img.at<Vec3b>(i,j)[1]>=220 && img.at<Vec3b>(i,j)[2]>=220){
				img2.at<Vec3b>(i,j)[0]=0;
				img2.at<Vec3b>(i,j)[1]=0;
				img2.at<Vec3b>(i,j)[2]=0;
			}
		}
	}
	for(int i=0; i<img.rows; i++){
		for(int j=0; j<img.cols; j++){
			if(img2.at<Vec3b>(i,j)[chnl] >= 230){
				sumx += i;
				sumy += j;
				ctr++;
			}
		}
	}	
	point centre = {sumx/ctr, sumy/ctr};
	return centre;
}

void path(vector <point> sp)
{
	Mat img1=img.clone();
	namedWindow("Path",WINDOW_NORMAL);
	float de;
	int i=0;
	point u=sp[i];
	img1.at<Vec3b>(u.x,u.y)[1]=255;
	for(int i=1; i<sp.size(); ++i)
	{
		u=sp[i];
		cout << u.x << " " << u.y << endl;
		int dx=abs(u.x-sp[i-1].x), dy=abs(u.y-sp[i-1].y);
		if (dx*dy==0)
			de+=1;
		else
			de+=1.414;
		imshow("Path",img1);
		img1.at<Vec3b>(u.x,u.y)[1]=255;
		waitKey(1);
	}
	// img1.at<Vec3b>(dest.x,dest.y)[1]=255;
	imshow("Path",img1);

	printf("Distance b/w src & dest(TH)= %.3f\n", dist(*sp.begin(),*(sp.end()-1)));
	printf("Distance b/w src & dest(EXP)= %.3f\n", de);
	waitKey(0);
}

int main()
{	
	binary();	
	// float th;
	// printf("Enter Th: "); scanf("%f",&th);
	point src, dest;	
	src= centre(1);
	
	/*for (int i = 0; i < img.rows; ++i)
	{
			for (int j = 0; j < img.cols; ++j)
			{
				dist[i][j]=(img.rows*img.cols)+200;
			}
	}
	dist[src.x][src.y]=0;*/	// initial distance of src set to 0
	// sp[src.x][src.y].push_back({src.x,src.y});	//shortest path for src plugged
	point curr={src.x,src.y};
	qu.push(curr);
	
	dest = centre(2);
	
	while(!qu.empty() && vis.at<uchar>(dest.x,dest.y)==0)
	{
		// cout<<"a\n";
		curr=qu.front();
		qu.pop();
		// djik(curr.x,curr.y);
		// cout<<"b\n";
		heur(src,curr,dest);
	}
	
	path(sp);
	return 0;
}