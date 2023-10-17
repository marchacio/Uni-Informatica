#include <iostream>
#include "movestack.h"

// Aggiungi in testa
void push(MoveStack & ms, char cmd)
{
  MoveStack head = new Move;
  head->cmd = cmd;
  head->next = ms;

  ms = head;
}

// Leggi e rimuovi dalla testa
char pop(MoveStack & ms)
{
  //Controllo che lo stack non sia vuoto
  if(ms == nullptr)
    throw -1;

  char command = ms->cmd;
  MoveStack new_head = ms->next;
  delete ms;
  ms = new_head;

  return command;
}


// Esegue mossa
void doMove(int &x, int&y, char cmd)
{
  if(cmd == 'E')
    x++;
  else if(cmd == 'W')
    x--;
  else if(cmd == 'S')
    y++;
  else if(cmd == 'N')
    y--;
  else
    throw -1;
}
