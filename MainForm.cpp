//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "Structs.h"
#include "MainAlgorithm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "perfgrap"
#pragma resource "*.dfm"
TMForm *MForm;
//---------------------------------------------------------------------------
__fastcall TMForm::TMForm(TComponent* Owner)
	: TForm(Owner), td(inf,pr), lb(table,inf)
{
    bmp = new Graphics::TBitmap;
    creatingBase = false;
    progress_bar->Parent = status_bar;
    status_bar->Panels->Items[0]->Width = status_bar->Width - 250;
    inf.set(progress_bar,status_bar);
    inf.set_graph(fstln_m,fstln_c);
    inf.set_point_graph(pnt);
    table.set(strngrd);
    pr.set(redt->Lines);
    edt_heavy->Text = FloatToStrF(moments::center_heavy,ffFixed,5,3);
    edt_min_delta->Text = FloatToStrF(LetterBase::min_delta,ffFixed,7,5);
}
// Открывает изображение
void __fastcall TMForm::tb_btn_1Click(TObject *Sender)
{
    if (dlg_open_pic->Execute())
    {
        bmp->LoadFromFile(dlg_open_pic->FileName);
        pic.set(bmp);
        pic.set_view(img);
    }
}
// Открывает изображение
void __fastcall TMForm::mni_openClick(TObject *Sender)
{
        if (dlg_open_pic->Execute())
        {
            bmp->LoadFromFile(dlg_open_pic->FileName);
            pic.set(bmp);
            pic.set_view(img);
        }
}
// Подгружает исходное изображение на форму
void __fastcall TMForm::btn_reloadClick(TObject *Sender)
{
	pic.refresh();
}
// Деструктор
void __fastcall TMForm::FormDestroy(TObject *Sender)
{
	if (bmp) delete bmp;
}
// Включает интерфейс создания базы
void TMForm::SetCreateBaseInterface(bool enabled)
{
	cbb_letter->Enabled = enabled;
        edt_letter->Enabled = enabled;
        btn_add_letter->Enabled = enabled;
        btn_del_letter->Enabled = enabled;
        rg_horizontal->Enabled = !enabled;
        rg_vertical->Enabled = !enabled;
}
// Выбор компоненты
void __fastcall TMForm::imgDblClick(TObject *Sender)
{
    if (td.comp_loaded())
    {
        TPoint p = img->ScreenToClient(Mouse->CursorPos);
        cbb_list_letter->ItemIndex = td.get_ind((p.x),int(p.y));
        if (creatingBase) {
        	cbb_letter->ItemIndex = td.get_ind((p.x),int(p.y));
        }
        edt1->Text = td[cbb_list_letter->ItemIndex].to_str().c_str();
    }
}
// Устанавить минимальную компоненту
void __fastcall TMForm::btn_set_as_minClick(TObject *Sender)
{
    if (cbb_list_letter->ItemIndex>=0)
    {
        td.remove_all_as_min(cbb_list_letter->ItemIndex);
        cbb_list_letter->Items->Clear();
        for(int i=0;i<td.size();i++)
            {
                cbb_list_letter->Items->Add(td[i].to_str().c_str());
            }
        cbb_list_letter->ItemIndex = 0;

    }
}
// Создать базу
void __fastcall TMForm::btn_base_newClick(TObject *Sender)
{
        vCount = rg_vertical->ItemIndex + 1;
        hCount = rg_horizontal->ItemIndex + 1;
	creatingBase = true;
        SetCreateBaseInterface(creatingBase);
        cbb_letter->Clear();
	for(int i=0;i<td.size();i++)
        { cbb_letter->Items->Add("[" + IntToStr(td[i].id) + "]"); }
        cbb_letter->ItemIndex = 0;
}

void __fastcall TMForm::btn_add_letterClick(TObject *Sender)
{
    wchar_t letter = edt_letter->Text.c_str()[0];
    moments m = td.get_moments(cbb_letter->ItemIndex,vCount,hCount);
    lb.AddLetter(letter,m);
    pic.draw_moments(td[cbb_letter->ItemIndex],vCount,hCount);
}
//---------------------------------------------------------------------------


void __fastcall TMForm::btn_del_letterClick(TObject *Sender)
{
    wchar_t letter = edt_letter->Text.c_str()[0];
    lb.DelLetter(letter);
}
//---------------------------------------------------------------------------






// Изменение размеров формы
void __fastcall TMForm::status_barResize(TObject *Sender)
{
    status_bar->Panels->Items[0]->Width = status_bar->Width - 250;
    RECT Rect;
    status_bar->Perform (SB_GETRECT,0,(LPARAM)&Rect );

    progress_bar->Top = Rect.top;
    progress_bar->Left = Rect.left;
    progress_bar->Width = status_bar->Panels->Items [0]->Width;
    progress_bar->Height = Rect.bottom - Rect.top;
}
//---------------------------------------------------------------------------




