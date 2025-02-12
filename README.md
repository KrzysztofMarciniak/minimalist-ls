# mls - minimalist ls 
size:
```bash
$ size bin/mls
   text    data     bss     dec     hex filename
   5456     704      16    6176    1820 bin/mls
```
in comparison with ls:
```bash
$ size $(which ls)
   text    data     bss     dec     hex filename
1279598   17084    2352 1299034  13d25a /usr/bin/ls
```
usage:
```bash
$ mls
.
..
.git
.gitignore
LICENSE
Makefile
src
README.md
build
bin
$ mls -l
drwxr-xr-x user     wheel       0.10 KB 2025-02-12 20:50 .
drwxr-xr-x user     wheel       4.00 KB 2025-02-12 20:19 ..
drwxr-xr-x user     wheel       0.12 KB 2025-02-12 20:49 .git
-rw-r--r-- user     wheel       0.11 KB 2025-02-12 20:19 .gitignore
-rw-r--r-- user     wheel       1.05 KB 2025-02-12 20:19 LICENSE
-rw-r--r-- user     wheel       1.10 KB 2025-02-12 20:51 Makefile
drwxr-xr-x user     wheel       0.01 KB 2025-02-12 20:19 src
-rw-r--r-- user     wheel       0.24 KB 2025-02-12 20:52 README.md
drwxr-xr-x user     wheel       0.02 KB 2025-02-12 20:50 build
drwxr-xr-x user     wheel       0.01 KB 2025-02-12 20:50 bin
```
compile:
```bash
make
```
move to /usr/local/bin/:
```bash
sudo cp bin/mls /usr/local/bin/mls
```