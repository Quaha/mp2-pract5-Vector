#include "Vector.h"

#include <gtest.h>
#include <vector>
#include <random>

TEST(Vector, can_create_Vector) {
    ASSERT_NO_THROW(Vector<int> Vector);
}

TEST(Vector, default_constructor) {
    Vector<int> Vector;
    EXPECT_TRUE(Vector.empty());
    EXPECT_EQ(Vector.size(), 0);
}

TEST(Vector, correct_push_back_working) {
    Vector<int> Vector;

    for (int i = 0; i < 100; i++) {
        Vector.push_back(i);
        EXPECT_EQ(Vector.back(), i);
    }
}

TEST(Vector, push_back_and_size) {
    Vector<int> Vector;
    Vector.push_back(5);
    Vector.push_back(10);

    EXPECT_FALSE(Vector.empty());
    EXPECT_EQ(Vector.size(), 2);
}

TEST(Vector, correct_pop_back_working) {
    Vector<int> Vector;

    for (int i = 0; i < 5; i++) {
        Vector.push_back(i);
        //for (int i = 0; i < Vector.curr_capacity / 2; i++) {
        //    std::cout << Vector.prev_vector[i] << " ";
        //}
        //std::cout << "\n";
        //for (int i = 0; i < Vector.curr_capacity; i++) {
        //    std::cout << Vector.curr_vector[i] << " ";
        //}
        //std::cout << "\n";
        //for (int i = 0; i < Vector.curr_capacity * 2; i++) {
        //    std::cout << Vector.next_vector[i] << " ";
        //}
        //std::cout << "\n";
    }

    for (int i = 4; i >= 0; i--) {
        EXPECT_EQ(Vector.back(), i);
        //for (int i = 0; i < Vector.curr_capacity / 2; i++) {
        //    std::cout << Vector.prev_vector[i] << " ";
        //}
        //std::cout << "\n";
        //for (int i = 0; i < Vector.curr_capacity; i++) {
        //    std::cout << Vector.curr_vector[i] << " ";
        //}
        //std::cout << "\n";
        //for (int i = 0; i < Vector.curr_capacity * 2; i++) {
        //    std::cout << Vector.next_vector[i] << " ";
        //}
        //std::cout << "\n";
        Vector.pop_back();
    }
}

TEST(Vector, pop_back_and_size) {
    Vector<int> Vector;
    Vector.push_back(5);
    Vector.push_back(10);
    Vector.pop_back();

    EXPECT_EQ(Vector.size(), 1);
    EXPECT_EQ(Vector.back(), 5);
}


TEST(Vector, back_on_empty_Vector) {
    Vector<int> Vector;
    EXPECT_ANY_THROW(Vector.back());
}

TEST(Vector, pop_back_on_empty_Vector) {
    Vector<int> Vector;
    EXPECT_ANY_THROW(Vector.pop_back());
}

TEST(Vector, copy_constructor) {
    Vector<int> Vector1;
    Vector1.push_back(1);
    Vector1.push_back(2);

    Vector<int> Vector2(Vector1);

    EXPECT_EQ(Vector2.size(), Vector1.size());
    EXPECT_EQ(Vector2.back(), Vector1.back());

    Vector2.pop_back();
    EXPECT_NE(Vector2.size(), Vector1.size());
}

TEST(Vector, copy_assignment_operator1) {
    Vector<int> Vector1;
    Vector1.push_back(5);
    Vector1.push_back(10);

    Vector<int> Vector2;
    Vector2 = Vector1;

    EXPECT_EQ(Vector2.size(), Vector1.size());
    EXPECT_EQ(Vector2.back(), Vector1.back());

    Vector2.pop_back();
    EXPECT_NE(Vector2.size(), Vector1.size());
}

TEST(Vector, copy_assignment_operator2) {
    Vector<int> Vector1;
    Vector1.push_back(5);

    ASSERT_NO_THROW(Vector1 = Vector1);
}

TEST(Vector, move_constructor) {
    Vector<int> Vector1;
    Vector1.push_back(8);
    Vector1.push_back(16);

    Vector<int> Vector2(std::move(Vector1));

    EXPECT_EQ(Vector2.size(), 2);
    EXPECT_EQ(Vector2.back(), 16);
    EXPECT_TRUE(Vector1.empty());
}

TEST(Vector, move_assignment_operator1) {
    Vector<int> Vector1;
    Vector1.push_back(8);
    Vector1.push_back(16);

    Vector<int> Vector2;
    Vector2 = std::move(Vector1);

    EXPECT_EQ(Vector2.size(), 2);
    EXPECT_EQ(Vector2.back(), 16);
    EXPECT_TRUE(Vector1.empty());
}

TEST(Vector, move_assignment_operator2) {
    Vector<int> Vector1;
    Vector1.push_back(5);

    ASSERT_NO_THROW(Vector1 = std::move(Vector1));
}

