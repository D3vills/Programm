//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <IniFiles.hpp>
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
int mode; //1=terms;2=help
AnsiString Dir_for_file;
String rates[5];
int answer;
int current_rate;
int current_q;
int num_of_rates;
bool start;

//---------------------------------------------------------------------------
void start_form_ini(TForm1 *f)//start form
{
 f->Caption="Начальное окно";
 f->Width=400;
 f->Height=200;
 //начать определение
 f->Button1->Visible=1;
 f->Button1->Width=300;
 f->Button1->Height=30;
 //термины
 f->Button3->Visible=1;
 f->Button3->Width=300;
 f->Button3->Height=30;
 f->Button3->Font->Size=12;
 f->Button3->Caption="Словарь";

 //справка
 f->Button4->Visible=1;
 f->Button4->Width=300;
 f->Button4->Height=30;
 f->Button4->Font->Size=12;
 f->Button4->Caption="Справка";

 f->Button1->Left=(f->Width-f->Button1->Width)/2;
 f->Button1->Top=3*(f->Height-f->Button1->Height)/4;
 f->Button3->Left=(f->Width-f->Button1->Width)/2;
 f->Button3->Top=(f->Height-f->Button3->Height)/8;
 f->Button4->Left=(f->Width-f->Button1->Width)/2;
 f->Button4->Top=3*(f->Height-f->Button3->Height)/8;

 f->Memo1->Visible=0;
 f->Panel1->Visible=0;
 f->Panel2->Visible=0;
 f->Button2->Visible=0;
 f->Button5->Visible=0;
}

void q_form_ini(TForm1 *f)//form for questions
{
 f->Width=700;
 f->Height=400;
 //кнопки ДА и НЕТ
 f->Panel1->Width=f->Width/4;
 f->Panel1->Height=f->Height/10;
 f->Panel2->Width=f->Width/4;
 f->Panel2->Height=f->Height/10;
 //кнопка ДАЛЕЕ
 f->Button2->Height=f->Panel2->Height;
 f->Button2->Width=f->Width/8;
 //кнопка СНАЧАЛА
 f->Button5->Height=f->Panel2->Height;
 f->Button5->Width=f->Width/8;
 //кнопка ОПРЕДЕЛЕНИЯ
 f->Button3->Height=f->Panel2->Height;
 f->Button3->Width=f->Width/8;
 f->Button3->Font->Size=8;
  //кнопка СПРАВКА
 f->Button4->Height=f->Panel2->Height;
 f->Button4->Width=f->Width/8;
 f->Button4->Font->Size=8;
 //окно для вопросов
  f->Memo1->Width=f->Width-f->Button2->Width-30;
  f->Memo1->Height=0.75*f->Height;
  f->Memo1->Font->Size=16;

 f->Memo1->Left=0;
 f->Memo1->Top=0;
 f->Panel1->Left=f->Width/7;
 f->Panel1->Top=0.75*f->Height+10;
 f->Panel2->Left=3*f->Width/8;
 f->Panel2->Top=0.75*f->Height+10;

 f->Button3->Top=0;
 f->Button3->Left=f->Memo1->Left+f->Memo1->Width;
 f->Button4->Top=f->Button3->Top+f->Button3->Height+8;
 f->Button4->Left=f->Memo1->Left+f->Memo1->Width;
 f->Button2->Top=0.75*f->Height+10;
 f->Button2->Left=f->Button3->Left;
 f->Button5->Top=f->Button4->Top+f->Button4->Height+50;
 f->Button5->Left=f->Button3->Left;

 f->Button1->Visible=0;
 f->Memo1->Visible=1;
 f->Panel1->Caption="ДА";
 f->Panel2->Caption="НЕТ";
 f->Button3->Caption="Словарь";
 f->Button4->Caption="Справка";
 f->Button5->Caption="Сначала";
 f->Caption="Определение возрастного рейтинга";
 f->Panel1->Visible=1;
 f->Panel2->Visible=1;
 f->Button2->Visible=1;
 f->Button5->Visible=1;
}

void init_rates()
{
 num_of_rates=5;
 current_rate=0;
 current_q=1;
 rates[0]="18+";
 rates[1]="16+";
 rates[2]="12+";
 rates[3]="6+";
 rates[4]="0+";
}

void Show_rate(TForm1 *f)
{
  start_form_ini(f);
  f->Button1->Caption="Возрастной рейтинг: "+rates[current_rate];
}

String read_from_file(String rate,int q_num)
{
   String q=""; //return text of the question
   AnsiString FilePath=Dir_for_file;
   TIniFile * SettingIniFile;
   SettingIniFile = new TIniFile(FilePath+"\\"+"questions.txt");
   try{
        q=SettingIniFile->ReadString(rate,"Q"+IntToStr(q_num),"");
       }
   catch (EFOpenError&)
     {
       //file not exist
       Application->MessageBox("Не найден файл данных","Ошибка",MB_OK);
     }
   return q;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
 start=1;
 mode=0;
 Dir_for_file=GetCurrentDir();
 start_form_ini(Form1);
 start=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  start=1;
  q_form_ini(Form1);
  answer=-1;
  //start test
  init_rates();// array of rates

  String q=read_from_file(rates[current_rate],current_q);
  Memo1->Text=q;
  start=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel1Click(TObject *Sender)
{
 //effect of click
 Panel1->BevelInner=bvLowered;
 Panel2->BevelInner=bvNone;

 answer=1;//yes
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel2Click(TObject *Sender)
{
   //effect of click
 Panel2->BevelInner=bvLowered;
 Panel1->BevelInner=bvNone;

 answer=0;//no
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
 start=1;
 //ответ не выбран
 Panel1->BevelInner=bvNone;
 Panel2->BevelInner=bvNone;

 if (answer==-1)
    {
    Application->MessageBox("Выберите вариант ответа","Ошибка",MB_OK);
    return;
    }
 if (answer==1)
    {
    Show_rate(Form1);
    return;
    }
 if (answer==0)
  {
   answer=-1;
   current_q++;
   String q=read_from_file(rates[current_rate],current_q);
   if (q!="")//если есть ещё вопросы в этом возрасте
      Memo1->Text=q; //вывод вопроса
   else
      {
       if (current_rate!=num_of_rates-1)
         {
           current_rate++;//в следующую возраст. группу
           current_q=1; //с первого вопроса
           String q=read_from_file(rates[current_rate],current_q);
           //дошли до 0+
           if (current_rate==4)
             Show_rate(Form1);
           else
            Memo1->Text=q;
         }
       else
         Show_rate(Form1);
      }

  }
 start=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel1DblClick(TObject *Sender)
{
  Button2->OnClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel2DblClick(TObject *Sender)
{
 Button2->OnClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCanResize(TObject *Sender, int &NewWidth,
      int &NewHeight, bool &Resize)
{
 if (start!=1)
  Resize=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
 //terms
  mode=1;
  Form2->OnCreate(Form2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
  //help
  mode=2;
  Form2->OnCreate(Form2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
 Form1->Button1->OnClick(this);        
}
//---------------------------------------------------------------------------

