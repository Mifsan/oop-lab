#pragma once

enum Protocol
{
	HTTP = 80,
	HTTPS = 443
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);
	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;
private:
	void ParseProtocol(std::string const& url) const;
	void ParseDomain(std::string const& url) const;
	void ParsePort(std::string const& url) const;
	void ParseDocument(std::string const& url) const;
	Protocol StringToProtocol(std::string protocol);
	std::string ProtocolToString(Protocol protocol) const;

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};