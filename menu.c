#include <allegro.h>
#include <stdio.h>
#define TELA_X 640
#define TELA_Y 480
void FecharJanela(void);
void inicializa_blocos(void);
void colisaoBlocos(void);
enum boolean {
    true = 1, false = 0
};
typedef  enum boolean  bool; //cria um tipo booleano,muito util!:D
typedef struct personagemt
{
	int x, y,espera,orientacao;
        bool status,data,disparo;

}inimigo;
struct EDisparoinimigo
{
	int x, y,
	    animacao, quadro,
        status,
	    Ntiro,
	    orientacao;
} EDisparoinimigo;

typedef struct blocos
{
	int x, y,
	    status;
}blocos;

bool fechar=false;
void controla_tanque(void);
void naveIA(void);
void colisaoNave(void);
void alienIA(int Tipo,int NAlien);
void inicializa_alien(void);
void ExeAliens(void);
void colisaoAlien(void);
void tiroAlien(void);
 int tanquex=328,tanquey=431;
 bool tanqueTiro=false;
 int tanqueTiroX,tanqueTiroY;
  int tanqueVida=3;
  int pontos=0;
 int NaveEspera=0;
 int naveX,naveY;
 int NaveStatus=false;
 int t1,p1;
 inimigo alien[3][5];
