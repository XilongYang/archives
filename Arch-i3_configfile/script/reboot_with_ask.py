#! /bin/python

import os

choose = input("Reboot now?<Y/n>")

if choose == "y" or choose == "Y" or choose == "":
    os.system("reboot")
