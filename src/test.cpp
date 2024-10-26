#include <Arduino.h>


String removeComments(String json) {
  String result = "";
  int inSingleLineComment = 0;
  int inMultiLineComment = 0;

  for (int i = 0; i < json.length(); ++i) {
    if (inMultiLineComment) {
      if (json[i] == '*' && i + 1 < json.length() && json[i + 1] == '/') {
        inMultiLineComment = 0;
        i++; // 跳过下一个字符 '/'
      }
    } else if (inSingleLineComment) {
      if (json[i] == '\n') {
        inSingleLineComment = 0;
      }
    } else {
      if (json[i] == '/' && i + 1 < json.length()) {
        if (json[i + 1] == '*') {
          inMultiLineComment = 1;
          i++; // 跳过下一个字符 '*'
        } else if (json[i + 1] == '/') {
          inSingleLineComment = 1;
          i++; // 跳过下一个字符 '/'
        } else {
          result += json[i];
        }
      } else {
        result += json[i];
      }
    }
  }

  return result;
}

void setup() {
  Serial.begin(9600);
  delay(4000);
  while (!Serial) { ; } // 等待串口初始化

  String jsonWithComments = "{ /* This is a JSON object */ \"key\": \"value\" // end of key-value pair\n"
                           "/* another comment */\n"
                           "\"anotherKey\": \"anotherValue\" // and another comment\n"
                           "}";

  Serial.println("Original JSON with comments:");
  Serial.println(jsonWithComments);

  String cleanJson = removeComments(jsonWithComments);

  Serial.println("\nCleaned JSON without comments:");
  Serial.println(cleanJson);
}

void loop() {
  // 主循环中不需要执行任何操作
}