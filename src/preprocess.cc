#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

const string INCLUDETAX("#include \"");

void readFile(string fileName, string & content)
{
   ifstream in(fileName.c_str());
   string line;
   for( string line; getline(in, line);  )
   {
      content.append(line).append("\n");
      if(line.find(INCLUDETAX)!=string::npos){
	 size_t start = line.find_first_of("\"") + 1;
	 size_t end = (line.find_last_of("\"") - 1);
	 size_t length = (end - start) + 1;

         string newFile(line.substr(start, length));
	 readFile(newFile, content);
      }
   }
   content.append("//End of ").append(fileName).append("\n");
}

int main(int ac, char* av[])
{
   ofstream out("temp.txt");
   string content = "";
   readFile(av[1], content);
   out << content << endl;
   return 0;
}