blocos EBloco[15];
int main()
{
    EDisparoinimigo.x=0;
EDisparoinimigo.y=0;
EDisparoinimigo.Ntiro=4;
EDisparoinimigo.status=0;
EDisparoinimigo.orientacao=0;
    int i,j;
    int x=220,y=100;
    int func = 0;
    bool fullscreen=false;
    bool som=true;
    int faseV=50;
    BITMAP *TELA;
    allegro_init(); //inicializa o allegro
    install_keyboard(); //habilita funcoes de  teclado
    install_mouse(); //habilita funcoes de mouse
    set_color_depth(16); //modo 16 bits de cor
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,TELA_X,TELA_Y,0,0)) //resolucao 640x480 nao fullscreen
    {
        //se der merda
        allegro_message("Problems na inicializacao do video!Erro:%s",allegro_error); // manda msg pro user fica putasso
        exit(1);  //e sai sorrateiramente...
    }
    if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL)) //inicializa funcoes de audio
    {
        //se der merda
        allegro_message("Problems na inicializacao do som!Erro:%s",allegro_error); // manda msg pro user fica putasso
        exit(1); //e sai sorrateiramente...
    }
    set_window_title("Space Invaders"); //muda titulo de janela para Space invaders
    TELA = create_bitmap(TELA_X,TELA_Y); //util para tecnica de screen buffer
     BITMAP *fundo;
    fundo = create_bitmap(640,480);
    fundo = load_bitmap("image/back.bmp",NULL);
     BITMAP *alien1=create_bitmap(59,50);
    alien1=load_bitmap("image/sprites4.bmp",NULL);
    BITMAP *tanque=create_bitmap(51,46);
    tanque=load_bitmap("image/tanque0.bmp",NULL);
    BITMAP *tiro;
    tiro=create_bitmap(10,9);
    tiro=load_bitmap("image/tiro.bmp",NULL);
    BITMAP *naveB;
    naveB=load_bitmap("image/navebonus1.bmp",NULL);
    MIDI *musica;
    musica = load_midi("som/fundo.mid");
    inicializa_alien();
    inicializa_blocos();
    BITMAP *alienB[3][5];
    BITMAP *blocosperfeitos[15];
    BITMAP *blocosdanificados[15];
    BITMAP *blocosfudidos[15];
    for(i=0;i<15;i++)
    {
        blocosperfeitos[i]=create_bitmap(18,18);
        blocosperfeitos[i]=load_bitmap("image/bloco0.bmp",NULL);
        blocosdanificados[i]=create_bitmap(18,18);
        blocosdanificados[i]=load_bitmap("image/bloco1.bmp",NULL);
        blocosfudidos[i]=create_bitmap(18,18);
         blocosfudidos[i]=load_bitmap("image/bloco2.bmp",NULL);
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<5;j++)
        {
            alienB[i][j]=create_bitmap(59,50);
                if(i==0)
                {
                    alienB[i][j]=load_bitmap("image/sprites0.bmp",NULL);
                }
                else if(i==1)
                {
                    alienB[i][j]=load_bitmap("image/sprites2.bmp",NULL);
                }
                else if(i==2)
                {
                        alienB[i][j]=load_bitmap("image/sprites4.bmp",NULL);
                }
    }
    }
    if(!fundo || !alien1) //se de problema na image
    {
        allegro_message("Erro ao carregar imagem!");
        exit(1);
    }
    if(!som)
    {
        allegro_message("Problemas para iniciar som!");
        exit(1);
    }
    LOCK_FUNCTION(FecharJanela);
    set_close_button_callback(FecharJanela); //se apertar x entao chama a funcao fecharjanela
    play_midi(musica,TRUE);
    text_mode(-1); //texto transparente
    while(!(key[KEY_ESC] || fechar)) //enquanto o usuario não achou o jogo um lixo e apertou esc,ou fechou pela janela xD
    {

        if(func == 0)
        { //esse e o menu
            blit(fundo,TELA, 0, 0, 0, 0, 640, 480); //copia fundo para bitmap TELA
            textout_centre(TELA, font, "Space Invaders", 320,20 , makecol(0,255,0));
            textout_centre(TELA,font,"1.Jogar",320,120,makecol(0,255,0));
            if(fullscreen==true) //se estiver em modo fullscreen
                textout_centre(TELA,font,"2.Janela",320,140,makecol(0,255,0));
            else
                textout_centre(TELA,font,"2.Fullscreen",320,140,makecol(0,255,0));
            textout_centre(TELA,font,"3.Som",320,160,makecol(0,255,0));
            textout_centre(TELA,font,"4.Sair",320,180,makecol(0,255,0));
             masked_blit(alien1,TELA, 0, 0, x, y, 59, 50);
             if(key[KEY_UP])
             {
                y-=20;
             }
            if(key[KEY_DOWN])
            {
                y+=20;
            }
            if(y<100 || y>160) //se o usuario mexeu ao extremo para cima ou para baixo
                y=100;
            if(key[KEY_ENTER]) //se o usuario apertar enter verificar a opcao desejada
            {
                if(y==100)
                {
                    func=1; //variavel func cuida quando o jogo vai ser inicializado,se for 1 o jogo comeca
                }
                if(y==120)
                {
                    if(fullscreen==false)
                    {
                        set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,TELA_X,TELA_Y,0,0);
                        fullscreen=true;
                    }
                    else
                    {
                        set_gfx_mode(GFX_AUTODETECT_WINDOWED,TELA_X,TELA_Y,0,0);
                        fullscreen=false;
                    }
                }
                if(y==140)
                {
                    if(som==true) //se tiver tocando midi
                        stop_midi();  //para
                    else
                        play_midi(musica,TRUE);
                }
                if(y==160)
                    fechar=true;
            }

            blit(TELA,screen, 0, 0, 0, 0, TELA_X, TELA_Y); //copia TELA para o monitor
            }
        if(func==1)
        {
            clear(TELA);
            naveIA();
            ExeAliens();
            masked_blit(fundo,TELA,0,0,0,0,TELA_X,TELA_Y);
            masked_blit(tanque,TELA, 0, 0, tanquex,tanquey ,59, 50);
            for(i=0;i<3;i++)
            {
                for(j=0;j<5;j++)
                {
                    if(alien[i][j].status==true)
                    {
                        masked_blit(alienB[i][j],TELA,0,0,alien[i][j].x,alien[i][j].y,59,50);
                    }
                    printf("x=%d,y=%d\n",alien[i][j].x,alien[i][j].y);
                }
            }
            tiroAlien();
            if(EDisparoinimigo.status==1)
            {
                masked_blit(tiro,TELA,0,0,EDisparoinimigo.x,EDisparoinimigo.y,10,9);
                EDisparoinimigo.y+=5;
                if(EDisparoinimigo.y>620)
                    EDisparoinimigo.status=0;
                if(EDisparoinimigo.x >= tanquex && EDisparoinimigo.x<=tanquex+51 && EDisparoinimigo.y >= tanquey && EDisparoinimigo.y<=tanquey+46)
                {
                    EDisparoinimigo.status=0;
                    tanqueVida--;
                }
            }
            if(tanqueTiro==true)
            {
                masked_blit(tiro,TELA,0,0,tanqueTiroX,tanqueTiroY,10,9);
                tanqueTiroY-=5;
                colisaoNave();
                colisaoAlien();
            }
            if(NaveStatus==true)
            {
                 masked_blit(naveB,TELA,0,0,naveX,naveY,57,30);
                 naveX-=5;
            }
             for(i=0;i<15;i++)
            {
                if(EBloco[i].status==3)
                {
                    masked_blit(blocosperfeitos[i],TELA,0,0,EBloco[i].x,EBloco[i].y,18,18);
                }
                else if(EBloco[i].status==2)
                {
                    masked_blit(blocosdanificados[i],TELA,0,0,EBloco[i].x,EBloco[i].y,18,18);
                }
                else if(EBloco[i].status==1)
                {
                    masked_blit(blocosfudidos[i],TELA,0,0,EBloco[i].x,EBloco[i].y,18,18);
                }
            }
            textprintf(TELA,font,10,10,makecol(255,255,255),"Pontos: %i",pontos);
            textprintf(TELA,font,580,10,makecol(255,255,255),"Vida: %i",tanqueVida);
            blit(TELA,screen, 0, 0, 0, 0, TELA_X, TELA_Y); //copia TELA para o monitor
            controla_tanque();
            colisaoBlocos();
            if(tanqueVida==0)
            {
                break;
            }

        }
       rest(faseV); //controla a velocidade do jogo,inicialmente comeca com 50,depois vai diminuindo pra ficar mais rapido
    }
     END_OF_MAIN()
    return 0;
}
 void FecharJanela()
    {
        fechar=true;
    }END_OF_FUNCTION(FecharJanela)

