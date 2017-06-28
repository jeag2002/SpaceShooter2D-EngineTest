/******************************************************************************
 * OpenGLES Tutorial Code - 2008/2009 - Pete Covert
 *
 * This code is public domain, do with it what you will.  If you make
 *  something interesting with it, let me know at satacoy@gmail.com!
 *****************************************************************************/

#ifndef _OBJECTMANAGER_H
#define _OBJECTMANAGER_H

#include <list>
#include <cstddef>

using namespace std;
#include "GameObject.h"

// Manages a collection of objects.
class ObjectManager
{
public:
  // Iterates through all contained objects, updating them as necessary.  Removes any dead objects
  void UpdateAll();

  // Iterates through all contained objects, drawing them.
  void DrawAll();

  // Removes all objects from list, and deletes each.  Usefull for changing levels.
  // Pass in true if you'd like player objects deleted, false otherwise.
  void DeleteAll();

  // Adds a game object to the collection
  void Add(GameObject *obj);
  void AddFront(GameObject *obj);

  GameObject *GetPlayer();

  // Returns the first object the specified object collides with
  GameObject *CollidesWith(GameObject *obj);

  int Count();


  ObjectManager(void) {player = NULL;};
  ~ObjectManager(void) {};

private:

  // List of all objects
  list<GameObject *> objs;

  GameObject *player;

};

#endif
