#include <iostream>
#define TAM 8

using namespace std;

void pDama (char tab[][TAM]);
void mostraTab (char tab[][TAM]);
void jogar (char tab[][TAM], int vez);
void troca (char tab[][TAM], int jogL, char jogC, int destL, char destC);
bool validaJogada (char tab[][TAM], int numJog, char letJog, int nNumJog, char nLetJog, int vez);
bool fimJogo(char tab[TAM][TAM],int& vez);

int main ()
{
    char tab[TAM][TAM];
    int i, j, vez=0;
    bool busca=true;

    pDama(tab);

    do
    {
        mostraTab(tab);
        jogar(tab,vez);
        if (vez==0)
            vez=1;
        else
            vez=0;

        busca=fimJogo(tab,vez);

    }
    while(busca);
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

void jogar (char tab[][TAM], int vez) //recebe a casa e move a peça do jogador,caso possível
{
    int numJog,nNumJog,captura,contX,contO;
    char letJog,nLetJog, jogada;
    bool resultValida,testeComer;

    if(vez==0)
        jogada='X';
    else
        jogada='O';

    cout << "[Vez do jogador " << jogada <<"]"<<endl;
    cout << "Selecione a peça para mover(ex: b 4): ";
    cin >> letJog >> numJog;

    while(tab[numJog-1][(int)letJog-97]!=jogada)//não permite que o jogador jogue peça diferente da sua vez
    {
        cout << "Peça invalida! Selecione outra peça:";
        cin >> letJog >> numJog;
    }

    cout << "Digite o local para mover:";
    cin >> nLetJog >> nNumJog; //nLetJog == letra da casa para qual vai ser mover a peça, nNumJog== linha para qual a peça vai ser movida

    resultValida = validaJogada (tab, numJog, letJog, nNumJog, nLetJog, vez);

    while(resultValida)
    {
        cout<<"Casa inválida! Selecione outra casa:";
        cin >> nLetJog >> nNumJog;
        resultValida = validaJogada (tab, numJog, letJog, nNumJog, nLetJog, vez);
    }

    numJog--;
    nNumJog--;

    troca(tab,numJog,letJog,nNumJog,nLetJog);//troca a casa depois de receber uma casa válida
}

void troca (char tab[][TAM], int jogL, char jogC, int destL, char destC) //troca a peça de casa
{
    char temp;
    temp=tab[jogL][(int)jogC-97];
    tab[jogL][(int)jogC-97]=tab[destL][(int)destC-97];
    tab[destL][(int)destC-97]=temp;
}

bool validaJogada (char tab[][TAM], int numJog, char letJog, int nNumJog, char nLetJog, int vez) //testa se a jogada é válida
{
    char pecaCome;
    int resultCome;
    if (vez==0)
        pecaCome='O';
    else
        pecaCome='X';

    if(nNumJog-numJog<5 && nLetJog-letJog<5 && tab[nNumJog-1][(int)nLetJog-97]==' ')
    {
        if (nNumJog-numJog==1 || (int)nLetJog-(int)letJog==1 || nNumJog-numJog==-1 || (int)nLetJog-(int)letJog==-1) // Mover 1 casa
        {
            if (vez==0) // Mover 1 casa diagonal principal/secundaria X
            {
                if ((nNumJog-numJog==1 && (int)nLetJog-(int)letJog==1) || (nNumJog-numJog==1 && (int)nLetJog-(int)letJog==-1)) // Valida se a jogada é permitida
                    return false;
                else
                    return true;
            }
            else // Mover 1 casa diagonal principal/secundaria O
            {
                if ((nNumJog-numJog==-1 && (int)nLetJog-(int)letJog==-1) || (nNumJog-numJog==-1 && (int)nLetJog-(int)letJog==1)) // Valida se a jogada é permitida
                    return false;
                else
                    return true;
            }
        }
        else if (nNumJog-numJog==2 || (int)nLetJog-(int)letJog==2 || nNumJog-numJog==-2 || (int)nLetJog-(int)letJog==-2) // Mover e comer 1 peça
        {
            if (nNumJog-numJog==2 && (int)nLetJog-(int)letJog==2) // Comer 1 peça diagonal principal descendo
            {
                if (tab[nNumJog-2][(int)nLetJog-98]==pecaCome)
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog-2][(int)nLetJog-98]=' ';
                    }
                    return false;
                }
            }
            else if (nNumJog-numJog==2 && (int)nLetJog-(int)letJog==-2) // Comer 1 peça diagonal secundaria descendo
            {
                if (tab[nNumJog-2][(int)nLetJog-96]==pecaCome)
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog-2][(int)nLetJog-96]=' ';
                    }
                    return false;
                }
            }
            else if (nNumJog-numJog==-2 && (int)nLetJog-(int)letJog==-2) // Comer 1 peça diagonal principal subindo
            {
                cout << "nNumJog: " << nNumJog << endl;
                cout << "(int)nLetJog-96: " << (int)nLetJog-96 << endl;
                if (tab[nNumJog][(int)nLetJog-96]==pecaCome)
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog][(int)nLetJog-96]=' ';
                    }
                    return false;
                }
            }
            else if (nNumJog-numJog==-2 && (int)nLetJog-(int)letJog==2) // Comer 1 peça diagonal secundaria subindo
            {
                if (tab[nNumJog][(int)nLetJog-98]==pecaCome)
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog][(int)nLetJog-98]=' ';
                    }
                    return false;
                }
            }
        }
        else if (nNumJog-numJog==4 || (int)nLetJog-(int)letJog==4 || nNumJog-numJog==-4 || (int)nLetJog-(int)letJog==-4) // Mover e comer 2 peças
        {
            if (nNumJog-numJog==4 && (int)nLetJog-(int)letJog==4) // Comer 2 peças diagonal principal descendo
            {
                if ((tab[nNumJog-2][(int)nLetJog-98]==pecaCome) && (tab[nNumJog-4][(int)nLetJog-100]==pecaCome))
                {
                    cout << "nNumJog" << nNumJog << endl;
                    cout << "nLetJog" << nLetJog << endl;
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog-2][(int)nLetJog-98]=' ';
                        tab[nNumJog-4][(int)nLetJog-100]=' ';
                    }
                    return false;
                }
            }
            else if (nNumJog-numJog==4 && (int)nLetJog-(int)letJog==-4) // Comer 2 peças diagonal secundaria descendo
            {
                if ((tab[nNumJog-2][(int)nLetJog-96]==pecaCome) && (tab[nNumJog-4][(int)nLetJog-94]==pecaCome))
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog-2][(int)nLetJog-96]=' ';
                        tab[nNumJog-4][(int)nLetJog-94]=' ';
                    }
                    return false;
                }
            }
            else if (nNumJog-numJog==-4 && (int)nLetJog-(int)letJog==-4) // Comer 2 peças diagonal principal subindo
            {
                if ((tab[nNumJog][(int)nLetJog-96]==pecaCome) && (tab[nNumJog+2][(int)nLetJog-94]==pecaCome))
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog][(int)nLetJog-96]=' ';
                        tab[nNumJog+2][(int)nLetJog-94]=' ';
                    }
                    return false;
                }
            }
            else if (nNumJog-numJog==-4 && (int)nLetJog-(int)letJog==4) // Comer 2 peças diagonal secundaria subindo
            {
                if ((tab[nNumJog][(int)nLetJog-98]==pecaCome) && (tab[nNumJog+2][(int)nLetJog-100]==pecaCome))
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog][(int)nLetJog-98]=' ';
                        tab[nNumJog+2][(int)nLetJog-100]=' ';
                    }
                    return false;
                }
            }
            else if (nNumJog-numJog==4 && (int)nLetJog-(int)letJog==0) // Comer 2 peças coluna descendo
            {
                if ((tab[nNumJog-2][(int)nLetJog-98]==pecaCome) && (tab[nNumJog-4][(int)nLetJog-98]==pecaCome)) // Comer 2 peças coluna descendo, lado esquerdo
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog-2][(int)nLetJog-98]=' ';
                        tab[nNumJog-4][(int)nLetJog-98]=' ';
                    }
                    return false;
                }
                else if ((tab[nNumJog-2][(int)nLetJog-96]==pecaCome) && (tab[nNumJog-4][(int)nLetJog-96]==pecaCome)) // Comer 2 peças coluna descendo, lado direito
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog-2][(int)nLetJog-96]=' ';
                        tab[nNumJog-4][(int)nLetJog-96]=' ';
                    }
                    return false;
                }
            }
            else if (nNumJog-numJog==-4 && (int)nLetJog-(int)letJog==0) // Comer 2 peças coluna subindo
            {
                if ((tab[nNumJog][(int)nLetJog-98]==pecaCome) && (tab[nNumJog+2][(int)nLetJog-98]==pecaCome)) // Comer 2 peças coluna subindo, lado esquerdo
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog][(int)nLetJog-98]=' ';
                        tab[nNumJog+2][(int)nLetJog-98]=' ';
                    }
                    return false;
                }
                else if ((tab[nNumJog][(int)nLetJog-96]==pecaCome) && (tab[nNumJog+2][(int)nLetJog-96]==pecaCome)) // Comer 2 peças coluna subindo, lado direito
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog][(int)nLetJog-96]=' ';
                        tab[nNumJog+2][(int)nLetJog-96]=' ';
                    }
                    return false;
                }
            }
            else if (nNumJog-numJog==0 && (int)nLetJog-(int)letJog==4) // Comer 2 peças linha direita
            {
                if ((tab[nNumJog-2][(int)nLetJog-98]==pecaCome) && (tab[nNumJog-2][(int)nLetJog-100]==pecaCome)) // Comer 2 peças linha direita, lado de cima
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog-2][(int)nLetJog-98]=' ';
                        tab[nNumJog-2][(int)nLetJog-100]=' ';
                    }
                    return false;
                }
                else if ((tab[nNumJog][(int)nLetJog-98]==pecaCome) && (tab[nNumJog][(int)nLetJog-100]==pecaCome)) // Comer 2 peças linha direita, lado de cima
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog][(int)nLetJog-98]=' ';
                        tab[nNumJog][(int)nLetJog-100]=' ';
                    }
                    return false;
                }
            }
            else if (nNumJog-numJog==0 && (int)nLetJog-(int)letJog==-4) // Comer 2 peças linha esquerda
            {
                if ((tab[nNumJog-2][(int)nLetJog-94]==pecaCome) && (tab[nNumJog-2][(int)nLetJog-96]==pecaCome)) // Comer 2 peças linha esquerda, lado de cima
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog-2][(int)nLetJog-94]=' ';
                        tab[nNumJog-2][(int)nLetJog-96]=' ';
                    }
                    return false;
                }
                else if ((tab[nNumJog][(int)nLetJog-94]==pecaCome) && (tab[nNumJog][(int)nLetJog-96]==pecaCome)) // Comer 2 peças linha esquerda, lado de cima
                {
                    cout << "Comer peça adversaria? [1-SIM] / [2-NÃO]: ";
                    cin >> resultCome;
                    if (resultCome==1)
                    {
                        tab[nNumJog][(int)nLetJog-94]=' ';
                        tab[nNumJog][(int)nLetJog-96]=' ';
                    }
                    return false;
                }
            }
        }
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
