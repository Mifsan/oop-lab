// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define BOOST_TEST_INCLUDED
#pragma warning (disable:4702) // To disable 4702 warning in boost
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <string>
#include <iostream>
#include <boost/algorithm/string/case_conv.hpp>
#include <exception>

// TODO: reference additional headers your program requires here
