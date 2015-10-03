//---------------------------------------------------------------------------

#pragma hdrstop

#include "ConnectedComponent.h"
#include <queue>
#include <iterator>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace std;
using namespace inc;

bool comporator(ComInfo& first, ComInfo& second)
{
	return (first.MinX()<=second.MinX() && first.MaxY()<=second.MaxY());
}


bool ConCom::InArea(int i, int j)
{
    if (i>=0 && i<m && j>=0 && j<n) return true;
    else return false;
}
bool ConCom::HasNear(int count, int i, int j)
{
     switch (count)
    {
        case 0: return InArea(i,j-1);
        case 1: return InArea(i+1,j-1);
        case 2: return InArea(i+1,j);
        case 3: return InArea(i+1,j+1);
        case 4: return InArea(i,j+1);
        case 5: return InArea(i-1,j+1);
        case 6: return InArea(i-1,j);
        case 7: return InArea(i-1,j-1);
        default: return InArea(i,j);
    }
}
TColor ConCom::GetClrNear(int count, int i, int j)
{
    switch (count)
    {
        case 0: return _map->Canvas->Pixels[i][j-1];
        case 1: return _map->Canvas->Pixels[i+1][j-1];
        case 2: return _map->Canvas->Pixels[i+1][j];
        case 3: return _map->Canvas->Pixels[i+1][j+1];
        case 4: return _map->Canvas->Pixels[i][j+1];
        case 5: return _map->Canvas->Pixels[i-1][j+1];
        case 6: return _map->Canvas->Pixels[i-1][j];
        case 7: return _map->Canvas->Pixels[i-1][j-1];
        default: return _map->Canvas->Pixels[i][j];
    }
}
point ConCom::GetNear(int count, int i, int j)
{
     switch (count)
    {
        case 0: return point(i,j-1);
        case 1: return point(i+1,j-1);
        case 2: return point(i+1,j);
        case 3: return point(i+1,j+1);
        case 4: return point(i,j+1);
        case 5: return point(i-1,j+1);
        case 6: return point(i-1,j);
        case 7: return point(i-1,j-1);
        default: return point(i,j);
    }
}
ConCom::ConCom(TBitmap* bitmap)
{
     curComp = 0;
     _map = bitmap;
     m = _map->Width;
     n = _map->Height;

     _matrix = new int*[m];
     for(int i=0; i<m; i++) _matrix[i] = new int[n];

     for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
           _matrix[i][j]=0;

}
ConCom::~ConCom()
{
    for(int i=0; i<m; i++) delete []_matrix[i];
    delete []_matrix;
}
void ConCom::FindComponent(int iStart, int jStart)
{
    queue<point> _queue;
    list<point> _donePoints;
    if (_map->Canvas->Pixels[iStart][jStart] == clBlack)
    {
        _donePoints.push_front(point(iStart,jStart));
        _matrix[iStart][jStart] = curComp;
        for(int i=0;i<8;i++)
            if (HasNear(i,iStart,jStart) && GetClrNear(i,iStart,jStart) == clBlack )
            {
                point pt = GetNear(i,iStart,jStart);
                _queue.push(pt);
            }
        while(!_queue.empty())
        {
            point pt = _queue.front();

            for(int i=0;i<8;i++)
                if (HasNear(i,pt.i,pt.j) && GetClrNear(i,pt.i,pt.j) == clBlack
                                            && _matrix[pt.i][pt.j] == 0)
                    _queue.push(GetNear(i,pt.i,pt.j));

            _matrix[pt.i][pt.j] = curComp;
            _donePoints.push_front(pt);
            _queue.pop();
        }

        int maxX = 0;
        int maxY = 0;
        int minX = m - 1;
        int minY = n - 1;
        list<point>::iterator it;
        for(it = _donePoints.begin(); it != _donePoints.end(); it++)
            {
                point pt = (*it);
                if (pt.i>maxX) maxX = pt.i;
                if (pt.j>maxY) maxY = pt.j;
                if (pt.i<minX) minX = pt.i;
                if (pt.j<minY) minY = pt.j;
            }
        _listComp.push_back(ComInfo(minX,minY,maxX,maxY,curComp));

    }
}
void ConCom::StartSearch(TProgressBar* _bar)
{
    _bar->Max = n*m;
    _bar->Step = 1;
    for(int j=0;j<n;j++)
        for(int i=0;i<m;i++)
        {
            _bar->StepIt();
            if (_map->Canvas->Pixels[i][j] == clBlack && _matrix[i][j] == 0)
            {
                curComp++;
                FindComponent(i,j);
            }
        }
}
list<ComInfo> ConCom::GetComponents()
{
    _listComp.sort(comporator);
    return _listComp;
}
void ConCom::DrawComponent(TBitmap* bitmap)
{
    list<ComInfo>::iterator it;
    for(it=_listComp.begin(); it!=_listComp.end(); it++)
    {
        (*it).Draw(bitmap);
    }
}



//---------------------------------------------------------------------------
