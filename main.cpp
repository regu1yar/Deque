#include <iostream>
#include "deque.h"
#include <deque>
#include <time.h>

const int MAX_ITEMS_IN_TEST = 1000;

class DequeTest : public ::testing::Test {
protected:
    Deque<int> myDeque;
    std::deque<int> stdDeque;

    void SetUp() {
        std::cout << "SET UP" << std::endl;
    }

    void TearDown() {
        std::cout << "TEARED DOWN" << std::endl;
    }
};

TEST_F(DequeTest, pushTest) {
    for(int test = 0; test <= MAX_ITEMS_IN_TEST; test += 10) {
        int task = 0;
        for(int i = 0; i < test; ++i) {
            task = rand() % 2;
            if(task == 0) {
                myDeque.push_back(i);
                stdDeque.push_back(i);
            } else if(task == 1) {
                myDeque.push_front(i);
                stdDeque.push_front(i);
            }

        }
        ASSERT_EQ(myDeque.size(), stdDeque.size()) << "My deque size " << myDeque.size() << " != std deque size "
                                                   << stdDeque.size() << " on push test " << test / 10 << std::endl;

        for(size_t i = 0; i < myDeque.size(); ++i) {
            EXPECT_EQ(myDeque[i], stdDeque[i]) << "myDeque[" << i << "] = " << myDeque[i] << " != " << stdDeque[i]
                                               << " =  stdDeque[" << i << "] on push test " << test << std::endl;

        }
        myDeque.clear();
        stdDeque.clear();

        EXPECT_EQ(myDeque.empty(), stdDeque.empty()) << "myDeque.empty() != stdDeque.empty()" << std::endl;
        std::cout << "PUSH TEST " << test << " PASSED" << std::endl;
    }
}

TEST_F(DequeTest, popTest) {
    for(int test = 0; test <= MAX_ITEMS_IN_TEST; test += 10) {
        int task = 0;
        for(int i = 0; i < test; ++i) {
            task = rand() % 2;
            if(task == 0) {
                myDeque.push_back(i);
                stdDeque.push_back(i);
            } else if(task == 1) {
                myDeque.push_front(i);
                stdDeque.push_front(i);
            }

        }
        for(int i = 0; i < test; ++i) {
            task = rand() % 2;
            if(task == 0) {
                myDeque.pop_back();
                stdDeque.pop_back();
            } else if(task == 1) {
                myDeque.pop_front();
                stdDeque.pop_front();
            }

            ASSERT_EQ(myDeque.size(), stdDeque.size()) << "My deque size " << myDeque.size() << " != std deque size "
                                                       << stdDeque.size() << " on pop test " << test / 10 << std::endl;

            for(size_t i = 0; i < myDeque.size(); ++i) {
                EXPECT_EQ(myDeque[i], stdDeque[i]) << "myDeque[" << i << "] = " << myDeque[i] << " != " << stdDeque[i]
                                                   << " =  stdDeque[" << i << "] on pop test " << test << std::endl;

            }
        }
        myDeque.clear();
        stdDeque.clear();

        std::cout << "POP TEST " << test << " PASSED" << std::endl;
    }
}

TEST_F(DequeTest, frontBackTest) {
    for(int test = 1; test <= MAX_ITEMS_IN_TEST; test += 10) {
        int task = 0;
        for(int i = 0; i < test; ++i) {
            task = rand() % 2;
            if(task == 0) {
                myDeque.push_back(i);
                stdDeque.push_back(i);
            } else if(task == 1) {
                myDeque.push_front(i);
                stdDeque.push_front(i);
            }

        }
        EXPECT_EQ(myDeque.back(), stdDeque.back()) << "My deque back " << myDeque.back() << " != std deque back "
                                                   << stdDeque.back() << " on back test " << test / 10 << std::endl;

        EXPECT_EQ(myDeque.front(), stdDeque.front()) << "My deque front " << myDeque.front() << " != std deque front "
                                                     << stdDeque.front() << " on front test " << test / 10 << std::endl;

        myDeque.clear();
        stdDeque.clear();

        EXPECT_EQ(myDeque.empty(), stdDeque.empty()) << "myDeque.empty() != stdDeque.empty()" << std::endl;

        std::cout << "FRONT BACK TEST " << test << " PASSED" << std::endl;
    }
}


