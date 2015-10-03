//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>

#include "Structs.h"
#include "Incapsulators.h"
#include "MainAlgorithm.h"
#include "perfgrap.h"
#include <Vcl.Samples.Gauges.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeeShape.hpp>


#include <list>
//---------------------------------------------------------------------------
class TMForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *menu;
	TToolBar *tool_bar;
	TToolButton *tb_btn_1;
	TToolButton *tb_btn_2;
	TStatusBar *status_bar;
	TPageControl *pg_ctrl;
	TTabSheet *ts_base;
	TTabSheet *ts_main;
	TSplitter *spltr;
	TTabSheet *ts_result;
	TMenuItem *mn_file;
	TMenuItem *mni_open;
	TMenuItem *mn_save;
	TMenuItem *N1;
	TMenuItem *mn_exit;
	TImageList *image_list;
	TScrollBox *scrlbx;
	TImage *img;
	TToolBar *tlb_base;
	TEdit *edt_base;
	TToolButton *btn_base_open;
	TToolButton *btn_base_save;
	TToolButton *btn_base_new;
	TToolButton *ToolButton1;
	TComboBox *cbb_letter;
	TToolButton *btn_add_letter;
	TRadioGroup *rg_vertical;
	TRadioGroup *rg_horizontal;
	TEdit *edt_letter;
	TGroupBox *grp_table;
	TToolButton *ToolButton2;
	TToolButton *btn_del_letter;
	TStringGrid *strngrd;
	TToolButton *ToolButton3;
	TToolButton *btn_set_as_min;
	TComboBox *cbb_list_letter;
	TToolButton *btn_start_search;
	TOpenPictureDialog *dlg_open_pic;
	TToolButton *ToolButton5;
	TToolButton *btn_reload;
	TToolButton *btn_draw_comp;
	TToolBar *tlb_main;
	TToolButton *btn_clear_text;
	TToolButton *btn2;
	TProgressBar *progress_bar;
	TMenuItem *mni_options;
	TMenuItem *mni_center_heavy;
	TComboBox *cbb_algorithm;
	TEdit *edt_lambda;
	TToolButton *ToolButton4;
	TToolButton *btn_start;
	TToolButton *ToolButton6;
	TGroupBox *GroupBox1;
	TRichEdit *redt;
	TSaveDialog *dlg_save;
	TOpenDialog *dlg_open;
	TToolButton *btn6;
	TMenuItem *mniN2;
	TToolButton *btn_start_struct;
	TToolButton *btn3;
	TToolButton *btn5;
	TEdit *edt_heavy;
	TSaveTextFileDialog *dlg_save_txt;
	TEdit *edt_min_delta;
	TToolButton *btn1;
	TChart *cht;
	TFastLineSeries *fstln_m;
	TFastLineSeries *fstln_c;
	TToolBar *tlb1;
	TToolButton *btn4;
	TToolButton *btn7;
	TEdit *edt1;
	TToolButton *btn8;
	TToolButton *btn9;
	TFastLineSeries *fstln_m_last;
	TFastLineSeries *fstln_c_last;
	TToolButton *btn10;
	TToolButton *btn_e;
	TToolButton *btn11;
	TGroupBox *grp1;
	TEdit *edt_a1;
	TButton *btn12;
	TEdit *edt_a2;
	TEdit *edt_a3;
	TChartShape *chrtshp_a1;
	TChartShape *chrtshp_a2;
	TChartShape *chrtshp_a3;
	TLabel *lbl1;
	TEdit *edt2;
	TEdit *edt3;
	TEdit *edt4;
	TTabSheet *ts_classes;
	TToolBar *tlb2;
	TToolButton *btn13;
	TChart *cht1;
	TPointSeries *pnt;
	void __fastcall tb_btn_1Click(TObject *Sender);
	void __fastcall mni_openClick(TObject *Sender);
	void __fastcall btn_reloadClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall imgDblClick(TObject *Sender);
	void __fastcall btn_set_as_minClick(TObject *Sender);
	void __fastcall btn_base_newClick(TObject *Sender);
	void __fastcall btn_add_letterClick(TObject *Sender);
	void __fastcall btn_del_letterClick(TObject *Sender);
	void __fastcall status_barResize(TObject *Sender);
	void __fastcall btn_start_searchClick(TObject *Sender);
	void __fastcall btn_draw_compClick(TObject *Sender);
	void __fastcall btn2Click(TObject *Sender);
	void __fastcall btn3Click(TObject *Sender);
	void __fastcall btn4Click(TObject *Sender);
	void __fastcall btn_base_saveClick(TObject *Sender);
	void __fastcall btn_base_openClick(TObject *Sender);
	void __fastcall mniN2Click(TObject *Sender);
	void __fastcall btn_clear_textClick(TObject *Sender);
	void __fastcall btn_start_structClick(TObject *Sender);
	void __fastcall btn_startClick(TObject *Sender);
	void __fastcall mni_center_heavyClick(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall btn7Click(TObject *Sender);
	void __fastcall btn12Click(TObject *Sender);
	void __fastcall chrtshp_a1DblClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall fstln_mDblClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall chrtshp_a2DblClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall chrtshp_a3DblClick(TChartSeries *Sender, int ValueIndex, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall btn13Click(TObject *Sender);
	void __fastcall cbb_algorithmChange(TObject *Sender);



private:
	bool creatingBase;
        int mom_num;
        int vCount;
        int hCount;
	TBitmap* bmp;
        inc::Picture pic;
        inc::Informator inf;
        inc::Printer pr;
        inc::Table table;
        TextData td;
        LetterBase lb;
        void SetCreateBaseInterface(bool enabled);
        void ReDrawGraph();
        void SetLines();

        

public:		// User declarations
	__fastcall TMForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMForm *MForm;
//---------------------------------------------------------------------------
#endif
