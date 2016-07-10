/* ******* STUDENT INFORMATION SYSTEM *******  */
#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<string.h>
#include<fstream.h>
#include<stdlib.h>
#include<stdio.h>
#include<dos.h>
#include<ctype.h>

struct Stinfo
{
	char Id[7];	char fname[20];
	char blood[5];	char dept[4];
	char hall[15]; 	char year[7];
	char semst[7]; 	char cgpa[5];
	Stinfo *next;  	Stinfo* prev;
};

struct Stinfo *predloc=NULL,*last=NULL;

struct TStinfo
{
	char Id[7]; char fname[20];  char blood[5];
	char dept[4]; char hall[15]; char year[7];
	char semst[7];	char cgpa[5];
};

void Insert(void);
void Delete(void);
void Search(void);
void Display(void);
void Update(void);
void Grouping(void);
void start_screen(void);
char Frontpage(void);
void Mainpage(void);
void Getdata(Stinfo *temp);
void Edit(Stinfo *temp);
void Creatbox(int x,int y,int x1,int y1,int col);
void Savecng(void);

char *opt[]={"  DATA ENTRY.","  SEARCH INF.","  DISPLAY BY YEAR.","   UPDATE.","   DELETE.","   GROUPING."};
char *elements[]={"Id","Name","Blood Group","Depertment","Year","Semester","CGPA","Hall"};
int j,i,ct,u1,v1, ht,col, xmax,u,v,x,y,ascii,scan,sig,save=1;
FILE* fl;
struct palettetype pal;
union REGS ii, oo ;

void s_graph()
{
	int gd=DETECT,gm,errorcode;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
	}
}

void e_graph()
{
	closegraph();
	restorecrtmode();
}

void pto()
{
	s_graph();
	int i;
	for(i=13;i>1;i--)
	{
		setrgbpalette(pal.colors[i], i*0, i*0, i*0);
		delay(60);
	}
	e_graph();
}

void clearbox()
{
	window(16,7,63,21);clrscr();
	window(1,1,80,25);
}

void printfields()
{

	int i,j;
	textcolor(10);
	for(i=7,j=0;i<=21;i+=2,j++){
		gotoxy(25,i);cprintf("%-13s",elements[j]);
		cout<<":";
	}
}

void printdata(Stinfo *temp){
	textcolor(15);
	gotoxy(40,7);cputs(temp->Id);
	gotoxy(40,9);cputs(temp->fname);
	gotoxy(40,11);cputs(temp->blood);
	gotoxy(40,13);cputs(temp->dept);
	gotoxy(40,15);cputs(temp->year);
	gotoxy(40,17);cputs(temp->semst);
	gotoxy(40,19);cputs(temp->cgpa);
	gotoxy(40,21);cputs(temp->hall);
}

