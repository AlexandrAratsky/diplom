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


// Класс для распознования растровых компонент
class ConCom
{
private:

    int** _matrix; // Матрица с номерами компонент
    TBitmap* _map; // Растровое изображение
    std::list<ComInfo> _listComp; // Список компонент
    int n; int m; // Размерность изображения
    int curComp; // Текущая компонента для разбора

    // Внутренние функции
    bool InArea(int i, int j);
    bool HasNear(int count, int i, int j);
    TColor GetClrNear(int count, int i, int j);
    inc::point GetNear(int count, int i, int j);

public:
    ConCom(TBitmap* bitmap);
    ~ConCom();
    // Поиск компоненты с начальной точки
    void FindComponent(int iStart, int jStart);
    // Полный поиск по всему изображению
    void StartSearch(TProgressBar* _bar);
    // Возвращает список компонент
    std::list<ComInfo> GetComponents();
    // Отрисовывает все компоненты на растре
    void DrawComponent(TBitmap* bitmap);

};

//---------------------------------------------------------------------------
#endif
