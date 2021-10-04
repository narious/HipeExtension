# Electrolize

## Introduction

Hipe `Electrolize` is user firendly GUI toolkit build on top `Hipe` display server.
It takes advantages of `Html` and `Css` in order for users to generate build their
app easier and faster.

## Get Started

### Installation


##### Prerequisite

* The following instructions have to be executed in a Linux distribution, perferablly Ubuntu.

* If not, make sure you have a working X installation. You can also refer to 
[Installing Hipe](http://www.hipe.tech/?l1=documentation&l2=Installation)
to install the `hipe` display server.

* Install the dependencies
``` bash
sudo apt install libqt5webkit5-dev qt5-default
```

##### Install `hipe`

1. Install and build `hipe` display server from our team's repository

``` bash
# download source code.
git clone https://github.com/narious/hipe-master.git
cd hipe-master/server
# generate make file from qmake file
qmake -makefile ./src/hiped.pro
# execute make script
make
```

2. Now you will be able to see an executable `hiped` in the current foler.
You can run it in the background or in a seperate terminal with command
`hiped &`.


##### Install and build `Electrolize`

``` bash
git clone https://github.com/narious/HipeExtension.git
cd HipeExtension/HtmlToHipe
make
```

#### Running an example

After install and build `Electorlize`, we have the executable `hipetohtml` to translate 
html files to c file with hipe instructions/functions.

We can use html files under `~/HtmlToHipe/data/` to test the program.
Also make sure `hiped` is running in the background.

``` bash
# use hipe-calc.html as an example
htmltohipe data/hipe-calc.html > calc.c
gcc calc.c -lhipe -o calc
./calc
```

Now you should be able to see a caculator window pops up.

* You can also use the Makefile we created to observe the difference between using a broswer and 
using hipe instructions.

``` bash
cd data
# NOTE: you need to have chromium installed on your system.
make testhipe-calc.html
```


## Documentation

### List of Supported Tags and Attributes

TODO: to be updated
[google doc](https://docs.google.com/spreadsheets/d/1Hg7m_Blj9LdwCqyFxwkCfdWY928O79K_ge3IN7phpbk/edit#gid=0)

### Contributors

### FAQ

