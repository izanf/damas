#include <iostream>
#define TAM 8
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

struct dadosJogador
{
    char nome[100];
};

struct jogadores
{
    dadosJogador nomes[2];
};

void pDama (char tab[][TAM]);
void mostraTab (char tab[][TAM]);
void jogar (char tab[][TAM], int vez,jogadores j, bool compMode);
void troca (char tab[][TAM], int jogL, char jogC, int destL, char destC);
bool validaJogada (char tab[][TAM], int numJog, int letJog, int nNumJog, int nLetJog, int vez);
bool fimJogo(char tab[TAM][TAM],int& vez);
void compON (char tab[][TAM], int numJog, int letJog, int nNumJog, int nLetJog, int vez);
void geraNum (int gerados[]);

int main ()
{
    char tab[TAM][TAM];
    int i, j, vez=0,opcao;
    bool busca,compMode=false;

    jogadores jogs;

    cout<<"     ______   _______  __   __  _______  _______ "<<endl;
    cout<<"    |      | |   _   ||  |_|  ||   _   ||       |"<<endl;
    cout<<"    |  _    ||  |_|  ||       ||  |_|  ||  _____|"<<endl;
    cout<<"    | | |   ||       ||       ||       || |_____ "<<endl;
    cout<<"    | |_|   ||       ||       ||       ||_____  |"<<endl;
    cout<<"    |       ||   _   || ||_|| ||   _   | _____| |"<<endl;
    cout<<"    |______| |__| |__||_|   |_||__| |__||_______|"<<endl;

    Sleep(3);

    cout<<"MENU"<<endl;
    cout<<"(1)Jogar humano X humano\n(2)Jogar contra computador\n(3)Sair\nInsira a opção desejada:";
    cin>>opcao;

    if(opcao==1)
    {
        for(int i=0; i<2; i++)
        {
            cout<<"Insira o nome do Jogador "<<i+1<<":";
            cin.get();
            cin.getline(jogs.nomes[i].nome,100);
        }
        busca=true;
    }
    else if(opcao==2)
    {
        cout<<"Insira o nome do Jogador:";
        cin.get();
        cin.getline(jogs.nomes[0].nome,100);
        strcpy(jogs.nomes[1].nome,"Computador");
        compMode=true;
        busca=true;
    }
    else if(opcao==3)
        busca=false;

    system("cls");

    pDama(tab);

    while(busca)
    {

        mostraTab(tab);
        jogar(tab,vez,jogs,compMode);
        if (vez==0)
            vez=1;
        else
            vez=0;

        busca=fimJogo(tab,vez);
    }
    return 0;
}

void pDama (char tab[][TAM]) //preenche o tabuleiro com os caracteres necessários
{
    int i, j;
    for (i=0; i<TAM; i++)
    {
        for (j=0; j<TAM; j++)
        {
            if ((i+j)%2!=0)
            {
                tab[i][j]=' ';
                if(i>=0 && i<3)
                    tab[i][j]='X';
                if(i>=5 && i<8)
                    tab[i][j]='O';
            }
            else
                tab[i][j]='|';
        }
    }
}

void mostraTab (char tab[][TAM]) //exibe o tabuleiro
{
    int i, j;
    cout<<endl;
    for (i=97; i<105; i++)
    {
        if (i==97)
        cout << "  ";
        cout << "  " << (char) i << " ";
    }
    cout << endl;

    for (i=0; i<TAM; i++)
    {
        cout << "  |---|---|---|---|---|---|---|---|" << endl;
        for (j=0; j<TAM; j++)
        {
            if (j==0)
                cout << i+1 << " ";
            cout << "| " << tab[i][j] << " ";
            if (j==7)
                cout <<"|";
        }
        cout << endl;
        if (i==7)
            cout << "  |---|---|---|---|---|---|---|---|" << endl;
    }
    for (i=97; i<105; i++)
    {

        if (i==97)
            cout << "  ";
        cout << "  " << (char) i << " ";
    }
    cout << endl;


    cout<<endl;
}

