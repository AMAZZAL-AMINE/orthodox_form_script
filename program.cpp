#include <iostream>
#include <unistd.h>
#include <fstream>
using namespace std;

string toUpper(string  str) {
  int i = 0;
  while (i < str.length()) {
    str[i] = toupper(str[i]);
    i++;
  }
  return str;
}


string firstIsUpper(string name) {
  int i = 1;
  name[0] = toupper(name[0]);
  while (i < name.length()) {
     name[i] = tolower(name[i]);
     i++;
  }
  return name;
}

void setorhodoxForm(string hppFile, string cppFile, string Filename) {
  string upperFileName = toUpper(Filename);
  string preifNotDefine = "#ifndef " + upperFileName + "_HPP";
  string prePressesureDefine = "#define " + upperFileName + "_HPP";
  string endPre = "#endif";
  int length = 0;
  ofstream file;
  file.open(hppFile);

  file << preifNotDefine << std::endl;
  file << prePressesureDefine << std::endl;
  file << "\n";
  string classForm[] = {"class " + Filename + " {",
    "    private :",
    "    public :",
    "      " + Filename + "();",
    "      "+Filename+"("+Filename+" const &src);",
    "      "+Filename+" &operator=("+Filename+" const &src);",
    "      ~"+ Filename +"();",
    "  };"
  };
  for (int i = 0; i < 8; i++) {
    file << classForm[i] << std::endl;
  }
  file << "\n";
  file << endPre;
  file.close();

  file.open(cppFile);
  file << "#include \"" + Filename + ".hpp\"";
  file << "\n\n"; 
  file << Filename +"::"+Filename+"() {}\n";
  file << Filename +"::"+Filename+"("+Filename+" const &src){}\n";
  file << Filename + " & " + Filename +"::operator=("+Filename+" const &src){}\n";
  file << Filename +"::~"+Filename+"() {}\n";
  file.close();
}

int main(int argc, char **argv) {
  if (argc != 2 ) {
    cerr << "orthodox : bad argments.\n";
    exit(1);
  }
  string fileName = firstIsUpper(argv[1]);
  string workinDir  = getcwd(NULL, 0);
  string scriptPath = workinDir + "/" + fileName;
  string hppFile = scriptPath + ".hpp";
  string cppFile = scriptPath + ".cpp";
  string cmdResutl = "touch " + hppFile + " " + cppFile;
  system(cmdResutl.c_str());
  setorhodoxForm(hppFile, cppFile, fileName);
}
