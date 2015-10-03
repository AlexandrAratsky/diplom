//---------------------------------------------------------------------------

#pragma hdrstop

#include "LetterBase.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;

void LetterBase::AddLetter(wchar_t c, moments m)
{
	base.insert(pair<wchar_t,moments>(c,m));

}
//---------------------------------------------------------------------------
moments LetterBase::GetMoments(wchar_t c)
{
       	return base.find(c)->second;
}
//---------------------------------------------------------------------------
wchar_t LetterBase::GetLetter(moments m)
{
	wchar_t letter = '?';
        float minDelta = 10.0;
	for (map<wchar_t,moments>::iterator it=base.begin(); it!=base.end(); ++it)
        {
        	if (it->second.vlen!=m.vlen || it->second.hlen!=m.hlen) continue;
                float delta = 0;
                for(int i=0;i<m.vlen;i++)
                {
                    delta += (float) fabs(it->second.v[i]-m.v[i]);
                }
                for(int i=0;i<m.hlen;i++)
                {
                    delta += (float) fabs(it->second.h[i]-m.h[i]);
                }
                if (minDelta>delta)
                {
                    letter = it->first;
                    minDelta = delta;
                }

        }
        return letter;

}
//---------------------------------------------------------------------------

void LetterBase::CreateTable(TStringGrid* strngrd, int v, int h)
{
    strngrd->ColCount = v + h + 1;
    strngrd->ColWidths[0] = 25;
    switch (v) {
    case 1: { strngrd->Cells[1][0] = "V(1/2)"; break; }
        case 2: {
                    strngrd->Cells[1][0] = "V(1/3)";
                    strngrd->Cells[2][0] = "V(2/3)";
                    break;
                }
        case 3: {
                    strngrd->Cells[1][0] = "V(1/4)";
                    strngrd->Cells[2][0] = "V(1/2)";
                    strngrd->Cells[3][0] = "V(3/4)";
                    break;
                }
        default: break;
    }
    switch (h) {
        case 1: { strngrd->Cells[1+v][0] = "H(1/2)"; break; }
        case 2: {
                    strngrd->Cells[1+v][0] = "H(1/3)";
                    strngrd->Cells[2+v][0] = "H(2/3)";
                    break;
                }
        case 3: {
                    strngrd->Cells[1+v][0] = "H(1/4)";
                    strngrd->Cells[2+v][0] = "H(1/2)";
                    strngrd->Cells[3+v][0] = "H(3/4)";
                    break;
                }
        default: break;
    }
    for (map<wchar_t,moments>::iterator it=base.begin(); it!=base.end(); ++it)
    {
        moments m = it->second;
        strngrd->RowCount++;
        strngrd->Cells[0][strngrd->RowCount-1] = AnsiString(it->first);
        for(int i=0;i<m.vlen;i++)
        {
            strngrd->Cells[1+i][strngrd->RowCount-1] = FloatToStrF(m.v[i],ffFixed,7,4);
        }
        for(int i=0;i<m.hlen;i++)
        {
            strngrd->Cells[1+m.vlen+i][strngrd->RowCount-1] = FloatToStrF(m.h[i],ffFixed,7,4);
        }
    }
}
//---------------------------------------------------------------------------
void LetterBase::DelLetter(wchar_t c)
{
    base.erase(c);
}
