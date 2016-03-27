#include <exception>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>

#include <futex.hpp>

futex ftx;

void first() {
    try {
        BOOST_CHECK_THROW(ftx.unlock(), std::logic_error);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void second() {
    try {
        std::this_thread::sleep_for(2s);

        BOOST_CHECK_THROW(ftx.unlock(), std::logic_error);

    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

BOOST_AUTO_TEST_SUITE( futex_tests )

BOOST_AUTO_TEST_CASE( throw_case ) {
    thread t1(first);
    thread t2(second);

    t1.join();
    t2.join();
}

BOOST_AUTO_TEST_SUITE_END()
