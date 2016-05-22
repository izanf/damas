//Falta:
//Oferecer a opção de comer a peça do oponente
//desenvolver a parte contra computador
//implementar um menu

#include <iostream>

using namespace std;

#define TAM 8

// Função de preenchimento do padrão dama (Tabuleiro preto e branco)
void pDama (char tab[][TAM]);
void mostraTab (char tab[][TAM]);
void jogar (char tab[][TAM], int vez);
void troca (char tab[][TAM], int jogL, char jogC, int destL, char destC);
bool validaJogada (char tab[][TAM], int numJog, char letJog, int nNumJog, char nLetJog, int vez);
bool comer(char tab[][TAM], int nNumJog, char nLetJog,int vez);
void capturaPeca(int decisao,int &contX,int &contO,int vez,char tab[][TAM],int nNumJog,char nLetJog);

int main ()
{
    char tab[TAM][TAM];
    int i, j, vez=0;
    bool busca=true;

    pDama(tab);
    while (busca==true)
    {
        mostraTab(tab);
        jogar(tab,vez);
        if (vez==0)
            vez=1;
        else
            vez=0;
    }

    return 0;
}

void pDama (char tab[][TAM]) //preenche o tabuleiro
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
                tab[i][j]='||';
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

    while(tab[numJog-1][(int)letJog-97]!=jogada)
    {
        cout << "Peça invalida! Selecione outra peça.";
        cin >> letJog >> numJog;
    }

    cout<<"Digite o local para mover:";
    cin>>nLetJog>>nNumJog;

    resultValida = validaJogada (tab, numJog, letJog, nNumJog, nLetJog, vez);

    while(resultValida)
    {
        cout<<"Casa inválida! Selecione outra casa:";
        cin>>nLetJog>>nNumJog;
    }

    numJog--;
    nNumJog--;

    troca(tab,numJog,letJog,nNumJog,nLetJog);

    testeComer=comer(tab,nNumJog,nLetJog,vez);


    if(testeComer)
    {
        cout<<"Desejar comer a peça do oponente?"<<'\t'<<"1-Sim"<<'\t'<<"2- Não"<<endl;
        cin>>captura;
    }
    capturaPeca(captura,contX,contO,vez,tab,nNumJog,nLetJog);


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
    if (vez==0)
    {
        if((nNumJog>=(numJog+1)) && (tab[nNumJog-1][(int)nLetJog-97]==' '))
            return false;
        else
            return true;
    }
    else if (vez==1)
    {
        if ((nNumJog<=(numJog+1)) && (tab[nNumJog-1][(int)nLetJog-97]==' '))
            return false;
        else
            return true;
    }

}
bool comer(char tab[][TAM], int nNumJog, char nLetJog,int vez)
{
    if(vez==0)
    {
        if(tab[nNumJog-1][(int)nLetJog-98]=='O' || tab[nNumJog-1][(int)nLetJog-96]=='O')
            return true;
        else
            return false;
    }
    if(vez==1)
    {
        if(tab[nNumJog+1][(int)nLetJog-98]=='X' || tab[nNumJog+1][(int)nLetJog-96]=='X')
            return true;
        else
            return false;
    }
}
void capturaPeca(int decisao,int &contX,int &contO,int vez,char tab[][TAM], int nNumJog, char nLetJog)
{
    if(vez==0 && decisao==1)
    {
        contX++;
        if(tab[nNumJog-1][(int)nLetJog-98]=='O')
            tab[nNumJog-1][(int)nLetJog-98]=' ';
        else if( tab[nNumJog-1][(int)nLetJog-96]=='O')
            tab[nNumJog-1][(int)nLetJog-96]=' ';
    }
    else if(vez==1 && decisao==1)
    {
        contO++;
        if(tab[nNumJog+1][(int)nLetJog-98]=='X')
            tab[nNumJog+1][(int)nLetJog-98]=' ';
        else if(tab[nNumJog+1][(int)nLetJog-96]=='X')
            tab[nNumJog+1][(int)nLetJog-96]=' ';

    }
}
