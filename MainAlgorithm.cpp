//---------------------------------------------------------------------------

#pragma hdrstop
#define N_STEP 8
#include "MainAlgorithm.h"
#include <queue>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;
using namespace inc;

point step(int num)
{
     switch (num) {
        case 0: return point(0,-1);
        case 1: return point(1,-1);
        case 2: return point(1,0);
        case 3: return point(1,1);
        case 4: return point(0,1);
        case 5: return point(-1,1);
        case 6: return point(-1,0);
        case 7: return point(-1,-1);
        default: return point(0,0);
    }
}

list<cc_info> search_comp(const Picture &bmp, Informator &inf)
{
    bool** mat;
    list<cc_info> cc_list;

    mat = new bool*[bmp.width()];
    for(int i=0; i<bmp.width(); i++) mat[i] = new bool[bmp.height()];

    for(int i=0; i<bmp.width(); i++)
        for(int j=0; j<bmp.height(); j++)
            mat[i][j]=false;

    inf.setMax(bmp.width()*bmp.height());
    inf.setStep(1);
    for(int j=0;j<bmp.height();j++)
        for(int i=0;i<bmp.width();i++)
        {
            if (bmp.isBlack(i,j) && !mat[i][j])
            {
                queue<point> q;
                int maxX = 0; int maxY = 0;
                int minX = bmp.width() - 1; int minY = bmp.height() - 1;
                point ps = point(i,j);
                if (bmp.isBlack(ps))
                {
                    q.push(ps);
                    mat[ps.i][ps.j] = true;
                    while(!q.empty())
                    {
                        point pt = q.front();
                        for(int i=0;i<N_STEP;i++)
                        {
                            point tmp = pt+step(i);
                            if (bmp.inArea(tmp) && bmp.isBlack(tmp) && !mat[tmp.i][tmp.j])
                               {
                                   q.push(tmp);
                                   mat[tmp.i][tmp.j] = true;
                               }
                        }
                        q.pop();
                        if (pt.i>maxX) maxX = pt.i;
                        if (pt.j>maxY) maxY = pt.j;
                        if (pt.i<minX) minX = pt.i;
                        if (pt.j<minY) minY = pt.j;
                    }
                    cc_info comp(minX,minY,maxX,maxY);
                    cc_list.push_back(comp);
                }
            }
            inf.stepIt();
        }
    for(int i=0; i<bmp.width(); i++) delete []mat[i];
    delete []mat;
    std::stringstream out;
    out<<cc_list. size()<<" компонент обработано.";
    inf.done(out.str());
    return cc_list;
}

//---------------------------------------------------------------------------

TextData::TextData(inc::Informator &infr,inc::Printer &pr)
{
    inf = &infr;
    p = &pr;
    pm = 2;
}
void TextData::reload(std::list<cc_info> l)
{
    float size = 0; float step = 0;
    vec.clear();
    vec.reserve(l.size());
    list<cc_info>::iterator it;
    for(it=l.begin(); it!=l.end(); it++)
        vec.push_back(*it);
    for(unsigned int i=0;i<vec.size();i++)
    {
        size+=vec[i].y_max - vec[i].y_min + 1;
        step+=vec[i].x_max - vec[i].x_min + 1;
    }
    avrHaight = size/vec.size();
    avrWidth = step/vec.size();
    inf->message("Компоненты обновлены!");
}
bool TextData::comp_loaded()
{
    if (vec.size()>0) return true;
    else return false;
}
bool TextData::dash_created()
{
    return (dashs!=NULL);
}
int TextData::size()
{
    return vec.size();
}
cc_info TextData::operator[] (int i)
{
    return vec[i];
}
int TextData::get_ind(int x, int y)
{
    for(int i=0;i<vec.size();i++)
        if (vec[i].in_area(x,y)) return i;
    return 0;

}
void TextData::remove_all_as_min(int ind)
{
    inf->setMax(vec.size());
    inf->setStep(1);
    vector<cc_info> nv(vec);
    vec.clear();
    int v = vec[ind].volume();
    for(int i=0;i<nv.size();i++)
    {
    	int n = nv[i].id;
    	int j = nv[i].volume();
        if (j>=v) vec.push_back(nv[i]);
        inf->stepIt();
    }
    inf->message("Удалены компоненты меньше заданного" );
}

