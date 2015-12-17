/*
*   Sexuada.
*	A melhor metade da população na geração anterior repopula o resto
*   Crossover sempre na metade
*/


#include <stdio.h>

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <string>

#define POPULATION 20
#define GENES 10
#define GENERATIONS 10000
#define DIVGEN 100 /* GENETATIONS/DIVGEN = 100 */
#define MUTATIONRATE 2
#define TRAPES 2


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
    int gama[TRAPES];
	int tempFeatness = 0;
    //cout << "_________________________" << endl;
	for (int i = 0; i < TRAPES; i++)
	{
		gama[i] = 0;
	}
	for(int k = 0; k < TRAPES; k++)
	{

		for(int i = k*GENES/TRAPES; i < k*GENES/TRAPES + GENES/TRAPES; i++)
		{
            //cout  << " Genotipo[" << i <<"] = " << ind->Genotipo[i] << " gama["<<k<< "] = " << gama[k]<< endl;
			gama[k] += ind->Genotipo[i];
		}
	//	cout << "-- i = " << value << "ind->Genotipo[i] = " << ind->Genotipo[value] << " gama[k] = " << gama[k]<< endl;
        //cout << endl;
        //cout << "gama = " <<  gama[k] << endl;

		if(gama[k] == GENES/TRAPES)
		{
			tempFeatness += GENES/TRAPES;
		}
		else
		{
			tempFeatness += GENES/TRAPES - gama[k] -1;
			//cout << "gama k " = gama[k] << endl;
			//ind->featness = GENES - gama -1;
		}
		//cout << "tempFeatness = " << tempFeatness << endl;
        //cout << "************************" << endl;
	}

	ind->featness = tempFeatness;
	//cout << "Featness = " << ind->featness << endl;

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

    myfile << "B <- matrix(,nrow="<< GENERATIONS/10 << ",ncol="<<POPULATION<< ")" << endl;

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
        for(int k = 0; k < TRAPES; k++)
        {
             for(int j = k*GENES/TRAPES; j < k*GENES/TRAPES + GENES/TRAPES; j++)
            {

                cout << Competidor[i].Genotipo[j] << ", ";
            }
            cout << "|";



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
                //O Crossover acontece aqui
                Competidor[i].Genotipo[j] = genesis(Competidor[k].Genotipo[j], MUTATIONRATE);
				Competidor[i].Genotipo[m] = genesis(Competidor[k+1].Genotipo[m], MUTATIONRATE);
				m++;
            }
            featinessCalc(&Competidor[i]);
			k++;
        }




        if(gen%DIVGEN == 0)
        {
            float avareFeatness = 0;


            //cout << "Featnesse médio = " << avareFeatness << endl;
            myfile << "B[" << (gen)/DIVGEN+ 1<< ",] <- c(";
            for(int i = 0; i< POPULATION; i++)
            {
                    avareFeatness += Competidor[i].featness;
                    myfile << Competidor[i].featness;
                    if(i != POPULATION -1) myfile << ", ";

            }
            myfile << ")" << endl;
            avareFeatness = avareFeatness/POPULATION;

        }


    }


    cout << "------------------------------------" << endl;
    for(int i = 0; i< POPULATION; i++)
    {
		cout << "Genotipo = ";
        for(int k = 0; k < TRAPES; k++)
        {
             for(int j = k*GENES/TRAPES; j <k*GENES/TRAPES + GENES/TRAPES; j++)
            {

                cout << Competidor[i].Genotipo[j] << ", ";
            }
            cout << "|";

        }
         cout << "Featness = " << Competidor[i].featness << endl;


    }

    myfile << "persp(-B, theta=45, scale=TRUE, ltheta=30, shade= 0.5)" << endl;
    myfile.close();
}
