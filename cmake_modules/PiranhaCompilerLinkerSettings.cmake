INCLUDE(CheckCXXCompilerFlag)

# Configuration for GCC.
IF(CMAKE_COMPILER_IS_GNUCXX)
	MESSAGE(STATUS "GNU compiler detected.")
	CHECK_CXX_COMPILER_FLAG(-Wnon-virtual-dtor GNUCXX_VIRTUAL_DTOR)
	IF(GNUCXX_VIRTUAL_DTOR)
		MESSAGE(STATUS "Enabling '-Wnon-virtual-dtor' compiler flag.")
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor")
	ENDIF(GNUCXX_VIRTUAL_DTOR)
	CHECK_CXX_COMPILER_FLAG(-std=c++0x GNUCXX_STD_CPP0X)
	IF(GNUCXX_STD_CPP0X)
		MESSAGE(STATUS "c++0x support detected.")
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	ELSE(GNUCXX_STD_CPP0X)
		MESSAGE(FATAL_ERROR "c++0x support could not be detected.")
	ENDIF(GNUCXX_STD_CPP0X)
	# Add to the base flags extra warnings. Also, additional flags to turn off some GCC warnings that in practice clutter the compilation output.
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wdisabled-optimization")
	# Suggested for multithreaded code.
	ADD_DEFINITIONS(-D_REENTRANT)
	# When compiling with GCC, enable the GNU extensions - used for instance in thread affinity settings.
	ADD_DEFINITIONS(-D_GNU_SOURCE)
ELSE(CMAKE_COMPILER_IS_GNUCXX)
	MESSAGE(FATAL_ERROR "This compiler is not supported at the present time.")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)
