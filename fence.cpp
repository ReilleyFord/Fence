#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

const string getInput(string &question) {
  string output;
  cout << question << endl;
  getline(cin, output);

  return output;
}

int main() {

  string inputDir;

  string question = "Input Directory: ";
  inputDir = getInput(question);

  question = "Filetype (mkv or mp4):"
  string extension = getInput(question);

  question = "Show and season (eg. Seinfeld S01)";
  string show = getInput(question);

  try {
    for(auto const &file : fs::directory_iterator(inputDir)) {
      string ext = file.path().extension();
      if(ext == ".mp4" || ext == ".mkv"){
        cout << file.path().filename() << endl;
      }
    }
  } catch(exception &e) {
    cout << e.what() << endl;
  }


  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
}