void __fastcall TMForm::btn_start_searchClick(TObject *Sender)
{

    td.reload(search_comp(pic,inf));
    for(int i=0;i<td.size();i++) pic.draw(td[i]);
    for(int i=0;i<td.size();i++)
    {
        cbb_list_letter->Items->Add(td[i].to_str().c_str());
    }
    cbb_list_letter->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMForm::btn_draw_compClick(TObject *Sender)
{
    for(int i=0;i<td.size();i++) pic.draw(td[i]);
}
//---------------------------------------------------------------------------

void __fastcall TMForm::btn2Click(TObject *Sender)
{
	td.dashCreate(pic);
}
//---------------------------------------------------------------------------



void __fastcall TMForm::btn3Click(TObject *Sender)
{
    moments::center_heavy = (float) edt_heavy->Text.ToDouble();
    edt_heavy->Text = FloatToStrF(moments::center_heavy,ffFixed,5,3);
}
//---------------------------------------------------------------------------

void __fastcall TMForm::btn4Click(TObject *Sender)
{
    if (btn10->Down) ReDrawGraph();
    else {
        fstln_m_last->Clear();
        fstln_c_last->Clear();
    }
    td.printDashs(cbb_list_letter->ItemIndex,false);
    cht->Title->Text->Text = "Горизонтальные моменты";
}
//---------------------------------------------------------------------------





void __fastcall TMForm::btn_base_saveClick(TObject *Sender)
{
    if (td.comp_loaded()) {
        if(dlg_save->Execute()) {
            TFileStream *output = new TFileStream(dlg_save->FileName + ".lb", fmCreate);
            TBinaryWriter *bin = new TBinaryWriter(output,TEncoding::ANSI);
            lb.Save(bin);
            bin->Free();
            output->Free();
            edt_base->Text = dlg_save->FileName;
        }
    } else ShowMessage("Загрузите изображение!");
}
//---------------------------------------------------------------------------

void __fastcall TMForm::btn_base_openClick(TObject *Sender)
{
    if (td.comp_loaded()) {
        if(dlg_open->Execute()) {
            TFileStream *input = new TFileStream(dlg_open->FileName, fmOpenRead);
            TBinaryReader *bin = new TBinaryReader(input,TEncoding::ANSI,false);
            lb.Load(bin);
            bin->Free();
            input->Free();
            creatingBase = true;
            SetCreateBaseInterface(creatingBase);
            cbb_letter->Clear();
            for(int i=0;i<td.size();i++)
            { cbb_letter->Items->Add("[" + IntToStr(td[i].id) + "]"); }
            cbb_letter->ItemIndex = 0;
            edt_base->Text = dlg_open->FileName;
            btn_base_new->Enabled = false;
            rg_vertical->ItemIndex = lb.getV()-1;
            rg_horizontal->ItemIndex = lb.getH()-1;
            vCount = rg_vertical->ItemIndex + 1;
            hCount = rg_horizontal->ItemIndex + 1;
        }
    } else ShowMessage("Загрузите изображение!");
}
//---------------------------------------------------------------------------

void __fastcall TMForm::mniN2Click(TObject *Sender)
{
    lb.Clear();
    cbb_letter->Clear();
    creatingBase = false;
    SetCreateBaseInterface(creatingBase);
}
//---------------------------------------------------------------------------




void __fastcall TMForm::btn_clear_textClick(TObject *Sender)
{
    redt->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TMForm::btn_start_structClick(TObject *Sender)
{
    if (!td.is_organaized()) td.organazeText();
    td.printText();
}
//---------------------------------------------------------------------------

void __fastcall TMForm::btn_startClick(TObject *Sender)
{
switch (cbb_algorithm->ItemIndex) {
    case 0: if (!td.is_organaized()) td.organazeText();
            LetterBase::use_delta = true;
            td.printOriginalText(lb); break;
    case 1: if (!td.is_organaized()) td.organazeText();
            LetterBase::use_delta = false;
            td.printOriginalText(lb); break;
    case 2: if (!td.is_organaized()) td.organazeText();
            td.printOriginalTextNew(lb,edt_lambda->Text.ToInt()); break;
    default: break;
}
}
//---------------------------------------------------------------------------


void __fastcall TMForm::mni_center_heavyClick(TObject *Sender)
{
    moments::center = mni_center_heavy->Checked;
    lb.Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TMForm::btn1Click(TObject *Sender)
{
    LetterBase::min_delta = edt_min_delta->Text.ToDouble();
    edt_min_delta->Text = FloatToStrF(LetterBase::min_delta,ffFixed,7,5);
}
//---------------------------------------------------------------------------



void TMForm::ReDrawGraph()
{
    fstln_m_last->Clear();
    fstln_m_last->AutoRepaint = false;
    for(int i=0;i<fstln_m->XValues->Count;i++)
    fstln_m_last->AddNullXY(fstln_m->XValues->operator [](i),fstln_m->YValues->operator [](i),"");
    fstln_m_last->AutoRepaint = true;
    fstln_c_last->Clear();
    fstln_c_last->AutoRepaint = false;
    for(int i=0;i<fstln_c->XValues->Count;i++)
    fstln_c_last->AddNullXY(fstln_c->XValues->operator [](i),fstln_c->YValues->operator [](i),"");
    fstln_c_last->AutoRepaint = true;
}
void TMForm::SetLines()
{
    chrtshp_a1->X0 = edt_a1->Text.ToDouble();
    chrtshp_a1->X1 = edt_a1->Text.ToDouble();
    chrtshp_a1->Y0 = 0;
    chrtshp_a1->Y1 = System::Math::Max(1.0,System::Math::Max(fstln_m->MaxYValue(),fstln_m_last->MaxYValue()));
    chrtshp_a1->Repaint();

    chrtshp_a2->X0 = edt_a2->Text.ToDouble();
    chrtshp_a2->X1 = edt_a2->Text.ToDouble();
    chrtshp_a2->Y0 = 0;
    chrtshp_a2->Y1 = System::Math::Max(1.0,System::Math::Max(fstln_m->MaxYValue(),fstln_m_last->MaxYValue()));
    chrtshp_a2->Repaint();

    chrtshp_a3->X0 = edt_a3->Text.ToDouble();
    chrtshp_a3->X1 = edt_a3->Text.ToDouble();
    chrtshp_a3->Y0 = 0;
    chrtshp_a3->Y1 = System::Math::Max(1.0,System::Math::Max(fstln_m->MaxYValue(),fstln_m_last->MaxYValue()));
    chrtshp_a3->Repaint();
}
void __fastcall TMForm::btn7Click(TObject *Sender)
{
    if (btn10->Down) ReDrawGraph();
    else {
        fstln_m_last->Clear();
        fstln_c_last->Clear();
    }
    td.printDashs(cbb_list_letter->ItemIndex, true);
    cht->Title->Text->Text = "Вертикальные моменты";
}
//---------------------------------------------------------------------------
void __fastcall TMForm::btn12Click(TObject *Sender)
{
    SetLines();
}
//---------------------------------------------------------------------------







void __fastcall TMForm::chrtshp_a1DblClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    mom_num = 1;
    lbl1->Caption = "- 1 -";
}
//---------------------------------------------------------------------------


void __fastcall TMForm::fstln_mDblClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
switch (mom_num) {

case 1: edt_a1->Text = fstln_m->XValues->ValueToString(ValueIndex);
    chrtshp_a1->X0 = fstln_m->XValues->operator [](ValueIndex);
    chrtshp_a1->X1 = fstln_m->XValues->operator [](ValueIndex);
    chrtshp_a1->Y0 = 0;
    chrtshp_a1->Y1 = System::Math::Max(1.0,System::Math::Max(fstln_m->MaxYValue(),fstln_m_last->MaxYValue()));
    chrtshp_a1->Repaint();
    break;
case 2: edt_a2->Text = fstln_m->XValues->ValueToString(ValueIndex);
    chrtshp_a2->X0 = fstln_m->XValues->operator [](ValueIndex);
    chrtshp_a2->X1 = fstln_m->XValues->operator [](ValueIndex);
    chrtshp_a2->Y0 = 0;
    chrtshp_a2->Y1 = System::Math::Max(1.0,System::Math::Max(fstln_m->MaxYValue(),fstln_m_last->MaxYValue()));
    chrtshp_a2->Repaint();
    break;
case 3: edt_a3->Text = fstln_m->XValues->ValueToString(ValueIndex);
    chrtshp_a3->X0 = fstln_m->XValues->operator [](ValueIndex);
    chrtshp_a3->X1 = fstln_m->XValues->operator [](ValueIndex);
    chrtshp_a3->Y0 = 0;
    chrtshp_a3->Y1 = System::Math::Max(1.0,System::Math::Max(fstln_m->MaxYValue(),fstln_m_last->MaxYValue()));
    chrtshp_a3->Repaint();
    break;
default: break;
}
}
//---------------------------------------------------------------------------

void __fastcall TMForm::chrtshp_a2DblClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    mom_num = 2;
    lbl1->Caption = "- 2 -";
}
//---------------------------------------------------------------------------

void __fastcall TMForm::chrtshp_a3DblClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
    mom_num = 3;
    lbl1->Caption = "- 3 -";
}
//---------------------------------------------------------------------------




void __fastcall TMForm::btn13Click(TObject *Sender)
{
    lb.Draw();
}
//---------------------------------------------------------------------------

void __fastcall TMForm::cbb_algorithmChange(TObject *Sender)
{
if (cbb_algorithm->ItemIndex == 2) {
    edt_lambda->Enabled = true;
} else {
    edt_lambda->Enabled = false;
}
}
//---------------------------------------------------------------------------

