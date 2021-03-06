#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "tinyxml2.h"
#include "TinyPath.h"

#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;
using namespace tinyxml2;

const char* xml =
"<pace foo=\"zoo\">"
"  <presenter name=\"minPresenter\" type=\"collectionpresenter\" version=\"1\">"
"    <input name=\"minBuffer\" />"
"    <custom>"
"      <recdef name=\"ALLFIELD\" />"
"    </custom>"
"  </presenter>"
"  <record name=\"minBuffer\" type=\"cseqrecbuf\" version=\"1\">"
"    <recdef name=\"ALLFIELD\" />"
"  </record>"
"  <gatherer name=\"minGat\" type=\"mingatherer\" version=\"1\">"
"    <output name=\"minBuffer\" />"
"  </gatherer>"
"</pace>";

SCENARIO("Testing tinypath", "[tinypath]") {
   GIVEN("a sample xml snippet") {
      XMLDocument doc;
      XMLError error = doc.Parse(xml);
      
      WHEN("a path is defined") {
         const char* p = "hello/world/foo";
         vector<string> parts = tinyutils::split(p);

         const char* p1 = "weird";
         vector<string> parts1 = tinyutils::split(p1);
         
         THEN("it would be partitioned into parts") {
            REQUIRE(parts.size() == 3);
            REQUIRE(parts[0] == "hello");
            REQUIRE(parts[1] == "world");
            REQUIRE(parts[2] == "foo");
            REQUIRE(parts1.size() == 1);
            REQUIRE(parts1[0] == "weird");
         }
      }

      WHEN("there is a prefix in path followed by '/'") {
         string s = "hello/world/foo";
         const string f = "hello";
         tinyutils::ltrim(s.erase(s.find(f), f.length()), '/');
         THEN("erase the prefix and '/'") {
            REQUIRE(s == "world/foo");
         }
      }

      WHEN("there is a valid attribute in the path") {
         string name, name1, name2;
         bool b = tinypath::attribute(doc.RootElement(), "presenter/name", name);
         bool b1 = tinypath::attribute(doc.RootElement(), "record/recdef/name", name1);
         bool b2 = tinypath::attribute(doc.RootElement(), "foo", name2);
         THEN("extract the value of that attribute") {
            REQUIRE(b == true);
            REQUIRE(!name.compare("minPresenter"));
            REQUIRE(b1 == true);
            REQUIRE(!name1.compare("ALLFIELD"));
            REQUIRE(b2 == true);
            REQUIRE(!name2.compare("zoo"));
         }
      }

      WHEN("there is no valid attribute in the path") {
         string name;
         bool b = tinypath::attribute(doc.RootElement(), "cooker/turner", name);
         bool b1 = tinypath::attribute(doc.RootElement(), "record/recdef/stupid", name);
         THEN("should fail as path did not match") {
            REQUIRE_FALSE(b);
            REQUIRE_FALSE(b);
         }
      }
   }
}
