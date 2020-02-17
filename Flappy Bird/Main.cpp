#include <graphics.h>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <easyx.h>
#pragma comment(lib,"winmm.lib")
#define WIDE 640
#define HIGH 480

typedef struct bird									//�ṹ�� ��
{
	int a1,a2,ans,wrans1,wrans2,wrans3,x,y,n,img;
	char syb;
	struct bird *next;
}BIRD;
typedef struct button								//�ṹ�� ��ť
{
	int x1,x2,y1,y2,stp,stn;
	char n[5];
}BUTTON;

void DRAWBUTTON(BUTTON b,COLORREF color,int t)		//��������ť��ָ����ť���ݡ���ɫ����ʽ��
{
	setfillcolor(color);
	if(t){fillellipse(b.x1,b.y1,b.x2,b.y2);outtextxy(b.x1+35,b.y1+10,b.n);}
	else {fillroundrect(b.x1,b.y1,b.x2,b.y2,10,5);outtextxy(b.x1+20,b.y1+10,b.n);}
	setfillcolor(LIGHTBLUE);
}
int ISIN(int x,int y,BUTTON b)						//�ж�����x,y�Ƿ��ڰ�ťb��
{
	if(x>=b.x1 && x<=b.x2 && y>=b.y1 && y<=b.y2)return 1;
	else return 0;
}
void DRAWMENU()										//������Ŀ¼��Ϊ��Լ��Դ����һ��������ť��
{
	IMAGE sky;
	IMAGE menu;
	loadimage(&menu,"menu.jpg");
	putimage(0,380,&menu);
	line(0,380,WIDE,380);
	line(250,380,250,480);
	line(400,380,400,480);
	outtextxy(260,390,"�û���");
	outtextxy(260,420,"�÷֣�");
	outtextxy(260,450,"ʣ��ʱ�䣺");
	fillroundrect(10,390,80,425,10,5);
	outtextxy(30,400,"����");
	fillroundrect(10,435,80,470,10,5);
	outtextxy(30,445,"ɾ��");
	fillroundrect(90,390,160,425,10,5);
	outtextxy(110,400,"�˳�");
	fillroundrect(90,435,160,470,10,5);
	outtextxy(110,445,"����");
	fillroundrect(170,390,240,425,10,5);
	outtextxy(190,400,"����");
	fillellipse(420,390,510,425);
	fillellipse(420,435,510,470);
	fillellipse(530,390,620,425);
	fillellipse(530,435,620,470);
	loadimage(&sky,"sky.jpg");
	putimage(0,0,&sky);
}
void GET_DATA(int *a,char *syb,int *b,int *ans,int *wrans1,int *wrans2,int *wrans3,int *x,int *y,int *n,int *img)	//�����ĸ������������ָ����ʽ����
{
    int a_,b_,sel_,ans_,wrans1_,wrans2_,wrans3_,x_,y_,n_,img_;		//������Ŀ���ĸ��𰸡��ĸ���ť����ȷ�𰸡����ꡢ״̬��ѡ��/δѡ�У�
    char syb_;
    a_=rand()%100+1;
    b_=rand()%(a_)+1;
    sel_=rand()%4;
	x_=-117;
	y_=rand()%283;
	n_=rand()%4;
	img_=0;
    switch(sel_)
	{
        case 0:syb_='+';ans_=a_+b_;break;
        case 1:syb_='-';ans_=a_-b_;break;
        case 2:syb_='*';ans_=a_*b_;break;
        case 3:syb_='/';while((a_%b_!=0) || (a_==b_) || (b_==1)){a_=rand()%9+1;b_=rand()%(a_)+1;}ans_=a_/b_;
    }
    wrans1_=ans_;
    wrans2_=ans_;
    wrans3_=ans_;
    while((wrans1_==ans_)||(wrans1_<0))wrans1_=rand()%11+ans_-5;
    while((wrans2_==ans_)||(wrans2_==wrans1_)||(wrans2_<0))wrans2_=rand()%11+ans_-5;
    while((wrans3_==ans_)||(wrans3_==wrans1_)||(wrans3_==wrans2_)||(wrans3_<0))wrans3_=rand()%11+ans_-5;
    *a=a_;*syb=syb_;*b=b_;*ans=ans_;*wrans1=wrans1_;*wrans2=wrans2_;*wrans3=wrans3_;*x=x_;*y=y_;*n=n_;*img=img_;
}
BIRD * CREATEBIRD(BIRD *h)			//����һ���񣬰����������������½ڵ�
{
    BIRD *p,*r=NULL;
    int a1,a2,ans,wrans1,wrans2,wrans3,x,y,n,img;
    char syb;
    GET_DATA(&a1,&syb,&a2,&ans,&wrans1,&wrans2,&wrans3,&x,&y,&n,&img);
    p = (BIRD *) malloc(sizeof( BIRD ));
    p->a1 = a1;
    p->a2 = a2;
    p->ans = ans;
    p->wrans1 = wrans1;
    p->wrans2 = wrans2;
    p->wrans3 = wrans3;
    p->x = x;
    p->y = y;
	p->n = n;
	p->img = img;
    p->syb = syb;
    p->next = NULL;
    if (h==NULL){
        h = p;
        r = p;
    }
    else {
		r=h;
		while((r->next)!=NULL)r=r->next;
		r->next=p;
    }
    return h;
}
void BIRDXPLUS(BIRD *h)				//��ÿ����ĺ������1
{
    BIRD *p = h;
	while (p!=NULL){
		if(p->x<640)p->x=p->x+3;
		else p->x=-117;
        p=p->next;
    }
}
void PRINTBIRD(BIRD *h)				//�������񻭳���
{
	BIRD *p=h;
	IMAGE bird0;
	IMAGE bird1;
	IMAGE birdm;
	IMAGE sky;
	loadimage(&bird0,"bird0.jpg");
	loadimage(&bird1,"bird1.jpg");
	loadimage(&sky,"sky.jpg");
	loadimage(&birdm,"birdm.jpg");
	char buf[4];
	BeginBatchDraw();
	putimage(0,0,&sky);
	while(p!=NULL)
		{
			if(p->img)
			{
				putimage(p->x,p->y,&birdm,SRCAND);
				putimage(p->x,p->y,&bird0,SRCPAINT);
			}
			else 
			{
				putimage(p->x,p->y,&birdm,SRCAND);
				putimage(p->x,p->y,&bird1,SRCPAINT);
			}
			sprintf(buf,"%d%c%d",p->a1,p->syb,p->a2);
			outtextxy((p->x)+50,(p->y)+45,buf);
			p=p->next;
		}
	EndBatchDraw();
}
BIRD * BIRDSEL(int x,int y,BIRD *h)				//�ж�������Ƿ�ѡ��һ���񣬽��������ʽΪָ�����ָ��
{
	BIRD *p=h,*q=NULL;
	while(p!=NULL){
		if(x>p->x && x<((p->x)+117) && y>p->y && y<((p->y)+97)){q=p;}
		p=p->next;
	}
	if(q!=NULL)q->img=1;
	return q;
}
BIRD * BIRDDEL(BIRD *h,BIRD *p)				//ɾ��һ����
{
	BIRD *q=h;
//	IMAGE temp;
	if(h==NULL)return NULL;
	else
	{
		if(p==NULL){q=q->next;free(h);h=q;}
		else
		{
//			getimage(&temp,p->x,p->y,p->x+117,p->y+97);
//			putimage(p->x,p->y, &temp);
			if(q==p){q=q->next;free(h);h=q;}
			else
			{	
				while((q->next)!=p)q=q->next;
				q->next=p->next;
				free(p);
				p=NULL;
			}
		}
	}
	return h;
}
void SAVE(BIRD *head,int score,char NAME[10],int timelim)		//����״̬������Ϊ.txt
{
	FILE *fp;
	BIRD *h=NULL;
	h=head;
	HWND wnd = GetHWnd();
	fp=fopen("save.txt","w");
	fprintf(fp,"%d %s %d",score,NAME,timelim);
	while(h!=NULL)
	{
		fprintf(fp,"\n%d %d %d %d %d %d %d %d %d %d %c",h->a1,h->a2,h->ans,h->wrans1,h->wrans2,h->wrans3,h->x,h->y,h->n,h->img,h->syb);
		h=h->next;
	}
	MessageBox(wnd, "����ɹ����浵�ļ���save.txt", "Good News", MB_OK | MB_ICONWARNING);
	fclose(fp);
}
BIRD* LOAD(int *score,char *NAME,int *timelim,BIRD *head)		//����״̬
{
	FILE *fp;
	fp=fopen("save.txt","r");
    BIRD *h=NULL,*p,*r=NULL;
	HWND wnd = GetHWnd();
    int a1,a2,ans,wrans1,wrans2,wrans3,x,y,n,img;
    char syb;
	if(fp==NULL){MessageBox(wnd, "����ʧ�ܣ�δ�ҵ��浵�ļ�", "Bad News", MB_OK | MB_ICONWARNING);return head;}
	else{
		fscanf(fp,"%d%s%d",score,NAME,timelim);
		while( !feof(fp) ){
			fscanf(fp,"%d %d %d %d %d %d %d %d %d %d %c ",&a1,&a2,&ans,&wrans1,&wrans2,&wrans3,&x,&y,&n,&img,&syb);
			p = (BIRD *) malloc(sizeof( BIRD ));
			p->a1 = a1;
			p->a2 = a2;
			p->ans = ans;
			p->wrans1 = wrans1;
			p->wrans2 = wrans2;
			p->wrans3 = wrans3;
			p->x = x;
			p->y = y;
			p->n = n;
			p->img = img;
			p->syb = syb;
			p->next = NULL;
			if (h==NULL){
				h = p;
				r = p;
			}
			else {
				r->next=p;
				r=p;
			}
		}
		MessageBox(wnd, "����ɹ���", "Good News", MB_OK | MB_ICONWARNING);
	}
	fclose(fp);
	return h;
}
void RENAME(char NAME[10])				//����û���
{
	IMAGE temp;
	loadimage(&temp,"bd0.jpg");
	putimage(300,390,&temp);
	outtextxy(300,390,NAME);
}
void CLEARSCORE()				//���������
{
	IMAGE temp;
	loadimage(&temp,"bd1.jpg");
	putimage(300,420,&temp);
}
void CLEARTIME()				//���ʱ����
{
	IMAGE temp;
	loadimage(&temp,"bd2.jpg");
	putimage(330,450,&temp);
}
void main()					//������
{
	initgraph(WIDE, HIGH);						//��ͼ�����ʼ��
	int i,j=0,score=0,psn=0,psp,timelim,scorep=0;
	char buf[6];
	char NAME[10],TIME[10];
	time_t  t1, t2;
	BIRD *head=NULL,*p=NULL,*q=NULL,*l=NULL;
	BUTTON b[9];																					//������ֱ���
	MOUSEMSG m;								
	b[0].x1=10;b[0].x2=80;b[0].y1=390;b[0].y2=425;b[0].stn=0;sprintf(b[0].n,"����");
	b[1].x1=10;b[1].x2=80;b[1].y1=435;b[1].y2=470;b[1].stn=0;sprintf(b[1].n,"ɾ��");
	b[2].x1=90;b[2].x2=160;b[2].y1=390;b[2].y2=425;b[2].stn=0;sprintf(b[2].n,"�˳�");
	b[3].x1=90;b[3].x2=160;b[3].y1=435;b[3].y2=470;b[3].stn=0;sprintf(b[3].n,"����");
	b[4].x1=170;b[4].x2=240;b[4].y1=390;b[4].y2=425;b[4].stn=0;sprintf(b[4].n,"����");
	b[5].x1=420;b[5].x2=510;b[5].y1=390;b[5].y2=425;b[5].stn=0;sprintf(b[5].n,"");
	b[6].x1=420;b[6].x2=510;b[6].y1=435;b[6].y2=470;b[6].stn=0;sprintf(b[6].n,"");
	b[7].x1=530;b[7].x2=620;b[7].y1=390;b[7].y2=425;b[7].stn=0;sprintf(b[7].n,"");
	b[8].x1=530;b[8].x2=620;b[8].y1=435;b[8].y2=470;b[8].stn=0;sprintf(b[8].n,"");					//���尴ť
	setbkcolor(WHITE);							//������ɫ
	cleardevice();
	setcolor(BLACK);
	setfillcolor(LIGHTBLUE);
	setbkmode(TRANSPARENT);
	DRAWMENU();									//��Ŀ¼
	InputBox(NAME, 10, "�û�:");
	InputBox(TIME, 10, "ʱ�䣨�룩:");			//�����û�����ʱ��
	if(NAME[0]=='\0')strcpy(NAME,"������");
	sscanf(TIME, "%d", &timelim);
	outtextxy(300,390,NAME);
	srand((unsigned)time(NULL));				//�����
	t2 = time(NULL);
	PlaySound("BGM.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);		//��ʼ���ű�������
	while(1)
	{
		if(p!=NULL)p->img=0;
		for(i=0;i<9;i++){b[i].stp=b[i].stn;b[i].stn=0;}		//����״ֵ̬����
		psp=psn;psn=0;
		q=p;
		t1=t2;t2 = time(NULL);
		if (MouseHit())m = GetMouseMsg();
		switch(m.uMsg)										//��궯�����
		{
			case WM_MOUSEMOVE:
				for(i=0;i<9;i++){if(ISIN(m.x,m.y,b[i]))b[i].stn=1;}			//����궯����Ӧ�İ�ť״ֵ̬�ı�
				break;
			case WM_LBUTTONDOWN:
				for(i=0;i<9;i++){if(ISIN(m.x,m.y,b[i]))b[i].stn=2;}
				if(m.y<=380)p=BIRDSEL(m.x,m.y,head);
				break;
			default:
				break;
		}
		for(i=0;i<5;i++){if(b[i].stp!=0 && b[i].stn==0)DRAWBUTTON(b[i],LIGHTBLUE,0);}		//��ť0-4����
		for(i=0;i<5;i++){if(b[i].stp!=1 && b[i].stn==1)DRAWBUTTON(b[i],WHITE,0);}
		for(i=0;i<5;i++){if(b[i].stp!=2 && b[i].stn==2)DRAWBUTTON(b[i],LIGHTGRAY,0);}
		if(b[0].stp!=2 && b[0].stn==2)														//�����°�ť0ʱ ����
			head=CREATEBIRD(head);
		if(b[2].stp!=2 && b[2].stn==2){break;}												//�����°�ť2ʱ �˳�
		if(b[1].stp!=2 && b[1].stn==2){head=BIRDDEL(head,p);p=NULL;}						//�����°�ť1ʱ ɾ��
		if(b[3].stp!=2 && b[3].stn==2){SAVE(head,score,NAME,timelim);}						//�����°�ť3ʱ ����
		if(b[4].stp!=2 && b[4].stn==2)
		{
			head=LOAD(&score,NAME,&timelim,head);
			CLEARSCORE();CLEARTIME();RENAME(NAME);
			sprintf(buf,"%d",score);outtextxy(300,420,buf);			//�����°�ť4ʱ ����
		}
		if(p!=NULL)																			//���ѡ����
		{
			psn=1;p->img=1;
			for(i=5;i<9;i++){if(b[i].stp!=0 && b[i].stn==0)DRAWBUTTON(b[i],LIGHTBLUE,1);}	//��ť5-8������������
			for(i=5;i<9;i++){if(b[i].stp!=1 && b[i].stn==1)DRAWBUTTON(b[i],WHITE,1);}
			for(i=5;i<9;i++){if(b[i].stp!=2 && b[i].stn==2)DRAWBUTTON(b[i],LIGHTGRAY,1);}
		}
		if(j==0)for(i=5;i<9;i++)DRAWBUTTON(b[i],LIGHTGRAY,1);
		if(p!=NULL && q!=p)					//��ѡ�е���ı�ʱ������һ��𰸰�ť
		{
			switch(p->n)
			{
				case 0:	sprintf(b[5].n,"%d",p->ans);sprintf(b[6].n,"%d",p->wrans1);sprintf(b[7].n,"%d",p->wrans2);sprintf(b[8].n,"%d",p->wrans3);break;
				case 1:	sprintf(b[5].n,"%d",p->wrans1);sprintf(b[6].n,"%d",p->ans);sprintf(b[7].n,"%d",p->wrans2);sprintf(b[8].n,"%d",p->wrans3);break;
				case 2:	sprintf(b[5].n,"%d",p->wrans1);sprintf(b[6].n,"%d",p->wrans2);sprintf(b[7].n,"%d",p->ans);sprintf(b[8].n,"%d",p->wrans3);break;
				case 3:	sprintf(b[5].n,"%d",p->wrans1);sprintf(b[6].n,"%d",p->wrans2);sprintf(b[7].n,"%d",p->wrans3);sprintf(b[8].n,"%d",p->ans);break;
			}
			for(i=5;i<9;i++)DRAWBUTTON(b[i],LIGHTBLUE,1);
		}
		if(psn==1)							//���ѡ��������������״̬��ѡ����ȷ�𰸼�1�֣�ѡ�д���𰸿�1��
		{
			switch(p->n)
			{
				case 0:	if(b[5].stp==1 && b[5].stn==2){head=BIRDDEL(head,p);score++;p=NULL;}
						if(b[6].stp==1 && b[6].stn==2 || b[7].stp==1 && b[7].stn==2 || b[8].stp==1 && b[8].stn==2){head=BIRDDEL(head,p);score--;p=NULL;}break;
				case 1:	if(b[6].stp==1 && b[6].stn==2){head=BIRDDEL(head,p);score++;p=NULL;}
						if(b[5].stp==1 && b[5].stn==2 || b[7].stp==1 && b[7].stn==2 || b[8].stp==1 && b[8].stn==2){head=BIRDDEL(head,p);score--;p=NULL;}break;
				case 2:	if(b[7].stp==1 && b[7].stn==2){head=BIRDDEL(head,p);score++;p=NULL;}
						if(b[5].stp==1 && b[5].stn==2 || b[6].stp==1 && b[6].stn==2 || b[8].stp==1 && b[8].stn==2){head=BIRDDEL(head,p);score--;p=NULL;}break;
				case 3:	if(b[8].stp==1 && b[8].stn==2){head=BIRDDEL(head,p);score++;p=NULL;}
						if(b[5].stp==1 && b[5].stn==2 || b[6].stp==1 && b[6].stn==2 || b[7].stp==1 && b[7].stn==2){head=BIRDDEL(head,p);score--;p=NULL;}break;
			}
		}
		if(psp==1 && psn==0)				//�����ѡ��һ�����Ϊ��ѡ���κ��񣬰Ѵ�����ťͿ��
		{
			for(i=5;i<9;i++)sprintf(b[i].n,"");
			for(i=5;i<9;i++)DRAWBUTTON(b[i],LIGHTGRAY,1);
		}
		if(psp==1 && psn==0 || j==1)		//�����ѡ��һ�����Ϊ��ѡ���κ��񣬻��һ��������ѭ�������һ���
		{
			CLEARSCORE();
			sprintf(buf,"%d",score);
			outtextxy(300,420,buf);
		}
		if(j%400==0){									//����ƶ���ÿ100����ѭ������һ�Σ�
			PRINTBIRD(head);
			BIRDXPLUS(head);
		}
		j++;
		if(timelim>-1)						//���ʣ��ʱ����ڵ���0������������-1��������Ϸ��С��-1����ʾ��δ����ʱ�䡱
		{
			if(t2!=t1)
			{
				timelim--;
				CLEARTIME();
				sprintf(buf,"%d",timelim);
				outtextxy(330,450,buf);
			}
			
		}
		else if(timelim==-1){break;}
		else {sprintf(buf,"δ����");outtextxy(330,450,buf);}
	}
	PlaySound("DEAD.wav", NULL, SND_ASYNC | SND_FILENAME );			//�����Ϸ������������ѭ����������������Ч
	IMAGE temp;
	loadimage(&temp,"TIMEUP.jpg");
	putimage(0,0,&temp);
	sprintf(buf,"�÷֣�%d",score);					//��ʾ�÷�
	settextstyle(40,0,"����");
	outtextxy(250,350,buf);
	getch();
}