#include "stdafx.h"
#include <iostream>
#include "../StringList/StringList.h"


struct WorkingStringList
{
	std::vector<std::string> checkList = { "Ymiray", "nado", "polychit", "zachet", "po", "OOP" };
};

void VerifyList(CStringList & list, const std::vector<std::string> & expectedList)
{
	BOOST_CHECK_EQUAL(list.GetSize(), expectedList.size());
	size_t counter = 0;
	for (auto it = list.cbegin(); it != list.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_SUITE(CIterator_class)

BOOST_AUTO_TEST_CASE(has_arrow_operator_and_returns_const_string_pointer)
{
	CStringList lst;
	lst.AppendBack("hello");
	BOOST_CHECK_EQUAL(lst.begin()->size(), 5);
}

BOOST_AUTO_TEST_CASE(iterator_has_postfix_form_of_increment)
{
	WorkingStringList expectedVector;
	CStringList myList;
	for (size_t i = 0; i < expectedVector.checkList.size(); i++)
	{
		myList.AppendBack(expectedVector.checkList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.begin(); it != myList.end(); it++)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(iterator_has_postfix_form_of_decrement)
{
	WorkingStringList expectedVector;
	CStringList myList;
	for (size_t i = 0; i < expectedVector.checkList.size(); i++)
	{
		myList.AppendBack(expectedVector.checkList[i]);
	}
	size_t counter = expectedVector.checkList.size() - 1;
	auto itEnd = myList.end();
	itEnd--;
	auto itBegin = myList.begin();
	for (auto it = itEnd; it != itBegin; it--)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkList[counter]);
		counter--;
	}
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CStringList_class)

BOOST_AUTO_TEST_CASE(has_zero_size_on_create)
{
	BOOST_CHECK_EQUAL(CStringList().GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(empty_on_create)
{
	BOOST_CHECK_EQUAL(CStringList().IsEmpty(), true);
}

BOOST_AUTO_TEST_CASE(can_input_into_the_front_of_list)
{
	CStringList myList;
	myList.AppendFront("Hello");
	BOOST_CHECK_EQUAL(myList.GetSize(), 1);
}

BOOST_AUTO_TEST_CASE(can_input_into_the_back_of_list)
{
	CStringList myList;
	myList.AppendBack("Hello");
	BOOST_CHECK_EQUAL(myList.GetSize(), 1);
}

BOOST_AUTO_TEST_CASE(append_to_it_changes_size)
{
	CStringList myList;
	myList.AppendFront("First");
	BOOST_CHECK_EQUAL(myList.GetSize(), 1);

	myList.AppendBack("Second");
	BOOST_CHECK_EQUAL(myList.GetSize(), 2);
}

BOOST_AUTO_TEST_CASE(can_insert_element_into_iterator_position)
{
	CStringList myList;
	myList.Insert(myList.begin(), "Ymiray");
	myList.Insert(myList.begin(), "nado");
	myList.Insert(myList.end(), "polychit");
	myList.Insert(++myList.begin(), "zachet");
	VerifyList(myList, { "nado", "zachet" , "Ymiray" , "polychit" });
}

BOOST_AUTO_TEST_CASE(can_clear_list)
{
	CStringList myList;
	myList.AppendBack("1");
	myList.AppendBack("2");
	myList.Clear();
	BOOST_CHECK_EQUAL(myList.GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(can_erase_element_at_iterator_position)
{
	CStringList myList;
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
	WorkingStringList expectedVector;
	CStringList myList;
	for (size_t i = 0; i < expectedVector.checkList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkList[i]);
	}
	VerifyList(myList, expectedVector.checkList);
}

BOOST_AUTO_TEST_CASE(has_iterators_at_the_begin_and_the_end_of_string_list)
{
	WorkingStringList expectedVector;
	CStringList myList;
	for (size_t i = 0; i < expectedVector.checkList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.begin(); it != myList.end(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(has_const_iterators_at_the_begin_and_the_end_of_string_list)
{
	WorkingStringList expectedVector;
	CStringList myList;
	for (size_t i = 0; i < expectedVector.checkList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkList[i]);
	}
	size_t counter = 0;
	for (auto it = myList.cbegin(); it != myList.cend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkList[counter]);
		counter++;
	}
}

BOOST_AUTO_TEST_CASE(has_reverse_iterators_and_const_revers_iterators_at_the_begin_and_the_end_of_string_list)
{
	WorkingStringList expectedVector;
	CStringList myList;
	for (size_t i = 0; i < expectedVector.checkList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkList[i]);
	}
	size_t counter = expectedVector.checkList.size() - 1;
	for (auto it = myList.crbegin(); it != myList.crend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkList[counter]);
		counter--;
	}
	counter = expectedVector.checkList.size() - 1;
	for (auto it = myList.rbegin(); it != myList.rend(); ++it)
	{
		BOOST_CHECK_EQUAL(*it, expectedVector.checkList[counter]);
		counter--;
	}

}

BOOST_AUTO_TEST_CASE(has_copy_constructor)
{
	WorkingStringList expectedVector;
	CStringList myList;
	for (size_t i = 0; i < expectedVector.checkList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkList[i]);
	}
	CStringList copiedList(myList);
	VerifyList(myList, expectedVector.checkList);
	VerifyList(copiedList, expectedVector.checkList);
}

BOOST_AUTO_TEST_CASE(has_move_constructor)
{
	WorkingStringList expectedVector;
	CStringList myList;
	for (size_t i = 0; i < expectedVector.checkList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkList[i]);
	}
	CStringList copiedList(std::move(myList));
	VerifyList(copiedList, expectedVector.checkList);
}

BOOST_AUTO_TEST_CASE(has_move_operator)
{
	WorkingStringList expectedVector;
	CStringList myList;
	for (size_t i = 0; i < expectedVector.checkList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkList[i]);
	}
	CStringList copiedList;
	copiedList = std::move(myList);
	VerifyList(copiedList, expectedVector.checkList);
}

BOOST_AUTO_TEST_CASE(has_alignment_operator)
{
	WorkingStringList expectedVector;
	CStringList myList;
	for (size_t i = 0; i < expectedVector.checkList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkList[i]);
	}
	CStringList copiedList;
	copiedList = myList;
	VerifyList(myList, expectedVector.checkList);
	VerifyList(copiedList, expectedVector.checkList);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CStringList_and_CIterators_classes_exceptions)

BOOST_AUTO_TEST_CASE(proprely_throws_exeptions)
{
	CStringList myList;
	BOOST_REQUIRE_THROW(myList.Erase(myList.begin()), std::out_of_range);
	BOOST_REQUIRE_THROW(*myList.end(), std::runtime_error);
	BOOST_REQUIRE_THROW(myList.rend()--, std::out_of_range);
	WorkingStringList expectedVector;
	for (size_t i = 0; i < expectedVector.checkList.size(); ++i)
	{
		myList.AppendBack(expectedVector.checkList[i]);
	}
	BOOST_REQUIRE_THROW(myList.Erase(myList.end()), std::out_of_range);
	BOOST_REQUIRE_THROW(myList.end()++, std::out_of_range);
	BOOST_REQUIRE_THROW(++myList.end(), std::out_of_range);
	BOOST_REQUIRE_THROW(--myList.begin(), std::out_of_range);
	BOOST_REQUIRE_THROW(myList.begin()--, std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()