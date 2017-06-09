#include "stdafx.h"
#include "..\HttpUrl\HttpUrl.h"
#include "..\HttpUrl\UrlParsingErrorTitles.h"
#include "..\HttpUrl\UrlParsingError.h"

std::string InformationAbout(CHttpUrl curl)
{
	std::string information = "URL: " + curl.GetURL() + "\n";
	if (curl.GetProtocol() == Protocol::HTTP)
	{
		information += "\tProtocol: http\n";
	}
	else
	{
		information += "\tProtocol: https\n";
	}
	information += "\tDomain: " + curl.GetDomain() + "\n";
	information += "\tPort: " + std::to_string(curl.GetPort()) + "\n";
	information += "\tDocument: " + curl.GetDocument() + "\n";
	return information;
}

BOOST_AUTO_TEST_SUITE(Url_can_return_)

BOOST_AUTO_TEST_CASE(data_from_normal_url)
{
	CHttpUrl normalURL("http://domain.ru:80/document");
	BOOST_CHECK_EQUAL(normalURL.GetProtocol(), Protocol::HTTP);
	BOOST_CHECK_EQUAL(normalURL.GetDomain(), "domain.ru");
	BOOST_CHECK_EQUAL(normalURL.GetPort(), 80);
	BOOST_CHECK_EQUAL(normalURL.GetDocument(), "/document");
	CHttpUrl httpsURL("https://domain.ru:80/document");
	BOOST_CHECK_EQUAL(httpsURL.GetProtocol(), Protocol::HTTPS);
}

BOOST_AUTO_TEST_CASE(port_80_for_http_protocol)
{
	CHttpUrl url("http://domain.ru/document");
	BOOST_CHECK_EQUAL(url.GetPort(), 80);
}

BOOST_AUTO_TEST_CASE(port_443_for_https_protocol)
{
	CHttpUrl url("https://domain.ru/document");
	BOOST_CHECK_EQUAL(url.GetPort(), 443);
}

BOOST_AUTO_TEST_CASE(full_information_about_url)
{
	std::string refStr1 = "URL: http://vk.com:77/doc\n\tProtocol: http\n\tDomain: vk.com\n\tPort: 77\n\tDocument: /doc\n";
	std::string httpUrl = "http://vk.com:77/doc";
	BOOST_CHECK_EQUAL(InformationAbout(CHttpUrl(httpUrl)), refStr1);

	std::string refStr2 = "URL: https://vk.com:22/doc\n\tProtocol: https\n\tDomain: vk.com\n\tPort: 22\n\tDocument: /doc\n";
	std::string httpsUrl = "https://vk.com:22/doc";
	BOOST_CHECK_EQUAL(InformationAbout(CHttpUrl(httpsUrl)), refStr2);
}

BOOST_AUTO_TEST_CASE(url_string)
{
	std::string refStr = "https://site.com:100/documentation";
	std::string url = "https://site.com:100/documentation";
	BOOST_CHECK_EQUAL(CHttpUrl(url).GetURL(), refStr);
}

BOOST_AUTO_TEST_CASE(string_without_port_if_construct_with_three_args_and_protocol_equal_HTTPS)
{
	CHttpUrl url("yandex.ru", "doc.txt", Protocol::HTTPS);
	BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTPS);
	BOOST_CHECK_EQUAL(url.GetURL(), "https://yandex.ru/doc.txt");
}

BOOST_AUTO_TEST_CASE(string_without_port_if_construct_with_three_args_and_protocol_equal_HTTP)
{
	CHttpUrl url("yandex.ru", "doc.txt", Protocol::HTTPS);
	BOOST_CHECK_EQUAL(url.GetProtocol(), 443);
	BOOST_CHECK_EQUAL(url.GetURL(), "https://yandex.ru/doc.txt");
}

BOOST_AUTO_TEST_CASE(string_without_port_if_construct_with_string_with_https_and_withput_port)
{
	CHttpUrl url("https://vk.com/doc");
	BOOST_CHECK_EQUAL(url.GetProtocol(), 443);
	BOOST_CHECK_EQUAL(url.GetURL(), "https://vk.com/doc");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Url_can_be_construct_with_)