TEST_F(DequeTest, iteratorTest) {
    for(int test = 0; test <= MAX_ITEMS_IN_TEST; test += 10) {
        int task = 0;
        for(int i = 0; i < test; ++i) {
            task = rand() % 2;
            if(task == 0) {
                myDeque.push_back(i);
                stdDeque.push_back(i);
            } else if(task == 1) {
                myDeque.push_front(i);
                stdDeque.push_front(i);
            }
        }
        ASSERT_EQ(myDeque.size(), stdDeque.size()) << "My deque size " << myDeque.size()
                                                   << " != std deque size " << stdDeque.size()
                                                   << " on pop test " << test / 10 << std::endl;
        EXPECT_EQ(myDeque.begin() <= myDeque.end(), true) << "Wrong operator<=" << std::endl;
        EXPECT_EQ(myDeque.begin() > myDeque.end(), false) << "Wrong operator>" << std::endl;
        EXPECT_EQ(myDeque.end() >= myDeque.begin(), true) << "Wrong operator>=" << std::endl;
        EXPECT_EQ(myDeque.end() < myDeque.begin(), false) << "Wrong operator<" << std::endl;
        EXPECT_EQ(myDeque.begin() == myDeque.begin(), true) << "Wrong operator==" << std::endl;
        EXPECT_EQ(myDeque.begin() != myDeque.begin(), false) << "Wrong operator!=" << std::endl;

        std::deque<int>::iterator stdIter = stdDeque.begin();
        Deque<int>::iterator myIter = myDeque.begin();
        while(stdIter < stdDeque.end()) {
            EXPECT_EQ(*myIter, *stdIter) << "My deque begin iterator " << *myIter << " != std deque begin iterator "
                                         << *stdIter << " on back test " << test / 10 << std::endl;
            ++stdIter;
            ++myIter;
        }
        EXPECT_EQ(myIter, myDeque.end()) << "Wrong end() or operator==" << std::endl;
        stdIter = stdDeque.begin();
        myIter = myDeque.begin();
        while(stdIter < stdDeque.end()) {
            EXPECT_EQ(*myIter, *stdIter) << "My deque begin iterator " << *myIter << " != std deque begin iterator "
                                         << *stdIter << " on back test " << test / 10 << std::endl;
            stdIter += 1;
            myIter += 1;
        }
        EXPECT_EQ(myIter, myDeque.end()) << "Wrong end() or operator==" << std::endl;
        stdIter = stdDeque.begin();
        myIter = myDeque.begin();
        int diff = rand() % 100;
        while(stdIter < stdDeque.end()) {
            diff = rand() % 100;
            EXPECT_EQ(*myIter, *stdIter) << "My deque begin iterator " << *myIter << " != std deque begin iterator "
                                         << *stdIter << " on back test " << test / 10 << std::endl;
            EXPECT_EQ(myIter - myDeque.begin(), stdIter - stdDeque.begin()) << "My deque begin iterator difference "
                                                                            << myIter - myDeque.begin()
                                                                            << " != std deque begin iterator difference "
                                                                            << stdIter - stdDeque.begin()
                                                                            << " on back test " << test / 10
                                                                            << std::endl;
            stdIter += diff;
            myIter += diff;
        }
        for(int i = 0; i < myDeque.size(); ++i) {
            EXPECT_EQ(*(myDeque.begin() + i), *(stdDeque.begin() + i)) << "Wrong operator* or operator+" << std::endl;
            EXPECT_EQ(myDeque.begin()[i], stdDeque.begin()[i]) << "Wrong operator[] or operator+" << std::endl;
        }

        stdIter = stdDeque.end();
        myIter = myDeque.end();
        while(stdIter > stdDeque.begin()) {
            --stdIter;
            --myIter;
            EXPECT_EQ(*myIter, *stdIter) << "My deque end iterator " << *myIter << " != std deque end iterator "
                                         << *stdIter << " on back test " << test / 10 << std::endl;
        }
        EXPECT_EQ(myIter, myDeque.begin()) << "Wrong begin() or operator==" << std::endl;
        stdIter = stdDeque.end();
        myIter = myDeque.end();
        while(stdIter > stdDeque.begin()) {
            stdIter -= 1;
            myIter -= 1;
            EXPECT_EQ(*myIter, *stdIter) << "My deque end iterator " << *myIter << " != std deque end iterator "
                                         << *stdIter << " on back test " << test / 10 << std::endl;
        }
        EXPECT_EQ(myIter, myDeque.begin()) << "Wrong begin() or operator==" << std::endl;
        stdIter = stdDeque.end();
        myIter = myDeque.end();
        for(int i = 1; i <= myDeque.size(); ++i) {
            EXPECT_EQ(*(myDeque.end() - i), *(stdDeque.end() - i)) << "Wrong operator* or operator+" << std::endl;
            EXPECT_EQ(myDeque.end()[-i], stdDeque.end()[-i]) << "Wrong operator[] or operator+" << std::endl;
        }

        myDeque.clear();
        stdDeque.clear();
        EXPECT_EQ(myDeque.empty(), stdDeque.empty()) << "myDeque.empty() != stdDeque.empty()" << std::endl;
        std::cout << "ITERATOR TEST " << test << " PASSED" << std::endl;
    }
}