void main()	//Start main()
{
	char msg[150];
	char msgt[10];
	char ch;
	int found=0,ant;
	struct TStinfo tstinfo;

	start_screen();

	fl=fopen("c:\\Arif.bin","rb");

	if(fl==NULL)
	{
		cout<<"\n\n\t\tThe file is not exist !!!\n\t\tDatabase is EMPTY ...";
		getch();
	}
	else
	{
		Stinfo *temp;
		while(!feof(fl))
		{
			Stinfo* newSt=new Stinfo;
			fread(&tstinfo,sizeof(tstinfo),1,fl);
			strcpy(newSt->Id,tstinfo.Id);strcpy(newSt->fname,tstinfo.fname);
			strcpy(newSt->blood,tstinfo.blood);strcpy(newSt->semst,tstinfo.semst);
			strcpy(newSt->year,tstinfo.year);strcpy(newSt->dept,tstinfo.dept);
			strcpy(newSt->cgpa,tstinfo.cgpa);strcpy(newSt->hall,tstinfo.hall);
			temp=predloc;
			while(temp!=NULL)
			{
				if(strcmpi(newSt->Id,temp->Id)==0)found=1;
				temp=temp->next;
			}
			if(found!=1)
			{
				if(predloc==NULL)
				{
					predloc=newSt;
					predloc->prev=NULL;
				}
				else
				{
					last->next=newSt;
					newSt->prev=last;
				}
				newSt->next=NULL;
				last=newSt;
			}
		}
	}

	do
	{
		ch=toupper(Frontpage());
		Mainpage();
		_setcursortype(_NOCURSOR);
		textcolor(LIGHTRED+BLINK);
		switch(ch){
			case 'I':
			save=0;
			gotoxy(32,4);cprintf("%s",opt[0]);
			Insert();
			break;
			case 'D':
			save=0;
			gotoxy(35,4);cprintf("%s",opt[4]);
			Delete();
			break;
			case 'F':
			gotoxy(32,4);cprintf("%s",opt[1]);
			Search();
			break;
			case 'U':
			save=0;
			gotoxy(32,4);cprintf("%s",opt[3]);
			Update();
			break;
			case 'G':
			gotoxy(33,4);cprintf("%s",opt[5]);
			Grouping();
			break;
			case 'S':
			gotoxy(33,4);cprintf("%s",opt[2]);
			Display();
			break;
			case 'E':
			exit(0);
			default:
			break;
			//cout<<"Wrong key ...";getch();
		}
		pto();
		Mainpage();
		if(save!=1){Savecng();}

	}while(1);

}		//End of main()

void start_screen()
{
	s_graph();
	int x,y,i;
	x=getmaxx();
	y=getmaxy();
	setcolor(0);
	setfillstyle(1,0);
	bar3d(0,0,x,y,1,1);
	setcolor(RED);
	setfillstyle(1,2);
	bar3d(100,100,540,380,1,1);
	bar3d(105,105,535,375,1,1);
	settextstyle(1,0,6);
	setcolor(RED);
	outtextxy(110,100,"      DUET");
	settextstyle(4,0,4);
	outtextxy(115,150,"Students' Information System");
	outtextxy(110,182,"        Version 1.0");
	outtextxy(110,215,"            By");
	settextstyle(7,0,3);
	setcolor(BLUE);
	outtextxy(135,253,"       Arifur Rahman");
	outtextxy(170,282,"        (074051)");
	setcolor(RED);
	bar3d(110,320,525,365,1,1);
	settextstyle(7,0,3);
	for(;!kbhit();)
	{
		setcolor(i=(i!=2)?2:10);
		outtextxy(225,325,"Press any key");
		delay(500);
	}
	getch();
	e_graph();
}

