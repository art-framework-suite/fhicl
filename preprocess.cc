#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

const string INCLUDETAX("#include \"");
//const string END_TAG("\n\\ END OF ");

string content;

void readFile(string fileName, string & content)
{
   ifstream in(fileName.c_str());
   string line;
   while (getline(in, line))
   {
      content.append("\n");
      content.append(line);
      if(line.find(INCLUDETAX)!=string::npos){
	 size_t start = line.find_first_of("\"") + 1;
	 size_t end = (line.find_last_of("\"") - 1);
	 size_t length = (end - start) + 1;

         string newFile(line.substr(start, length));
	 readFile(newFile, content);
      }
   }
   content.append("\n//End of ");
   content.append(fileName);
}

int main(int ac, char* av[])
{
   ofstream out("temp.txt");
   string line;
   readFile(av[1], content);
   out << content << endl;
   return 0;
}
