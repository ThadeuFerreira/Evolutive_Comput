/*
*   Sexuada.
*	A melhor metade da população na geração anterior repopula o resto
*
*/


#include <stdio.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define POPULATION 20
#define GENES 5
#define GENERATIONS 100
#define MUTATIONRATE 2

using namespace std;

struct Individuo
{
    int featness;
    int Genotipo_1[GENES];
	int Genotipo_2[GENES];
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
    int gama_1 = 0;
	int gama_2 = 0;
    for(int i = 0; i < GENES; i++)
    {
        gama_1 += ind->Genotipo_1[i];
		gama_2 += ind->Genotipo_2[i];
    }

	int tempFeatness = 0;
    if(gama_1 == GENES)
    {
		tempFeatness = GENES;
    }
    else
    {
		tempFeatness = GENES - gama_1 -1;
        //ind->featness = GENES - gama -1;
    }

	if(gama_2 == GENES)
    {
		tempFeatness += GENES;
    }
    else
    {
		tempFeatness += GENES - gama_2 -1;
        //ind->featness = GENES - gama -1;
    }

	ind->featness = tempFeatness;

	return 0;
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
            Competidor[i].Genotipo_1[j] = randBitValue(50);
			Competidor[i].Genotipo_2[j] = randBitValue(50);
        }
        featinessCalc(&Competidor[i]);

    }
    for(int i = 0; i< POPULATION; i++)
    {
        cout << "Genotipo = ";
        for(int j = 0; j < GENES; j++)
        {

            cout << Competidor[i].Genotipo_1[j] << ", ";
        }

		cout << "|| " ;
		for(int j = 0; j < GENES; j++)
        {

            cout << Competidor[i].Genotipo_2[j] << ", ";
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

		int k = 0;
        for(int i = POPULATION/2; i < POPULATION; i++)
        {
            for(int j = 0; j < GENES; j++)
            {
                Competidor[i].Genotipo_1[j] = genesis(Competidor[k].Genotipo_1[j], MUTATIONRATE);
				Competidor[i].Genotipo_2[j] = genesis(Competidor[k+1].Genotipo_2[j], MUTATIONRATE);
            }
            featinessCalc(&Competidor[i]);
			k++;
        }




    }

    cout << "------------------------------------" << endl;
    for(int i = 0; i< POPULATION; i++)
    {
        cout << "Genotipo = ";
        for(int j = 0; j < GENES; j++)
        {

            cout << Competidor[i].Genotipo_1[j] << ", ";
        }
        cout << "|| " ;
        for(int j = 0; j < GENES; j++)
        {

            cout << Competidor[i].Genotipo_2[j] << ", ";
        }
            cout << "Featness = " << Competidor[i].featness << endl;

    }

}