char Frontpage()
{
	e_graph();
	clrscr();
	int count=0,id=0,len,flag=0,col,i;char ch;
	char name[]="DEVELOPED BY: ARIFUR RAHMAN";
	len=strlen(name);
	pto();
	gotoxy(7,4);
	textcolor(LIGHTCYAN);cprintf("S"); textcolor(LIGHTRED+BLINK);cprintf("i"); textcolor(LIGHTCYAN);cprintf("S");
	gotoxy(30,4);
	textcolor(LIGHTRED);cprintf("Select Your Choice:");
	gotoxy(70,4);
	textcolor(LIGHTCYAN);cprintf("S"); textcolor(LIGHTRED+BLINK);cprintf("i"); textcolor(LIGHTCYAN);cprintf("S");
	textcolor(4);
	gotoxy(25,9);   cprintf("[I]  DATA ENTRY. ");
	gotoxy(25,10);  cprintf("[F]  SEARCH INFORMATION. ");
	gotoxy(25,11);	cprintf("[S]  DISPLAY BY YEAR");
	gotoxy(25,12);  cprintf("[U]  UPDATE. ");
	gotoxy(25,13);  cprintf("[D]  DELETE. ");
	gotoxy(25,14);  cprintf("[G]  GROUPING. ");
	gotoxy(25,15);	cprintf("[E]  EXIT");
	textcolor(YELLOW);
	gotoxy(25,9);    cprintf("[I]");
	gotoxy(25,10);   cprintf("[F]");
	gotoxy(25,11);	 cprintf("[S]");
	gotoxy(25,12);   cprintf("[U]");
	gotoxy(25,13);   cprintf("[D]");
	gotoxy(25,14);   cprintf("[G]");
	gotoxy(25,15);	 cprintf("[E]");
	_setcursortype(_NOCURSOR);
	textcolor(10);
	for(i=1;i<80;i++)
	{
		gotoxy(i,1);	cprintf("%c",205);
		gotoxy(i,3);	cprintf("%c",205);
		gotoxy(i,2);	cprintf("%c",176);
		gotoxy(i,25);	cprintf("%c",205);
		gotoxy(i,23);	cprintf("%c",196);
		gotoxy(i,5);	cprintf("%c",196);
	}
	for(i=2;i<25;i++)
	{
		gotoxy(1,i);	cprintf("%c",186);
		gotoxy(79,i);	cprintf("%c",186);
	}
	gotoxy(1,1);cprintf("%c",201);
	gotoxy(1,25);cprintf("%c",200);
	gotoxy(79,1);cprintf("%c",187);
	gotoxy(79,25);cprintf("%c",188);
	gotoxy(1,3);cprintf("%c",204);
	gotoxy(79,3);cprintf("%c",185);
	gotoxy(1,23);cprintf("%c",199);
	gotoxy(79,23);cprintf("%c",182);
	gotoxy(1,5);cprintf("%c",199);
	gotoxy(79,5);cprintf("%c",182);

	gotoxy(15,5);cprintf("%c",193);
	gotoxy(15,3);cprintf("%c",209);
	gotoxy(15,4);cprintf("%c",179);

	gotoxy(64,5);cprintf("%c",193);
	gotoxy(64,3);cprintf("%c",209);
	gotoxy(64,4);cprintf("%c",179);

	textcolor(WHITE);
	gotoxy(21,2);cprintf("STUDENT'S INFORMATION SYSTEM OF DUET");
	for(;!kbhit();)
	{
		if(count>1000)
		{
			count=0;
			if(id<=len)
			{
				gotoxy(29,24);
				textcolor(4);
				if(flag==0)
					textcolor(col);
				cprintf("%.*s",id,name);
				id++;
			}
			else
			{
				col=(rand()*15);
				if(flag==1)flag=0;
				else flag=1;
				id=0;
				count=-9000;
			}
		}
		count++;
		gotoxy(29,24);
	}
	ch=getch();
	return(ch);
}

void Mainpage()
{
	e_graph();
	clrscr();
	int i;
	_setcursortype(_NOCURSOR);
	textcolor(LIGHTGREEN);
	for(i=1;i<80;i++)
	{
		gotoxy(i,1);	cprintf("%c",205);
		gotoxy(i,3);	cprintf("%c",205);
		gotoxy(i,2);	cprintf("%c",176);
		gotoxy(i,25);	cprintf("%c",205);
		gotoxy(i,23);	cprintf("%c",196);
		gotoxy(i,5);	cprintf("%c",196);
	}
	for(i=2;i<25;i++)
	{
		gotoxy(1,i);	cprintf("%c",186);
		gotoxy(79,i);	cprintf("%c",186);
	}
	gotoxy(1,1);cprintf("%c",201);
	gotoxy(1,25);cprintf("%c",200);
	gotoxy(79,1);cprintf("%c",187);
	gotoxy(79,25);cprintf("%c",188);
	gotoxy(1,3);cprintf("%c",204);
	gotoxy(79,3);cprintf("%c",185);
	gotoxy(1,23);cprintf("%c",199);
	gotoxy(79,23);cprintf("%c",182);
	gotoxy(1,5);cprintf("%c",199);
	gotoxy(79,5);cprintf("%c",182);

	gotoxy(15,5);cprintf("%c",193);
	gotoxy(15,3);cprintf("%c",209);
	gotoxy(15,4);cprintf("%c",179);

	gotoxy(64,5);cprintf("%c",193);
	gotoxy(64,3);cprintf("%c",209);
	gotoxy(64,4);cprintf("%c",179);

	textcolor(WHITE);
	gotoxy(21,2);cprintf("STUDENT'S INFORMATION SYSTEM OF DUET");
}