void jogar (char tab[][TAM], int vez,jogadores j, bool compMode) //recebe a casa e move a peça do jogador,caso possível
{
    int numJog,nNumJog,captura,contX,contO,jogada,letJog,nLetJog;
    char carac,letJogI,nLetJogI;
    bool resultValida,testeComer;

    if(vez==0)
    {
        carac='X';
        jogada=0;
    }
    else
    {
        carac='O';
        jogada=1;
    }
    if (!compMode || vez==0)
    {
        cout << "ENTROU!!" << endl;
        cout << "[Vez do jogador " << j.nomes[jogada].nome <<" ("<<carac<<")]"<<endl;

        cout << "Selecione a peça para mover(ex: b 4): ";
        cin >> letJogI >> numJog;
        while(tab[numJog-1][(int)letJogI-97]!=carac || ((int)letJogI<97 || (int)letJogI>104)) //não permite que o jogador jogue peça diferente da sua vez
        {
            cout << "Peça invalida! Selecione outra peça:";
            cin >> letJogI >> numJog;
        }
        letJog = letJogI-97;

        cout << "Digite o local para mover:";
        cin >> nLetJogI >> nNumJog; //nLetJog == letra da casa para qual vai ser mover a peça, nNumJog== linha para qual a peça vai ser movida
        nLetJog = nLetJogI-97;
        resultValida = validaJogada (tab, numJog, letJog, nNumJog, nLetJog, vez);
        while(resultValida)
        {
            cout<<"Casa inválida! Selecione outra casa:";
            cin >> nLetJogI >> nNumJog;
            nLetJog=nLetJogI-97;
            resultValida = validaJogada (tab, numJog, letJog, nNumJog, nLetJog, vez);
        }

        numJog--;
        nNumJog--;
    }
    else
    {
        compON(tab, letJog, numJog, nLetJog, nNumJog, vez);
    }
    cout << numJog << endl;
    cout << letJog << endl;
    cout << nLetJog << endl;
    cout << nNumJog << endl;

    troca(tab,numJog,letJog,nNumJog,nLetJog);//troca a casa depois de receber uma casa válida
}

void troca (char tab[][TAM], int jogL, char jogC, int destL, char destC) //troca a peça de casa
{
    char temp;
    temp=tab[jogL][(int)jogC];
    tab[jogL][(int)jogC]=tab[destL][(int)destC];
    tab[destL][(int)destC]=temp;
}

