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
	float ang;
};

Mat img = imread("Test1.png", 1);

int isValid(point p)	
{
	point a={p.x-4,p.y-9};
	for (int ang = 0; ang >-91; ang-=10)
	{
		int flag=0;
		for (int i = 0; i <10; i+=9)
		{
			for (int j = 0; j < 20; ++j)
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
			for (int i = 0; i <10; ++i)
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
	return -1;
}

int main()
{
	int x,y,ang;
	printf("Enter x y: "); scanf("%d %d ",&x,&y);
	ang=isValid({x,y,0});
	if (ang!=-1)
	{
		cout << "Point Possible" << endl;
		printf("(%d,%d) at %d\n",x,y,ang);
	}
	else
		cout << "Not Possible" << endl;
}