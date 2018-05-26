#pragma once

#include <string>
#include <vector>
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace tinyutils
{
   /// <summary>
   /// Splits a slash delimited string path ("elt1/elt2/attr1") into a vector of its parts
   /// </summary>
   vector<string> split(const string& subject, const char* sep = "/");

   /// /// <summary>
   /// Trims the string from start until c is not found
   /// </summary>
   void ltrim(string& s, int ch);
}

namespace tinypath
{   
   /// /// <summary>
   /// Starting from an xml root finds the attribute at the end of a path, extracts and returns its value
   /// </summary>
   bool attribute(XMLElement* root, const string& path, string& value);
};

