//---------------------------------------------------------------------------

#ifndef TextResolverH
#define TextResolverH

#include "Structs.h"
#include <vcl.h>
#include <vector>
#include <list>
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------

//// Класс для распознования общей структуры текста
//class TextResolver
//{
//private:
//    // Массив-вектор из компонент-букв
//    std::vector<cc_info> vec;
//    // Средняя высота буквы
//    float avr_height;
//    // Средняя ширина буквы
//    float avr_width;
//    // Минимальный объём буквы
//    int min_val;
//    // Список индексов структурировнного текста
//    std::list<int> text;
//    // Порядок моментов
//    int p;
//
//    bool is_min(int i);
//public:
//
//    TextResolver(std::list<cc_info> l);
//    // Возвращает строку с номерами букв в массиве в-векторе
//    void PrintVectorIDs(TStrings* lines);
//    // Число букв
//    int CompCount();
//    cc_info GetComp(int i);
//    // Устанавливет i-ую компоненту как компоненту минимального объёма
//    void SetAsMinimumComp(int i);
//    // Удалает меньшие компоненты
//    void ClearMinimum();
//    // Формирует структуру текста
//    void CreateTextStructue(TStrings* lines);
//    int GetIndByID(int num);
//    int GetIndexByYX(int x, int y);
//    moments GetMoment(int i,TBitmap* map,int v, int h);
//    void StartProcess(TProgressBar* _bar, LetterBase* base,TStrings* lines,TBitmap* map,int v,int h);
//
//};

#endif
