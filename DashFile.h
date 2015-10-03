//---------------------------------------------------------------------------

#ifndef DashFileH
#define DashFileH
//---------------------------------------------------------------------------
#include <list>
#include <vcl.h>
#include <Vcl.Graphics.hpp>
#include "ComponentInfo.h"
#include "Structs.h"



class DashFile
{
private:
    // ������ � ������ ������
    int w;
    int h;
    // ������ �� ������� ��� ��������� ������
    std::list<dash>* _fileH;
    std::list<dash>* _fileV;
    // ���������� ������ �������� � ������� ������� ����� ������������� ���������� ������
    int sW,fW,sH,fH;
    // ������� ������������� ������� i-��� ������� ������� p
    float MomentV(int i,int p);
    // ������� ��������������� ������� j-�� ������ ������� p
    float MomentH(int j,int p);
public:
    DashFile(TBitmap* map, ComInfo info);
    ~DashFile();
    int GetWidth();
    int GetHeight();
    AnsiString  GetInfo(int i,bool v = true);
    float NormalMomentV(int i,int p);
    float NormalMomentH(int i,int p);
    float PNormalMomentV(int i,int p);
    float PNormalMomentH(int i,int p);

};

//---------------------------------------------------------------------------
#endif
