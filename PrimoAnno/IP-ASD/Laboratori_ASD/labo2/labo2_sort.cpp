#include "labo2_sort.h"
#include "time.h"
#include <iostream>

void scambia(vector<int>& v, int i, int j)
{
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}


/**************************************************************************************
				SELECTION SORT
***************************************************************************************/
void selectionSort(vector<int>& v)
{
   int current_min_index;
   unsigned int size = v.size();
   for (unsigned int i=0; i<size; ++i)
   {
     current_min_index = i;
     for (unsigned int j=i+1;j<size; ++j)
        if (v[current_min_index] > v[j])
            current_min_index = j;
     scambia(v, i, current_min_index);
   }
}



/**************************************************************************************
				INSERTION SORT
***************************************************************************************/
void insertionSort(vector<int>& v)
{
   int current, prev;
   unsigned int size = v.size();
   for (unsigned int i=1; i<size; ++i)
   { current=i;
     prev=i-1;
     while(prev>=0 && v[current]<v[prev])
        {
         scambia(v, current, prev);
         --current;
         --prev;
        }
   }
}


/**************************************************************************************
				BUBBLESORT
***************************************************************************************/
void bubbleSort(vector<int>& v)
{
   unsigned int size = v.size();
   bool scambiati;
   for (unsigned int i=1; i<size; ++i)
      {
      scambiati = false;
      for (unsigned int j=0; j<size-i; ++j)
          if(v[j]>v[j+1])
            {
              scambia(v, j, j+1);
              scambiati = true;
            }
      if (!scambiati) return;
      }
}



/**************************************************************************************
				   MERGESORT
***************************************************************************************/
void fondi(vector<int>& v, unsigned int inizio, unsigned int centro, unsigned int fine)
{
   vector<int> vsinistra, vdestra;

   for (unsigned int i=inizio; i<=centro; ++i)
      vsinistra.push_back(v[i]);

   for (unsigned int i=centro+1; i<=fine; ++i)
      vdestra.push_back(v[i]);

   unsigned int indicesinistra = 0;
   unsigned int maxsin = vsinistra.size();
   unsigned int indicedestra = 0;
   unsigned int maxdes = vdestra.size();

   for (unsigned int i=inizio; i<=fine; ++i)
   {
      if (indicesinistra < maxsin && indicedestra < maxdes)
         {
         if (vsinistra[indicesinistra]<vdestra[indicedestra])
            {
             v[i] = vsinistra[indicesinistra];
             indicesinistra++; continue;
             }
         else
            {
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
            }
         }

      if (indicesinistra == maxsin && indicedestra < maxdes)
         {
            v[i] = vdestra[indicedestra];
            indicedestra++; continue;
         }

       if (indicedestra == maxdes && indicesinistra < maxsin)
         {
            v[i] = vsinistra[indicesinistra];
            indicesinistra++; continue;
         }
   }
}

void ms(vector<int>& v, unsigned int inizio, unsigned int fine)
{
    if (inizio < fine)
      {
          unsigned int centro = (inizio+fine)/2;
          ms(v, inizio, centro);
          ms(v, centro+1, fine);
          fondi(v, inizio, centro, fine);
      }
}


void mergeSort(vector<int>& v)
{
   if (v.size() != 0)
      ms(v, 0, v.size()-1);
}


/**************************************************************************************
				QUICKSORT CON SCELTA "BANALE" DEL PIVOT
***************************************************************************************/
void qsb(vector<int>& v, int sx, int dx) {
  if(sx >= dx)
    return;

  //Inizializza il pivot
  int pivot = v.at(sx);

  //divisore della parte minore del pivot da quella maggiore
  int i = sx+1;

  for (unsigned int j = sx+1; j <= (unsigned int)dx; j++) {
    if(v.at(j) < pivot){
      scambia(v, j, i);
      i++;
    }
  }
  //sposta il pivot dalla posizione a sinistra alla posizione corretta
  --i;
  scambia(v, sx, i);

  //Chiama qs ricorsivamente
  qsb(v, sx, i-1);
  qsb(v, i+1, dx);
}

void quickSortTrivial(vector<int>& v)
{
   /* Implementare quickSort banale con partizione in place */

   if(v.size() <= 1) return;

   qsb(v, 0, v.size()-1);
}

/**************************************************************************************
				QUICKSORT RANDOMIZZATO
***************************************************************************************/

void qsr(vector<int>& v, int sx, int dx) {
  if(sx >= dx)
    return;

  //Inizializza il pivot
  int pivot_index = (rand() % (dx - sx)) + sx;
  int pivot = v.at(pivot_index);

  //Metti il pivot all'inizio
  scambia(v, sx, pivot_index);

  //Effettuare il partizionamento in place
  int i = sx+1;
  for (unsigned int j = sx+1; j <= (unsigned int)dx; j++) {
    if(v.at(j) < pivot){
      scambia(v, j, i);
      i++;
    }
  }

  //Rimettere a posto il pivot
  --i;
  scambia(v, sx, i);

  //Chiama qs ricorsivamente
  qsr(v, sx, i-1);
  qsr(v, i+1, dx);
}

void quickSortRandom(vector<int>& v)
{
  if(v.size() <= 1) return;

  //Inizializza il generatore randomico con un seed
  srand((unsigned) time(NULL));
  qsr(v, 0, v.size()-1);
 /* Implementare quickSort randomizzato con partizione in place*/
}
