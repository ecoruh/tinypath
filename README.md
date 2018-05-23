# tinypath
## xpath like wrapper for TinyXml library

This is a helper library that will eliminate loops that traverse the TinyXml trees. Loops create verbose code and make it harder to maintain the code base.

Conside this:

```
const char* GetMyAttribute(TiXmlElement* poElement)
{
   while ((poChild = (TiXmlElement*)poElement->IterateChildren( "mychild", (TiXmlNode*)poChild)) != NULL )
   {
      while ((poGrandChild = poChild->IterateChildren(poGrandChild)) != NULL)
      {
         if (!strcmp(poGrandChild->Name(), "mygrandchild"))
         {
            return poChild->Attribute( "myattribute" );
         }
        
```

This is what you have to do to achieve the same thing in tinypath:

```
const char* attr = attribute(poElement, "mychild/mygrandchild/myattribute");
```   
