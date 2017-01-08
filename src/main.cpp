#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace cv;
using namespace std;

Mat src, frame, traceP;
vector <Point> res;
int go [4];

void on_mouse( int event, int x, int y, int flags, void* ustc)  
{  
    if( event == CV_EVENT_LBUTTONDOWN )  
    {  
        Point pt = Point(x,y);  
        char temp[16];  
        sprintf(temp,"(%d,%d)",pt.x,pt.y);  
        putText(src,temp, pt, FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0, 0));  
        circle ( src, pt, 1,Scalar(255,0,255,0) ,CV_FILLED, CV_AA, 0 );  
        res.push_back(pt);
        imshow ( "src", src );  
    }   
}  

int main(int argc, const char *argv[])
{  
    if (argc != 2) {
        puts ("plz input filename!");
        return 0;
    }
    string filename = string(argv[1]);
    src= imread ("../data/" + filename + ".jpg");  
    res.clear();
    src.copyTo(frame);

    cvNamedWindow("Frame", 0);  
//    cvSetMouseCallback( "src", on_mouse, 0 );  

    imshow ("Frame", frame);  
    Point pt = Point (0, 0);
    circle ( frame, pt, 1,Scalar(255,0,255,0) ,CV_FILLED, CV_AA, 0 );  
    memset (go, 0, sizeof (0));
    while (1) {
        int key = waitKey(0) & 255;
        if (key == 'i') {
            res.push_back(pt);
            printf ("%d %d\n", pt.x, pt.y);
        }
        if (key == 'h') {
            go[0] += 1;
            go[1] = 0;
            go[2] = 0;
            go[3] = 0;
            pt = pt + Point (-go[0], 0);
        }
        if (key == 'j') {
            go[0] = 0;
            go[1] += 1;
            go[2] = 0;
            go[3] = 0;
            pt = pt + Point (0, go[1]);
        }
        if (key == 'k') {
            go[0] = 0;
            go[1] = 0;
            go[2] += 1;
            go[3] = 0;
            pt = pt + Point (0, -go[2]);
        }
        if (key == 'l') {
            go[0] = 0;
            go[1] = 0;
            go[2] = 0;
            go[3] += 1;
            pt = pt + Point (go[3], 0);
        }
        if (key == 'u') {
            if (res.size())
                res.pop_back ();
        }
        if (key == 'q') {
            break;
        }
        src.copyTo(frame);
        circle ( frame, pt, 5, Scalar(0,0,255,0) ,1, CV_AA, 0 );  
        circle ( frame, pt, 1, Scalar(255,0,255,0) ,CV_FILLED, CV_AA, 0 );  
        vector<Point2f> pts1, pts2;
        pts1.clear (); pts2.clear ();
        pts1.push_back (pt + Point (-20, -20));
        pts1.push_back (pt + Point (20, -20));
        pts1.push_back (pt + Point (20, 20));
        pts1.push_back (pt + Point (-20, 20));
        pts2.push_back (Point2f (0, 0));
        pts2.push_back (Point2f (100, 0));
        pts2.push_back (Point2f (100, 100));
        pts2.push_back (Point2f (0, 100));
        Mat M = getPerspectiveTransform (pts1, pts2);
        warpPerspective (frame, traceP, M, Size (100, 100));
        for (int i = 0; i < res.size(); ++i)
            circle ( frame, res[i], 1,Scalar(255,0,0,0) ,CV_FILLED, CV_AA, 0 );  
        imshow ("Frame", frame);  
        imshow ("Trace", traceP);  
    }
    ofstream out ("../data/" + filename + ".dat");  
    for (int i = 0; i < res.size (); ++i) 
        out <<  res[i].x << " " << res[i].y << endl;
    cvDestroyAllWindows();  

    return 0;  
}  

