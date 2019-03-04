#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <bits/stdc++.h> 

using namespace cv;
using namespace std;

struct thing
{
    int a;
    char b;
    bool operator<(const thing& rhs) const
    {
        return a > rhs.a;
    }
};


int main()
{
	stack<thing> q;
	thing stuff = {42, 'x'};
	q.push(stuff);
	q.push({5656, 'y'});    
	q.push({4242, 'y'});
	stack<thing> v=q;    
	thing otherStuff = v.top();
	cout << otherStuff.a << endl;
	if(q.empty())
		cout << 1 << endl;

	
	
}