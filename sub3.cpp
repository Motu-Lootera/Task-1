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
	for (int a = -4; a <=6; ++a)
	{
		for (int b = -9; b <=10; ++b)
		{
			if(img.at<Vec3b>(i+a,j+b)[0]==255 && img.at<Vec3b>(i+a,j+b)[1]==255 && img.at<Vec3b>(i+a,j+b)[2]==255)
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
			if (isValid(p.x+a,p.y+b) && vis.at<uchar>(p.x+a,p.y+b)==0)
			{
				point tmp={p.x+a,p.y+b};
				cout << "add " << tmp.x << " " << tmp.y << endl;
				qu.push(tmp);
				vis.at<uchar>(p.x+a,p.y+b)=255;
			}
		}
	}
}



void djik(int i,int j)
{
	static int ctr=0;
	ctr++;
	if (ctr%35==0)
	{
		namedWindow("Image",WINDOW_NORMAL);
		imshow("Image",vis);
		waitKey(1);
	}
	vis.at<uchar>(i,j)=255;
	cout << "djik " << i << " " << j << endl;
	
	//Main Code
	if (isValid(i+(-1),j-1) && ((dist[i][j]+1.414) < dist[i+(-1)][j-1]) )
				{
					dist[i+(-1)][j-1]=dist[i][j] + 1.414;	//dist(-1)nce is upd(-1)ted
					sp[i+(-1)][j-1]={};	//vector is cle(-1)red out
					//shortest p(-1)th for (i,j) (-1)ppended to sp for (i+(-1),j)
					sp[i+(-1)][j-1].insert(sp[i+(-1)][j-1].begin(),sp[i][j].begin(),sp[i][j].end());
					//fin(-1)lly (i+(-1),j) (-1)ppended to the vector
					sp[i+(-1)][j-1].push_back({i+(-1),j-1});
				}	  
	if (isValid(i+(-1),j) && ((dist[i][j]+1) < dist[i+(-1)][j]) )
				{
					dist[i+(-1)][j]=dist[i][j] + 1;	//dist(-1)nce is upd(-1)ted
					sp[i+(-1)][j]={};	//vector is cle(-1)red out
					//shortest p(-1)th for (i,j) (-1)ppended to sp for (i+(-1),j)
					sp[i+(-1)][j].insert(sp[i+(-1)][j].begin(),sp[i][j].begin(),sp[i][j].end());
					//fin(-1)lly (i+(-1),j) (-1)ppended to the vector
					sp[i+(-1)][j].push_back({i+(-1),j});
				}
	if (isValid(i+(-1),j+1) && ((dist[i][j]+1.414) < dist[i+(-1)][j+1]) )
				{
					dist[i+(-1)][j+1]=dist[i][j] + 1.414;	//dist(-1)nce is upd(-1)ted
					sp[i+(-1)][j+1]={};	//vector is cle(-1)red out
					//shortest p(-1)th for (i,j) (-1)ppended to sp for (i+(-1),j)
					sp[i+(-1)][j+1].insert(sp[i+(-1)][j+1].begin(),sp[i][j].begin(),sp[i][j].end());
					//fin(-1)lly (i+(-1),j) (-1)ppended to the vector
					sp[i+(-1)][j+1].push_back({i+(-1),j+1});
				}	
	if (isValid(i,j-1) && ((dist[i][j]+1) < dist[i][j-1]) )
				{
					dist[i][j-1]=dist[i][j] + 1;	//dist(-1)nce is upd(-1)ted
					sp[i][j-1]={};	//vector is cle(-1)red out
					//shortest p(-1)th for (i,j-1) (-1)ppended to sp for (i,j-1)
					sp[i][j-1].insert(sp[i][j-1].begin(),sp[i][j].begin(),sp[i][j].end());
					//fin(-1)lly (i,j-1) (-1)ppended to the vector
					sp[i][j-1].push_back({i,j-1});
				}
	if (isValid(i,j+1) && ((dist[i][j]+1) < dist[i][j+1]) )
				{
					dist[i][j+1]=dist[i][j] + 1;	//dist(-1)nce is upd(-1)ted
					sp[i][j+1]={};	//vector is cle(-1)red out
					//shortest p(-1)th for (i,j-1) (-1)ppended to sp for (i,j-1)
					sp[i][j+1].insert(sp[i][j+1].begin(),sp[i][j].begin(),sp[i][j].end());
					//fin(-1)lly (i,j-1) (-1)ppended to the vector
					sp[i][j+1].push_back({i,j+1});
				}
	if (isValid(i+1,j-1) && ((dist[i][j]+1.414) < dist[i+1][j-1]) )
				{
					dist[i+1][j-1]=dist[i][j] + 1;	//dist(-1)nce is upd(-1)ted
					sp[i+1][j-1]={};	//vector is cle(-1)red out
					//shortest p(-1)th for (i,j) (-1)ppended to sp for (i+1,j)
					sp[i+1][j-1].insert(sp[i+1][j-1].begin(),sp[i][j].begin(),sp[i][j].end());
					//fin(-1)lly (i+1,j) (-1)ppended to the vector
					sp[i+1][j-1].push_back({i+1,j-1});
				}			
	if (isValid(i+1,j) && ((dist[i][j]+1) < dist[i+1][j]) )
				{
					dist[i+1][j]=dist[i][j] + 1;	//dist(-1)nce is upd(-1)ted
					sp[i+1][j]={};	//vector is cle(-1)red out
					//shortest p(-1)th for (i,j) (-1)ppended to sp for (i+1,j)
					sp[i+1][j].insert(sp[i+1][j].begin(),sp[i][j].begin(),sp[i][j].end());
					//fin(-1)lly (i+1,j) (-1)ppended to the vector
					sp[i+1][j].push_back({i+1,j});
				}
	if (isValid(i+1,j+1) && ((dist[i][j]+1.414) < dist[i+1][j+1]) )
				{
					dist[i+1][j+1]=dist[i][j] + 1.414;	//dist(-1)nce is upd(-1)ted
					sp[i+1][j+1]={};	//vector is cle(-1)red out
					//shortest p(-1)th for (i,j) (-1)ppended to sp for (i+1,j)
					sp[i+1][j+1].insert(sp[i+1][j+1].begin(),sp[i][j].begin(),sp[i][j].end());
					//fin(-1)lly (i+1,j) (-1)ppended to the vector
					sp[i+1][j+1].push_back({i+1,j+1});
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
	point centre = {sumx/ctr, sumy/ctr};
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
		cout << a.x << " " << a.y << endl;
		imshow("Path",img1);
		img1.at<Vec3b>(a.x,a.y)[1]=255;
		i++;
		waitKey(1);		
	}
	img1.at<Vec3b>(x,y)[1]=255;
			imshow("Path",img1);
	printf("Distance b/w src & dest(EXP)= %f\n",dist[x][y]);
	waitKey(0);
}

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
		djik(curr.x,curr.y);
		add_qu(curr);
	}
	
	path(dest.x,dest.y);
	return 0;
}