BOOST_AUTO_TEST_CASE(domain_and_document)
{
	CHttpUrl url2("vk.com", "document");
	BOOST_CHECK_EQUAL(url2.GetProtocol(), Protocol::HTTP);
	BOOST_CHECK_EQUAL(url2.GetDomain(), "vk.com");
	BOOST_CHECK_EQUAL(url2.GetPort(), 80);
	BOOST_CHECK_EQUAL(url2.GetDocument(), "/document");
}
BOOST_AUTO_TEST_CASE(domain_and_document_and_protocol)
{
	CHttpUrl url1("vk.com", "document", Protocol::HTTP);
	BOOST_CHECK_EQUAL(url1.GetProtocol(), Protocol::HTTP);
	BOOST_CHECK_EQUAL(url1.GetDomain(), "vk.com");
	BOOST_CHECK_EQUAL(url1.GetPort(), 80);
	BOOST_CHECK_EQUAL(url1.GetDocument(), "/document");

	CHttpUrl url2("vk.com", "document", Protocol::HTTPS);
	BOOST_CHECK_EQUAL(url2.GetProtocol(), Protocol::HTTPS);
	BOOST_CHECK_EQUAL(url2.GetDomain(), "vk.com");
	BOOST_CHECK_EQUAL(url2.GetPort(), 443);
	BOOST_CHECK_EQUAL(url2.GetDocument(), "/document");
}
BOOST_AUTO_TEST_CASE(domain_and_document_and_protocol_and_port)
{
	CHttpUrl url1("vk.com", "document", Protocol::HTTP, 500);
	BOOST_CHECK_EQUAL(url1.GetProtocol(), Protocol::HTTP);
	BOOST_CHECK_EQUAL(url1.GetDomain(), "vk.com");
	BOOST_CHECK_EQUAL(url1.GetPort(), 500);
	BOOST_CHECK_EQUAL(url1.GetDocument(), "/document");

	CHttpUrl url2("vk.com", "document", Protocol::HTTPS, 100);
	BOOST_CHECK_EQUAL(url2.GetProtocol(), Protocol::HTTPS);
	BOOST_CHECK_EQUAL(url2.GetDomain(), "vk.com");
	BOOST_CHECK_EQUAL(url2.GetPort(), 100);
	BOOST_CHECK_EQUAL(url2.GetDocument(), "/document");
}
BOOST_AUTO_TEST_CASE(mixed_protocol_register)
{
	CHttpUrl url5("hTTp://domain.ru:80/document");
	BOOST_CHECK_EQUAL(url5.GetProtocol(), Protocol::HTTP);

	CHttpUrl url6("HtTpS://domain.ru:80/document");
	BOOST_CHECK_EQUAL(url6.GetProtocol(), Protocol::HTTPS);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Exceptions_are_thrown_when_)

BOOST_AUTO_TEST_CASE(protocol_is_absent)
{
	BOOST_REQUIRE_THROW(CHttpUrl("://domain/document"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(protocol_unresolved)
{
	BOOST_REQUIRE_THROW(CHttpUrl("ftp://domain/document"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(construct_url_with_four_args_and_domain_are_empty)
{
	BOOST_REQUIRE_THROW(CHttpUrl("", "", Protocol::HTTP, 300), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(url_without_separator)
{
	BOOST_REQUIRE_THROW(CHttpUrl("http/domain/document"), std::invalid_argument);
	BOOST_REQUIRE_THROW(CHttpUrl("https:domain/document"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_domain_or_they_absent)
{
	BOOST_REQUIRE_THROW(CHttpUrl("http:///document"), std::invalid_argument);
	BOOST_REQUIRE_THROW(CHttpUrl("http:///document"), std::invalid_argument);
	BOOST_REQUIRE_THROW(CHttpUrl("https://:10/document"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(port_is_absent)
{
	BOOST_REQUIRE_THROW(CHttpUrl("http://site.com:/document"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(port_equal_zero)
{
	BOOST_REQUIRE_THROW(CHttpUrl("http://site.com:65536/document"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(port_greather_than_65535)
{
	BOOST_REQUIRE_THROW(CHttpUrl("http://site.com:0/document"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(domain_empty_when_cunstruct_with_two_arg)
{
	BOOST_REQUIRE_THROW(CHttpUrl("", "doc"), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()