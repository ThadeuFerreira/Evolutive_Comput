/*
*   Assexuada
*   A cada geração o ultimo colocado é eliminado e um individuo com
*   genotipo aleatório é criado.
*
*/


#include <stdio.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define POPULATION 5
#define GENES 5
#define GENERATIONS 100
#define MUTATIONRATE 10

using namespace std;

struct Individuo
{
    int featness;
    int Genotipo[GENES];
};

int
randBitValue(int chance)
{

    int retVal = 0;
    int val = rand() % 100 + 1 ;

    if (val < chance )
    {
        retVal = 1;
    }


    return retVal;
}

int
featinessCalc(Individuo *ind)
{
    int gama = 0;
    for(int i = 0; i < GENES; i++)
    {
        gama += ind->Genotipo[i];
    }

    if(gama == GENES)
    {
        ind->featness = GENES;
    }
    else
    {
        ind->featness = GENES - gama -1;
    }
}

//Replica o valor 0 ou 1 com chance de uma troca acontecer
int
genesis(int val, int mutRate)
{
    int retVal = val;
    int variation = rand() % 100 + 1;

    if (variation < mutRate)
    {
        if(val == 0)
        {
            retVal = 1;
        }
        else
        {
            retVal = 0;
        }
    }

    return retVal;
}

int main()
{
    /* initialize random seed: */
    srand (time(NULL));

    Individuo Competidor[POPULATION];



    for(int i = 0; i< POPULATION; i++)
    {
        for(int j = 0; j < GENES; j++)
        {
            Competidor[i].Genotipo[j] = randBitValue(50);
        }
        featinessCalc(&Competidor[i]);

    }
    for(int i = 0; i< POPULATION; i++)
    {
        cout << "Genotipo = ";
        for(int j = 0; j < GENES; j++)
        {

            cout << Competidor[i].Genotipo[j] << ", ";
        }
            cout << "Featness = " << Competidor[i].featness << endl;

    }

    for(int gen = 0; gen < GENERATIONS; gen++)
    {

        for(int j = 0; j < POPULATION; j++)
        {
            for(int i = 0 ; i < POPULATION - 1; i++)
            {
                if(Competidor[i].featness < Competidor[i+1].featness)
                {
                    Individuo temp = Competidor[i];
                    Competidor[i] = Competidor[i+1];
                    Competidor[i+1] = temp;
                }
            }
        }


		for(int j = 0; j < GENES; j++)
         {
                Competidor[POPULATION -1].Genotipo[j] = randBitValue(50);
         }
         featinessCalc(&Competidor[POPULATION -1]);



    }

    cout << "------------------------------------" << endl;
    for(int i = 0; i< POPULATION; i++)
    {
        cout << "Genotipo = ";
        for(int j = 0; j < GENES; j++)
        {

            cout << Competidor[i].Genotipo[j] << ", ";
        }
            cout << "Featness = " << Competidor[i].featness << endl;

    }

}