TEST_F(DequeTest, reverseIteratorTest) {
    for(int test = 0; test <= MAX_ITEMS_IN_TEST; test += 10) {
        int task = 0;
        for(int i = 0; i < test; ++i) {
            task = rand() % 2;
            if(task == 0) {
                myDeque.push_back(i);
                stdDeque.push_back(i);
            } else if(task == 1) {
                myDeque.push_front(i);
                stdDeque.push_front(i);
            }
        }
        ASSERT_EQ(myDeque.size(), stdDeque.size()) << "My deque size " << myDeque.size()
                                                   << " != std deque size " << stdDeque.size()
                                                   << " on pop test " << test / 10 << std::endl;
        EXPECT_EQ(myDeque.rbegin() <= myDeque.rend(), true) << "Wrong operator<=" << std::endl;
        EXPECT_EQ(myDeque.rbegin() > myDeque.rend(), false) << "Wrong operator>" << std::endl;
        EXPECT_EQ(myDeque.rend() >= myDeque.rbegin(), true) << "Wrong operator>=" << std::endl;
        EXPECT_EQ(myDeque.rend() < myDeque.rbegin(), false) << "Wrong operator<" << std::endl;
        EXPECT_EQ(myDeque.rbegin() == myDeque.rbegin(), true) << "Wrong operator==" << std::endl;
        EXPECT_EQ(myDeque.rbegin() != myDeque.rbegin(), false) << "Wrong operator!=" << std::endl;

        std::deque<int>::reverse_iterator stdIter = stdDeque.rbegin();
        Deque<int>::reverse_iterator myIter = myDeque.rbegin();
        while(stdIter < stdDeque.rend()) {
            EXPECT_EQ(*myIter, *stdIter) << "My deque rbegin iterator " << *myIter << " != std deque rbegin iterator "
                                         << *stdIter << " on back test " << test / 10 << std::endl;
            ++stdIter;
            ++myIter;
        }
        EXPECT_EQ(myIter, myDeque.rend()) << "Wrong rend() or operator==" << std::endl;
        stdIter = stdDeque.rbegin();
        myIter = myDeque.rbegin();
        while(stdIter < stdDeque.rend()) {
            EXPECT_EQ(*myIter, *stdIter) << "My deque rbegin iterator " << *myIter << " != std deque rbegin iterator "
                                         << *stdIter << " on back test " << test / 10 << std::endl;
            stdIter += 1;
            myIter += 1;
        }
        EXPECT_EQ(myIter, myDeque.rend()) << "Wrong rend() or operator==" << std::endl;
        stdIter = stdDeque.rbegin();
        myIter = myDeque.rbegin();
        int diff = rand() % 100;
        while(stdIter < stdDeque.rend()) {
            diff = rand() % 100;
            EXPECT_EQ(*myIter, *stdIter) << "My deque rbegin iterator " << *myIter << " != std deque rbegin iterator "
                                         << *stdIter << " on back test " << test / 10 << std::endl;
            EXPECT_EQ(myIter - myDeque.rbegin(), stdIter - stdDeque.rbegin()) << "My deque rbegin iterator difference "
                                                                            << myIter - myDeque.rbegin()
                                                                            << " != std deque rbegin iterator difference "
                                                                            << stdIter - stdDeque.rbegin()
                                                                            << " on back test " << test / 10
                                                                            << std::endl;
            stdIter += diff;
            myIter += diff;
        }
        for(int i = 0; i < myDeque.size(); ++i) {
            EXPECT_EQ(*(myDeque.rbegin() + i), *(stdDeque.rbegin() + i)) << "Wrong operator* or operator+" << std::endl;
            EXPECT_EQ(myDeque.rbegin()[i], stdDeque.rbegin()[i]) << "Wrong operator[] or operator+" << std::endl;
        }

        stdIter = stdDeque.rend();
        myIter = myDeque.rend();
        while(stdIter > stdDeque.rbegin()) {
            --stdIter;
            --myIter;
            EXPECT_EQ(*myIter, *stdIter) << "My deque rend iterator " << *myIter << " != std deque rend iterator "
                                         << *stdIter << " on back test " << test / 10 << std::endl;
        }
        EXPECT_EQ(myIter, myDeque.rbegin()) << "Wrong rbegin() or operator==" << std::endl;
        stdIter = stdDeque.rend();
        myIter = myDeque.rend();
        while(stdIter > stdDeque.rbegin()) {
            stdIter -= 1;
            myIter -= 1;
            EXPECT_EQ(*myIter, *stdIter) << "My deque rend iterator " << *myIter << " != std deque rend iterator "
                                         << *stdIter << " on back test " << test / 10 << std::endl;
        }
        EXPECT_EQ(myIter, myDeque.rbegin()) << "Wrong rbegin() or operator==";
        stdIter = stdDeque.rend();
        myIter = myDeque.rend();
        for(int i = 1; i <= myDeque.size(); ++i) {
            EXPECT_EQ(*(myDeque.rend() - i), *(stdDeque.rend() - i)) << "Wrong operator* or operator+" << std::endl;
            EXPECT_EQ(myDeque.rend()[-i], stdDeque.rend()[-i]) << "Wrong operator[] or operator+" << std::endl;
        }

        myDeque.clear();
        stdDeque.clear();
        EXPECT_EQ(myDeque.empty(), stdDeque.empty()) << "myDeque.empty() != stdDeque.empty()" << std::endl;
        std::cout << "REVERSE ITERATOR TEST " << test << " PASSED" << std::endl;
    }
}

