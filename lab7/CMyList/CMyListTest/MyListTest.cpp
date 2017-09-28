#include "stdafx.h"
#include <iostream>
#include "../CMyList/MyList.h"


struct S
{
	bool throwOnCopy = false;
	S() = default;
	S(S const & x)
	{
		if (throwOnCopy) throw;
	}
};

template <typename T>
void VerifyList(CMyList<T> & list, const std::vector<T> & expectedElements)
{
	BOOST_CHECK_EQUAL(list.GetSize(), expectedElements.size());
	size_t counter = 0;
	for (CIterator<const T> it = list.cbegin(); it != list.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedElements[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_SUITE(CIterator_class)

BOOST_AUTO_TEST_SUITE(with_string_data)

BOOST_AUTO_TEST_CASE(has_arrow_operator_and_returns_pointer)
{
	CMyList<std::string> lst;
	lst.AppendBack("hello");
	BOOST_CHECK_EQUAL(lst.begin()->size(), 5);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CMyList_class)

struct MyListFix
{
	std::vector<std::string> stringList = { "Screaming", "At", "Myself", "Stay", "Away", "From Me" };
	std::vector<size_t> intList = { 1, 2, 3, 4, 5, 6 };
};

BOOST_AUTO_TEST_SUITE(with_string_data)

BOOST_AUTO_TEST_CASE(has_zero_size_on_create)
{
	BOOST_CHECK_EQUAL(CMyList<std::string>().GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(empty_on_create)
{
	BOOST_CHECK_EQUAL(CMyList<std::string>().IsEmpty(), true);
}

BOOST_AUTO_TEST_CASE(can_input_into_the_front_of_list)
{
	CMyList<std::string> myList;
	myList.AppendFront("Hello");
	BOOST_CHECK_EQUAL(myList.GetSize(), 1);
}

BOOST_AUTO_TEST_CASE(can_input_into_the_back_of_list)
{
	CMyList<std::string> myList;
	myList.AppendBack("Hello");
	BOOST_CHECK_EQUAL(myList.GetSize(), 1);
}

BOOST_AUTO_TEST_CASE(push_to_it_changes_size)
{
	CMyList<std::string> myList;
	myList.AppendFront("First");
	BOOST_CHECK_EQUAL(myList.GetSize(), 1);

	myList.AppendBack("Second");
	BOOST_CHECK_EQUAL(myList.GetSize(), 2);
}

BOOST_AUTO_TEST_CASE(can_insert_element_into_iterator_position)
{
	CMyList<std::string> myList;
	myList.Insert(myList.begin(), "Screaming");
	myList.Insert(myList.begin(), "At");
	myList.Insert(myList.end(), "Myself");
	myList.Insert(++myList.begin(), "Stay");
	VerifyList<std::string>(myList, { "At", "Stay" , "Screaming" , "Myself" });
}

BOOST_AUTO_TEST_CASE(can_clear_list)
{
	CMyList<std::string> myList;
	myList.AppendBack("1");
	myList.AppendBack("2");
	myList.Clear();
	BOOST_CHECK_EQUAL(myList.GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(can_erase_element_at_iterator_position)
{
	CMyList<std::string> myList;
	myList.AppendBack("Screaming");
	myList.AppendBack("At");
	myList.AppendBack("Myself");
	myList.AppendBack("Stay");
	myList.Erase(myList.begin());
	VerifyList<std::string>(myList, { "At", "Myself", "Stay" });

	myList.Erase(++myList.begin());
	VerifyList<std::string>(myList, { "At", "Stay" });

	myList.Erase(++myList.begin());
	VerifyList<std::string>(myList, { "At" });

	myList.Erase(myList.begin());
	VerifyList<std::string>(myList, {});
	BOOST_CHECK(myList.IsEmpty());
}

BOOST_AUTO_TEST_CASE(can_create_vector_equal_to_std_vector)
{
	MyListFix expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.stringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.stringList[i]);
	}
	VerifyList<std::string>(myList, expectedVector.stringList);
}

BOOST_AUTO_TEST_CASE(has_iterators_at_the_begin_and_the_end_of_string_list)
{
	MyListFix expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.stringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.stringList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.stringList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(iterator_has_postfix_form_of_increment)
{
	MyListFix expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.stringList.size(); i++)
	{
		myList.AppendBack(expectedVector.stringList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.begin(); it != myList.end(); it++)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.stringList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(has_const_iterators_at_the_begin_and_the_end_of_string_list)
{
	MyListFix expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.stringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.stringList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.cbegin(); it != myList.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.stringList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(has_reverse_iterators_and_const_revers_iterators_at_the_begin_and_the_end_of_string_list)
{
	MyListFix expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.stringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.stringList[i]);
	}
	size_t counter = expectedVector.stringList.size() - 1;
	for (auto it = myList.crbegin(); it != myList.crend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.stringList[counter]);
		counter--;
	}
	counter = expectedVector.stringList.size() - 1;
	for (auto it = myList.rbegin(); it != myList.rend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.stringList[counter]);
		counter--;
	}

}

BOOST_AUTO_TEST_CASE(has_copy_constructor)
{
	MyListFix expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.stringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.stringList[i]);
	}
	CMyList<std::string> copiedList(myList);
	VerifyList<std::string>(myList, expectedVector.stringList);
	VerifyList<std::string>(copiedList, expectedVector.stringList);
}

BOOST_AUTO_TEST_CASE(has_move_constructor)
{
	MyListFix expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.stringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.stringList[i]);
	}
	CMyList<std::string> copiedList(std::move(myList));
	VerifyList<std::string>(copiedList, expectedVector.stringList);
}

