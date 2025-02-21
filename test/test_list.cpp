#include <gtest.h>
#include "list.h"

TEST(List, can_create_default) {
	ASSERT_NO_THROW(List<int>());
}

TEST(List, can_create_initializer_list)
{
	ASSERT_NO_THROW(List<int>({ 1,2,3,4,5 }));
}

TEST(List, check_correct_initializer_list)
{
	List<int> a{ 1,2,3,4,5 };
	auto it = a.begin();
	for (int i = 1; i <= 5; i++) {
		ASSERT_EQ(*it, i);
		++*it;
	}
}

TEST(List, check_iterators) {
	List<int> a = { 1,2,3,4,5 };
	int i = 1;
	for (auto it = a.begin(); it != a.end(); ++it, i++) {
		ASSERT_EQ(*it, i);
	}
	ASSERT_EQ(6, i);
}

TEST(List, can_create_copy_constructor) {
	List<int> a;
	a.push_back(1, 1); a.push_back(2, 2); a.push_back(3, 3); a.push_back(4, 4); a.push_back(5, 5);
	ASSERT_NO_THROW(List<int> b(a));
}

TEST(List, check_copy_constructor) {
	List<int> a;
	a.push_back(1, 1); a.push_back(2, 2); a.push_back(3, 3); a.push_back(4, 4); a.push_back(5, 5);
	List<int> b(a);
	ASSERT_EQ(a == b, 1);
}

TEST(List, can_push_back_val) {
	List<int> a = { 1 };
	ASSERT_NO_THROW(a.push_back(243, 2));
}

TEST(List, check_push_back) {
	List<int> a;
	a.push_back(1, 1); a.push_back(2, 2); a.push_back(3, 3); a.push_back(4, 4); a.push_back(5, 5);
	List<int> b;
	b = a;
	ASSERT_EQ(b == a, 1);
}

TEST(List, check_constructor_own_memory) {
	List<int> a = { 1,2,3,4,5 };
	List<int> b(a);
	for (auto it1 = a.begin(), it2 = b.begin(); it1 != a.end(), it2 != b.end(); ++it1, ++it2) {
		*it1 = (*it1) + 1;
	}
	ASSERT_NE(a == b, 1);

}

TEST(List, can_append) {
	List<int> a = { };
	ASSERT_NO_THROW(a.append(1, 5));
}
TEST(List, can_append_in_begin) {
	List<int> a = { };
	a.push_back(50, 50);
	ASSERT_NO_THROW(a.append(1, 5));
}
TEST(List, can_append_in_back) {
	List<int> a = { };
	a.push_back(1, 1);
	ASSERT_NO_THROW(a.append(1, 5));
}
TEST(List, can_append_in_median) {
	List<int> a = { };
	a.push_back(1, 1);
	a.push_back(1, 10);
	ASSERT_NO_THROW(a.append(1, 5));
}
TEST(List, can_append_correctly) {
	List<int> a = { };
	a.append(1, 0);
	List<int> b = { 1 };
	ASSERT_EQ(a == b, 1);
}

TEST(List, can_append_in_begin_correctly) {
	List<int> a = { };
	a.push_back(50, 1);
	a.append(1, 0);
	List<int> b = { 1, 50 };
	ASSERT_EQ(a == b, 1);
}
TEST(List, can_append_in_back_correctly) {
	List<int> a = { };
	a.push_back(1, 0);
	a.append(2, 1);
	List<int> b = { 1, 2 };
	ASSERT_EQ(a == b, 1);
}
TEST(List, can_append_median_correctly) {
	List<int> a = { };
	a.push_back(1, 0);
	a.push_back(3, 2);
	a.append(2, 1);
	List<int> b = { 1,2,3 };
	ASSERT_EQ(a == b, 1);
}
TEST(List, append_exist_element_in_begin) {
	List<int> a = { };
	a.push_back(1, 0);
	a.push_back(3, 1);
	ASSERT_NO_THROW(a.append(5, 0));
}
TEST(List, append_exist_element_in_end) {
	List<int> a = { };
	a.push_back(1, 0);
	a.push_back(3, 1);
	ASSERT_NO_THROW(a.append(5, 1));
}
TEST(List, append_exist_element_in_median) {
	List<int> a = { };
	a.push_back(1, 0);
	a.push_back(3, 1);
	a.push_back(9, 2);
	ASSERT_NO_THROW(a.append(5, 1));
}
TEST(List, append_exist_element_in_begin_correct) {
	List<int> a = { };
	a.push_back(1, 0);
	a.push_back(3, 1);
	a.append(5, 0);
	auto it = a.begin();
	ASSERT_EQ(*it, 6);
}
TEST(List, append_exist_element_in_end_correct) {
	List<int> a = { };
	a.push_back(1, 0);
	a.push_back(3, 1);
	a.append(5, 1);
	auto it = a.begin();
	ASSERT_EQ(*++it, 8);
}
TEST(List, append_exist_element_in_median_correct) {
	List<int> a = { };
	a.push_back(1, 0);
	a.push_back(3, 1);
	a.push_back(7, 2);
	a.append(5, 1);
	auto it = a.begin();
	ASSERT_EQ(*++it, 8);
}
TEST(List, push_back_after_append) {
	List<int> a = { };
	a.push_back(1, 0);
	a.append(5, 1);
	a.push_back(7, 2);
	a.append(8, 3);
	auto it = a.begin();
	++it; ++it;
	ASSERT_EQ(*it, 7);
	++it;
	ASSERT_EQ(*it, 8);
}
TEST(List, throw_to_big_size_push_back) {
	List<int> a = { };
	ASSERT_ANY_THROW(a.push_back(1, 1000));
}
TEST(List, throw_to_big_size_append) {
	List<int> a = { };
	ASSERT_ANY_THROW(a.append(1, 1000));
}