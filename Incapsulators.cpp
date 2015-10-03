//---------------------------------------------------------------------------

#pragma hdrstop

#include "Incapsulators.h"
#include <map>
#include <iterator>
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace inc {

    void Picture::set(TBitmap* img)
    {
        bmp = img;
    }
    void Picture::set_view(TImage* img)
    {
        view = img;
        view->Picture->Graphic = bmp;
        view->Canvas->Draw(0, 0, bmp);
    }
    Picture::Picture()
    {
	bmp = NULL;
    }
    int Picture::width() const
    {
        return bmp->Width;
    }
    int Picture::height() const
    {
        return bmp->Height;
    }
    bool Picture::isBlack(int i, int j) const
    {
        if (bmp->Canvas->Pixels[i][j] == clBlack) return true;
        else return false;
    }
    bool Picture::inArea(int i, int j) const
    {
        return (i>=0 && i<bmp->Width && j>=0 && j<bmp->Height);
    }
    bool Picture::isBlack(point p) const
    {
        if (bmp->Canvas->Pixels[p.i][p.j] == clBlack) return true;
        else return false;
    }
    bool Picture::inArea(point p) const
    {
        return (p.i>=0 && p.i<bmp->Width && p.j>=0 && p.j<bmp->Height);
    }
    void Picture::draw(cc_info cc)
    {
        view->Canvas->Font->Color = clBlue;
        view->Canvas->Font->Size = 6;
        view->Canvas->TextOut(cc.x_min+1,cc.y_min+1,IntToStr(cc.id));
        view->Canvas->Pen->Color = clRed;
        view->Canvas->MoveTo(cc.x_min,cc.y_min);
        view->Canvas->LineTo(cc.x_min,cc.y_max);
        view->Canvas->LineTo(cc.x_max,cc.y_max);
        view->Canvas->LineTo(cc.x_max,cc.y_min);
        view->Canvas->LineTo(cc.x_min,cc.y_min);
    }
    void Picture::draw_moments(cc_info cc,int v, int h)
    {
        for(int i=0;i<v;i++)
        {
            int r =  moment_info::get_ratio(i+1,v)*cc.width();
            view->Canvas->Pen->Color = clGreen;
            view->Canvas->MoveTo(cc.x_min+r,cc.y_min);
            view->Canvas->LineTo(cc.x_min+r,cc.y_max);
        }
        for(int i=0;i<h;i++)
        {
            int r =  moment_info::get_ratio(i+1,h)*cc.height();
            view->Canvas->Pen->Color = clGreen;
            view->Canvas->MoveTo(cc.x_min,cc.y_min+r);
            view->Canvas->LineTo(cc.x_max,cc.y_min+r);
        }
    }
    void Picture::refresh()
    {
        view->Picture->Graphic = bmp;
        view->Canvas->Draw(0, 0, bmp);
    }



    void Informator::set(TProgressBar* bp, TStatusBar* sp)
    {
        bar = bp;
        st = sp->Panels->Items[1];

    }
    void Informator::set_graph(TFastLineSeries *m,TFastLineSeries *c)
    {
    	fstln_m = m;
        fstln_c = c;
    }
    void Informator::set_point_graph(TPointSeries *pnt_graph)
    {
        pnt = pnt_graph;
    }
    Informator::Informator()
    {
        bar = NULL;
        st = NULL;
    }
    void Informator::setMax(int max)
    { bar->Max = max; }
    void Informator::setStep(int step)
    { bar->Step = step; }
    void Informator::stepIt()
    { bar->StepIt(); }
    void Informator::message(std::string msg)
    { st->Text = msg.c_str(); }
    void Informator::done(std::string msg)
    {
        bar->Position = 0;
        st->Text = msg.c_str();
    }
    void Informator::send_msg(std::string msg)
    {
        ShowMessage(msg.c_str());
    }
    void Informator::draw_clear()
    {
    	fstln_c->Clear();
        fstln_m->Clear();
       	fstln_c->DrawBetweenPoints = true;
        fstln_c->AutoRepaint = false;
        fstln_m->DrawBetweenPoints = true;
        fstln_m->AutoRepaint = false;
    }
    void Informator::draw_refresh()
    {
    	//fstln_c->AutoRepaint = true;
        //fstln_m->AutoRepaint = true;
        fstln_c->Repaint();
        fstln_m->Repaint();
    }
    void Informator::draw_points(std::map<wchar_t,moments> base)
    {
        for (std::map<wchar_t,moments>::iterator it=base.begin(); it!=base.end(); ++it)
        {
            pnt->AddXY(it->second.ver.val[0],it->second.hor.val[0],it->first,RGB(random(255),random(255),random(255)));
        }
    }
    void Informator::draw(double x, double y, bool center)
    {
        if (!center) fstln_m->AddXY(x,y,"",clRed);
        else fstln_c->AddXY(x,y,"",clGreen);
    }


    // point
    point::point(int I,int J)
        :i(I),j(J) { }
    bool operator ==(const point &a,const point &b)
    {
        return (a.i==b.i && a.j==b.j);
    }
    point point::operator+(const point& a) const
    {
        return point(a.i+i,a.j+j);
    }
    AnsiString point::to_str() const
    {
        return "("+IntToStr(i)+","+IntToStr(j)+")";
    }

    Printer::Printer ()
    {

    }
    void Printer::set(TStrings* ts)
    {
        st = ts;
    }
    void Printer::add(std::string str)
    {
        st->Add(str.c_str());
    }
    void Printer::add(std::wstring str)
    {
    	st->Add(str.c_str());
    }
    void Table::set(TStringGrid* strngrd)
    {
    	s = strngrd;
    }
    void Table::refresh(std::map<wchar_t,moments> base,int v, int h)
    {
    	s->ColCount = 1; s->RowCount = 1;
        s->ColCount = v + h + 1;
        s->ColWidths[0] = 25;
        switch (v) {
        case 1: { s->Cells[1][0] = "V(1/2)"; break; }
            case 2: {
                        s->Cells[1][0] = "V(1/3)";
                        s->Cells[2][0] = "V(2/3)";
                        break;
                    }
            case 3: {
                        s->Cells[1][0] = "V(1/4)";
                        s->Cells[2][0] = "V(1/2)";
                        s->Cells[3][0] = "V(3/4)";
                        break;
                    }
            default: break;
        }
        switch (h) {
            case 1: { s->Cells[1+v][0] = "H(1/2)"; break; }
            case 2: {
                        s->Cells[1+v][0] = "H(1/3)";
                        s->Cells[2+v][0] = "H(2/3)";
                        break;
                    }
            case 3: {
                        s->Cells[1+v][0] = "H(1/4)";
                        s->Cells[2+v][0] = "H(1/2)";
                        s->Cells[3+v][0] = "H(3/4)";
                        break;
                    }
            default: break;
        }
        for (std::map<wchar_t,moments>::iterator it=base.begin(); it!=base.end(); ++it)
        {
            moments m = it->second;
            s->RowCount++;
            s->Cells[0][s->RowCount-1] = AnsiString(it->first);
            for(int i=0;i<m.ver.count;i++)
            {
                s->Cells[1+i][s->RowCount-1]
                	= FloatToStrF(float(m.ver.val[i]),ffFixed,7,4);
                if (moments::center) {
                    s->Cells[1+i][s->RowCount-1]
                	= s->Cells[1+i][s->RowCount-1]
                        + " (" + FloatToStrF(float(m.ver.cen[i]),ffFixed,5,3) + ")";
                    s->ColWidths[1+i] = s->DefaultColWidth+25;
                }
            }
            for(int i=0;i<m.hor.count;i++)
            {
                s->Cells[1+m.ver.count+i][s->RowCount-1]
                	= FloatToStrF(float(m.hor.val[i]),ffFixed,7,4);
                if (moments::center) {
                    s->Cells[1+m.ver.count+i][s->RowCount-1]
                	= s->Cells[1+m.ver.count+i][s->RowCount-1]
                        + " (" + FloatToStrF(float(m.hor.cen[i]),ffFixed,5,3) + ")";
                    s->ColWidths[1+m.ver.count+i] = s->DefaultColWidth+25;
                }
            }
        }
    }
}

