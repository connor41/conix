#pragma once
#include <kernel/test.h>
#include <kernel/vector.h>

class test_vector : public test
{
private:
        void vector_entity_test()
        {
                add_test();
                message() << "vector() starting...\n";
                
                vector<int> vec;
                
                if (!assert_eq<size_t>(vec.size(), 0)) {
                        fail();
                        return;
                } 
                pass();
        }

        void vector_size_test()
        {
                add_test();
                message() << "vector(size_t) starting...\n";

                vector<int> vec(5);
                
                if (!assert_eq<size_t>(vec.size(), 0)) {
                        fail();
                        return;
                }
                pass();
        }

        void vector_size_data_test()
        {
                add_test();
                message() << "vector(size_t, const T &data) starting...\n";

                vector<int> vec(3, 3);
                
                if (!assert_eq<size_t>(vec.size(), 3)) {
                        fail();
                        return;
                }

                for (size_t i = 0; i < vec.size(); ++i) {
                        if (!assert_eq<int>(vec[i], 3)) {
                                fail();
                                return;
                        }
                }
                pass();
        }

        void vector_size_data_array_test()
        {
                add_test();
                message() << "vector(size_t, T* data) starting...\n";
                
                int tmp[6] = {0, 1, 2, 3, 4, 5};
                vector<int> vec(6, tmp);
                
                if (!assert_eq<size_t>(vec.size(), 6)) {
                        fail();
                        return;
                }

                for (size_t i = 0; i < vec.size(); ++i) {
                        if (!assert_eq<int>(vec[i], tmp[i])) {
                                fail();
                                return;
                        }
                }
                pass();
        }

        void vector_vector_test()
        {
                add_test();
                message() << "vector(const vector &_vector) starting...\n";

                int data[6] = {0, 1, 2, 3, 4, 5};
                vector<int> vec0(6, data);
                vector<int> vec1(vec0);

                if (!assert_eq<size_t>(vec1.size(), 6)) {
                        fail();
                        return;
                }

                for (size_t i = 0; i < vec1.size(); ++i) {
                        if (!assert_eq<int>(vec1[i], data[i])) {
                                fail();
                                return;
                        }
                }
                pass();
        }

        void append_test()
        {
                add_test();
                message() << "append(const T&) starting...\n";

                vector<int> vec;
                int data[6] = {0, 1, 2, 3, 4, 5};

                for (size_t i = 0; i < 6; ++i) {
                        vec.append(data[i]);
                }

                if (!assert_eq<size_t>(vec.size(), 6)) {
                        fail();
                        return;
                }

                for (size_t i = 0; i < vec.size(); ++i) {
                        if (!assert_eq<int>(vec[i], data[i])) {
                                fail();
                                return;
                        }
                }
                pass();
        }

        void insert_test()
        {
                add_test();
                message() << "insert(size_t, const T&) starting...\n";

                vector<int> vec;
                int data[6] = {0, 1, 2, 3, 4, 5};

                for (size_t i = 0; i < 6; ++i) {
                        vec.insert(i, data[i]);
                }

                if (!assert_eq<size_t>(vec.size(), 6)) {
                        fail();
                        return;
                }

                for (size_t i = 0; i < vec.size(); ++i) {
                        if (!assert_eq(vec[i], data[i])) {
                                fail();
                                return;
                        }
                }
                pass();
        }

public:
        test_vector() :
                test("Kernel Vector")
        {  }

        void start()
        {
                log << "Starting the [" << name << "] test...\n";

                vector_entity_test();
                vector_size_test();
                vector_size_data_test();
                vector_size_data_array_test();
                vector_vector_test();
                append_test();
                insert_test();

                stat();
        }
};