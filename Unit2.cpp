//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <IniFiles.hpp>
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
extern int mode; //1=terms;2=help
extern AnsiString Dir_for_file;
int start_f2;
//---------------------------------------------------------------------------
void init_form(TForm2 *f)
{
 if (mode==1 || mode==2)
 {
  f->Width=600;
  f->Height=550;
  f->Left=Screen->Width-f->Width;
  f->Top=0;

  f->ListBox1->Left=0;
  f->ListBox1->Height=0;
  f->ListBox1->Width=f->Width-28;
  f->ListBox1->Height=f->Height-18;
  f->VertScrollBar->Visible=0;
  f->HorzScrollBar->Visible=0;
  f->Visible=1;
 }
 if (mode==1)
  f->Caption="Словарь";
 if (mode==2)
 f->Caption="Справка";
}

TStringList* read(String filename)
{
  
   TStringList *list=new TStringList; //return text from file
   AnsiString FilePath=Dir_for_file;
   try{
       list->LoadFromFile(FilePath+"\\"+filename+".txt");
       }
   catch (EFOpenError&)
     {
       list->Add("Данные не найдены.");
     }
   return list;

}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
 ListBox1->Font->Size=12;
 start_f2=1;
 init_form(Form2);
 AnsiString text="first";
 ListBox1->Clear();
 if (mode==1)
  {
     ListBox1->Items=read("terms");
  }

 if (mode==2)
  {
     ListBox1->Items=read("help");
  }

 start_f2=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCanResize(TObject *Sender, int &NewWidth,
      int &NewHeight, bool &Resize)
{
 if (start_f2==0)
  Resize=0;
}
//---------------------------------------------------------------------------