void Getdata(Stinfo *temp){
	//Creatbox(15,6,64,22,3);
	clearbox();
	printfields();
	_setcursortype(_NORMALCURSOR);
	gotoxy(40,7);gets(temp->Id);
	gotoxy(40,9);gets(temp->fname);
	gotoxy(40,11);gets(temp->blood);
	gotoxy(40,13);gets(temp->dept);
	gotoxy(40,15);gets(temp->year);
	gotoxy(40,17);gets(temp->semst);
	gotoxy(40,19);gets(temp->cgpa);
	gotoxy(40,21);gets(temp->hall);
	_setcursortype(_NOCURSOR);
}

void Insert()
{
	char ch;
	int found=0;
	Creatbox(15,6,64,22,3);
	gotoxy(22,14);textcolor(15);cprintf("ARE YOU READY TO ENTRY NEW DATA (Y/N) ?");
	ch=toupper(getch());
	if(ch=='Y')
	{
		do
		{
			Stinfo *newSt=new Stinfo;
			Stinfo *temp=predloc;
			Stinfo *current=temp->next;
			Getdata(newSt);
			while(temp!=NULL)
			{
				if(strcmpi(newSt->Id,temp->Id)==0){found=1;break;}
				temp=temp->next;
			}
			if(found==1)
			{
				clearbox();
				gotoxy(28,14);cout<<"This Id is already exists !!!";
				getch();
			}
			else
			{
				temp=predloc;
				if(predloc!=NULL)
				{
					if(strcmpi(newSt->Id,temp->Id)<0)
					{
						newSt->prev=NULL;
						newSt->next=predloc;
						predloc->prev=newSt;
						predloc=newSt;
					}
					else
					{
						while(current!=NULL)
						{
							if(strcmpi(newSt->Id,current->Id)<0)
							{
								newSt->next=current;
								newSt->prev=current->prev;
								current->prev->next=newSt;
								current->prev=newSt;
								//temp->next=newSt;
								break;
							}
							temp=current;
							current=current->next;
						}
						if(current==NULL)
						{
							temp->next=newSt;
							newSt->next=NULL;
						}
					}
				}
				else
				{
					newSt->next=NULL;
					predloc=newSt;
				}
			}
			clearbox();
			gotoxy(18,13);cout<<"Press any key to more entry or ESC to back ..";
		}while(toascii(getch())!=27);  //ascii code of esc is 27
	}
}

void Delete()
{
	char ch,Id[10];
	char *dept,*year,*semst;
	int found=0;
	Stinfo *temp,*current;
	Creatbox(15,6,64,22,3);
	do
	{
		clearbox();
		gotoxy(5,24);cout<<"                                                                        ";
		gotoxy(25,13);cout<<"ARE YOU SURE TO DELETE (Y/N) ?";
		ch=toupper(getch());
		if(ch=='Y')
		{
			do
			{
				gotoxy(17,24);cout<<"                                              ";
				clearbox();
				_setcursortype(_NORMALCURSOR);
				gotoxy(27,13);cout<<"Please give the Id : ";
				gets(Id);
				_setcursortype(_NOCURSOR);
				temp=predloc;
				Stinfo *current=temp->next;
				if(strcmpi(temp->Id,Id)==0)
				{
					found=1;
					predloc=current;
					predloc->prev=NULL;
					delete(temp);
				}
				else
				{
					while(current!=NULL)
					{
						if(strcmpi(current->Id,Id)==0)
						{
							found=1;
							clearbox();
							current->prev->next=current->next;
							if(current->next!=NULL)
								current->next->prev=current->prev;
							delete(current);
							current=temp;
						}
						temp=current;
						current=current->next;
					}
					if(found==0)
					{
						gotoxy(30,15);cout<<"This Id is not found !!!";
					}
					else
					{
						gotoxy(25,15);cout<<"This Id is successfully deleted ...";
					}
				}
				gotoxy(17,24);textcolor(YELLOW);cprintf("Press any key to try again or ESC to exit...");
			}while(toascii(getch())!=27);
			ch='q';
		}else ch='q';
	}while(ch!='q');
}

