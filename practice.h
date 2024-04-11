#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void land();
void leave();
int occupied();

enum SpaceType 
{
  START,
  NORMAL,
  CHUTE,
  LADDER,
  FINISH
} SpaceType;

enum Color 
{
  RED,
  BLUE,
  WHITE,
  BLACK,
} Color;

struct Space
{
  enum SpaceType type;
  char *value;
  struct Avatar *avatarsInSpace[5];
  void (*land)(struct Avatar, struct Space);
  void (*leave)(struct Avatar, struct Space);
  int (*occupied)(struct Space *);
};

struct Avatar
{
  char *name;
  enum Color color;
  struct Space *location;
};

struct Player
{
  char *name;
  int order;
  char *id;
  struct Avatar avatar;
};

void land(struct Avatar *avatar, struct Space *this)
{

  if (this->avatarsInSpace[0] == 0) 
  {
  this->avatarsInSpace[0] = avatar;
  avatar->location = this;
  }
  else 
  {
    struct Avatar *old = this->avatarsInSpace[0];
    leave(old, this);
    this->avatarsInSpace[0] = avatar;
  }

};

int occupied(struct Space *this)
{
  for (int i = 0; i < 5; i++)
  {
    if (this->avatarsInSpace[i] != NULL)
    {
      return 1;
    };
    printf("%d index in %s\n", i, this->value);
  }
  return 0;
};

void leave(struct Avatar *avatar, struct Space *this)
{
  this->avatarsInSpace[0] = NULL;
  avatar->location = NULL;
};

void practice()
{

struct Space s1;
struct Space *s1Ptr = &s1;

s1.type = START;
s1.value = "START";

struct Space s2;
struct Space *s2Ptr = &s2;

s2.type = NORMAL;
s2.value = "SPACE 2";

struct Player p1;

p1.name = "ANDREW";
p1.id = "P1@y3R 1";
p1.order = 1;

struct Avatar a1;
struct Avatar *a1Ptr = &a1;

a1.name ="AVATAR 1";
a1.color = RED;

struct Avatar a2;
struct Avatar *a2Ptr = &a1;

a2.name = "AVATAR 2";
a2.color = WHITE;

land(a1Ptr, s1Ptr);
land(a2Ptr, s1Ptr);

printf("%s is occupied, 1 = true, 0 = false\n%d\n", s1.value, occupied(s1Ptr));

for (int i = 0; i < 5; i++)
{
  if (s1Ptr->avatarsInSpace[i] != 0){
    printf("%s is in %s\n", s1Ptr->avatarsInSpace[i]->name, s1.value);
  }
  if (s2Ptr->avatarsInSpace[i] != 0)
  {
    printf("%s is in %s\n", s2Ptr->avatarsInSpace[i]->name, s2.value);
  }
};

leave(a1Ptr, s1Ptr);
land(a1Ptr, s2Ptr);

printf("%s's Location %s\n", a1.name, a1Ptr->location->value);
printf("%s's Location %s\n", a2.name, a2Ptr->location->value);
printf("%s is occupied, 1 = true, 0 = false\n%d\n", s2.value, occupied(s2Ptr));
printf("%s is occupied, 1 = true, 0 = false\n%d\n", s1.value, occupied(s1Ptr));

for (int i = 0; i < 5; i++)
{
if(s2Ptr->avatarsInSpace[i] != 0) printf("%s\n", s2Ptr->avatarsInSpace[i]->name);    
}

};