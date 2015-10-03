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

// Класс для распознования общей структуры текста
class TextStruct
{
private:
    // Массив-вектор из компонент-букв
    std::vector<ComInfo> _vec;
    // Средняя высота буквы
    int _avrSize;
    // Средняя ширина буквы
    float _avrStep;
    // Минимальный объём буквы
    int _minVolume;
    // Список индексов структурировнного текста
    std::list<int> _text;
    // Порядок моментов
    float p;

    bool IsMin(ComInfo i);
public:

    TextStruct(std::list<ComInfo> l);
    // Возвращает строку с номерами букв в массиве в-векторе
    void PrintVectorIDs(TStrings* lines);
    // Число букв
    int LetterCount();
    ComInfo GetComp(int i);
    // Устанавливет i-ую компоненту как компоненту минимального объёма
    void SetMinimumComp(int i);
    // Удалает меньшие компоненты
    void ClearMinimum();
    // Формирует структуру текста
    void CreateTextStructue(TStrings* lines);
    std::list<int> GetText();
    int GetCompByNum(int num);
    int GetIndexByYX(int x, int y);
    moments GetMoment(int i,TBitmap* map,int v, int h);
    void StartProcess(TProgressBar* _bar, LetterBase* base,TStrings* lines,TBitmap* map,int v,int h);

};
//---------------------------------------------------------------------------
#endif
