#include "Exception.h"

Exception::Exception(const QString& _message) : std::exception(_message.toStdString().c_str()), m_message(_message) {
	
}