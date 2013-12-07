#include "../src/char_queue.h"
#include <assert.h>

class CharQueueTest {
public:
  CharQueue *char_queue;

  CharQueueTest() {
    setup();
  }

  void setup() {
    char_queue = new CharQueue();
  }

  void test_constructor() {
    setup();
  }

  void test_push() {
    setup();
    char_queue->push('h');
  }

  void test_size_when_empty() {
    setup();
    assert( char_queue->size() == 0 );
  }

  void test_size_with_one_item() {
    setup();
    char_queue->push('h');
    assert( char_queue->size() == 1 );
  }

  void test_size_with_two_items() {
    setup();
    char_queue->push('h');
    char_queue->push('x');
    assert( char_queue->size() == 2 );
  }

  void test_size_after_a_push_and_a_pop() {
    setup();
    char_queue->push('h');
    char_queue->pop();
    assert( char_queue->size() == 0 );
  }

  void test_size_after_two_pushes_and_a_pop() {
    setup();
    char_queue->push('h');
    char_queue->push('x');
    char_queue->pop();
    assert( char_queue->size() == 1 );
  }
};


void char_queue_test(){
  CharQueueTest *test = new CharQueueTest();
  test->test_constructor();
  test->test_push();
  test->test_size_when_empty();
  test->test_size_with_one_item();
  test->test_size_with_two_items();
  test->test_size_after_a_push_and_a_pop();
  test->test_size_after_two_pushes_and_a_pop();
}