void Update()
{
	char ch,Id[10];
	char *dept,*year,*semst;
	int found=0;
	Stinfo *temp,*current;
	Creatbox(15,6,64,22,3);
	do
	{
		gotoxy(5,24);cout<<"                                                                        ";
		clearbox();
		gotoxy(25,13);cout<<"ARE YOU SURE TO UPDATE (Y/N) ?";
		ch=toupper(getch());
		if(ch=='Y')
		{
			clearbox();
			do
			{
				gotoxy(17,24);cout<<"                                              ";
				clearbox();
				gotoxy(27,13);cout<<"Please give the Id : ";
				gets(Id);
				temp=predloc;
				while(temp!=NULL)
				{
					if(strcmpi(temp->Id,Id)==0)
					{
						found=1;
						clearbox();
						printfields();
						printdata(temp);

						Edit(temp);

						printfields();
						printdata(temp);
						break;
					}
					temp=temp->next;
				}
				if(found==0)
					{gotoxy(30,15);cout<<"This Id is not found !!!";}

				gotoxy(7,24);cout<<"                                                                      ";
				clearbox();
				gotoxy(17,24);cout<<"Press any key to try again or ESC to exit...";
			}while(toascii(getch())!=27);
			ch='q';
		}else ch='q';
	}while(ch!='q');

}

void Search(){
	char ch,Id[10];
	Creatbox(15,6,64,22,3);
	_setcursortype(_NOCURSOR);
	gotoxy(25,13);textcolor(YELLOW);cprintf("ARE YOU SURE TO SEARCH (Y/N) ?");
	ch=toupper(getch());
	if(ch=='Y'){
		do{
			gotoxy(17,24);cout<<"                                              ";
			clearbox();
			gotoxy(27,13);textcolor(YELLOW);cprintf("Please give the Id : ");
			gets(Id);
			_setcursortype(_NOCURSOR);
			Stinfo *temp=predloc;
			while(temp!=NULL){
				if(strcmpi(temp->Id,Id)==0){
					clearbox();
					printfields();
					printdata(temp);
					break;
				}
				temp=temp->next;
			}
			if(temp==NULL){
				gotoxy(30,15);textcolor(YELLOW);cprintf("This Id is not found !!!");
			}
			gotoxy(17,24);textcolor(YELLOW);cprintf("Press any key to try again or ESC to exit...");
		}while(toascii(getch())!=27);
	}
}

void Edit(Stinfo *temp)
{
	_setcursortype(_NOCURSOR);
	gotoxy(8,24);cprintf("                                                                    ");
	gotoxy(10,24);cprintf("Press %c & %c to select field and [Enter] to edit...[ESC] to back.",24,25);
	int y=7,i=0;
	while(ascii!=27)
	{

		if(scan==72)
		{
			y-=2;i-=1;
			if(y<7){y=21;i=7;}
		}else if(scan==80)
		{
			y+=2;i+=1;
			if(y>21){y=7;i=0;}
		}
		if(ascii==13)
		{
			gotoxy(8,24);cprintf("                                                                    ");
			gotoxy(30,24);cprintf(" Give the new data");
			_setcursortype(_NORMALCURSOR);
			gotoxy(40,y);cout<<"                     ";
			gotoxy(40,y);
			if(i==0)gets(temp->Id);
			else if(i==1)gets(temp->fname);
			else if(i==2)gets(temp->blood);
			else if(i==3)gets(temp->dept);
			else if(i==4)gets(temp->year);
			else if(i==5)gets(temp->semst);
			else if(i==6)gets(temp->cgpa);
			else gets(temp->hall);
			printdata(temp);
			_setcursortype(_NOCURSOR);
			gotoxy(8,24);cprintf("                                                                    ");
			gotoxy(10,24);cprintf("Press %c & %c to select field and [Enter] to edit...[ESC] to back.",24,25);
		}
		printfields();
		textcolor(4);
		gotoxy(25,y);
		cprintf("%-13s",elements[i]);
		while ( ! kbhit() );
		ii.h.ah = 0 ;
		int86 ( 22, &ii, &oo ) ;
		scan = oo.h.ah ;
		ascii = oo.h.al ;

	}

}

