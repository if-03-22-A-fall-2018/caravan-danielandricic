/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			caravan.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include "caravan.h"
#include <stdlib.h>
#include "pack_animal.h"

typedef struct _node
{
  PackAnimal Pack_Animal;
  struct _node* Next;
}Node;

struct CaravanImplementation
{
    Node* _head;
};

Caravan new_caravan()
{
  Caravan caravan = (Caravan)malloc(sizeof(struct CaravanImplementation));
  caravan->_head = 0;
  return caravan;
}

int get_length(Caravan caravan)
{
  int length = 0;
  Node* currentnode = caravan->_head;
  while(currentnode)
  {
    length++;
    currentnode = currentnode->Next;
  }

  return length;
}

void delete_caravan(Caravan caravan)
{
  int length = get_length(caravan);

  for(int i = 0; i < length; i++)
  {
    Node* head = caravan->_head;
    caravan->_head = head->Next;
    sfree(head);
  }
  sfree(caravan);
}

void add_pack_animal(Caravan caravan, PackAnimal animal)
{
  if((animal == 0) || (get_caravan(animal) == caravan))
  {
    return;
  }
  if(get_caravan(animal) != 0)
  {
    remove_pack_animal(get_caravan(animal), animal);
  }

  add_to_caravan(animal, caravan);
  Node* newnode = (Node*) malloc(sizeof(Node));

  newnode->Pack_Animal = animal;
  newnode->Next = caravan->_head;
  caravan->_head = newnode;
}

void remove_pack_animal(Caravan caravan, PackAnimal animal)
{
  if(caravan->_head == 0 || animal == 0)
  {
    return;
  }

  Node* currentnode = caravan->_head;
  remove_from_caravan(animal, caravan);

  if(currentnode->Pack_Animal == animal)
  {
    caravan->_head = currentnode->Next;
    sfree(currentnode);
    return;
  }

  while((currentnode->Next != 0) && (currentnode->Next->Pack_Animal != animal))
  {
    currentnode = currentnode->Next;
  }

  if(currentnode->Next == 0)
  {
    return;
  }

  Node* nextnode = currentnode->Next;
  currentnode->Next = nextnode->Next;
  sfree(nextnode);
}

int get_caravan_load(Caravan caravan)
{
  int load = 0;
  int length = get_length(caravan);
  Node* currentnode = caravan->_head;
  for(int i = 0; i < length; i++)
  {
    load += get_load(currentnode->Pack_Animal);
    currentnode = currentnode->Next;
  }
  return load;
}

void unload(Caravan caravan)
{
  if(!caravan->_head)
  {
    return;
  }

  Node* currentnode = caravan->_head;
  while(currentnode)
  {
    unload(currentnode->Pack_Animal);
    currentnode = currentnode->Next;
  }
}

int get_caravan_speed(Caravan caravan)
{
  int lowest_speed = 51; //50 weil kein Tier schneller als 50 sein kann
  int length = get_length(caravan);

  Node* currentnode = caravan->_head;

  for(int i = 0; i < length; i++)
  {
    if(get_actual_speed(currentnode->Pack_Animal) < lowest_speed)
    {
      lowest_speed = get_actual_speed(currentnode->Pack_Animal);
    }
    currentnode = currentnode->Next;
  }

  if(lowest_speed >= 51)
  {
    lowest_speed = 0;
  }
  return lowest_speed;
}
