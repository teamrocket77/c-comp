#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
enum TokenType{
  LEFT_PAREN, 
  RIGHT_PAREN,
  LEFT_BRACE, 
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS_EQUAL,
  LESS,

  IDENTIFIER,
  STRING,
  NUMBER,

  AND,
  CLASS, 
  ELSE,
  FALSE,
  TRUE,
  FOR,
  FUN,
  NIL,
  OR,
  IF,
  PRINT,
  RETURN,
  SUPER,
  VAR,
  WHILE,
  THIS,
};

template <class T>
struct Token final{
  TokenType type;
  string lexeme;
  T literal;
  int line;

  Token(TokenType type, string lexeme, T literal, int line)
      : type(type), lexeme(lexeme), literal(literal), line(line) {}
};

template <class T>
ostream& operator<<(ostream &s, const Token<T> &t){
  return s << "Token: " << to_string(t.type) << " lexeme: " << t.lexeme << ", Type: " << to_string(t.literal) << " line: " <<  to_string(t.line) << endl;
}

class Scanner{
  public:
  //vector<Token> scan_tokens(){
  void scan_tokens(){

    }
  static void conv_string(string s, char* ptr){
    int len = s.length();
    cout << "inside of string function" <<endl;
    for (int i = 0; i < len; i++){
      ptr[i] = s[i];
      };
    }
};

// void run_file(char *f_path){
//   ifstream ifs(f_path, ifstream::in);
//   char c = ifs.get();
//   while (ifs.good()){
//     cout << c;
//     c = ifs.get();
//   }
//   ifs.close();
//   cout << "Done reading file" << endl;
// }

class Lox{
  public:
    static bool had_error;
    Lox(char* file_name){
      this->f_name = file_name;
    }

    static void error(int line, string msg){
      Lox::report(line, "", msg);
    }

    int run_file(){
      ifstream ifs(this->f_name, ifstream::in);
      char c = ifs.get();
      while (ifs.good()){
        cout << c;
        c = ifs.get();
      }
      ifs.close();
      cout << "Done reading file" << endl;
      // reconstructing the return value
      //Lox::had_error = true;
      if (Lox::had_error){
        return(65);
      }
        return(0);
    }

    static void run_prompt(){
      string prompt = "> ";
      string command;
      ssize_t c_len = 0;
      int i = 0;
      cout << "This is a basic echo program" << endl;
      cout << prompt;
      while (getline(cin, command)){
        //scanf("%s", command);
        cout << command << endl;
        if (!cin){
          cerr << "Exiting Now";
          break; 
        }
        cout << prompt;
    
      }
    }

  private:
    int argc;
    char* argv;
    char* f_name;
    static void report(int line, string where, string msg){
      cerr << "[Line " << line << " Error" << where << ": " << msg << endl;
    }
};
bool Lox::had_error = false;

int main(int argc, char *argv[]){
  char *f_name;
  bool f = false;
  bool p = false;
  int c;
  string usage = "Usage: jlox [script]";
  while ((c = getopt(argc, argv, "p::f::")) != -1 ){
    switch (c){
      case 'p':
        p = true;
        break;
      case 'f':
        f_name = optarg;
        f = true;
        break;
      default:
        break;
    }
  }
  int return_val = 0;
  if (f and !p){
        //to pass use -ffile_name.txt
        cout << "f: " << f_name << endl;
        Lox lox(f_name);
        return_val = lox.run_file();
  }
  else if (p and !f ){
        //cout << "f: " << f_name << endl;
    cout << "Typing to write some info: ";
    Token<int> token( TokenType::LEFT_PAREN, "(", 42, 1);
    cout << token << endl;
    Lox::run_prompt();
    // creation of the token
  }
  else {
        cout << usage << endl;
        // failure
        return 1;
  }
  if (return_val == 0)
    return 0;
  else 
    return return_val;
}

