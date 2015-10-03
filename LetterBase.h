//---------------------------------------------------------------------------

#ifndef LetterBaseH
#define LetterBaseH
//---------------------------------------------------------------------------
#include "Structs.h"
#include <vcl.h>
#include <map>
#include <Vcl.Grids.hpp>

struct moments
{
	int vlen;
        int hlen;
        float v[3];
        float h[3];

        moments(int vcount, int hcount): vlen(vcount), hlen(hcount) { }
};

class LetterBase
{
private:
       	std::map<wchar_t,moments> base;

public:

	void CreateTable(TStringGrid* strngrd,int v,int h);
	wchar_t GetLetter(moments m);
       	moments GetMoments(wchar_t c);
      	void AddLetter(wchar_t c, moments m);
        void DelLetter(wchar_t c);
};


//---------------------------------------------------------------------------
#endif
