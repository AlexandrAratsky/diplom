//---------------------------------------------------------------------------
#pragma hdrstop

#include "TextStructure.h"
#include <iterator>
#include <algorithm>
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace std;

bool comp(ComInfo& first,ComInfo& second)
{
	return (first.GetCenterX()>second.GetCenterX());
}

bool TextStruct::IsMin(ComInfo i)
{
    if ((i.MaxX()-i.MinX())*(i.MaxY()-i.MinY()) < _minVolume) return true;
    else return false;
}

TextStruct::TextStruct(list<ComInfo> l)
{
    float size = 0; float step = 0;
    _vec.reserve(l.size());
    list<ComInfo>::iterator it;
    for(it=l.begin(); it!=l.end(); it++)
        _vec.push_back(*it);
    for(unsigned int i=0;i<_vec.size();i++)
    {
        size+=_vec[i].MaxY()-_vec[i].MinY();
        step+=_vec[i].MaxX()-_vec[i].MinX();
    }
    _avrSize = int(size/_vec.size());
    _avrStep = int(step/_vec.size());

    p = 2;
}
void TextStruct::PrintVectorIDs(TStrings* lines)
{
    AnsiString str = "";
    for(int i=0;i<_vec.size();i++)
    {
        str+=_vec[i].GetID() + ", ";
    }
    lines->Add("comp[" + IntToStr(int(_vec.size())) + "] {" + str + "}");
}
int TextStruct::LetterCount()
{
    return _vec.size();
}
ComInfo TextStruct::GetComp(int i)
{
    return _vec[i];
}
void TextStruct::SetMinimumComp(int i)
{
    _minVolume = (_vec[i].MaxX()-_vec[i].MinX())*(_vec[i].MaxY()-_vec[i].MinY());
}
void TextStruct::ClearMinimum()
{
    int i = 0;
    while (i<_vec.size())
    {
        if (IsMin(_vec[i]))
        {
            _vec.erase(_vec.begin()+i);
        }
        else { ++i; }
    }
}
void TextStruct::CreateTextStructue(TStrings* lines)
{
    vector<ComInfo> tmp(_vec);
    while(tmp.size()>0)
    {
        list<ComInfo> _line;
        int lineY = tmp[0].GetCenterY();
        for(int i=0;i<tmp.size();i++)
            if (tmp[i].OnLine(lineY)) _line.push_back(tmp[i]);

        //sort(_line.begin(), _line.end(), comp);
        //_line.sort(comporator);

        list<ComInfo>::iterator it;
        for(it=_line.begin(); it!=_line.end(); it++)
        {
            int pos = GetCompByNum((*it).ID());
            _text.push_back(pos);
            list<ComInfo>::iterator nx = it; nx++;
            if (nx != _line.end())
                if (abs((*nx).GetCenterX()-(*it).GetCenterX())>1.5*_avrStep)
                    _text.push_back(-1);
            tmp.erase(remove(tmp.begin(),tmp.end(),*it),tmp.end());
        }
        _text.push_back(-2);
    }

    if (lines!=NULL)
    {
        AnsiString str = "";
        list<int>::iterator t;
        for(t=_text.begin(); t!=_text.end(); t++)
        {
            if (*t>=0) str+="[" + IntToStr(*t) + "]";
            else if (*t==-1) str+="  ";
            else
            {
                lines->Add(str);
                str = "";
            }
        }
    }

}
list<int> TextStruct::GetText()
{
    return _text;
}
int TextStruct::GetCompByNum(int num)
{
    for(int i=0;i<_vec.size();i++)
        if (_vec[i].ID() == num) return i;
    return -1;
}
int TextStruct::GetIndexByYX(int x, int y)
{
    for(int i=0;i<_vec.size();i++)
        if (_vec[i].OnColumn(x) && _vec[i].OnLine(y)) return i;
    return 0;
}
//---------------------------------------------------------------------------
// Возвращиет соотношения моментов
float GetFloat(int num, int max)
{
    if (max==1) return 1.0/2;
    if (max==2)
    {
        switch (num) {
           case 1: return 1.0/3;
           case 2: return 2.0/3;
           default: return -1;
        }
    }
    if (max==3)
    {
        switch (num) {
           case 1: return 1.0/4;
           case 2: return 2.0/4;
           case 3: return 3.0/4;
           default: return -1;
        }
    }
    return -1;
}

//---------------------------------------------------------------------------
moments TextStruct::GetMoment(int i,TBitmap* map,int v, int h)
{
    moments val = moments(v,h);
    DashFile* df = new DashFile(map,_vec[i]);
    for(int i=0;i<v;i++)
    {
        float m = df->PNormalMomentV((int)(GetFloat(i+1,v)*df->GetWidth()),p);
        val.v[i] = m;
    }
    for(int i=0;i<h;i++)
    {
        float m = df->PNormalMomentH((int)(GetFloat(i+1,h)*df->GetHeight()),p);
        val.h[i] = m;
    }
    delete df;
    return val;
}
void TextStruct::StartProcess(TProgressBar* _bar, LetterBase* base,TStrings* lines,TBitmap* map,int v, int h)
{
    _bar->Max = _text.size();
    _bar->Step = 1;
    AnsiString str = "";
    list<int>::iterator t;
    for(t=_text.begin(); t!=_text.end(); t++)
    {

        if (*t>=0)
        {
            moments m = GetMoment(*t,map,v,h);
            wchar_t letter = base->GetLetter(m);
            str+=AnsiString(letter);
        }
        else if (*t==-1) str+=" ";
        else
        {
            lines->Add(str);
            str = "";
        }
        _bar->StepIt();
    }

}
