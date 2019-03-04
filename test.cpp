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
	float d;
	bool operator<(const point& rhs) const
    {
        return d > rhs.d;
    }
};

Mat img = imread("Test1.png", 1);	//Test Image
Mat vis(img.rows,img.cols,CV_8UC1,Scalar(0));	//for storing if pixel visited
//for storing distance.Initialised at greater than possible in the image
priority_queue<point> qu;	//priority queue for implementing bfs
float dist[1080][1080];
// 2-d array of vectors storing points for shortest path
vector<point> sp[1080][1080]; 
 


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



bool isValid(int i,int j)	
{
	if(i<0||j<0||i>=img.rows||j>=img.cols)
		return 0;
	if(img.at<Vec3b>(i,j)[0]==255 && img.at<Vec3b>(i,j)[1]==255 && img.at<Vec3b>(i,j)[2]==255)
		return 0;
	return 1;
}



/*void add_qu(point p)
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
*/


void djik(int i,int j)
{
	vis.at<uchar>(i,j)=255;
	/*namedWindow("Image",WINDOW_NORMAL);
	imshow("Image",vis);
	waitKey(1);*/
	
	//Main Code
	for (int a = -1; a < 2; ++a)
	{
		for (int b = -1; b < 2; ++b)
		{
			if(isValid(i+a,j+b))
			{
				if((abs(a+b)==1) && (dist[i][j] + 1< dist[i+a][j+b]))
				{
					dist[i+a][j+b]=dist[i][j] + 1;	//distance is updated
					sp[i+a][j+b]={};	//vector is cleared out
					//shortest path for (i,j) appended to sp for (i+a,j)
					sp[i+a][j+b].insert(sp[i+a][j+b].begin(),sp[i][j].begin(),sp[i][j].end());
					//finally (i+a,j) appended to the vector
					sp[i+a][j+b].push_back({i+a,j+b,dist[i+a][j+b]});
					qu.push({i+a,j+b,dist[i+a][j+b]});
				}
				else if (abs(a*b)==1 && (dist[i][j] + 1.414< dist[i+a][j+b]))
				{
					dist[i+a][j+b]=dist[i][j] + 1.414;	//distance is updated
					sp[i+a][j+b]={};	//vector is cleared out
					//shortest path for (i,j) appended to sp for (i+a,j)
					sp[i+a][j+b].insert(sp[i+a][j+b].begin(),sp[i][j].begin(),sp[i][j].end());
					//finally (i+a,j) appended to the vector
					sp[i+a][j+b].push_back({i+a,j+b,dist[i+a][j+b]});
					qu.push({i+a,j+b,dist[i+a][j+b]});				
				}
			}
		}
	}					
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
	point centre = {sumx/ctr, sumy/ctr, (float)(img.rows*img.cols+200)};
	return centre;
}

void path(int x,int y)
{
	Mat img1=img.clone();
	namedWindow("Path",WINDOW_NORMAL);
	point a;
	int i=0;
	// a=sp[x][y][i];
	// cout << sp[x][y].size() << endl;
	while(a.x!=x || a.y!=y)
	{
		a=sp[x][y][i];
		// cout << a.x << " " << a.y << endl;
		imshow("Path",img1);
		img1.at<Vec3b>(a.x,a.y)[1]=255;
		i++;
		waitKey(1);		
	}
	img1.at<Vec3b>(x,y)[1]=255;
			imshow("Path",img1);

	printf("Distance b/w src & dest= %f\n",dist[x][y]);
	waitKey(0);
}

int main()
{	
	binary();
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
	point curr={src.x,src.y,0};
	qu.push(curr);
	
	dest = centre(2);
	
	while(!qu.empty() && vis.at<uchar>(dest.x,dest.y)==0)
	{
		djik(qu.top().x,qu.top().y);	
		qu.pop();
		// add_qu(curr);
	}  
	
	path(dest.x,dest.y);
	return 0;
}