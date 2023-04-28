#pragma once
#include <exception>
#include <QtCore/qstring.h>

class Exception : public std::exception {
public:
	Exception(const QString& _message);
	virtual ~Exception() {};

	const QString& message(void) const { return m_message; };

private:
	QString m_message;

	Exception() = delete;
};
