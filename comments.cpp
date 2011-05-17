#include "comments.h"
#include "fileio.h"

void strip_file_comments() {
   string line;
   bool in_comment = false;
   ifstream working_file;
   ofstream temp_file;
   working_file.open(WORKING_FILENAME);
   temp_file.open(TEMP_FILENAME);
   
   if (working_file.is_open()) {
      while (working_file.good()) {
         getline(working_file, line);
         strip_comments(&line, &in_comment);
         if (!line.empty()) {
            temp_file << line << endl;
         }

      }
      if (in_comment) {
         cout << ERROR_UNCLOSED_COMMENT;
      }
      working_file.close();
      temp_file.close();
      copy_file(TEMP_FILENAME, WORKING_FILENAME);
   } else {
      cout << ERROR_TEMP_FILE_NOT_OPEN;
   }
}

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
