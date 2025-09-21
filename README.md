# C++ snippets
While this started out as a design pattern repo and extending this will learning small modules and other usefull techniques. Not all of these will be original thoughts but implemented in my style with comments.

## List of Patterns

1. Adaptor
2. Decorator
3. Executor
4. Singleton
5. Factory
6. Visitor
7. CRTP

### Some good techniques which are not so much a pattern

1. Fluent
2. ScopeGuard

## List of future ideas to implement and test.

1. Concurrent LinkedList 
2. Concurrent Rate Limiter
3. Task Scheduler
4. Exponential Backoff

## Proving concurrency

1. Write test cases for concurrency and test using valgrind/TSAN.

## References
https://www.bogotobogo.com/DesignPatterns/introduction.php

### Books

* C++ Software Design, Klaus Iglberger

## Building

./configure.sh
ninja -C build