bool validaJogada (char tab[][TAM], int numJog, int letJog, int nNumJog, int nLetJog, int vez) //testa se a jogada é válida
{
    char pecaCome;
    int resultCome, posL1=9, posC1=9, posC2=9, posL2=9,v1,v2;

    if (vez==0)
    {
        v1=1;
        v2=-1;
        pecaCome='O';
    }
    else
    {
        v1=-1;
        v2=1;
        pecaCome='X';
    }

    if(nNumJog-numJog<5 && nLetJog-letJog<5)
    {
        if (nNumJog-numJog==1 || nLetJog-letJog==1 || nNumJog-numJog==-1 || nLetJog-letJog==-1) // Mover 1 casa
        {
            // Mover 1 casa diagonal principal/
            if ((nNumJog-numJog==v1 && nLetJog-letJog==v1) || (nNumJog-numJog==v1 && nLetJog-letJog==v2)) // Valida se a jogada é permitida
               {
                  return false;
            cout << "ENTROU!!!" << endl;
               }
            else
                return true;
        }
        else if (nNumJog-numJog==2 || nLetJog-letJog==2 || nNumJog-numJog==-2 || nLetJog-letJog==-2) // Mover e comer 1 peça
        {
            if (nNumJog-numJog==2 && nLetJog-letJog==2 && tab[nNumJog-2][nLetJog-1]==pecaCome) // Comer 1 peça diagonal principal descendo
            {
                posL1=nNumJog-2;
                posC1=nLetJog-1;
            }
            else if (nNumJog-numJog==2 && nLetJog-letJog==-2 && tab[nNumJog-2][nLetJog+1]==pecaCome) // Comer 1 peça diagonal secundaria descendo
            {
                posL1=nNumJog-2;
                posC1=nLetJog+1;
            }
            else if (nNumJog-numJog==-2 && nLetJog-letJog==-2 && tab[nNumJog][nLetJog+1]==pecaCome) // Comer 1 peça diagonal principal subindo
            {
                posL1=nNumJog;
                posC1=nLetJog+1;
            }
            else if (nNumJog-numJog==-2 && nLetJog-letJog==2 && tab[nNumJog][nLetJog-1]==pecaCome) // Comer 1 peça diagonal secundaria subindo
            {
                posL1=nNumJog;
                posC1=nLetJog-1;
            }
        }
        else if (nNumJog-numJog==4 || nLetJog-letJog==4 || nNumJog-numJog==-4 || nLetJog-letJog==-4) // Mover e comer 2 peças
        {
            if (nNumJog-numJog==4 && nLetJog-letJog==4 && (tab[nNumJog-2][nLetJog-1]==pecaCome) && (tab[nNumJog-4][nLetJog-3]==pecaCome)) // Comer 2 peças diagonal principal descendo
            {
                posL1=nNumJog-2;
                posC1=nLetJog-1;
                posL2=nNumJog-4;
                posC2=nLetJog-3;
            }
            else if (nNumJog-numJog==4 && nLetJog-letJog==-4 && (tab[nNumJog-2][nLetJog+1]==pecaCome) && (tab[nNumJog-4][nLetJog+3]==pecaCome)) // Comer 2 peças diagonal secundaria descendo
            {
                posL1=nNumJog-2;
                posC1=nLetJog+1;
                posL2=nNumJog-4;
                posC2=nLetJog+3;
            }
            else if (nNumJog-numJog==-4 && nLetJog-letJog==-4 && (tab[nNumJog][nLetJog+1]==pecaCome) && (tab[nNumJog+2][nLetJog+3]==pecaCome)) // Comer 2 peças diagonal principal subindo
            {
                posL1=nNumJog;
                posC1=nLetJog+1;
                posL2=nNumJog+2;
                posC2=nLetJog+3;
            }
            else if (nNumJog-numJog==-4 && nLetJog-letJog==4 && (tab[nNumJog][nLetJog-1]==pecaCome) && (tab[nNumJog+2][nLetJog-3]==pecaCome)) // Comer 2 peças diagonal secundaria subindo
            {
                posL1=nNumJog;
                posC1=nLetJog-1;
                posL2=nNumJog+2;
                posC2=nLetJog-3;
            }
            else if (nNumJog-numJog==4 && nLetJog-letJog==0) // Comer 2 peças coluna descendo
            {
                if ((tab[nNumJog-2][nLetJog-1]==pecaCome) && (tab[nNumJog-4][nLetJog-1]==pecaCome)) // Comer 2 peças coluna descendo, lado esquerdo
                {
                    posL1=nNumJog-2;
                    posC1=nLetJog-1;
                    posL2=nNumJog-4;
                    posC2=nLetJog-1;
                }
                else if ((tab[nNumJog-2][nLetJog+1]==pecaCome) && (tab[nNumJog-4][nLetJog+1]==pecaCome)) // Comer 2 peças coluna descendo, lado direito
                {
                    posL1=nNumJog-2;
                    posC1=nLetJog+1;
                    posL2=nNumJog-4;
                    posC2=nLetJog+1;
                }
            }
            else if (nNumJog-numJog==-4 && nLetJog-letJog==0) // Comer 2 peças coluna subindo
            {
                if ((tab[nNumJog][nLetJog-1]==pecaCome) && (tab[nNumJog+2][nLetJog-1]==pecaCome)) // Comer 2 peças coluna subindo, lado esquerdo
                {
                    posL1=nNumJog;
                    posC1=nLetJog-1;
                    posL2=nNumJog+2;
                    posC2=nLetJog-1;
                }
                else if ((tab[nNumJog][nLetJog+1]==pecaCome) && (tab[nNumJog+2][nLetJog+1]==pecaCome)) // Comer 2 peças coluna subindo, lado direito
                {
                    posL1=nNumJog;
                    posC1=nLetJog+1;
                    posL2=nNumJog+2;
                    posC2=nLetJog+1;
                }
            }
            else if (nNumJog-numJog==0 && nLetJog-letJog==4) // Comer 2 peças linha direita
            {
                if ((tab[nNumJog-2][nLetJog-1]==pecaCome) && (tab[nNumJog-2][nLetJog-3]==pecaCome)) // Comer 2 peças linha direita, lado de cima
                {
                    posL1=nNumJog-2;
                    posC1=nLetJog-1;
                    posL2=nNumJog-2;
                    posC2=nLetJog-3;
                }
                else if ((tab[nNumJog][nLetJog-1]==pecaCome) && (tab[nNumJog][nLetJog-3]==pecaCome)) // Comer 2 peças linha direita, lado de cima
                {
                    posL1=nNumJog;
                    posC1=nLetJog-1;
                    posL2=nNumJog;
                    posC2=nLetJog-3;
                }
            }
            else if (nNumJog-numJog==0 && nLetJog-letJog==-4) // Comer 2 peças linha esquerda
            {
                if ((tab[nNumJog-2][nLetJog+3]==pecaCome) && (tab[nNumJog-2][nLetJog+1]==pecaCome)) // Comer 2 peças linha esquerda, lado de cima
                {
                    posL1=nNumJog-2;
                    posC1=nLetJog+3;
                    posL2=nNumJog-2;
                    posC2=nLetJog+1;
                }
                else if ((tab[nNumJog][nLetJog+3]==pecaCome) && (tab[nNumJog][nLetJog+1]==pecaCome)) // Comer 2 peças linha esquerda, lado de cima
                {
                    posL1=nNumJog;
                    posC1=nLetJog+3;
                    posL2=nNumJog;
                    posC2=nLetJog+1;
                }
            }
        }
    }

    if (posL1<9 && posC1<9)
    {
        cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
        cin >> resultCome;
        if (resultCome==1)
        {
            tab[posL1][posC1]=' ';
            if (posL2<9 && posC2<9)
            {
                tab[posL2][posC2]=' ';
            }
        }
        return false;
    }
    else
        return true;
}

