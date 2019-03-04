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
	/*bool operator<(const point& rhs) const
    {
        return d > rhs.d;
    }*/
};



Mat img = imread("Test1.png", 1);	//Test Image
Mat vis(img.rows,img.cols,CV_8UC1,Scalar(0));	//for storing if pixel visited
//for storing distance.Initialised at greater than possible in the image
// float dist[1080][1080];
queue<point> qu;	//queue for implementing bfs
// 2-d array of vectors storing points for shortest path
// vector<point> sp[1080][1080]; 
vector<point> sp;



bool isValid(point p)	
{
	point a={p.x-4,p.y-9};
	for (int ang = 0; ang >-91; ang-=10)
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
	for (int ang = 0; ang <91; ang+=10)
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

void a_star(point src,point p,point dest)
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
			int c=isValid({p.x+a,p.y+b});
			if (c!=-1 && vis.at<uchar>(p.x+a,p.y+b)==0)
			{
				tmp={p.x+a,p.y+b,c};
				float fn= dist(src,tmp) + 10*dist(tmp,dest);
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
	point centre = {sumx/ctr, sumy/ctr, 0};
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

	sp.push_back({src.x,src.y,0});	//shortest path for src plugged
	point curr={src.x,src.y,0};
	qu.push(curr);
	
	dest = centre(2);
	
	while(!qu.empty() && vis.at<uchar>(dest.x,dest.y)==0)
	{
		a_star(src,qu.front(),dest);
		qu.pop();
		// cout<<"a\n";
		// djik(curr.x,curr.y);
		// cout<<"b\n";
	}
	
	path(sp);
	return 0;
}