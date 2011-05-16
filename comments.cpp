#include "comments.h"

void strip_comments(string* line, bool* in_comment) {
   unsigned int comment_position;
   string temp = "";
   // If is in a multiline comment already
   if (*in_comment) {
      comment_position = line->find("*/");
      if (comment_position < line->size()) {
         temp += line->substr(comment_position + 2);
         *in_comment = false;
      }
      *line = temp;
      return;
   }

   // If this has the start of a single line comment
   strip_multiline(line, in_comment);
   
   // If this has a single line comment
   strip_single_line(line);

}

void strip_single_line(string* line) {
   unsigned int comment_position;
   string temp = "";
   
   comment_position = line->find("//");
   if (comment_position < line->size()) {
      *line = line->substr(0, comment_position);
   }
}

bool strip_multiline(string* line, bool* in_comment) {
   unsigned int comment_position;
   string temp = "";
   comment_position = line->find("/*");
   if (comment_position < line->size()) {
      temp = line->substr(0, comment_position);      
      comment_position = line->find("*/") ;
      if (comment_position < line->size()) {
         temp += line->substr(comment_position + 2);
      } else {
         *line = temp;
         *in_comment = true;
         return false;
      }
      *line = temp;
      return strip_multiline(line, in_comment);
   } else {
      return false;
   }
}
