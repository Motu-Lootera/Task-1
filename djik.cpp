#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <bits/stdc++.h> 

using namespace cv;
using namespace std;

struct point	//used for storing points
{
	int x;
	int y;
};



Mat img(50,50,CV_8UC1,Scalar(0));	//Test Image
Mat vis(img.rows,img.cols,CV_8UC1,Scalar(0));	//for storing if pixel visited
//for storing distance.Initialised at greater than possible in the image
int dist[50][50];
queue<point> qu;	//queue for implementing bfs
// 2-d array of vectors storing points for shortest path
vector<point> sp[50][50]; 



bool isValid(int i,int j)	
{
	if(i<0||j<0||i>=img.rows||j>=img.cols)
		return 0;
	if(img.at<uchar>(i,j)==255)
		return 0;
	return 1;
}



void add_qu(point p)
{
	for (int a = -1; a < 2; a++)
	{
		for (int b = -1; b < 2; b++)
		{
			// for only selectig the adjacent 4 valid pixels
			if (isValid(p.x+a,p.y+b) && vis.at<uchar>(p.x+a,p.y+b)==0)
			{
				point tmp={p.x+a,p.y+b};
				qu.push(tmp);
				vis.at<uchar>(p.x+a,p.y+b)=255;
			}
		}
	}
}



void djik(int i,int j)
{
	vis.at<uchar>(i,j)=255;
	namedWindow("Image",WINDOW_NORMAL);
	imshow("Image",vis);
	namedWindow("Image1",WINDOW_NORMAL);
	imshow("Image1",img);
	waitKey(1);
	
	//Main Code  
	for (int a = -1; a < 2; a++)
	{
		for (int b = -1; b < 2; b++)
		{ 
			// for selectig only the adjacent 4 valid pixels 
			
			// cout << i+a << " " << j+b << endl;
			// cout << dist[i][j] << endl;
			// cout << dist[i+a][j+b] << endl;
			if (isValid(i+a,j+b) && ((dist[i][j]+1) < dist[i+a][j+b]) )
				{
					dist[i+a][j+b]=dist[i][j] + 1;	//distance is updated
					cout << i+a << " " << j+b << endl;
					cout << dist[i+a][j+b] << endl;
					sp[i+a][j+b]={};	//vector is cleared out
					//shortest path for (i,j) appended to sp for (i+a,j+b)
					sp[i+a][j+b].insert(sp[i+a][j+b].begin(),sp[i][j].begin(),sp[i][j].end());
					//finally (i+a,j+b) appended to the vector
					sp[i+a][j+b].push_back({i+a,j+b});
					// cout << sp[i+a][i+b] << endl;
				}
			
		}
	}
}

int main()
{	
	for (int i = 0; i < 50; ++i)
	{
			for (int j = 0; j < 50; ++j)
			{
				dist[i][j]=2600;
			}
	}
	dist[0][0]=0;	// initial distance of src set to 0
	// cout << dist[0][0] << endl;
	sp[0][0].push_back({0,0});	//shortest path for src plugged
	point curr={0,0};
	qu.push(curr);
	while(!qu.empty())
	{
		curr=qu.front();
		qu.pop();
		add_qu(curr);
		djik(curr.x,curr.y);
	}
	return 0;
}