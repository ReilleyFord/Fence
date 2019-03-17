#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

// function that grabs a single input
const string getInput(string question) {
  string input;
  cout << question << endl;
  getline(cin, input);
  return input;
}

/*
  Function that iterates through a passed directory and returns
  a vector filled with file paths. Using filesystem::path class.
 */
const vector<fs::path> getFiles(string &directory) {
  vector<fs::path> files;
  try {
    for(fs::path const &file : fs::directory_iterator(directory)) {
      string ext = file.extension().string();
      if(ext == ".mp4" || ext == ".mkv")
        files.push_back(file.filename());
    }
    sort(files.begin(), files.end());
    cout << "Files in directory " << directory << endl;
    for(fs::path const &file : files) {
      cout << file.filename() << endl;
    }
  } catch(exception &e) {
    cout << e.what() << endl;
  }
  return files;
}

/*
  Function that accepts an extension, a title, and a vector of paths.
  Iterates vector renames each file and extension.
 */
const void renameFiles(string &ext, string &show, vector<fs::path> files) {
  int i = 0;
  string name;
  for(fs::path &file : files) {
    i++;
    if(i >= 10)
      name = show + "E" + to_string(i);
    else
      name = show + "E0" + to_string(i);

    string oldFile = file.filename();
    file.replace_filename(name);
    file.replace_extension(ext);
    cout << "Renamed file " << oldFile << " => " << file.filename() << endl;
  }
}

int main() {
  string cont = "Y";
  do {
    string inputDir = getInput("Input Directory: ");
    if(!fs::exists(inputDir)) {
      cout << "Error: That directory does not exist" << endl;
      continue;
    }

    string extension = getInput("Filetype (mkv or mp4):");
    string show = getInput("Show and season (eg. Seinfeld S01)");

    vector<fs::path> files = getFiles(inputDir);
    renameFiles(extension, show, files);

    cont = getInput("Press 'y' to enter another \nEnter any other key to exit");
  } while(cont == "Y" || cont == "y");

}
