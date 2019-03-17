#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

const string getInput(string &question) {
  string output;
  cout << question << endl;
  getline(cin, output);

  return output;
}

const vector<fs::path> getFiles(string &directory) {
  vector<fs::path> files;
  try {
    for(fs::path const &file : fs::directory_iterator(directory)) {
      string ext = file.extension();
      if(ext == ".mp4" || ext == ".mkv"){
        files.push_back(file.filename());
      }
    }
    sort(files.begin(), files.end());
  } catch(exception &e) {
    cout << e.what() << endl;
  }
  return files;
}

const void renameFiles(string &ext, string &show, vector<fs::path> files) {
  int i = 0;
  for(fs::path &file : files) {
    i++;
    string name;
    if(i >= 10) {
      name = show + "E" + to_string(i);
    } else {
      name = show + "E0" + to_string(i);
    }
    file.replace_filename(name);
    file.replace_extension(ext);
    cout << file.filename() << endl;
  }
}

int main() {

  string question = "Input Directory: ";
  string inputDir = getInput(question);

  question = "Filetype (mkv or mp4):";
  string extension = getInput(question);

  question = "Show and season (eg. Seinfeld S01)";
  string show = getInput(question);

  vector<fs::path> files = getFiles(inputDir);

  renameFiles(extension, show, files);

  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
}
