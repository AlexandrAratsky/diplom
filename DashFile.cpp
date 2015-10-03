//---------------------------------------------------------------------------

#pragma hdrstop
#include <math.h>
#include "DashFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------

using namespace std;

float DashFile::MomentV(int i,int p)
{
    float f = 0;
    list<dash>::iterator it;
    for(it=_fileV[i].begin(); it!=_fileV[i].end(); it++)
        f=f+powf(float((*it).finish+1),float(p+1))-powf(float((*it).start),float(p+1));
    f = f / (p+1);
    return f;
}
float DashFile::MomentH(int j,int p)
{
    float f = 0;
    list<dash>::iterator it;
    for(it=_fileH[j].begin(); it!=_fileH[j].end(); it++)
        f=f+powf(float((*it).finish+1),float(p+1))-powf(float((*it).start),float(p+1));
    f = f / (p+1);
    return f;
}
DashFile::DashFile(TBitmap* map, ComInfo info)
{
    sW = info.MinX(); sH = info.MinY();
    fW = info.MaxX(); fH = info.MaxY();
    w = fW - sW + 1;
    h = fH - sH + 1;
//        ShowMessage("Start dashfile constructor:\n" +
//        	info.GetNumber() + " [ " +  IntToStr(sW) + " "
//                +  IntToStr(sH) + " " +  IntToStr(fW)+ " " +  IntToStr(fH) + "]");
    _fileV = new list<dash>[w];
    _fileH = new list<dash>[h];
    // Создаём вертикальный штриховой файл
    for(int i=sW;i<=fW;i++)
    {
        int s = -1;
        for(int j=sH;j<=fH;j++)
            if (map->Canvas->Pixels[i][j] == clBlack)
             { if (s<0) s = j - sH; }
            else if (s>=0)
             {
                 _fileV[i-sW].push_back(dash(i,s,j-sH-1));
                 s=-1;
             }
        if (s>=0) _fileV[i-sW].push_back(dash(i,s,fH-sH));
    }
    // Создаём горизонтальный штриховой файл
    for(int j=sH;j<=fH;j++)
    {
        int s = -1;
        for(int i=sW;i<=fW;i++)
            if (map->Canvas->Pixels[i][j] == clBlack)
             { if (s<0) s = i - sW; }
            else if (s>=0)
             {
                 _fileH[j-sH].push_back(dash(j,s,i-sW-1));
                 s=-1;
             }
        if (s>=0) _fileH[j-sH].push_back(dash(j,s,fW-sW));
    }
}
DashFile::~DashFile()
{
    delete[] _fileV;
    delete[] _fileH;
}
int DashFile::GetWidth() { return w; }
int DashFile::GetHeight() { return h; }
AnsiString  DashFile::GetInfo(int i,bool v)
{
    AnsiString str = IntToStr(i) + ":";
    list<dash>::iterator it;
    if (v) for(it=_fileV[i].begin(); it!=_fileV[i].end(); it++)
            str+=(*it).to_str().c_str();
    else for(it=_fileH[i].begin(); it!=_fileH[i].end(); it++)
            str+=(*it).to_str().c_str();
    return str;
}
float DashFile::NormalMomentV(int i,int p)
{
    float mZero = powf(MomentV(i,0),float(p+1));
    return MomentV(i,p) / (mZero == 0 ? 1 : mZero);
}
float DashFile::NormalMomentH(int i,int p)
{
    float mZero = powf(MomentH(i,0),float(p+1));
    return MomentH(i,p) / (mZero == 0 ? 1 : mZero);
}
float DashFile::PNormalMomentV(int i,int p)
{
    return powf(NormalMomentV(i,p),1/float(p+1));
}
float DashFile::PNormalMomentH(int i,int p)
{
    return powf(NormalMomentH(i,p),1/float(p+1));
}

