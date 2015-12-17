/*
*   Sexuada.
*	A melhor metade da população na geração anterior repopula o resto
*
*/


#include <stdio.h>

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <string>

#define POPULATION 20
#define GENES 10
#define GENERATIONS 1000
#define MUTATIONRATE 20

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
    int gama_1 = 0;
	int gama_2 = 0;
	int j = GENES/2;
    for(int i = 0; i < GENES/2; i++)
    {
        gama_1 += ind->Genotipo[i];
		gama_2 += ind->Genotipo[j++];
    }

	int tempFeatness = 0;
    if(gama_1 == GENES/2)
    {
		tempFeatness = GENES/2;
    }
    else
    {
		tempFeatness = GENES/2 - gama_1 -1;
        //ind->featness = GENES - gama -1;
    }

	if(gama_2 == GENES/2)
    {
		tempFeatness += GENES/2;
    }
    else
    {
		tempFeatness += GENES/2 - gama_2 -1;
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

   // string outputfile("");
    //outputfile = __FILE__ + ".r";

    ofstream myfile;
    myfile.open ("output.r");

    myfile << "B <- matrix(,nrow="<< GENERATIONS/1000 << ",ncol="<<POPULATION<< ")" << endl;

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
        for(int j = 0; j < GENES/2; j++)
        {

            cout << Competidor[i].Genotipo[j] << ", ";
        }
		cout << "|";
		for(int j = GENES/2; j < GENES; j++)
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

		int k = 0;
        for(int i = POPULATION/2; i < POPULATION; i++)
        {
			int m = GENES/2;
            for(int j = 0; j < GENES/2; j++)
            {
                Competidor[i].Genotipo[j] = genesis(Competidor[k].Genotipo[j], MUTATIONRATE);
				Competidor[i].Genotipo[m] = genesis(Competidor[k+1].Genotipo[m], MUTATIONRATE);
				m++;
            }
            featinessCalc(&Competidor[i]);
			k++;
        }

        if(gen%1000 == 0)
        {
            myfile << "B[" << (gen)/1000 + 1<< ",] <- c(";
            for(int i = 0; i< POPULATION; i++)
            {
                     myfile << Competidor[i].featness;
                    if(i != POPULATION -1) myfile << ", ";

            }
            myfile << ")" << endl;
        }


    }

    cout << "------------------------------------" << endl;
    for(int i = 0; i< POPULATION; i++)
    {
		cout << "Genotipo = ";
        for(int j = 0; j < GENES/2; j++)
        {

            cout << Competidor[i].Genotipo[j] << ", ";
        }
		cout << "|";
		for(int j = GENES/2; j < GENES; j++)
        {

            cout << Competidor[i].Genotipo[j] << ", ";
        }


            cout << "Featness = " << Competidor[i].featness << endl;


    }

    myfile << "persp(-B, theta=45, scale=TRUE, ltheta=30, shade= 0.5)" << endl;
    myfile.close();
}
