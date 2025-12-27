#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

/*
config looks like this:
```
pdf = zathura %f
png jpg txt = qutebrowser %f
```
*/

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Expected exactly one argument\n";
    return 1;
  }

  const std::string arg{argv[1]};

  const std::string CONFIG_HOME{std::getenv("XDG_CONFIG_HOME")};
  const std::string CONFIG_FILEPATH{CONFIG_HOME + "/pigpen/config.txt"};

  // if there is no config, we take a shortcut and just open it
  if (!std::filesystem::exists(CONFIG_FILEPATH)) {
    return std::system(std::string{"xdg-open " + arg}.c_str());
  }

  // otherwise, there is a user defined configuration
  // so, we need to parse that and go from there

  // loads config
  std::ifstream fs{};
  fs.open(CONFIG_FILEPATH);

  // what side of the equals sign we are reading
  enum Side {
    left,
    right,
  } side{left};

  // if the current line has the type that we are trying to open
  bool found_type{false};

  std::string suffix{};
  std::string command{};

  // iterate over the characters
  char c{};
  while (true) {
    c = fs.get();
    if (fs.eof()) break;

    // in between file types on the left side of the equals
    if (std::isspace(c) || c == '=') {
      if (arg.ends_with(suffix)) {
        found_type = true;
      }
    }

    // done declaring file types for the line
    if (c == '=') {
      side = right;
      continue;
    }

    // end of line
    if (c == '\n') {
      suffix = "";
      side = left;
      if (found_type) break;
      continue;
    }

    // read file type
    if (!found_type && side == left) {
      suffix += c;
      continue;
    }

    // read command
    if (found_type && side == right) {
      command += c;
      continue;
    }
  }

  // done reading
  fs.close();

  // command not defined, failsafe to default open
  if (command == "") command = "xdg-open %f";

  // replace %f tag with filename
  char prev_char{};
  for (std::size_t i{}; i < command.length(); ++i) {
    char c{command[i]};
    if (prev_char == '%' && c == 'f') {
      command.replace(i - 1, 2, arg);
    }
    prev_char = c;
  }

  return std::system(command.c_str());
}
