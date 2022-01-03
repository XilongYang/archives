#! /bin/python

import os

choose = input("Shutdown now?<Y/n>")

if choose == "y" or choose == "Y" or choose == "":
    os.system("shutdown -h now")
