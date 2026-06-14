add_executable(Adaptor Adaptor.cpp)
add_executable(Fluent Fluent.cpp)
add_executable(Decorator Decorator.cpp)
add_executable(DecoratorStatic ../test/test_decorator_static.cc)
target_link_libraries(DecoratorStatic PRIVATE GTest::gtest_main)
add_executable(Singleton Singleton.cpp)
add_executable(ScopeGuard ScopeGuard.cpp)
add_executable(Visitor Visitor.cpp)

