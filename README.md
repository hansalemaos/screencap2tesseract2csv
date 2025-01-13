# screencap2tesseract2csv
Fast Screencap to Tesseract to CSV converter for Android

## 1. Install termux and break out of the [termux env](https://github.com/hansalemaos/termuxfree) and install
```sh
pkg install tesseract
pkg install imagemagick
pkg install imagemagick-static
pkg install cloneit

# To download the tesseract models
cloneit https://github.com/hansalemaos/tessdata_best
cloneit https://github.com/hansalemaos/tessdata
cloneit https://github.com/hansalemaos/tessdata_fast
```


## 2. Push the source code to the device
```sh
adb -s 127.0.0.1:5516 push "C:\Users\hansc\source\repos\tesseractwithimagemagick\tesseractwithimagemagick.cpp" /sdcard
```

## 3. Compile and run the code
```sh
cp /sdcard/tesseractwithimagemagick.cpp . && g++ -std=c++2a -O3 -g0 tesseractwithimagemagick.cpp && ./a.out --width=1024 --height=768 --tessdata=/data/data/com.termux/files/home/tessdata_fast --tesseract_args="-l por+eng --oem 3"
```

## 4. Example with aditional ImageMagick filter
```sh
./a.out --width=1024 --height=768 --tessdata=/data/data/com.termux/files/home/tessdata_fast --imagemagick_args="-colorspace LinearGray -normalize -auto-level -alpha deactivate  -adaptive-blur 1 -adaptive-sharpen 1 -trim -fuzz 60 -antialias -auto-gamma -auto-level -black-point-compensation -normalize -enhance -white-balance -antialias -black-threshold 4 -mean-shift 1x5+17%" --tesseract_args="-l por+eng --oem 3"
```


## 5. All possible arguments

```sh
Mandatory arguments:
--width
        Description: screen width
--height
        Description: screen height
--tessdata
        Description: folder with tessdata


Optional arguments:
--path_screencap
        Default:     screencap
        Description: Android screencap path
--path_outpic
        Default:     /sdcard/tesseractwithimagemagick.ppm
        Description: Save path for screencap result as ppm file
--path_outpic_filtered
        Default:     /sdcard/tesseractwithimagemagickfiltered.ppm
        Description: Save path for ImageMagick filtered screencap result as ppm file
--path_outhorc
        Default:     /sdcard/tesseractwithimagemagick
        Description: Save path for tesseract result, without extension
--path_exe_tesseract
        Default:     /data/data/com.termux/files/usr/bin/tesseract
        Description: tesseract path
--path_exe_imagemagick
        Default:     /data/data/com.termux/files/usr/bin/magick
        Description: ImageMagick path
--tesseract_args
        Default:
        Description: aditional tesseract arguments, e.g. --tesseract_args="-l por+eng --oem 3"
--imagemagick_args
        Default:
        Description: aditional ImageMagick arguments, e.g. --imagemagick_args="-colorspace LinearGray -normalize -auto-level -alpha deactivate  -adaptive-blur 1 -adaptive-sharpen 1 -trim -fuzz 60 -antialias -auto-gamma -auto-level -black-point-compensation -normalize -enhance -white-balance -antialias -black-threshold 4 -mean-shift 1x5+17%"
--delete_outpic
        Default:     0
        Description: Whether to delete screencap result or not
--delete_outpic_filtered
        Default:     0
        Description: Whether to delete ImageMagick filtered screencap result or not
--delete_outhorc
        Default:     0
        Description: Whether to delete tesseract result or not
```