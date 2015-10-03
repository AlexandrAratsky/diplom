//---------------------------------------------------------------------------

#ifndef ComponentInfoH
#define ComponentInfoH
//---------------------------------------------------------------------------
#include <Vcl.Graphics.hpp>

// ���������� � ��������� ���������� (�����)
class ComInfo
{
private:
        // ���������� �������� ������ � ������� ������� ����
	int _minX,_minY,_maxX,_maxY;
        // ID �����
        int _num;
public:
	ComInfo(int minX, int minY, int maxX,int maxY,int number);
        friend bool operator ==(const ComInfo &a,const ComInfo &b);

        void Draw(TBitmap* _map);
        AnsiString GetID();
        int MinX();
        int MinY();
        int MaxX();
        int MaxY();
        int ID();
        bool OnLine(int y);
        bool OnColumn(int x);
        int GetCenterY();
        int GetCenterX();
};

//---------------------------------------------------------------------------
#endif