TEST(Vector, large_number_of_elements) {
    Vector<int> Vector;
    for (int i = 0; i < 1000; ++i) {
        Vector.push_back(i);
    }

    EXPECT_EQ(Vector.size(), 1000);
    EXPECT_EQ(Vector.back(), 999);
}

TEST(Vector, push_and_pop_multiple_times) {
    Vector<int> Vector;
    for (int i = 0; i < 5; ++i) {
        Vector.push_back(i);
    }
    for (int i = 0; i < 5; ++i) {
        Vector.pop_back();
    }

    EXPECT_TRUE(Vector.empty());
    EXPECT_EQ(Vector.size(), 0);
}

TEST(Vector, empty_after_push_and_pop) {
    Vector<int> Vector;
    Vector.push_back(1);
    Vector.pop_back();

    EXPECT_TRUE(Vector.empty());
}

TEST(Vector, combination_of_push_and_pop_1) {
    Vector<int> Vector;

    for (int i = 0; i < 100; i++) {
        Vector.push_back(i);
    }

    for (int i = 0; i < 100; i++) {
        Vector.pop_back();
    }

    for (int i = 0; i < 100; i++) {
        Vector.push_back(i);
        EXPECT_EQ(Vector.back(), i);
    }

    for (int i = 99; i >= 0; i--) {
        EXPECT_EQ(Vector.back(), i);
        Vector.pop_back();
    }
}

TEST(Vector, combination_of_push_and_pop_2) {
    Vector<int> Vector;

    for (int i = 0; i < 16; i++) {
        ASSERT_NO_THROW(Vector.push_back(i));
    }

    ASSERT_NO_THROW(Vector.pop_back());
    for (int i = 0; i < 20; i++) {
        ASSERT_NO_THROW(Vector.push_back(i));
    }

    while (!Vector.empty()) {
        ASSERT_NO_THROW(Vector.pop_back());
    }
}

TEST(Vector, access_elements_using_bracket_operator) {
    Vector<int> Vector;
    Vector.push_back(10);
    Vector.push_back(20);
    Vector.push_back(30);

    EXPECT_EQ(Vector[0], 10);
    EXPECT_EQ(Vector[1], 20);
    EXPECT_EQ(Vector[2], 30);
}

TEST(Vector, modify_elements_using_bracket_operator) {
    Vector<int> Vector;
    Vector.push_back(5);
    Vector.push_back(15);

    Vector[0] = 50;
    Vector[1] = 150;

    EXPECT_EQ(Vector[0], 50);
    EXPECT_EQ(Vector[1], 150);
}

TEST(Vector, const_access_using_bracket_operator) {
    Vector<int> vector;
    vector.push_back(100);
    vector.push_back(200);

    const Vector<int>& ConstVector = vector;

    EXPECT_EQ(ConstVector[0], 100);
    EXPECT_EQ(ConstVector[1], 200);
}

TEST(Vector, out_of_bounds_access_throws_exception) {
    Vector<int> Vector;
    Vector.push_back(1);
    Vector.push_back(2);

    EXPECT_THROW(Vector[2], std::out_of_range);
    EXPECT_THROW(Vector[100], std::out_of_range);
}

TEST(Vector, access_elements_after_resizing) {
    Vector<int> vector;
    vector.push_back(42);
    vector.push_back(84);

    EXPECT_EQ(vector[0], 42);
    EXPECT_EQ(vector[1], 84);

    vector.push_back(168);
    vector.push_back(336);

    EXPECT_EQ(vector[2], 168);
    EXPECT_EQ(vector[3], 336);
    EXPECT_EQ(vector.size(), 4);
}

TEST(Vector, negative_index_access_throws_exception) {
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(20);

    ASSERT_ANY_THROW(vector[-1]);
    ASSERT_ANY_THROW(vector[5]);
}

TEST(Vector, stress_test_push_and_pop) {
    std::srand(time(0));

    int COUNT_OF_TESTS = 1000;
    int ACTIONS_PER_TEST = 10000;

    for (int CURR_TEST_CASE = 0; CURR_TEST_CASE < COUNT_OF_TESTS; CURR_TEST_CASE++) {
        Vector<int> Vector;
        std::vector<int> Vector_copy;

        for (int CURR_ACTION = 0; CURR_ACTION < ACTIONS_PER_TEST; CURR_ACTION++) {
            int type = rand() % 2;

            if (type == 0) {
                int value = rand();
                Vector.push_back(value);
                Vector_copy.push_back(value);
            }
            if (type == 1) {
                if (!Vector.empty()) {
                    Vector.pop_back();
                    Vector_copy.pop_back();
                }
            }

            if (!Vector.empty()) {
                EXPECT_EQ(Vector.back(), Vector_copy.back());
            }
            EXPECT_EQ(Vector.size(), Vector_copy.size());
        }
    }
}