void controla_tanque()
{
    if(key[KEY_SPACE] && tanqueTiro==false)
    {
        tanqueTiro=true;
        tanqueTiroX=tanquex+20;
        tanqueTiroY=tanquey;
    }
    if(key[KEY_LEFT])
    {
        if(tanquex>46)
        {
        tanquex-=5;
        }
    }
    else if(key[KEY_RIGHT])
    {
        if(tanquex<520)
        {
            tanquex+=5;
        }
    }
    if(tanqueTiro==true && tanqueTiroY<0)
        tanqueTiro=false;
}

void naveIA(void)
{
    NaveEspera++;
    if(NaveEspera>50 && NaveStatus==false)
    {
        NaveStatus=true;
        naveX=520,naveY=37;
    }
}
void colisaoNave()
{
        if(tanqueTiroX >= naveX && tanqueTiroX <= naveX+57 && tanqueTiroY >= naveY && tanqueTiroY<=naveY+30 && NaveStatus==true)
        {
            NaveStatus=false;
            NaveEspera=0;
            tanqueTiro=false;
            pontos+=30;
        }
        if(naveX<0 && NaveStatus==true)
        {
            NaveStatus=false;
            NaveEspera=0;
        }
}
void inicializa_alien(void)
{
    int i,j,pontox=320,pontoy=67,valorx=0,valory=0;

    for(i=0;i<3;i++)
    {
        for(j=0;j<5;j++)
        {
            alien[i][j].x=pontox+valorx;
            alien[i][j].y=pontoy+valory;
            alien[i][j].data=true;
            alien[i][j].status=true;
            valorx=valorx+59;
        }
        valory=valory+50;
        valorx=0;
    }
}
void inicializa_blocos(void)
{
    int i;
    EBloco[0].x=25; EBloco[0].y=315;
EBloco[1].x=43; EBloco[1].y=315;
EBloco[2].x=61; EBloco[2].y=315;
EBloco[3].x=176; EBloco[3].y=315;
EBloco[4].x=194; EBloco[4].y=315;
EBloco[5].x=212; EBloco[5].y=315;
EBloco[6].x=324; EBloco[6].y=315;
EBloco[7].x=342; EBloco[7].y=315;
EBloco[8].x=360; EBloco[8].y=315;
EBloco[9].x=25; EBloco[9].y=333;
EBloco[10].x=61; EBloco[10].y=333;
EBloco[11].x=176; EBloco[11].y=333;
EBloco[12].x=212; EBloco[12].y=333;
EBloco[13].x=324; EBloco[13].y=333;
EBloco[14].x=360; EBloco[14].y=333;
for(i=0;i<15;i++)
{
        EBloco[i].status=3;
}
}

