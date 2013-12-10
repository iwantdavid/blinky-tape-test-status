#include "../src/char.h"
#include <assert.h>

class CharTest {
public:
  Char *character;
  Char *next_character;

  CharTest() {
    setup();
  }

  void setup() {
    character = new Char('h');
    next_character = new Char('n');
    character->set_next(next_character);
  }

  void test_constructor() {
    setup();
    assert( character->get_character() == 'h' );
    assert( next_character->get_character() == 'n' );
  }

  void test_char_is_last_when_not_last() {
    setup();
    assert( !character->is_last() );
  }

  void test_char_is_last_when_last() {
    setup();
    assert( next_character->is_last() );
  }

  void test_get_next_when_not_last() {
    setup();
    assert(character->get_next()->get_character() == 'n');
  }
};


void char_test(){
  CharTest *test = new CharTest();
  test->test_constructor();
  test->test_char_is_last_when_last();
  test->test_char_is_last_when_not_last();
  test->test_get_next_when_not_last();
}
