#include "stdafx.h"
#include "../CMyList/MyList.h"


struct WorkingMyList
{
	std::vector<std::string> checkStringList = { "Ymiray", "nado", "polychit", "zachet", "po", "OOP" };
	std::vector<int> checkIntList = { 0 , 1 , 2, 3, 4 , 5 };
};

template <typename T>
void VerifyList(CMyList<T> & list, const std::vector<T> & expectedList)
{
	BOOST_CHECK_EQUAL(list.GetSize(), expectedList.size());
	size_t counter = 0;
	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_SUITE(with_string)

BOOST_AUTO_TEST_SUITE(CIterator_class)

BOOST_AUTO_TEST_CASE(has_arrow_operator_and_returns_const_string_pointer)
{
	CMyList<std::string> lst;
	lst.AppendBack("hello");
	BOOST_CHECK_EQUAL(lst.begin()->size(), 5);
}

BOOST_AUTO_TEST_CASE(iterator_has_postfix_form_of_increment)
{
	WorkingMyList expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.checkStringList.size(); i++)
	{
		myList.AppendBack(expectedVector.checkStringList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.begin(); it != myList.end(); it++)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkStringList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(iterator_has_postfix_form_of_decrement)
{
	WorkingMyList expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.checkStringList.size(); i++)
	{
		myList.AppendBack(expectedVector.checkStringList[i]);
	}
	size_t counter = expectedVector.checkStringList.size() - 1;
	auto itEnd = myList.end();
	itEnd--;
	auto itBegin = myList.begin();
	for (auto it = itEnd; it != itBegin; it--)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkStringList[counter]);
		counter--;
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CMyList_class)

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

BOOST_AUTO_TEST_CASE(append_to_it_changes_size)
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
	myList.Insert(myList.begin(), "Ymiray");
	myList.Insert(myList.begin(), "nado");
	myList.Insert(myList.end(), "polychit");
	myList.Insert(++myList.begin(), "zachet");
	VerifyList(myList, { "nado", "zachet" , "Ymiray" , "polychit" });
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
	myList.AppendBack("Ymiray");
	myList.AppendBack("nado");
	myList.AppendBack("polychit");
	myList.AppendBack("zachet");
	myList.Erase(myList.begin());
	VerifyList(myList, { "nado", "polychit", "zachet" });

	myList.Erase(++myList.begin());
	VerifyList(myList, { "nado", "zachet" });

	myList.Erase(++myList.begin());
	VerifyList(myList, { "nado" });

	myList.Erase(myList.begin());
	VerifyList(myList, {});
	BOOST_CHECK(myList.IsEmpty());
}

BOOST_AUTO_TEST_CASE(can_create_vector_equal_to_std_vector)
{
	WorkingMyList expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.checkStringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkStringList[i]);
	}
	VerifyList(myList, expectedVector.checkStringList);
}

BOOST_AUTO_TEST_CASE(has_iterators_at_the_begin_and_the_end_of_string_list)
{
	WorkingMyList expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.checkStringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkStringList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkStringList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(has_const_iterators_at_the_begin_and_the_end_of_string_list)
{
	WorkingMyList expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.checkStringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkStringList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.cbegin(); it != myList.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkStringList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(has_reverse_iterators_and_const_revers_iterators_at_the_begin_and_the_end_of_string_list)
{
	WorkingMyList expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.checkStringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkStringList[i]);
	}
	size_t counter = expectedVector.checkStringList.size() - 1;
	for (auto it = myList.crbegin(); it != myList.crend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkStringList[counter]);
		counter--;
	}
	counter = expectedVector.checkStringList.size() - 1;
	for (auto it = myList.rbegin(); it != myList.rend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkStringList[counter]);
		counter--;
	}

}

BOOST_AUTO_TEST_CASE(has_copy_constructor)
{
	WorkingMyList expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.checkStringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkStringList[i]);
	}
	CMyList<std::string> copiedList(myList);
	VerifyList(myList, expectedVector.checkStringList);
	VerifyList(copiedList, expectedVector.checkStringList);
}

BOOST_AUTO_TEST_CASE(has_move_constructor)
{
	WorkingMyList expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.checkStringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkStringList[i]);
	}
	CMyList<std::string> copiedList(std::move(myList));
	VerifyList(copiedList, expectedVector.checkStringList);
}