void Savecng()
{
	struct TStinfo tstinfo;
	char ch;
	Creatbox(15,6,64,22,3);
	gotoxy(22,13);cprintf("DO YOU WANT TO SAVE THE CHANGES (Y/N) ?");
	gotoxy(30,4);cprintf("%s",opt[2]);
	ch=toupper(getch());
	if(ch=='Y')
	{
		if(predloc!=NULL){
			fl=fopen("c:\\Arif.bin","wb");
			Stinfo *temp=predloc;
			while(temp!=NULL){
				strcpy(tstinfo.Id,temp->Id);   strcpy(tstinfo.fname,temp->fname);
				strcpy(tstinfo.blood,temp->blood);strcpy(tstinfo.semst,temp->semst);
				strcpy(tstinfo.year,temp->year);  strcpy(tstinfo.dept,temp->dept);
				strcpy(tstinfo.cgpa,temp->cgpa);  strcpy(tstinfo.hall,temp->hall);

				fwrite(&tstinfo,sizeof(tstinfo),1,fl);
				temp=temp->next;
			}
		}
		clearbox();
		gotoxy(22,13);cprintf("THE CHANGES HAVE SAVED SUCCESSFULLY !!!");
		getch();
	}
	fclose(fl);
	save=1;
}

void Grouping()
{
	char ch;
	char *dept,*hall;
	int count=0;
	Stinfo *temp;
	Creatbox(15,6,64,22,3);
	do
	{
		clearbox();
		gotoxy(5,24);cout<<"                                                                        ";
		gotoxy(25,13);cout<<"ARE YOU SURE TO GROUPING (Y/N) ?";
		ch=toupper(getch());
		if(ch=='Y')
		{
			clearbox();
			gotoxy(25,16);cout<<" To group on Dept & Hall.";getch();
			ch=toupper('4');
			clearbox();
			count=0;
			temp=predloc;
			if(ch=='4')
			{
				gotoxy(25,14);cout<<"DEPT. :";gets(dept);
				gotoxy(25,15);cout<<"HALL  :";gets(hall);
				while(temp!=NULL)
				{
					if((strcmpi(temp->dept,dept)==0)&&(strcmpi(temp->hall,hall)==0))
						count+=1;
					temp=temp->next;
				}
				temp=predloc;
				while(temp!=NULL)
				{
					if((strcmpi(temp->dept,dept)==0)&&(strcmpi(temp->hall,hall)==0))
						break;
					temp=temp->next;
				}
			}
			clearbox();
			if(temp!=NULL)
			{
				printfields();
				printdata(temp);
				gotoxy(5,4);textcolor(YELLOW);cprintf("TOTAL :");
				gotoxy(69,4);cprintf("%d",count);
				ascii=0;scan=0;
				gotoxy(17,24);cprintf("Press %c or %c key to move record ...[ESC] to back..",27,26);
				while(ascii!=27)
				{
		   			//clearbox();
					printfields();
					if(scan==75)
					{
						temp=temp->prev;
						while(temp!=NULL)
						{
							if(ch=='4')
							{
								if((strcmpi(temp->dept,dept)==0)&&(strcmpi(temp->hall,hall)==0))
								{
									printdata(temp);
									break;
								}
							}
							temp=temp->prev;
						}

						if(temp==NULL)
						{
							clearbox();
							gotoxy(30,14);cout<<"Begining of database...";
							temp=predloc;
						}


					}
					if(scan==77)
					{
						temp=temp->next;
						while(temp!=NULL)
						{
							if(ch=='4')
							{
								if((strcmpi(temp->dept,dept)==0)&&(strcmpi(temp->hall,hall)==0))
								{
									printdata(temp);
									break;
								}
							}


							temp=temp->next;
						}
						if(temp==NULL)
						{
							clearbox();
							gotoxy(30,14);cout<<"Bottom of database...";
							temp=last;
						}
					}

					while ( ! kbhit() );
					ii.h.ah = 0 ;
					int86 ( 22, &ii, &oo ) ;
					scan = oo.h.ah ;
					ascii = oo.h.al ;
					clearbox();
				}
				clearbox();
				gotoxy(5,4);cout<<"       ";
				gotoxy(69,4);cout<<"       ";
			}
			else
			{ 
				gotoxy(30,14);cout<<"NO SUCH RECORD FOUND !!";
				getch();
			}
		}
		else {ch='q';}

	}while(ch!='q');

}