bool fimJogo(char tab[TAM][TAM],int& vez)
{
    int i,j,contX=0,contO=0,cont=0,a=0,b=7,ok1=0,ok2=0,jg=0;

    for(i=0; i<TAM; i++)
    {
        for(j=0; j<TAM; j++)
        {
            if(tab[i][j]=='X')
                contX++;
            else if(tab[i][j]=='O')
                contO++;
            else if(tab[i][j]==' ')
                cont++;
        }
    }
    for(j=0; j<TAM; j++)
    {
        if(tab[a][j]=='O')
            ok1++;
        else if(tab[b][j]=='X')
            ok2++;
    }

    if((contX>=contO && (contO==0 || contO<=4) && cont>=24) || (ok1<=4 && ok2<=4 && cont>=24))
    {
        cout<<"Fim de jogo!\nDeseja jogar novamente?[1-SIM][2-NÃO]";
        cin>>jg;
        if(jg==1)
        {
            pDama(tab);
            vez=0;
            return true;
        }
        else
            return false;
    }
    else if((contO>=contX && (contX==0 || contX<=4) && cont>=24)|| (ok1<=4 && ok2<=4 && cont>24))
    {
        cout<<"Fim de jogo!\nDeseja jogar novamente? [1-SIM]|[2-NÃO] = ";
        cin>>jg;
        if(jg==1)
        {
            pDama(tab);
            vez=0;
            return true;
        }
        else
            return false;
    }
    else
        return true;
}
void menuJ(bool& comp,bool& busca,jogadores *jogs)
{
    int opcao;
}

void compON (char tab[][TAM], int numJog, int letJog, int nNumJog, int nLetJog, int vez)
{
    int gerados[2], result=true;
    cout << "COMPUTER MODE!! Aguarde";
    while (result)
    {
        cout << "..";
        geraNum(gerados);
        letJog = gerados[0];
        numJog = gerados[1];
        while(tab[numJog][(int)letJog]!='O') //não permite que o computador jogue peça diferente da sua vez
        {
            geraNum(gerados);
            letJog = gerados[0];
            numJog = gerados[1];
        }
        if (tab[numJog-1][(int)letJog-1]=='X') // Comer 1 peça diagonal principal subindo
        {
            nNumJog = numJog-2;
            nLetJog = letJog-2;
        }
        else if (tab[numJog-1][(int)letJog+1]=='X') // Comer 1 peça diagonal secundaria subindo
        {
            nNumJog = numJog-2;
            nLetJog = letJog+2;
        }
        else if (tab[numJog-1][(int)letJog-1]==' ') // Comer 1 peça diagonal principal subindo
        {
            nNumJog = numJog-1;
            nLetJog = letJog-1;
        }
        else if (tab[numJog-1][(int)letJog+1]==' ') // Comer 1 peça diagonal secundaria subindo
        {
            nNumJog = numJog-1;
            nLetJog = letJog+1;
        }
        else
        {
            nNumJog = 5;
            nLetJog = 5;
        }
        if (nNumJog<5 && nLetJog<5)
            result = validaJogada(tab,numJog,letJog,nNumJog,nLetJog,vez);
    }
    cout << numJog << endl;
    cout << letJog << endl;
    cout << nNumJog << endl;
    cout << nLetJog << endl;
}

void geraNum (int gerados[])
{
    int i;
    srand(time(0));
    for (i=0; i<2; i++)
    {
        gerados[i] = rand() % 8;
    }
}