const int TIME_TESTING_MAX_ITEMS = 10000000;
const int ITEMS_SHIFT = 100000;

class DequeTimeTest : public ::testing::Test {
public:
    static long long operations;
protected:
    Deque<int> myDeque;

    void SetUp() {
        std::cout << "SET UP" << std::endl;
    }

    void TearDown() {
        std::cout << "TEARED DOWN" << std::endl;
    }
};

long long DequeTimeTest::operations = 0;

TEST_F(DequeTimeTest, randomTest) {
    long long curTime = clock();
    int task = 0;
    for(long long items = 0; items <= TIME_TESTING_MAX_ITEMS; items += ITEMS_SHIFT) {
        curTime = clock();
        operations = 0;
        for(int i = 0; i < items; ++i) {
            task = rand() % 2;
            if(task == 0) {
                myDeque.push_back(i);
            } else {
                myDeque.push_front(i);
            }
            ++operations;
        }
        while(!myDeque.empty()) {
            task = rand() % 2;
            if(task == 0) {
                myDeque.pop_back();
            } else {
                myDeque.pop_front();
            }
            ++operations;
        }
        long long clk = clock() - curTime;
        std::cout << "CLOCKS " << clk << " / OPERATIONS " << operations << " = " << (double)clk / operations
                  << " WITH " << items << " ITEMS ON RANDOM TEST" << std::endl;
    }
}

TEST_F(DequeTimeTest, badTest) {
    long long curTime = clock();
    for(int pushTask = 0; pushTask <= 1; ++pushTask) {
        for(int popTask = 0; popTask <= 1; ++popTask) {
            for(long long items = 0; items <= TIME_TESTING_MAX_ITEMS; items += ITEMS_SHIFT) {
                curTime = clock();
                operations = 0;
                for(int i = 0; i < items; ++i) {
                    if(pushTask == 0) {
                        myDeque.push_back(i);
                    } else {
                        myDeque.push_front(i);
                    }
                    ++operations;
                }
                while(!myDeque.empty()) {
                    if(popTask == 0) {
                        myDeque.pop_back();
                    } else {
                        myDeque.pop_front();
                    }
                    ++operations;
                }
                long long clk = clock() - curTime;
                std::cout << "CLOCKS " << clk << " / OPERATIONS " << operations << " = " << (double)clk / operations
                          << " WITH " << items << " ITEMS ON BAD TEST " << pushTask << popTask << std::endl;
            }
        }
    }
}


int main(int argc, char **argv) {
    srand(time(NULL));
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}