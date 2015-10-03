//---------------------------------------------------------------------------

#ifndef TextStructureH
#define TextStructureH
//---------------------------------------------------------------------------
#include "ComponentInfo.h"
#include "DashFile.h"
#include "LetterBase.h"
#include <vcl.h>
#include <vector>
#include <list>
#include <Vcl.Graphics.hpp>

// ����� ��� ������������� ����� ��������� ������
class TextStruct
{
private:
    // ������-������ �� ���������-����
    std::vector<ComInfo> _vec;
    // ������� ������ �����
    int _avrSize;
    // ������� ������ �����
    float _avrStep;
    // ����������� ����� �����
    int _minVolume;
    // ������ �������� ����������������� ������
    std::list<int> _text;
    // ������� ��������
    float p;

    bool IsMin(ComInfo i);
public:

    TextStruct(std::list<ComInfo> l);
    // ���������� ������ � �������� ���� � ������� �-�������
    void PrintVectorIDs(TStrings* lines);
    // ����� ����
    int LetterCount();
    ComInfo GetComp(int i);
    // ������������ i-�� ���������� ��� ���������� ������������ ������
    void SetMinimumComp(int i);
    // ������� ������� ����������
    void ClearMinimum();
    // ��������� ��������� ������
    void CreateTextStructue(TStrings* lines);
    std::list<int> GetText();
    int GetCompByNum(int num);
    int GetIndexByYX(int x, int y);
    moments GetMoment(int i,TBitmap* map,int v, int h);
    void StartProcess(TProgressBar* _bar, LetterBase* base,TStrings* lines,TBitmap* map,int v,int h);

};
//---------------------------------------------------------------------------
#endif