bool comp_x(const cc_info& first,const cc_info& second)
{
    return (first.center_x()<second.center_x());
}
bool comp_y(const cc_info& first,const cc_info& second)
{
    return (first.center_y()<second.center_y());
}

void TextData::organazeText()
{
    inf->setMax(vec.size());
    inf->setStep(1);
    list<cc_info> letters;
    for(int i=0;i<vec.size();i++) letters.push_back(vec[i]);
    text.clear();
    while(letters.size()>0)
    {
        letters.sort(comp_y);

        list<cc_info> line;
        int y = letters.front().center_y();

        list<cc_info>::iterator i;
        for(i=letters.begin(); i!=letters.end(); i++)
            if (i->in_line(y))
            {
            	line.push_back(*i);
                inf->stepIt();
            }

        line.sort(comp_x);

        list<cc_info>::iterator it;
        for(it=line.begin(); it!=line.end(); it++)
        {
            int pos = it->id;
            text.push_back(pos);
            list<cc_info>::iterator nx = it; nx++;
            if (nx != line.end())
                if (abs(nx->x_min-it->x_max)>0.25*avrWidth)
                    text.push_back(-1);
            letters.remove(*it);
        }
        text.push_back(-2);
        inf->done("Текст разбит по структуре!");
    }
}
bool TextData::is_organaized()
{
    if (text.size()>0) return true;
    else return false;
}
void TextData::printText()
{
    p->add("-+-+-+-");
    std::stringstream out;
    list<int>::iterator t;
    for(t=text.begin(); t!=text.end(); t++)
    {
        if (*t>=0) out<<"["<<*t<<"]";
        else if (*t==-1) out<<"  ";
        else
        {
            p->add(out.str().c_str());
            out.str("");
        }
    }
}
void TextData::dashCreate(const inc::Picture &bmp)
{
    inf->setMax(vec.size());
    inf->setStep(1);
    dashs = new DashComp*[vec.size()];
    for(int i=0;i<vec.size();i++)
    {
    	dashs[i] = new DashComp(bmp,vec[i]);
        inf->stepIt();
    }
    inf->done("Созданы штриховые изображения!");
}
void TextData::printDashs(int i, bool ver)
{
  if (ver) {
    inf->draw_clear();
    for(int j=0;j<dashs[i]->width();j++)
    {
        inf->draw(double(j)/dashs[i]->width(),
            get_normal_moment(dashs[i]->getColumn(j),pm),false);
        inf->draw(double(j)/dashs[i]->width(),
            get_center_x(dashs[i]->getColumn(j))/dashs[i]->height(),true);
    }
    inf->draw_refresh();
  } else {
    inf->draw_clear();
    for(int j=0;j<dashs[i]->height();j++)
    {
        inf->draw(double(j)/dashs[i]->height(),
            get_normal_moment(dashs[i]->getLine(j),pm),false);
        inf->draw(double(j)/dashs[i]->height(),
            get_center_x(dashs[i]->getLine(j))/dashs[i]->width(),true);
    }
    inf->draw_refresh();
  }
    
}
void TextData::printDashsE(int i, bool ver)
{
  if (ver) {
    inf->draw_clear();
    for(int j=0;j<dashs[i]->width();j++)
    {
        inf->draw(double(j)/dashs[i]->width(),
            get_e_moment(dashs[i]->getColumn(j),dashs[i]->height(), pm),false);
        inf->draw(double(j)/dashs[i]->width(),
            get_center_x(dashs[i]->getColumn(j))/dashs[i]->height(),true);
    }
    inf->draw_refresh();
  } else {
    inf->draw_clear();
    for(int j=0;j<dashs[i]->height();j++)
    {
        inf->draw(double(j)/dashs[i]->height(),
            get_e_moment(dashs[i]->getLine(j),dashs[i]->width(), pm),false);
        inf->draw(double(j)/dashs[i]->height(),
            get_center_x(dashs[i]->getLine(j))/dashs[i]->width(),true);
    }
    inf->draw_refresh();
  }
}
TextData::~TextData()
{
    if (dashs!=NULL) {
    	for(int i=0;i<vec.size();i++) delete dashs[i];
        delete []dashs;
        //inf->send_msg("Штрихи удалены");
    }
}
int TextData::ind_by_id(int id)
{
    for(int i=0;i<vec.size();i++)
        if (vec[i].id == id) return i;
    return 0;
}
void TextData::printOriginalText(LetterBase &lb)
{
    p->add("-+-+-+-");
    std::wstringstream out;
    int v = lb.getV();
    int h = lb.getH();
    list<int>::iterator t;
    for(t=text.begin(); t!=text.end(); t++)
    {
        if (*t>=0) out<<lb.GetLetter(dashs[ind_by_id(*t)]->get_moment(v,h,pm));
        else if (*t==-1) out<<" ";
        else
        {
            p->add(out.str());
            out.str(L"");
        }
    }
}
wchar_t TextData::getLetter(DashComp* dashfile, LetterBase &lb, int disp)
{
    int v = lb.getV();
    int h = lb.getH();
    std::map<wchar_t,int> letters;
    for(int i = - disp; i<=disp; i+=disp)
    {
        wchar_t letter = lb.GetLetter(dashfile->get_moment_disp(v,h,pm,i,true));
        if (letters.count(letter)==1) letters[letter]++;
        else letters.insert(pair<wchar_t,int>(letter,1));
    }
    for(int i = - disp; i<=disp; i+=disp)
    {
        wchar_t letter = lb.GetLetter(dashfile->get_moment_disp(v,h,pm,i,false));
        if (letters.count(letter)==1) letters[letter]++;
        else letters.insert(pair<wchar_t,int>(letter,1));
    }
    int max = 0; wchar_t l;
    for (map<wchar_t,int>::iterator it=letters.begin(); it!=letters.end(); ++it)
    {
    	if (it->second>max) {
            max = it->second;
            l = it->first;
        }
    }
    return l;
}
void TextData::printOriginalTextNew(LetterBase &lb, int disp)
{
    p->add("-+-+-+-");
    std::wstringstream out;
    int v = lb.getV();
    int h = lb.getH();
    list<int>::iterator t;
    for(t=text.begin(); t!=text.end(); t++)
    {
        if (*t>=0) out<<getLetter(dashs[*t],lb,disp);
        else if (*t==-1) out<<" ";
        else
        {
            p->add(out.str());
            out.str(L"");
        }
    }
}
moments TextData::get_moments(int j, int v, int h)
{
	return dashs[j]->get_moment(v,h,pm);
}

