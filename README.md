# 🐷 Pigpen
![demo](demo.gif)

Pigpen is a smarter way to open your files. It wraps around Linux's default
`open` command, providing an easier way to configure what applications open
what file types.

## 🔧 Configuration
Pigpen reads from `$XDG_CONFIG_HOME/pigpen/config.txt`. `$XDG_CONFIG_HOME` is
usually set to `~/.config`.

A config file looks like this:
```
pdf = zathura %f
png jpg jpeg = qutebrowser %f
```

Each line is dedicated to a different program or command. On the left hand of
the equals sign, the file suffixes are defined, each one separated by a space.
On the right hand side, the command is specified. The %f tag is replaced by the
file name.

Keep in mind that for the file suffixes, they are matched to the file name by
checking if the file name ends in the given suffix. It is completely unaware of
the position of the dot in the file name. For example, `foo.png` and `bar.png`
would both match `png`. `monday` and `tuesday` would both match `day`. Neither
`car` nor `cat` would match `ca`.

## 📦 Installation
Run this command:
```bash
wget https://github.com/kolin63/pigpen/releases/latest/download/pigpen -O
$HOME/.local/bin/pigpen
chmod +x $HOME/.local/bin/pigpen
```
