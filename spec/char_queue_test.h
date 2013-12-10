#include "../src/char_queue.h"
#include <stdio.h>
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

  void test_pop_with_nothing() {
    setup();
    assert( !char_queue->pop() );
  }

  void test_pop_after_push() {
    setup();
    char_queue->push('h');
    assert( char_queue->pop() == 'h' );
  }

  void test_pop_after_two_pushes() {
    setup();
    char_queue->push('x');
    char_queue->push('y');
    assert( char_queue->pop() == 'x' );
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

  void test_size_after_a_pop() {
    setup();
    char_queue->pop();
    assert( char_queue->size() == 0 );
  }

  void test_double_pop_after_double_push() {
    setup();
    char_queue->push('f');
    char_queue->push('b');
    assert( char_queue->pop() == 'f' );
    assert( char_queue->pop() == 'b' );
  }

  void test_clear_with_nothing() {
    setup();

    char_queue->clear();
    assert( char_queue->pop() == '\0' );
    assert( char_queue->size() == 0 );
  }

  void test_clear_after_two_pushes() {
    setup();

    char_queue->push('h');
    char_queue->push('r');
    char_queue->clear();
    assert( char_queue->pop() == '\0' );
    assert( char_queue->size() == 0 );
  }
};


void char_queue_test(){
  CharQueueTest *test = new CharQueueTest();
  test->test_constructor();
  test->test_push();
  test->test_pop_with_nothing();
  test->test_pop_after_push();
  test->test_pop_after_two_pushes();
  test->test_size_when_empty();
  test->test_size_with_one_item();
  test->test_size_with_two_items();
  test->test_size_after_a_push_and_a_pop();
  test->test_size_after_two_pushes_and_a_pop();
  test->test_size_after_a_pop();
  test->test_double_pop_after_double_push();
  test->test_clear_with_nothing();
  test->test_clear_after_two_pushes();
}
