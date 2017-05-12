#include "stdafx.h"
#include "..\secondTask\HTMLDecoder.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(HtmlDecode_function)

BOOST_AUTO_TEST_CASE(return_empty_string_if_input_are_empty_string)
{
	BOOST_CHECK_EQUAL(HtmlDecode(""), "");
}

BOOST_AUTO_TEST_CASE(rename_me)
{
	BOOST_CHECK_EQUAL(HtmlDecode("aaa &amp;amp; bbb"), "aaa &amp; bbb");
}

BOOST_AUTO_TEST_CASE(source_string_without_html)
{
	string strWithoutHtmlEntities = "We don`t: \"have\" HTML entities";
	BOOST_CHECK_EQUAL(HtmlDecode(strWithoutHtmlEntities), strWithoutHtmlEntities);
}

BOOST_AUTO_TEST_CASE(entities_not_full)
{
	string strWithoutHtmlEntities = "We &lthave&gt &quotdistroyed&quot. H&ampT&apML";
	BOOST_CHECK_EQUAL(HtmlDecode(strWithoutHtmlEntities), strWithoutHtmlEntities);
}

BOOST_AUTO_TEST_CASE(replace_entities)
{
	string strWithHtmlEntities = "I don&apos;t see &lt;anything&gt; there.";
	string requiredStr = "I don't see <anything> there.";
	BOOST_CHECK_EQUAL(HtmlDecode(strWithHtmlEntities), requiredStr);

	strWithHtmlEntities = "There &lt;being&gt; nothing else to do, &quot;we&quot; went&apos;&apos;&apos; to bed.";
	requiredStr = "There <being> nothing else to do, \"we\" went''' to bed.";
	BOOST_CHECK_EQUAL(HtmlDecode(strWithHtmlEntities), requiredStr);
}

BOOST_AUTO_TEST_SUITE_END()