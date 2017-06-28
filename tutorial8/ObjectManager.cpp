/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#include "objectmanager.h"


// Adds a game object to the collection
void ObjectManager::Add(GameObject *obj) {
  objs.push_back(obj);

  if (obj->GetType() == OBJ_PLAYER)
    player = obj;
};

// Adds a game object to the front of the collectoin
void ObjectManager::AddFront(GameObject *obj) {
  objs.push_front(obj);

  if (obj->GetType() == OBJ_PLAYER)
    player = obj;
};

int ObjectManager::Count() {
  return objs.size();
}

// Iterates through all contained objects, updating them as necessary.  Removes any dead objects
// Note that currently an object will die in one update loop, and not be removed until the next.
// We may change this down the road.
void ObjectManager::UpdateAll(){

  list<GameObject *>::iterator iter;

  iter = objs.begin();
  while(iter != objs.end())
  {
    if((*iter)->IsDead()) {
      if ((*iter)->GetType() == OBJ_PLAYER)
        player = NULL;
      delete (*iter);
      objs.erase(iter++);
    }
    else {
      (*iter)->Update();
       iter++;
    }
  }

};

// Draws each object
void ObjectManager::DrawAll(){
  list<GameObject *>::iterator iter;

  for (iter=objs.begin(); iter != objs.end(); iter++)
  {
    if ((*iter)->IsDead() == false)
      (*iter)->Draw();
  }
};


// Removes all objects from list, and deletes each.  Usefull for changing levels.  
// Pass in true if you'd like player objects deleted, false otherwise.
void ObjectManager::DeleteAll()
{
  list<GameObject *>::iterator i;
  
  for (i=objs.begin(); i != objs.end(); i++) {
    delete (*i);
  }
  objs.clear();

  player = NULL;
}

// Takes the passed in object, and returns the first object it has collided with
GameObject *ObjectManager::CollidesWith(GameObject *obj) {
  list<GameObject *>::iterator iter;
  GameObject *retVal = NULL;

  for (iter=objs.begin(); iter != objs.end(); iter++)
  {
    if ((*iter)->IsDead() == false && (*iter) != obj) {
      // Find the squared distance between the two objects
      GLfixed o1x = obj->GetX() >> 12;
      GLfixed o2x = (*iter)->GetX() >> 12;
      GLfixed o1y = obj->GetY() >> 12;
      GLfixed o2y = (*iter)->GetY() >> 12;
      GLfixed sqDist = (o1x - o2x) * (o1x - o2x) + (o1y - o2y) * (o1y - o2y);
      sqDist = sqDist >> 8;

      int hr1 = obj->GetHitRadius();
      int hr2 = (*iter)->GetHitRadius();

      if (sqDist < (hr1 + hr2) * (hr1 + hr2))
        return (*iter);
    }
  }

  return retVal;
}

GameObject *ObjectManager::GetPlayer() {
  return player;
}