BOOST_AUTO_TEST_CASE(has_move_operator)
{
	WorkingMyList expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.checkStringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkStringList[i]);
	}
	CMyList<std::string> copiedList;
	copiedList = std::move(myList);
	VerifyList(copiedList, expectedVector.checkStringList);
}

BOOST_AUTO_TEST_CASE(has_alignment_operator)
{
	WorkingMyList expectedVector;
	CMyList<std::string> myList;
	for (size_t i = 0; i < expectedVector.checkStringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkStringList[i]);
	}
	CMyList<std::string> copiedList;
	copiedList = myList;
	VerifyList(myList, expectedVector.checkStringList);
	VerifyList(copiedList, expectedVector.checkStringList);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CMyList_and_CIterators_classes_exceptions)

BOOST_AUTO_TEST_CASE(proprely_throws_exeptions)
{
	CMyList<std::string> myList;
	BOOST_REQUIRE_THROW(myList.Erase(myList.begin()), std::out_of_range);
	BOOST_REQUIRE_THROW(*myList.end(), std::runtime_error);
	BOOST_REQUIRE_THROW(myList.rend()--, std::out_of_range);
	WorkingMyList expectedVector;
	for (size_t i = 0; i < expectedVector.checkStringList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkStringList[i]);
	}
	BOOST_REQUIRE_THROW(myList.Erase(myList.end()), std::out_of_range);
	BOOST_REQUIRE_THROW(myList.end()++, std::out_of_range);
	BOOST_REQUIRE_THROW(++myList.end(), std::out_of_range);
	BOOST_REQUIRE_THROW(--myList.begin(), std::out_of_range);
	BOOST_REQUIRE_THROW(myList.begin()--, std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(with_int)

BOOST_AUTO_TEST_SUITE(CIterator_class)

BOOST_AUTO_TEST_CASE(iterator_has_postfix_form_of_increment)
{
	WorkingMyList expectedVector;
	CMyList<int> myList;
	for (size_t i = 0; i < expectedVector.checkIntList.size(); i++)
	{
		myList.AppendBack(expectedVector.checkIntList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.begin(); it != myList.end(); it++)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkIntList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(iterator_has_postfix_form_of_decrement)
{
	WorkingMyList expectedVector;
	CMyList<int> myList;
	for (size_t i = 0; i < expectedVector.checkIntList.size(); i++)
	{
		myList.AppendBack(expectedVector.checkIntList[i]);
	}
	size_t counter = expectedVector.checkIntList.size() - 1;
	auto itEnd = myList.end();
	itEnd--;
	auto itBegin = myList.begin();
	for (auto it = itEnd; it != itBegin; it--)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkIntList[counter]);
		counter--;
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CMyList_class)

BOOST_AUTO_TEST_CASE(has_zero_size_on_create)
{
	BOOST_CHECK_EQUAL(CMyList<int>().GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(empty_on_create)
{
	BOOST_CHECK_EQUAL(CMyList<int>().IsEmpty(), true);
}

BOOST_AUTO_TEST_CASE(can_input_into_the_front_of_list)
{
	CMyList<int> myList;
	myList.AppendFront(0);
	BOOST_CHECK_EQUAL(myList.GetSize(), 1);
}

BOOST_AUTO_TEST_CASE(can_input_into_the_back_of_list)
{
	CMyList<int> myList;
	myList.AppendBack(0);
	BOOST_CHECK_EQUAL(myList.GetSize(), 1);
}

BOOST_AUTO_TEST_CASE(append_to_it_changes_size)
{
	CMyList<int> myList;
	myList.AppendFront(0);
	BOOST_CHECK_EQUAL(myList.GetSize(), 1);

	myList.AppendBack(1);
	BOOST_CHECK_EQUAL(myList.GetSize(), 2);
}

BOOST_AUTO_TEST_CASE(can_insert_element_into_iterator_position)
{
	CMyList<int> myList;
	myList.Insert(myList.begin(), 0);
	myList.Insert(myList.begin(), 1);
	myList.Insert(myList.end(), 2);
	myList.Insert(++myList.begin(), 3);
	VerifyList(myList, { 1, 3, 0, 2 });
}

BOOST_AUTO_TEST_CASE(can_clear_list)
{
	CMyList<int> myList;
	myList.AppendBack(0);
	myList.AppendBack(1);
	myList.Clear();
	BOOST_CHECK_EQUAL(myList.GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(can_erase_element_at_iterator_position)
{
	CMyList<int> myList;
	myList.AppendBack(0);
	myList.AppendBack(1);
	myList.AppendBack(2);
	myList.AppendBack(3);
	myList.Erase(myList.begin());
	VerifyList(myList, { 1, 2, 3 });

	myList.Erase(++myList.begin());
	VerifyList(myList, { 1, 3 });

	myList.Erase(++myList.begin());
	VerifyList(myList, { 1 });

	myList.Erase(myList.begin());
	VerifyList(myList, {});
	BOOST_CHECK(myList.IsEmpty());
}

BOOST_AUTO_TEST_CASE(can_create_vector_equal_to_std_vector)
{
	WorkingMyList expectedVector;
	CMyList<int> myList;
	for (size_t i = 0; i < expectedVector.checkIntList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkIntList[i]);
	}
	VerifyList(myList, expectedVector.checkIntList);
}

BOOST_AUTO_TEST_CASE(has_iterators_at_the_begin_and_the_end_of_int_list)
{
	WorkingMyList expectedVector;
	CMyList<int> myList;
	for (size_t i = 0; i < expectedVector.checkIntList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkIntList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkIntList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(has_const_iterators_at_the_begin_and_the_end_of_int_list)
{
	WorkingMyList expectedVector;
	CMyList<int> myList;
	for (size_t i = 0; i < expectedVector.checkIntList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkIntList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.cbegin(); it != myList.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkIntList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(has_reverse_iterators_and_const_revers_iterators_at_the_begin_and_the_end_of_int_list)
{
	WorkingMyList expectedVector;
	CMyList<int> myList;
	for (size_t i = 0; i < expectedVector.checkIntList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkIntList[i]);
	}
	size_t counter = expectedVector.checkIntList.size() - 1;
	for (auto it = myList.crbegin(); it != myList.crend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkIntList[counter]);
		counter--;
	}
	counter = expectedVector.checkIntList.size() - 1;
	for (auto it = myList.rbegin(); it != myList.rend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkIntList[counter]);
		counter--;
	}

}

BOOST_AUTO_TEST_CASE(has_copy_constructor)
{
	WorkingMyList expectedVector;
	CMyList<int> myList;
	for (size_t i = 0; i < expectedVector.checkIntList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkIntList[i]);
	}
	CMyList<int> copiedList(myList);
	VerifyList(myList, expectedVector.checkIntList);
	VerifyList(copiedList, expectedVector.checkIntList);
}

BOOST_AUTO_TEST_CASE(has_move_constructor)
{
	WorkingMyList expectedVector;
	CMyList<int> myList;
	for (size_t i = 0; i < expectedVector.checkIntList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkIntList[i]);
	}
	CMyList<int> copiedList(std::move(myList));
	VerifyList(copiedList, expectedVector.checkIntList);
}

BOOST_AUTO_TEST_CASE(has_move_operator)
{
	WorkingMyList expectedVector;
	CMyList<int> myList;
	for (size_t i = 0; i < expectedVector.checkIntList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkIntList[i]);
	}
	CMyList<int> copiedList;
	copiedList = std::move(myList);
	VerifyList(copiedList, expectedVector.checkIntList);
}

BOOST_AUTO_TEST_CASE(has_alignment_operator)
{
	WorkingMyList expectedVector;
	CMyList<int> myList;
	for (size_t i = 0; i < expectedVector.checkIntList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkIntList[i]);
	}
	CMyList<int> copiedList;
	copiedList = myList;
	VerifyList(myList, expectedVector.checkIntList);
	VerifyList(copiedList, expectedVector.checkIntList);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CMyList_and_CIterators_classes_exceptions)

BOOST_AUTO_TEST_CASE(proprely_throws_exeptions)
{
	CMyList<int> myList;
	BOOST_REQUIRE_THROW(myList.Erase(myList.begin()), std::out_of_range);
	BOOST_REQUIRE_THROW(*myList.end(), std::runtime_error);
	BOOST_REQUIRE_THROW(myList.rend()--, std::out_of_range);
	WorkingMyList expectedVector;
	for (size_t i = 0; i < expectedVector.checkIntList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkIntList[i]);
	}
	BOOST_REQUIRE_THROW(myList.Erase(myList.end()), std::out_of_range);
	BOOST_REQUIRE_THROW(myList.end()++, std::out_of_range);
	BOOST_REQUIRE_THROW(++myList.end(), std::out_of_range);
	BOOST_REQUIRE_THROW(--myList.begin(), std::out_of_range);
	BOOST_REQUIRE_THROW(myList.begin()--, std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()