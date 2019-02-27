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



bool isValid(int i,int j)	
{
	if(i<0||j<0||i>=img.rows||j>=img.cols)
		return 0;
	if(img.at<Vec3b>(i,j)[0]==255 && img.at<Vec3b>(i,j)[1]==255 && img.at<Vec3b>(i,j)[2]==255)
		return 0;
	return 1;
}



void heur(point p,point dest)
{
	int dx=abs(p.x-dest.x);	
	int dy=abs(p.y-dest.y);
	float fn,hn= (dx+dy) - (0.586 * ( dx<dy ? dx : dy));
	float min=(dist[p.x][p.y]) + hn;
	point tmp;
	
	for (int a = -1; a < 2; a++)
	{
		for (int b = -1; b < 2; b++)
		{
			// for only selectig the adjacent 4 valid pixels
			if (isValid(p.x+a,p.y+b) && vis.at<uchar>(p.x+a,p.y+b)==0)
			{
				cout<<"c\n";
				dx=abs((p.x+a)-dest.x);	dy=abs((p.y+b)-dest.y);
				hn= (dx+dy) - (0.586 * ( dx<dy ? dx : dy));
				fn=(dist[p.x+a][p.y+b]) + hn;
				if (fn<min)
				{
					min=fn;
					tmp={p.x+a,p.y+b};
					// vis.at<uchar>(p.x+a,p.y+b)=255;
				}			
			}
		}
	}
	qu.push(tmp);
}



void djik(int i,int j)
{
	vis.at<uchar>(i,j)=255;
	namedWindow("Image",WINDOW_NORMAL);
	imshow("Image",vis);
	waitKey(1);
	
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

	printf("Distance b/w src & dest= %f\n",dist[x][y]);
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
		cout<<"a\n";
		curr=qu.front();
		qu.pop();
		djik(curr.x,curr.y);
		cout<<"b\n";
		heur(curr,dest);
	}
	
	path(dest.x,dest.y);
	return 0;
}