//---------------------------------------------------------------------------

#ifndef StructsH
#define StructsH
#include <string>
//---------------------------------------------------------------------------
// Структура, содержащая информацию по связной компоненте растра
struct cc_info {
    const unsigned short id;
    const int x_min;
    const int x_max;
    const int y_min;
    const int y_max;

    cc_info(int x1, int y1, int x2, int y2);
    int width() const;
    int height() const;
    bool in_line(int y) const;
    bool in_column(int x) const;
    bool in_area(int x, int y) const;
    int center_y() const;
    int center_x() const;
    std::string to_str() const;
    int volume();
    static int counter();
    static void reset_counter();

    cc_info operator=(const cc_info& a);
    friend bool operator ==(const cc_info &a,const cc_info &b);

private:
    static unsigned short count;
    cc_info(int x1, int y1, int x2, int y2,int id);
};
//---------------------------------------------------------------------------
// Структура, хранящая штрих
struct dash {
    const int level;
    const int start;
    const int finish;
    dash(int l,int s,int f);
    int length() const;
    std::string to_str() const;
    double moment(int p) const;
    double center_moment(int p, double x) const;
    double e_moment(int p, double length) const;
};

//---------------------------------------------------------------------------
// Структура хранящая моменты
struct moment_info {
    static float get_ratio(int i, int count);
    double val[3];
    double cen[3];
    const int count;
    moment_info(int c);
    moment_info(double center);
    moment_info(double left, double right);
    moment_info(double left, double center, double right);
};

struct moments {
    moment_info ver;
    moment_info hor;
    static bool center;
    static float center_heavy;
    moments(const moment_info v, const moment_info h)
    	:ver(v), hor(h) { }
    std::string to_str() const;
};
#endif
