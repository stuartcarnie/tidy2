#include <v8.h>
#include "tidy/tidy.h"
#include "tidy/buffio.h"

#include <memory>

using namespace v8;

class MStr : public String::ExternalAsciiStringResource {
public:
  MStr(char * str, size_t len) 
    :_str(str), _len(len)
  {
    
  }
  
  ~MStr() {
    free(_str);
  }
  
  virtual const char* data() const {
    return (char*)_str;
  }
  
  virtual size_t length() const {
    return _len;
  }
  
private:
  char * _str;
  size_t _len;
};

using std::shared_ptr;

const int ENOMEM = -12;

char* newString(unsigned int length) {
  return (char *)calloc(length, sizeof(char));
}

Handle<Value> tidyString(const Arguments& args) {
  int rc;
  int len = args.Length();
  if(len < 1) return Undefined();
  String::Utf8Value content(args[0]); 
  char *html = *content;
  unsigned int resultLength = 32;
  auto result = newString(resultLength);
  TidyDoc doc = tidyCreate();
  tidySetCharEncoding(doc, "raw");
  TidyBuffer errorBuffer;
  tidyBufInit(&errorBuffer);

  tidyOptSetBool(doc, TidyQuiet, yes);
  tidyOptSetBool(doc, TidyHideComments, yes);
  tidyOptSetBool(doc, TidyForceOutput, yes);
  tidyOptSetBool(doc, TidyMark, no);
#ifndef __APPLE__
  tidyOptSetBool(doc, TidyPreserveEntities, yes);
#endif
  //tidyOptSetBool(doc, TidyBodyOnly, yes);

  tidySetErrorBuffer(doc, &errorBuffer);

  tidyParseString(doc, html);
  tidyCleanAndRepair(doc);
  if((rc = tidySaveString(doc, result, &resultLength)) == ENOMEM) {
    free(result);
    result = newString(resultLength+1);
    rc = tidySaveString(doc, result, &resultLength);
  }
  /*
  if(rc >= 0) {
    fprintf(stdout, "Diagnostics:\n%s", errorBuffer.bp);
    fprintf(stdout, "Results:'%d'\n", strlen(result));
  } else {
    fprintf(stderr, "An error has occurred tidying input");
  }
  */
  tidyRelease(doc);
  tidyBufFree(&errorBuffer);
  auto str = new MStr(result, resultLength);
  return String::NewExternal(str);
}

extern "C" void init(Handle<Object> target) {
  HandleScope scope;
  target->Set(String::New("tidyString"), FunctionTemplate::New(tidyString)->GetFunction());
}