void alienIA(int Tipo,int NAlien)
{

if(alien[Tipo][NAlien].status==true)
{
    if(alien[Tipo][NAlien].orientacao==0)
    {
        alien[Tipo][NAlien].x-=2;
    }
}
if (alien[Tipo][NAlien].x<40)
{
    alien[Tipo][NAlien].x+=2;
    for(t1=0; t1<3; t1++)
    {
        for (p1=0; p1<5; p1++)
    {
            alien[t1][p1].orientacao=1;
            alien[t1][p1].y+=5;
    }
}
}
    if (alien[Tipo][NAlien].orientacao==1)
{
    alien[Tipo][NAlien].x+=2;
}
    if (alien[Tipo][NAlien].x>580)
{
    for (t1=0; t1<3; t1++)
{
        for (p1=0; p1<5; p1++)
{
    alien[t1][p1].orientacao=0;
    alien[t1][p1].y+=5;
}
}
}
if(alien[Tipo][NAlien].y>431)
    {
           tanqueVida=0;
    }

}
void ExeAliens()
{
    int t,p;
for (t=0; t<3; t++)
 {
  for (p=0; p<5; p++)
  {
   if (alien[t][p].status==true)
    {
     alienIA(t, p);
    }

  }// fecha segundo for
 }// fecha primeiro for

}
void colisaoAlien()
{
    int t,p;
    for(t=0;t<3;t++)
    {
        for(p=0;p<5;p++)
        {
              if(tanqueTiroX >= alien[t][p].x && tanqueTiroX <= alien[t][p].x + 59 && tanqueTiroY >= alien[t][p].y && tanqueTiroY<=alien[t][p].y +50 && alien[t][p].status==true)
              {
                  pontos+=5;
                  alien[t][p].status=false;
                  tanqueTiro=false;
              }

        }
    }
}


void tiroAlien()
{
    if (EDisparoinimigo.status==0)
  {

   if (alien[2][EDisparoinimigo.Ntiro].status==1)
    {
     EDisparoinimigo.status=1;
     EDisparoinimigo.x=alien[2][EDisparoinimigo.Ntiro].x+25;
     EDisparoinimigo.y=alien[2][EDisparoinimigo.Ntiro].y+50;
    }

   else if (alien[1][EDisparoinimigo.Ntiro].status==1)
    {
     EDisparoinimigo.status=1;
     EDisparoinimigo.x=alien[1][EDisparoinimigo.Ntiro].x+25;
     EDisparoinimigo.y=alien[1][EDisparoinimigo.Ntiro].y+50;
    }

   else if (alien[0][EDisparoinimigo.Ntiro].status==1)
    {
     EDisparoinimigo.status=1;
     EDisparoinimigo.x=alien[0][EDisparoinimigo.Ntiro].x+25;
     EDisparoinimigo.y=alien[0][EDisparoinimigo.Ntiro].y+50;
    }




   if (EDisparoinimigo.orientacao==0 && EDisparoinimigo.Ntiro>0)
    {
     EDisparoinimigo.Ntiro--;
      if (EDisparoinimigo.Ntiro==0)
       {
        EDisparoinimigo.orientacao=1;
        EDisparoinimigo.Ntiro--;
       }
    }

   if (EDisparoinimigo.orientacao==1 && EDisparoinimigo.Ntiro<4)
    {
     EDisparoinimigo.Ntiro++;
      if (EDisparoinimigo.Ntiro==4)
       {
        EDisparoinimigo.orientacao=0;
       }
    }

  }
}
void colisaoBlocos()
{
        int i;
        if(tanqueTiro==true)
        {
        for(i=0;i<15;i++)
        {
            if(EBloco[i].status>0 && tanqueTiroX >= EBloco[i].x && tanqueTiroX<=EBloco[i].x+18 && tanqueTiroY>=EBloco[i].y && tanqueTiroY <=EBloco[i].y+18)
            {
                EBloco[i].status--;
                tanqueTiro=false;
            }
        }
        }
        if(EDisparoinimigo.status==true)
        {
             for(i=0;i<15;i++)
        {
            if(EBloco[i].status>0 && EDisparoinimigo.x>=EBloco[i].x && EDisparoinimigo.x<=EBloco[i].x+18 && EDisparoinimigo.y>=EBloco[i].y && EDisparoinimigo.y <=EBloco[i].y+18)
            {
                EBloco[i].status--;
                EDisparoinimigo.status=false;
            }
        }
        }
}







