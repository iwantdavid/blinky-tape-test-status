#ifndef _CHAR_QUEUE
#define _CHAR_QUEUE

#include "char.h"

class CharQueue {
private:
  int mSize;
  Char *head;

public:
  CharQueue() {
    mSize = 0;
  }

  int size() {
    return mSize;
  }

  char pop() {
    char character = head->get_character();
    head = head->get_next();
    mSize--;
    return character;
  }

  void push(char character) {
    Char *next = new Char(character);
    Char *current = head;
    while (mSize > 0 && !current->last()) {
      current = current->get_next();
    }
    current->set_next(next);
    mSize++;
  }
};

#endif /* _CHAR_QUEUE */
