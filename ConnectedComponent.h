//---------------------------------------------------------------------------

#ifndef ConnectedComponentH
#define ConnectedComponentH
//---------------------------------------------------------------------------
#include "ComponentInfo.h"
#include "Incapsulators.h"
#include "Structs.h"
#include <Vcl.Graphics.hpp>
#include <vcl.h>
#include <list>


// ����� ��� ������������� ��������� ���������
class ConCom
{
private:

    int** _matrix; // ������� � �������� ���������
    TBitmap* _map; // ��������� �����������
    std::list<ComInfo> _listComp; // ������ ���������
    int n; int m; // ����������� �����������
    int curComp; // ������� ���������� ��� �������

    // ���������� �������
    bool InArea(int i, int j);
    bool HasNear(int count, int i, int j);
    TColor GetClrNear(int count, int i, int j);
    inc::point GetNear(int count, int i, int j);

public:
    ConCom(TBitmap* bitmap);
    ~ConCom();
    // ����� ���������� � ��������� �����
    void FindComponent(int iStart, int jStart);
    // ������ ����� �� ����� �����������
    void StartSearch(TProgressBar* _bar);
    // ���������� ������ ���������
    std::list<ComInfo> GetComponents();
    // ������������ ��� ���������� �� ������
    void DrawComponent(TBitmap* bitmap);

};

//---------------------------------------------------------------------------
#endif
