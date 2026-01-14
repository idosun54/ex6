#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "utils.h"

// Map display functions
static void displayMap(GameState* g) {
    if (!g->rooms) return;
    
    // Find bounds
    int minX = 0, maxX = 0, minY = 0, maxY = 0;
    for (Room* r = g->rooms; r; r = r->next) {
        if (r->x < minX) minX = r->x;
        if (r->x > maxX) maxX = r->x;
        if (r->y < minY) minY = r->y;
        if (r->y > maxY) maxY = r->y;
    }
    
    int width = maxX - minX + 1;
    int height = maxY - minY + 1;
    
    // Create grid
    int** grid = malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++) {
        grid[i] = malloc(width * sizeof(int));
        for (int j = 0; j < width; j++) grid[i][j] = -1;
    }
    
    for (Room* r = g->rooms; r; r = r->next)
        grid[r->y - minY][r->x - minX] = r->id;
    
    printf("=== SPATIAL MAP ===\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j] != -1) printf("[%2d]", grid[i][j]);
            else printf("    ");
        }
        printf("\n");
    }
    printf("=== ROOM LEGEND ===\n");
     Room* r=g->rooms;
      printLegend(r);
    printf("===================\n");
    for (int i = 0; i < height; i++) free(grid[i]);
    free(grid);
}

void printLegend(Room* r)
{
  if(!r)
  {
   printLegend(r->next);
   if(r->monster==NULL&&r->item==NULL)
    printf("ID %d: [M:X] [I:X]\n", r->id);
   if(r->monster==NULL&&r->item!=NULL)
    printf("ID %d: [M:X] [I:V]\n", r->id);
   if(r->monster!=NULL&&r->item==NULL)
    printf("ID %d: [M:V] [I:X]\n", r->id);
   if(r->monster!=NULL&&r->item!=NULL)
    printf("ID %d: [M:V] [I:V]\n", r->id);
  }
  else
   return;
}

void addRoom(GameState* g)
{
  Room* r= malloc(sizeof(Room));
  if(g->roomCount!=0)
  {
  void displayMap(g);
  int NewId=g->roomCount;
  r->id=++NewId;
  r->visited=0;
  int id=getInt("Attach to room ID: ");
  Room *temp=g->rooms;
  int x;
  int y;
  while(!temp)
  {
    if(temp->id==id)
    {
      x=temp->x;
      y=temp->y;
    }
    temp=temp->next;
  }
  int direction=getInt("Direction (0=Up,1=Down,2=Left,3=Right): ");
  switch (direction)
  {
  case UP:
  y--;
    break;
  case DOWN:
  y++;
    break;
  case LEFT:
  x--;
    break;
  case RIGHT:
  x++;
    break;
  }

Room *full=g->rooms;
while(!full)
{
  if((x==full->x)&&(y==full->y))
  {
    printf("Room exists there\n");
    free(r);
    return;
  }
 full=full->next;
}

r->x=x;
r->y=y;
}

else
 {
  r->id=0;
  r->x=0;
  r->y=0;
  r->visited=1;
 }

Monster *mon=malloc(sizeof(Monster));
int monChoise=getInt("Add monster? (1=Yes, 0=No): ");
if(monChoise)
{
 mon->name=getString("Monster name: ");
 mon->type=getInt("Type (0-4): ");
 mon->hp=getInt("HP: ");
 mon->attack=getInt("Attack: ");
 r->monster=mon;
}
else {
 r->monster=NULL;
}

Item *item=malloc(sizeof(Item));
int itemChoise=getInt("Add item? (1=Yes, 0=No): ");
if(itemChoise)
{
 item->name=getString("Item name: ");
 item->type=getInt("Type (0=Armor, 1=Sword): ");
 item->value=getInt("Value: ");
 r->item=item;
}
else {
 r->item=NULL;
}
r->next=NULL;
g->roomCount++;
printf("Created room %d at (%d,%d)", r->id, r->x, r->y);

Room *findEmpty=g->rooms;
while(findEmpty!=NULL)
 findEmpty=findEmpty->next;
findEmpty=r;
}

void initPlayer(GameState* g)
{
 if(g->rooms==NULL)
 {
  printf("Create rooms first");
  return;
 }
 Player* player= malloc(sizeof(Player));
 player->maxHp=g->configMaxHp;
 player->baseAttack=g->configBaseAttack;
 player->bag=NULL;
 player->hp=player->maxHp;
 player->defeatedMonsters=NULL;
 player->currentRoom=0;
 g->player=player;
}

void playGame(GameState* g)
{
  if(g->player=NULL)
  {
   printf("Init player first");
   return;
  }
   for (Room* r = g->rooms; r; r = r->next)
   { int count;
    if(r->visited&&(r->monster->hp==0))
      count++;
    if(count==g->roomCount)
     {  
      printf("***************************************\n");
      printf("             VICTORY!                  \n");
      printf(" All rooms explored. All monsters defeated.\n");
      printf("***************************************\n");
      freeGame(g);
     }
   }
 
 Room* r = g->rooms;
 displayMap(g);
 printf("--- Room %d ---", r->id);
 if(r->monster!=NULL)
  printf("Monster: %s (HP:%d)", r->monster->name, r->monster->hp);
 if(r->item!=NULL)
  printf("Item: %s", r->item->name);
 printf("HP: %d/%d", g->player->hp, g->player->maxHp);
 int choise=getInt("1.Move 2.Fight 3.Pickup 4.Bag 5.Defeated 6.Quit\n");
 switch (choise)
 {
 case MOVE:
  if(r->monster->hp!=0)
   {
     printf("Kill monster first\n");
     playGame(g);
   }
  break;
 case FIGHT:
 



 }







}