//---------------------------------------------------------------------------

DashComp::DashComp(const inc::Picture &bmp,cc_info c): cc(c)
{
    ver = new list<dash>[cc.width()];
    hor = new list<dash>[cc.height()];
    // Создаём вертикальный штриховой файл
    for(int i=cc.x_min;i<=cc.x_max;i++)
    {
        int s = -1;
        for(int j=cc.y_min;j<=cc.y_max;j++)
            if (bmp.isBlack(i,j))
             { if (s<0) s = j - cc.y_min; }
            else if (s>=0)
             {
                 ver[i-cc.x_min].push_back(dash(i-cc.x_min,s,j-cc.y_min-1));
                 s=-1;
             }
        if (s>=0) ver[i-cc.x_min].push_back(dash(i-cc.x_min,s,cc.y_max-cc.y_min));
    }
    // Создаём горизонтальный штриховой файл
    for(int j=cc.y_min;j<=cc.y_max;j++)
    {
        int s = -1;
        for(int i=cc.x_min;i<=cc.x_max;i++)
            if (bmp.isBlack(i,j))
             { if (s<0) s = i - cc.x_min; }
            else if (s>=0)
             {
                 hor[j-cc.y_min].push_back(dash(j-cc.y_min,s,i-cc.x_min-1));
                 s=-1;
             }
        if (s>=0) hor[j-cc.y_min].push_back(dash(j-cc.y_min,s,cc.x_max-cc.x_min));
    }
}
DashComp::~DashComp()
{
    delete[] ver;
    delete[] hor;
}
std::list<dash> DashComp::getLine(int j)
{
    return hor[j];
}
std::list<dash> DashComp::getColumn(int i)
{
    return ver[i];
}
int DashComp::width() const
{
    return cc.width();
}
int DashComp::height() const
{
    return cc.height();
}
moments DashComp::get_moment(int v, int h, int p)
{
    moments mom = moments(moment_info(v),moment_info(h));
    for(int i=0;i<v;i++)
    {
        int r =  moment_info::get_ratio(i+1,v)*cc.width();
        if (!moments::center) {
            mom.ver.val[i] = get_normal_moment(ver[r],p);
            mom.ver.cen[i] = 0;
        } else {
            //mom.ver.val[i] = get_center_normal_moment(ver[r],p);
            mom.ver.val[i] = get_normal_moment(ver[r],p);
            mom.ver.cen[i] = get_center_x(ver[r]) / height();
        }
    }
    for(int i=0;i<h;i++)
    {
        int r =  moment_info::get_ratio(i+1,h)*cc.height();
        if (!moments::center) {
            mom.hor.val[i] = get_normal_moment(hor[r],p);
            mom.hor.cen[i] = 0;
        } else {
            //mom.hor.val[i] = get_center_normal_moment(hor[r],p);
            mom.hor.val[i] = get_normal_moment(hor[r],p);
            mom.hor.cen[i] = get_center_x(hor[r]) / width();
        }
    }
    return mom;
}
moments DashComp::get_moment_disp(int v, int h, int p, int disp, bool vertical)
{
    moments mom = moments(moment_info(v),moment_info(h));
    for(int i=0;i<v;i++)
    {
        int r =  moment_info::get_ratio(i+1,v)*cc.width() + (vertical ? disp : 0);
        if (!moments::center) {
            mom.ver.val[i] = get_normal_moment(ver[r],p);
            mom.ver.cen[i] = 0;
        } else {
            //mom.ver.val[i] = get_center_normal_moment(ver[r],p);
            mom.ver.val[i] = get_normal_moment(ver[r],p);
            mom.ver.cen[i] = get_center_x(ver[r]) / height();
        }
    }
    for(int i=0;i<h;i++)
    {
        int r =  moment_info::get_ratio(i+1,h)*cc.height() + (vertical ? 0 : disp);
        if (!moments::center) {
            mom.hor.val[i] = get_normal_moment(hor[r],p);
            mom.hor.cen[i] = 0;
        } else {
            //mom.hor.val[i] = get_center_normal_moment(hor[r],p);
            mom.hor.val[i] = get_normal_moment(hor[r],p);
            mom.hor.cen[i] = get_center_x(hor[r]) / width();
        }
    }
    return mom;
}

