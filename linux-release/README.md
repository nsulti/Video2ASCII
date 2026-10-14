############################################################
# This is a release built and tested on Arch Linux 64-bit. #
############################################################

Removed the general vidtoascii.cpp. To find the original, look at the Windows release.

Updated to match OpenCV 5+ (after a year of no updates). Recompiled V2A binary --- requires OpenCV libs installed.
Also, added color support. Yay. Windows version is obsolete and will not be updated. It works, just no colors.

Addendum: no static build will be added.

Why?
A) It's a big hassle.
B) Necessary to keep the binary file relatively small.
C) To prevent breaking the code in Wayland/KDE or any other environment.

Static builds suck. Or not. I don't care.

Ironically, due to DLLs, the Windows version will run without recompiling.

son im crine 😭🙏🏻 (trademarked and copyrighted)

# RU: 
я КЛЯНУСЬ это было сделано без ИИ, я оформил комментарии сам, и код тоже мой. просто захотел оформить как-то презентабельно.

COMPILATION: "g++ -O3 vidtoascii_linuxbuild.cpp -o V2A -I/usr/include/opencv5/ -L/usr/lib -lopencv_core -lopencv_videoio -lopencv_imgproc -lopencv_highgui".

-nsulti
