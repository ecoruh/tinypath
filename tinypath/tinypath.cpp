#include "stdafx.h"
#include <regex>
#include <algorithm>
#include <iterator>
#include "TinyPath.h"

namespace tinyutils 
{
   /// <summary>
   /// Splits a slash delimited path into a vector of parts
   /// </summary>
   /// <param name="subject">A slash delimited path to be splitted</param>
   /// <returns>vector of splitted parts</returns>
   vector<string> split(const string& subject, const char* sep) {
      static const regex re{ sep };
      vector<string> container{
         sregex_token_iterator(subject.begin(), subject.end(), re, -1),
         sregex_token_iterator()
      };
      return container;
   }

   /// <summary>
   /// Trims the string from start until c is not found
   /// </summary>
   /// <param name="s">string to trim its beginning</param>
   /// <param name="c">character to trim from the beginning</param>
   void ltrim(string& s, int c) {
      s.erase(s.begin(), find_if(s.begin(), s.end(), [c](int ch) {
         return ch != c;
      }));
   }
}

namespace tinypath
{
   /// <summary>
   /// Starting from an xml root finds the attribute at the end of a path, 
   /// then extracts and returns its value.
   /// </summary>
   /// <param name="root">Root element</param>
   /// <param name="path">Slash delimited path of [element1[/element2[/../]]/]attribute</param>
   /// <param name="value">The value of the attribute if found</param>
   /// <returns>true if attribute is resolved</returns>
   bool attribute(XMLElement* root, const string& path, string& value)
   {
      auto parts = tinyutils::split(path);
      if (parts.size() == 1) {
         const char* ptr = root->Attribute(parts[0].c_str());
         if (ptr != nullptr) value = ptr;
         return ptr != nullptr;
      }
      auto part = parts[0];
      for (auto sib = root->FirstChildElement(); sib != nullptr; sib = sib->NextSiblingElement()) {
         auto part_len = part.length();
         if (!part.compare(sib->Value())) {
            string _path(path);
            tinyutils::ltrim(_path.erase(_path.find(part), part_len), '/');
            return attribute(sib, _path, value);
         }
      }
      return false;
   }
}

