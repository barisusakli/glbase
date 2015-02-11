

#ifndef INC_EXCEPTION_H
#define INC_EXCEPTION_H

#include <string>

namespace glBase
{
	#define STRINGIFY(x) #x
	#define TOSTRING(x) STRINGIFY(x)
	#define CURRENT_LOCATION (__FUNCTION__ ":" TOSTRING(__LINE__) "[" __FILE__ "]" )
 
	class RuntimeException
	{
	public:
		RuntimeException(const std::string& error,const std::string& at):
			  m_Error(error),
			  m_At(at)
		  {

		  }
	
		  std::string m_Error;
		  std::string m_At;
	};

}
#endif //INC_EXCEPTION_H