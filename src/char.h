#ifndef _CHAR
#define _CHAR

class Char {
private:
  bool last;
  char character;
  Char *next;

public:
  Char(char pcharacter) {
    last = true;
    character = pcharacter;
  }

  char get_character() {
    return character;
  }

  Char *get_next() {
    return next;
  }

  void set_next(Char *pnext) {
    last = false;
    next = pnext;
  }

  bool is_last() {
    return last;
  }
};

#endif /* _CHAR */
