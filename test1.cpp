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



Mat img(50,50,CV_8UC3,Scalar(0,0,0));	//Test Image
Mat vis(img.rows,img.cols,CV_8UC1,Scalar(0));	//for storing if pixel visited
//for storing distance.Initialised at greater than possible in the image
float dist[50][50];
queue<point> qu;	//queue for implementing bfs
// 2-d array of vectors storing points for shortest path
vector<point> sp[50][50]; 



bool isValid(int i,int j)	
{
	if(i<0||j<0||i>=img.rows||j>=img.cols)
		return 0;
	if(img.at<Vec3b>(i,j)[0]==255 && img.at<Vec3b>(i,j)[1]==255 && img.at<Vec3b>(i,j)[2]==255)
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
				// vis.at<uchar>(p.x+a,p.y+b)=255;
			}
		}
	}
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
	int x,y;
	//taking co-ords for src pt.
	printf("Enter src_x: "); scanf("%d",&x);
	printf("Enter src_y: "); scanf("%d",&y);
	
	for (int i = 0; i < img.rows; ++i)
	{
			for (int j = 0; j < img.cols; ++j)
			{
				dist[i][j]=(img.rows*img.cols)+200;
			}
	}
	dist[x][y]=0;	// initial distance of src set to 0
	sp[x][y].push_back({x,y});	//shortest path for src plugged
	point curr={x,y};
	qu.push(curr);
	while(!qu.empty())
	{
		curr=qu.front();
		qu.pop();
		add_qu(curr);
		djik(curr.x,curr.y);
	}
	
	//Taking co-ords for destination pt.
	printf("Enter dest_x: "); scanf("%d",&x);
	printf("Enter dest_y: "); scanf("%d",&y);
	path(x,y);
	return 0;
}