void Display()
{
	char ch;
	char *year;
	int count=0;
	Stinfo *temp;
	Creatbox(15,6,64,22,3);
	do
	{
		clearbox();
		gotoxy(5,24);cout<<"                                                                        ";
		gotoxy(25,13);cout<<"ARE YOU DISPLAY BY YEAR (Y/N) ?";
		ch=toupper(getch());
		if(ch=='Y')
		{
			clearbox();
			ch=toupper('4');
			clearbox();
			count=0;
			temp=predloc;

			if(ch=='4')
			{
				gotoxy(25,12);cout<<"YEAR. :";gets(year);
				while(temp!=NULL)
				{
					if(strcmpi(temp->year,year)==0)
						count+=1;
					temp=temp->next;
				}
				temp=predloc;
				while(temp!=NULL)
				{
					if(strcmpi(temp->year,year)==0)
						break;
					temp=temp->next;
				}
			}
			
			clearbox();
			if(temp!=NULL)
			{
				printfields();
				printdata(temp);
				gotoxy(5,4);textcolor(YELLOW);cprintf("TOTAL :");
				gotoxy(69,4);cprintf("%d",count);
				ascii=0;scan=0;
				gotoxy(17,24);cprintf("Press %c or %c key to move record ...[ESC] to back..",27,26);
				while(ascii!=27)
				{
		   			//clearbox();
					printfields();
					if(scan==75)
					{
						temp=temp->prev;
						while(temp!=NULL)
						{
							if(ch=='4')
							{
								if(strcmpi(temp->year,year)==0)
								{
									printdata(temp);
									break;
								}
							}
							temp=temp->prev;
						}

						if(temp==NULL)
						{
							clearbox();
							gotoxy(30,14);cout<<"Begining of database...";
							temp=predloc;
						}
					}

					if(scan==77)
					{
						temp=temp->next;
						while(temp!=NULL)
						{
							if(ch=='4')
							{
								if(strcmpi(temp->year,year)==0)
								{
									printdata(temp);
									break;
								}
							}

							temp=temp->next;
						}

						if(temp==NULL)
						{
							clearbox();
							gotoxy(30,14);cout<<"Bottom of database...";
							temp=last;
						}
					}

					while ( ! kbhit() );

					ii.h.ah = 0 ;
					int86( 22, &ii, &oo ) ;// 22 we can identify keystrokes.
					scan = oo.h.ah ;
					ascii = oo.h.al ;
					clearbox();
				}

				clearbox();
				gotoxy(5,4);cout<<"       ";
				gotoxy(69,4);cout<<"       ";

			}
			else
			{ 
				gotoxy(30,14);cout<<"NO SUCH RECORD FOUND !!";
				getch();
			}
		}
		else {ch='q';}

	}while(ch!='q');
}

void Creatbox(int x,int y,int x1,int y1,int col)
{
	textcolor(col);
	for(int i=x;i<=x1;i++)
	{
		gotoxy(i,y);cprintf("%c",205);
		gotoxy(i,y1);cprintf("%c",205);
	}
	for(i=y+1;i<y1;i++)
	{
		gotoxy(x-1,i);cprintf("%c%c",175,186);
		gotoxy(x1,i);cprintf("%c%c",186,174);
	}
	gotoxy(x,y);printf("%c",201);
	gotoxy(x1,y1);printf("%c",188);
	gotoxy(x1,y);printf("%c",187);
	gotoxy(x,y1);printf("%c",200);
}