//---------------------------------------------------------------------------

double get_moment(std::list<dash> dashs, int p)
{
    double m = 0;
    list<dash>::iterator it;
    for(it=dashs.begin(); it!=dashs.end(); it++)
    	m+=it->moment(p);
    return m;
}
double get_e_moment(std::list<dash> dashs,int length, int p)
{
    double m = 0;
    list<dash>::iterator it;
    for(it=dashs.begin(); it!=dashs.end(); it++)
    	m+=it->e_moment(p+1,length)*(p+1);
    return m;
}
double get_normal_moment(std::list<dash> dashs, int p)
{
    double m_zero = pow(get_moment(dashs,0),double(p+1));
    double n_moment = get_moment(dashs,p) / (m_zero == 0 ? 1 : m_zero);
    return pow(n_moment,1.0/double(p+1));
}
double get_center_x(std::list<dash> dashs)
{
    return get_moment(dashs,1)/get_moment(dashs,0);
}
double get_center_moment(std::list<dash> dashs, int p)
{
    double m = 0;
    double center = get_center_x(dashs);
    list<dash>::iterator it;
    for(it=dashs.begin(); it!=dashs.end(); it++)
    	m+=it->center_moment(p,center);
    return m;
}
double get_center_normal_moment(std::list<dash> dashs, int p)
{
    double m_zero = pow(get_moment(dashs,0),double(p+1));
    double n_moment = get_center_moment(dashs,p) / (m_zero == 0 ? 1 : m_zero);
    return pow(n_moment,1.0/double(p+1));
}

//---------------------------------------------------------------------------