BOOST_AUTO_TEST_CASE(has_move_operator)
{
	MyListFix expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.stringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.stringList[i]);
	}
	CMyList<std::string> copiedList;
	copiedList = std::move(myList);
	VerifyList<std::string>(copiedList, expectedVector.stringList);
}

BOOST_AUTO_TEST_CASE(has_alignment_operator)
{
	MyListFix expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.stringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.stringList[i]);
	}
	CMyList<std::string> copiedList;
	copiedList = myList;
	VerifyList<std::string>(myList, expectedVector.stringList);
	VerifyList<std::string>(copiedList, expectedVector.stringList);
}

BOOST_AUTO_TEST_CASE(proprely_throws_exeptions)
{
	CMyList<std::string> myList;
	BOOST_REQUIRE_THROW(myList.Erase(myList.begin()), std::out_of_range);
	BOOST_REQUIRE_THROW(*myList.end(), std::runtime_error);
	BOOST_REQUIRE_THROW(myList.rend()--, std::out_of_range);
	MyListFix expectedVector;
	for (size_t i = 0; i < expectedVector.stringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.stringList[i]);
	}
	BOOST_REQUIRE_THROW(myList.Erase(myList.end()), std::out_of_range);
	BOOST_REQUIRE_THROW(myList.end()++, std::out_of_range);
	BOOST_REQUIRE_THROW(++myList.end(), std::out_of_range);
	BOOST_REQUIRE_THROW(----myList.begin(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(with_size_t_data)

BOOST_AUTO_TEST_CASE(has_zero_size_on_create)
{
	BOOST_CHECK_EQUAL(CMyList<size_t>().GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(empty_on_create)
{
	BOOST_CHECK_EQUAL(CMyList<size_t>().IsEmpty(), true);
}

BOOST_AUTO_TEST_CASE(can_input_into_the_front_of_list)
{
	CMyList<size_t> myList;
	myList.AppendFront(1);
	BOOST_CHECK_EQUAL(myList.GetSize(), 1);
}

BOOST_AUTO_TEST_CASE(can_input_into_the_back_of_list)
{
	CMyList<size_t> myList;
	myList.AppendBack(1);
	BOOST_CHECK_EQUAL(myList.GetSize(), 1);
}

BOOST_AUTO_TEST_CASE(can_insert_element_into_iterator_position)
{
	CMyList<size_t> myList;
	myList.Insert(myList.begin(), 1);
	myList.Insert(myList.begin(), 2);
	myList.Insert(myList.end(), 3);
	myList.Insert(++myList.begin(), 4);
	VerifyList<size_t>(myList, { 2, 4, 1, 3 });
}

BOOST_AUTO_TEST_CASE(can_clear_list)
{
	CMyList<size_t> myList;
	myList.AppendBack(1);
	myList.AppendBack(2);
	myList.Clear();
	BOOST_CHECK_EQUAL(myList.GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(can_erase_element_at_iterator_position)
{
	CMyList<size_t> myList;
	myList.AppendBack(1);
	myList.AppendBack(2);
	myList.AppendBack(3);
	myList.AppendBack(4);
	myList.Erase(myList.begin());
	VerifyList<size_t>(myList, { 2, 3, 4 });

	myList.Erase(++myList.begin());
	VerifyList<size_t>(myList, { 2, 4 });

	myList.Erase(++myList.begin());
	VerifyList<size_t>(myList, { 2 });

	myList.Erase(myList.begin());
	VerifyList<size_t>(myList, {});
	BOOST_CHECK(myList.IsEmpty());
}

BOOST_AUTO_TEST_CASE(can_create_vector_equal_to_std_vector)
{
	MyListFix expectedVector;
	CMyList<size_t> myList;
	for (size_t i = 0; i < expectedVector.intList.size(); ++i)
	{
		myList.AppendBack(expectedVector.intList[i]);
	}
	VerifyList<size_t>(myList, expectedVector.intList);
}

BOOST_AUTO_TEST_CASE(has_iterators_at_the_begin_and_the_end_of_string_list)
{
	MyListFix expectedVector;
	CMyList<size_t> myList;
	for (size_t i = 0; i < expectedVector.intList.size(); ++i)
	{
		myList.AppendBack(expectedVector.intList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.intList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(iterator_has_postfix_form_of_increment)
{
	MyListFix expectedVector;
	CMyList<size_t> myList;
	for (size_t i = 0; i < expectedVector.intList.size(); i++)
	{
		myList.AppendBack(expectedVector.intList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.begin(); it != myList.end(); it++)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.intList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(has_const_iterators_at_the_begin_and_the_end_of_string_list)
{
	MyListFix expectedVector;
	CMyList<size_t> myList;
	for (size_t i = 0; i < expectedVector.intList.size(); ++i)
	{
		myList.AppendBack(expectedVector.intList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.cbegin(); it != myList.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.intList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(has_reverse_iterators_and_const_revers_iterators_at_the_begin_and_the_end_of_string_list)
{
	MyListFix expectedVector;
	CMyList<size_t> myList;
	for (size_t i = 0; i < expectedVector.intList.size(); ++i)
	{
		myList.AppendBack(expectedVector.intList[i]);
	}
	size_t counter = expectedVector.intList.size() - 1;
	for (auto it = myList.crbegin(); it != myList.crend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.intList[counter]);
		counter--;
	}
	counter = expectedVector.intList.size() - 1;
	for (auto it = myList.rbegin(); it != myList.rend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.intList[counter]);
		counter--;
	}

}

BOOST_AUTO_TEST_CASE(has_copy_constructor)
{
	MyListFix expectedVector;
	CMyList<size_t> myList;
	for (size_t i = 0; i < expectedVector.intList.size(); ++i)
	{
		myList.AppendBack(expectedVector.intList[i]);
	}
	CMyList<size_t> copiedList(myList);
	VerifyList<size_t>(myList, expectedVector.intList);
	VerifyList<size_t>(copiedList, expectedVector.intList);
}

BOOST_AUTO_TEST_CASE(has_move_constructor)
{
	MyListFix expectedVector;
	CMyList<size_t> myList;
	for (size_t i = 0; i < expectedVector.intList.size(); ++i)
	{
		myList.AppendBack(expectedVector.intList[i]);
	}
	CMyList<size_t> copiedList(std::move(myList));
	VerifyList<size_t>(copiedList, expectedVector.intList);
}

BOOST_AUTO_TEST_CASE(has_move_operator)
{
	MyListFix expectedVector;
	CMyList<size_t> myList;
	for (size_t i = 0; i < expectedVector.intList.size(); ++i)
	{
		myList.AppendBack(expectedVector.intList[i]);
	}
	CMyList<size_t> copiedList;
	copiedList = std::move(myList);
	VerifyList<size_t>(copiedList, expectedVector.intList);
}

BOOST_AUTO_TEST_CASE(has_alignment_operator)
{
	MyListFix expectedVector;
	CMyList<size_t> myList;
	for (size_t i = 0; i < expectedVector.intList.size(); ++i)
	{
		myList.AppendBack(expectedVector.intList[i]);
	}
	CMyList<size_t> copiedList;
	copiedList = myList;
	VerifyList<size_t>(myList, expectedVector.intList);
	VerifyList<size_t>(copiedList, expectedVector.intList);
}

BOOST_AUTO_TEST_CASE(proprely_throws_exeptions)
{
	CMyList<size_t> myList;
	BOOST_REQUIRE_THROW(myList.Erase(myList.begin()), std::out_of_range);
	BOOST_REQUIRE_THROW(*myList.end(), std::runtime_error);
	BOOST_REQUIRE_THROW(myList.rend()--, std::out_of_range);
	MyListFix expectedVector;
	for (size_t i = 0; i < expectedVector.intList.size(); ++i)
	{
		myList.AppendBack(expectedVector.intList[i]);
	}
	BOOST_REQUIRE_THROW(myList.Erase(myList.end()), std::out_of_range);
	BOOST_REQUIRE_THROW(myList.end()++, std::out_of_range);
	BOOST_REQUIRE_THROW(++myList.end(), std::out_of_range);
	BOOST_REQUIRE_THROW(----myList.begin(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
