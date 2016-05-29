//Falta:
//corrigir a opção de comer a peça do oponente
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
bool fimJogo(char tab[TAM][TAM]);

int main ()
{
    char tab[TAM][TAM];
    int i, j, vez=0;
    bool busca;

    busca=fimJogo(tab);

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
        cout << "Peça invalida! Selecione outra peça:";
        cin >> letJog >> numJog;
    }

    cout << "Digite o local para mover:";
    cin >> nLetJog >> nNumJog;

    resultValida = validaJogada (tab, numJog, letJog, nNumJog, nLetJog, vez);

    while(resultValida)
    {
        cout<<"Casa inválida! Selecione outra casa:";
        cin >> nLetJog >> nNumJog;
        resultValida = validaJogada (tab, numJog, letJog, nNumJog, nLetJog, vez);
    }

    numJog--;
    nNumJog--;

    troca(tab,numJog,letJog,nNumJog,nLetJog);
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
        if (nNumJog-numJog==1 || (int)nLetJog-(int)letJog==1 || nNumJog-numJog==-1 || (int)nLetJog-(int)letJog==-1)
        {
            if (vez==0)
            {
                if ((nNumJog-numJog==1 && (int)nLetJog-(int)letJog==1) || (nNumJog-numJog==1 || (int)nLetJog-(int)letJog==-1))
                    return false;
                else
                    return true;
            }
            else
            {
                if ((nNumJog-numJog==-1 && (int)nLetJog-(int)letJog==1) || (nNumJog-numJog==-1 || (int)nLetJog-(int)letJog==1))
                    return false;
                else
                    return true;
            }
        }
        else if (nNumJog-numJog==2 || (int)nLetJog-(int)letJog==2 || nNumJog-numJog==-2 || (int)nLetJog-(int)letJog==-2)
        {
            if (nNumJog-numJog==2 && (int)nLetJog-(int)letJog==2)
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
            else if (nNumJog-numJog==2 && (int)nLetJog-(int)letJog==-2)
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
            else if (nNumJog-numJog==-2 && (int)nLetJog-(int)letJog==-2)
            {
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
            else if (nNumJog-numJog==-2 && (int)nLetJog-(int)letJog==2)
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
    }
    else
        return true;
}
bool fimJogo(char tab[TAM][TAM])
{
    int i,j,contX=0,contO=0,cont=0;
     
    for(i=0; i<TAM; i++)
    {
        for(j=0; j<TAM; j++)
        {
            if(tab[i][j]=='X')
                contX++;
	    else
		    if(tab[i][j]=='O')
            		contO++;
	    		else
				if(tab[i][j]==' ')
					cont++;
        }
    }
    if((contX>contO && contO==0) || (contX<4 && contO<4 && cont>=26))
        return false;
    else{
	    if(contO>contX && contX==0)
   	 	return false;
    	    else
        	return true;
}
}
