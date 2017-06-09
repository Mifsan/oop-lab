#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"
#include "UrlParsingErrorTitles.h"

using namespace std;

CHttpUrl::CHttpUrl(std::string const & url)
{
	string urlCopy = url;
	boost::regex ex("(?i)(http|https)://([^/ \:]+)(:?[^/ :a-z]*)(/?[^ :]*)");
	boost::cmatch what;
	if (regex_match(urlCopy.c_str(), what, ex))
	{
		m_protocol = StringToProtocol(boost::to_lower_copy(string(what[1].first, what[1].second)));
		m_domain = string(what[2].first, what[2].second);
		if (string(what[3].first, what[3].second).length() > 0)
		{
			ParsePort(urlCopy);
			m_port = stoi(string(what[3].first, what[3].second).erase(0, 1));
		}
		m_document = string(what[4].first, what[4].second);
		if (string(what[4].first, what[4].second).length() == 0)
		{
			m_document = "/";
		}
	}
	else
	{
		ParseProtocol(urlCopy);
		ParseDomain(urlCopy);
		ParsePort(urlCopy);
		ParseDocument(urlCopy);
	}
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol)
{
	CHttpUrl copy = CHttpUrl(domain, document, protocol, static_cast<unsigned short>(protocol));
	m_domain = copy.GetDomain();
	m_document = copy.GetDocument();
	m_protocol = copy.GetProtocol();
	m_port = copy.GetPort();
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port)
{
	ParseProtocol(ProtocolToString(protocol) + "://");
	m_protocol = protocol;
	ParseDomain("http://" + domain);
	m_domain = domain;
	ParsePort("http://" + domain + ":" + std::to_string(port));
	if (port > 0)
	{
		m_port = port;
	}
	if (document[0] != '/')
	{
		ParseDocument("http://" + domain + "/" + document);
		m_document = '/' + document;
	}
	else
	{
		ParseDocument("http://" + domain + document);
		m_document = document;
	}
}

Protocol CHttpUrl::StringToProtocol(std::string protocolStr)
{
	if (protocolStr == "http")
	{
		m_port = 80;
		return Protocol::HTTP;
	}
	m_port = 443;
	return Protocol::HTTPS;
}

std::string CHttpUrl::ProtocolToString(Protocol protocol) const
{
	if (protocol == Protocol::HTTP)
	{
		return "http";
	}
	return "https";
}

std::string CHttpUrl::GetURL() const
{
	if ((m_protocol == Protocol::HTTP) && (m_port == 80)
		|| (m_protocol == Protocol::HTTPS) && (m_port == 443))
	{
		return ProtocolToString(m_protocol) + "://" + m_domain + m_document;
	}
	else
		return ProtocolToString(m_protocol) + "://" + m_domain + ":" + std::to_string(m_port) + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::ParseProtocol(std::string const& url) const
{
	boost::cmatch what;
	boost::regex protocolEx("(?i)(http|https)://");
	if (!regex_search(url.c_str(), what, protocolEx))
	{
		throw CUrlParsingError(INVALID_PROTOCOL);
	}
}

void CHttpUrl::ParseDomain(std::string const& url) const
{
	boost::cmatch what;
	boost::regex domainEx("(?i)https?://([^/ \:]+)");
	if (!regex_search(url.c_str(), what, domainEx))
	{
		throw CUrlParsingError(INVALID_DOMAIN);
	}
}

void CHttpUrl::ParsePort(std::string const& url) const
{
	boost::cmatch what;
	boost::regex portEx("(?i)https?://[^:/ \]+(:?([^/ :a-z])*)");
	if (!regex_search(url.c_str(), what, portEx))
	{
		throw CUrlParsingError(INVALID_PORT);
	}
	else if (string(what[1].first, what[1].second).length() > 0)
	{
		try
		{
			if (stoi(string(what[1].first, what[1].second).erase(0, 1)) < 1
				|| stoi(string(what[1].first, what[1].second).erase(0, 1)) > 65535)
			{
				throw CUrlParsingError(INVALID_PORT);
			}
		}
		catch (...)
		{
			throw CUrlParsingError(INVALID_PORT);
		}
	}
}

void CHttpUrl::ParseDocument(std::string const& url) const
{
	boost::cmatch what;
	boost::regex documentEx("(?i)http|https://[^/ \:]+:?[^/ :a-z]*(/?[^:]*)");
	if (!regex_search(url.c_str(), what, documentEx))
	{
		if (string(what[1].first, what[1].second).find(" "))
		{
			throw CUrlParsingError(INVALID_DOCUMENT);
		}
	}
}