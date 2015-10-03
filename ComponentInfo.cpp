//---------------------------------------------------------------------------

#pragma hdrstop

#include "ComponentInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace std;

ComInfo::ComInfo(int minX, int minY, int maxX,int maxY,int number)
{
    _minX = minX;
    _minY = minY;
    _maxX = maxX;
    _maxY = maxY;
    _num = number;
}
void ComInfo::Draw(TBitmap* _map)
{
    _map->Canvas->Font->Color = clBlue;
    _map->Canvas->TextOut(_minX+1,_minY+1,IntToStr(_num));
    _map->Canvas->Pen->Color = clRed;
    _map->Canvas->MoveTo(_minX,_minY);
    _map->Canvas->LineTo(_minX,_maxY);
    _map->Canvas->LineTo(_maxX,_maxY);
    _map->Canvas->LineTo(_maxX,_minY);
    _map->Canvas->LineTo(_minX,_minY);
}
AnsiString ComInfo::GetID()
{
    return IntToStr(_num);
}
int ComInfo::MinX() { return _minX; }
int ComInfo::MinY() { return _minY; }
int ComInfo::MaxX() { return _maxX; }
int ComInfo::MaxY() { return _maxY; }
int ComInfo::ID() { return _num; }
bool ComInfo::OnLine(int y)
{
    if (_minY<=y && _maxY>=y) return true;
    else return false;
}
bool ComInfo::OnColumn(int x)
{
    if (_minX<=x && _maxX>=x) return true;
    else return false;
}
int ComInfo::GetCenterY()
{
    return (_maxY+_minY)/2;
}
int ComInfo::GetCenterX()
{
    return (_maxX+_minX)/2;
}

bool operator ==(const ComInfo &a,const ComInfo &b) { return a._num==b._num; }
//---------------------------------------------------------------------------
