#include "factory_test_fixture.hpp"

using namespace utils;

struct Dummy {
    int x = 42;
};

TEST_F(FactoryTest, CreateWithoutRegisterReturnsNullptr) {
    auto p = factory.create<Dummy>();
    EXPECT_EQ(p, nullptr);
}

TEST_F(FactoryTest, RegisterAndCreateReturnsInstance) {
    factory.register_creator<Dummy>([]()-> std::shared_ptr<Dummy> { return std::make_shared<Dummy>(); });
    auto p = factory.create<Dummy>();
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->x, 42);
}

TEST_F(FactoryTest, MultipleTypesIndependent) {
    struct A { int a = 1; };
    struct B { int b = 2; };

    factory.register_creator<A>([](){ return std::make_shared<A>(); });
    factory.register_creator<B>([](){ return std::make_shared<B>(); });

    auto pa = factory.create<A>();
    auto pb = factory.create<B>();

    ASSERT_NE(pa, nullptr);
    ASSERT_NE(pb, nullptr);
    EXPECT_EQ(pa->a, 1);
    EXPECT_EQ(pb->b, 2);
}

TEST_F(FactoryTest, RegisterCreatorWithArgsAndCreateForwardsArgs) {
    struct S { int a; std::string b; };

    // register a creator that accepts (int, std::string)
    factory.register_creator([](int x, std::string s){
        return std::make_shared<S>(S{x, s});
    });

    auto p = factory.create<S>(7, std::string("hello"));
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->a, 7);
    EXPECT_EQ(p->b, "hello");
}

// TEST_F(FactoryTest, CreateWithWrongArgTypesReturnsNullptr) {
//     struct S2 { double v; };

//     // creator expects a double, but we'll call create with an int -> should fail any_cast
//     factory.register_creator<S2>([](double d){ return std::make_shared<S2>(S2{d}); });

//     auto p = factory.create<S2>(42); // int vs double
//     EXPECT_EQ(p, nullptr);
// }

// TEST_F(FactoryTest, CreateStringNoArgAndWithArgs) {
//     // no-arg creator returning a preset string
//     factory.register_creator<std::string>([](){ return std::make_shared<std::string>("preset"); });
//     auto p1 = factory.create<std::string>();
//     ASSERT_NE(p1, nullptr);
//     EXPECT_EQ(*p1, "preset");

//     // creator that builds a string from prefix and number
//     factory.register_creator<std::string>([](const std::string& prefix, int n){
//         return std::make_shared<std::string>(prefix + std::to_string(n));
//     });

//     auto p2 = factory.create<std::string>(std::string("item-"), 5);
//     ASSERT_NE(p2, nullptr);
//     EXPECT_EQ(*p2, "item-5");
// }
