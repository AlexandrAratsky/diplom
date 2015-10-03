//---------------------------------------------------------------------------

#pragma hdrstop

#include "Structs.h"
#include <math.h>
#include <sstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;


// c_info
unsigned short cc_info::count = 0;
cc_info::cc_info(int x1, int y1, int x2, int y2)
    :x_min(x1),x_max(x2),y_min(y1),y_max(y2), id(count++) { }
int cc_info::width() const
{
    return abs(x_max - x_min) + 1;
}
int cc_info::height() const
{
    return abs(y_max - y_min) + 1;
}
bool cc_info::in_line(int y) const
{
    return (y>=y_min && y<=y_max);
}
bool cc_info::in_column(int x) const
{
    return (x>=x_min && x<=x_max);
}
bool cc_info::in_area(int x, int y) const
{
    return (y>=y_min && y<=y_max) && (x>=x_min && x<=x_max);
}
int cc_info::center_y() const
{
    return (y_min+y_max)/2;
}
int cc_info::center_x() const
{
    return (x_min+x_max)/2;
}
int cc_info::counter()
{
    return count;
}
void cc_info::reset_counter()
{
    count = 0;
}
std::string cc_info::to_str() const
{
    std::stringstream out;
    out<<"["<<id<<"] ("<<x_min<<","<<y_min<<";"<<x_max<<","<<y_max<<")";
    return out.str();
}
bool operator ==(const cc_info &a,const cc_info &b)
{
    return (a.id == b.id);
}
int cc_info::volume()
{
    return (x_max-x_min+1)*(y_max-y_min+1);
}
cc_info cc_info::operator=(const cc_info& a)
{
    return cc_info(a.x_min,a.y_min,a.x_max,a.y_max,a.id);
}
cc_info::cc_info(int x1, int y1, int x2, int y2, int i)
    :x_min(x1),x_max(x2),y_min(y1),y_max(y2), id(i) { }


// dash
dash::dash(int l,int s,int f)
    :level(l),start(s),finish(f) { }
int dash::length() const
{
    return finish-start+1;
}
std::string dash::to_str() const
{
    std::stringstream out;
    out<<"{"<<level<<";"<<start<<","<<finish<<"}";
    return out.str();
}
double dash::moment(int p) const
{
    return (pow(finish+1,double(p+1)) - pow(start,double(p+1))) / (p+1);
}
double dash::center_moment(int p, double x) const
{
    return (pow(finish+1 - x,double(p+1)) - pow(start - x,double(p+1))) / (p+1);
}
double dash::e_moment(int p, double length) const
{
    return (pow((finish+1)/length,double(p+1)) - pow(start/length,double(p+1))) / (p+1);
}

// moments_info
bool moments::center = true;
float moments::center_heavy = 1;
float moment_info::get_ratio(int i, int count)
{
    if (count==1) return 1.0/2;
    if (count==2)
    {
        switch (i) {
           case 1: return 1.0/3;
           case 2: return 2.0/3;
           default: return -1;
        }
    }
    if (count==3)
    {
        switch (i) {
           case 1: return 1.0/4;
           case 2: return 2.0/4;
           case 3: return 3.0/4;
           default: return -1;
        }
    }
    return -1;
}
moment_info::moment_info(double center)
: count(1)
{
    val[0] = center;
    val[1] = -1;
    val[2] = -1;
}
moment_info::moment_info(double left, double right)
: count(2)
{
    val[0] = left;
    val[1] = right;
    val[2] = -1;
}
moment_info::moment_info(double left, double center, double right)
: count(3)
{
    val[0] = left;
    val[1] = center;
    val[2] = right;
}
moment_info::moment_info(int c):count(c)
{
    val[0] = -1;
    val[1] = -1;
    val[2] = -1;
}
std::string moments::to_str() const
{
    std::stringstream out;
    for(int i=0;i<ver.count;i++) out<<" "<<ver.val[i]<<" ("<<ver.cen[i]<<")";
    out<<"\n";
    for(int i=0;i<hor.count;i++) out<<" "<<hor.val[i]<<" ("<<hor.cen[i]<<")";
    return out.str();
}


