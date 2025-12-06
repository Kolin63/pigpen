#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <fstream>

const std::string CONFIG_FILEPATH{"$XDG_CONFIG_HOME/pigpen/config.txt"};
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

  // if there is no config, we take a shortcut and just open it
  if (!std::filesystem::exists(CONFIG_FILEPATH)) {
    return std::system(std::string{"xdg-open " + arg}.c_str());
  }

  // otherwise, there is a user defined configuration
  // so, we need to parse that and go from there

  // loads config
  std::ifstream fs{};
  fs.open(CONFIG_FILEPATH);
}
