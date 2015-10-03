//---------------------------------------------------------------------------

#ifndef MainAlgorithmH
#define MainAlgorithmH

#include "Structs.h"
#include "Incapsulators.h"
#include <list>
#include <vector>
#include <map>
//---------------------------------------------------------------------------

class DashComp
{
private:

    // Массив из списков для штриховых файлов
    std::list<dash>* hor;
    std::list<dash>* ver;
    // Информация о компoненте
    cc_info cc;
public:
    DashComp(const inc::Picture &bmp,cc_info c);
    ~DashComp();
    std::list<dash> getLine(int j);
    std::list<dash> getColumn(int i);
    int width() const;
    int height() const;
    moments get_moment(int v, int h, int p);
    moments get_moment_disp(int v, int h, int p, int disp, bool ver);
};

class LetterBase
{
private:
       	std::map<wchar_t,moments> base;
        inc::Table *table;
        inc::Informator *inf;
        int vc; int hc;

public:
	static double min_delta;
        static bool use_delta;
        int getV();
        int getH();
	LetterBase(inc::Table &t,inc::Informator &i);
	wchar_t GetLetter(moments m);
       	moments GetMoments(wchar_t c);
      	void AddLetter(wchar_t c, moments m);
        void DelLetter(wchar_t c);
        void Load(TBinaryReader *br);
        void Save(TBinaryWriter *bw);
        void Clear();
        void Refresh();
        void Draw();
};

// Класс для хранения общей структуры текста
class TextData
{
private:
    // Массив-вектор из компонент-букв
    std::vector<cc_info> vec;
    DashComp** dashs;
    // Вспомогательные классы для взаимодействия с пользователем
    inc::Informator *inf;
    inc::Printer *p;
    // Средняя высота и ширина буквы
    float avrHaight;
    float avrWidth;
    // Список индексов структурировнного текста
    std::list<int> text;
    int pm;
    wchar_t getLetter(DashComp* dashfile,LetterBase &lb, int disp);
    int ind_by_id(int id);
public:
    TextData(inc::Informator &infr,inc::Printer &pr);
    ~TextData();
    void reload(std::list<cc_info> l);
    bool comp_loaded();
    void dashCreate(const inc::Picture &bmp);
    void printDashs(int i, bool ver);
    void printDashsE(int i, bool ver);
    bool dash_created();
    int size();
    cc_info operator[] (int i);
    moments get_moments(int i, int v, int h);
    int get_ind(int x, int y);
    void remove_all_as_min(int ind);
    void organazeText();
    bool is_organaized();
    void printText();
    void printOriginalText(LetterBase &lb);
    void printOriginalTextNew(LetterBase &lb, int disp);
};



std::list<cc_info> search_comp(const inc::Picture &bmp, inc::Informator &inf);
double get_moment(std::list<dash> dashs, int p);
double get_e_moment(std::list<dash> dashs, int length, int p);
double get_normal_moment(std::list<dash> dashs, int p);
double get_center_x(std::list<dash> dashs);
double get_center_moment(std::list<dash> dashs, int p);
double get_center_normal_moment(std::list<dash> dashs, int p);
#endif