LetterBase::LetterBase(inc::Table &t,inc::Informator &i)
{
    table = &t;
    inf = &i;
    vc = 0;
    hc = 0;
}
wchar_t LetterBase::GetLetter(moments m)
{
    wchar_t letter = '?';
    double minDelta = 100.0;
    for (map<wchar_t,moments>::iterator it=base.begin(); it!=base.end(); ++it)
    {
            if (it->second.ver.count!=m.ver.count
            	|| it->second.hor.count!=m.hor.count) continue;
            double delta = 0;
            for(int i=0;i<m.ver.count;i++)
            {
                delta += pow(abs(it->second.ver.val[i]-m.ver.val[i]),2.0);
            }
            for(int i=0;i<m.hor.count;i++)
            {
                delta += pow(abs(it->second.hor.val[i]-m.hor.val[i]),2.0);
            }
            delta = pow(delta,1.0/2);
            if (moments::center) {
            	double delta_c = 0;
            	for(int i=0;i<m.ver.count;i++)
                {
                    delta_c += pow(abs(it->second.ver.cen[i]-m.ver.cen[i]),2.0);
                }
                for(int i=0;i<m.hor.count;i++)
                {
                    delta_c += pow(abs(it->second.hor.cen[i]-m.hor.cen[i]),2.0);
                }
                if (use_delta) {
                    if (delta<min_delta) {
                        delta += pow(delta_c * moments::center_heavy,1.0/2) ;
                    }
                } else {
                    if (delta>min_delta) {
                        delta += pow(delta_c * moments::center_heavy,1.0/2) ;
                    }
                }

            }
            if (minDelta>delta)
            {
                letter = it->first;
                minDelta = delta;
            }
    }
    return letter;
}
moments LetterBase::GetMoments(wchar_t c)
{
    return base.find(c)->second;
}
void LetterBase::Draw()
{
    inf->draw_points(base);
}
void LetterBase::AddLetter(wchar_t c, moments m)
{
    base.insert(pair<wchar_t,moments>(c,m));
    vc = (m.ver.count>vc?m.ver.count:vc);
    hc = (m.hor.count>hc?m.hor.count:hc);
    std::stringstream out;
    table->refresh(base,vc,hc);
    out<<"Буква '"<<c<<"' добавлена в базу!";
    inf->message(out.str());
}
void LetterBase::DelLetter(wchar_t c)
{
    base.erase(c);
    std::stringstream out;
    table->refresh(base,vc,hc);
    out<<"Буква '"<<c<<"' удалена из базы!";
    inf->message(out.str());
}
int LetterBase::getV()
{ return vc; }
int LetterBase::getH()
{ return hc; }
void LetterBase::Load(TBinaryReader *br)
{
    std::stringstream out;
    vc = br->ReadInteger();
    hc = br->ReadInteger();
    int n = br->ReadInteger();
    base.clear();
    for(int i=0;i<n;i++)
    {
        wchar_t l = br->ReadChar();
        moments m = moments(moment_info(vc),moment_info(hc));
        for(int i=0;i<3;i++) m.ver.val[i] = br->ReadDouble();
        for(int i=0;i<3;i++) m.ver.cen[i] = br->ReadDouble();
        for(int i=0;i<3;i++) m.hor.val[i] = br->ReadDouble();
        for(int i=0;i<3;i++) m.hor.cen[i] = br->ReadDouble();
        base.insert(pair<wchar_t,moments>(l,m));
    }

    table->refresh(base,vc,hc);
    out<<"База загружена!";
    inf->message(out.str());
}
void LetterBase::Save(TBinaryWriter *bw)
{
    std::stringstream out;
    bw->Write(vc);
    bw->Write(hc);
    bw->Write((int) base.size());
    for (map<wchar_t,moments>::iterator it=base.begin(); it!=base.end(); ++it)
    {
    	out.str("");
    	bw->Write(it->first);
        for(int i=0;i<3;i++) bw->Write(it->second.ver.val[i]);
        for(int i=0;i<3;i++) bw->Write(it->second.ver.cen[i]);
        for(int i=0;i<3;i++) bw->Write(it->second.hor.val[i]);
        for(int i=0;i<3;i++) bw->Write(it->second.hor.cen[i]);
    }
    out<<"База сохронена!";
    inf->message(out.str());
}
void LetterBase::Clear()
{
    base.clear();
    table->refresh(base,vc,hc);
}
void LetterBase::Refresh()
{
    table->refresh(base,vc,hc);
}
double LetterBase::min_delta = 0.1;
bool LetterBase::use_delta = true;
//---------------------------------------------------------------------------





