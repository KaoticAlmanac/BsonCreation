// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <ios>
#include <mongo-cxx-driver-releases-stable\\src\\bsoncxx>
#include <mongo-cxx-driver-releases-stable\\src\\bsoncxx\\json.hpp>
//#include <mongocxx/client.hpp>
//#include <mongocxx/stdx.hpp>
//#include <mongocxx/uri.hpp>
#include <iomanip>
using std::setw;

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;


// TODO: reference additional headers your program requires here
