//---------------------------------------------------------------------------
#include <Vcl.Graphics.hpp>
#include <Vcl.Grids.hpp>
#include <vcl.h>
#include <string>
#include <map>
#include "Structs.h"
#include "MainAlgorithm.h"
#include "perfgrap.h"
#include <Vcl.Samples.Gauges.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeeShape.hpp>
#ifndef IncapsulatorsH
#define IncapsulatorsH
//---------------------------------------------------------------------------

namespace inc {

    struct point {
        const int i;
        const int j;
        point(int I,int J);
        friend bool operator ==(const point &a,const point &b);
        point operator+(const point& a) const;
        AnsiString to_str() const;
    };

    class Picture {
    private:
        TBitmap* bmp;
        TImage* view;
    public:
    	Picture();
        void set(TBitmap* bmp);
        void set_view(TImage* img);
        int width() const;
        int height() const;
        bool isBlack(int i, int j) const;
        bool inArea(int i, int j) const;
        bool isBlack(point p) const;
        bool inArea(point p) const;
        void draw(cc_info cc);
        void draw_moments(cc_info cc,int v, int h);
        void refresh();
    };

    class Informator {
    private:
        TProgressBar* bar;
        TStatusPanel* st;
        TFastLineSeries *fstln_m;
        TFastLineSeries *fstln_c;
        TPointSeries *pnt;
        int s;
    public:
        void set(TProgressBar* bp, TStatusBar* sp);
        void set_graph(TFastLineSeries *m,TFastLineSeries *c);
        void set_point_graph(TPointSeries *pnt_graph);
        Informator();
        void setMax(int max);
        void setStep(int step);
        void stepIt();
        void done(std::string msg);
        void message(std::string msg);
        void send_msg(std::string msg);
        void draw_clear();
        void draw_refresh();
        void draw_points(std::map<wchar_t,moments> base);
        void draw(double x, double y, bool center);
    };

    class Printer {
    private:
        TStrings* st;
    public:
        Printer();
        void set(TStrings* ts);
        void add(std::string str);
        void add(std::wstring str);
    };

    class Table {
    private:
    TStringGrid* s;
    public:
        void set(TStringGrid* strngrd);
        void refresh(std::map<wchar_t,moments> base,int v, int h);

    };
}

//---------------------------------------------------------------------------
#endif
