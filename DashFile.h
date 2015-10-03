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
    // Ширина и высота растра
    int w;
    int h;
    // Массив из списков для штриховых файлов
    std::list<dash>* _fileH;
    std::list<dash>* _fileV;
    // Координаты левого верхнего и нижнего правого углов прямоугольной компоненты растра
    int sW,fW,sH,fH;
    // Функция вертикального момента i-ого столбца порядка p
    float MomentV(int i,int p);
    // Функция горизонтального момента j-ой строки порядка p
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
