# Vulnerable Android App

This Android Application was developed in order to effectively check our Android-fuzzer.
This application as shown in next image includes two main buttons, one that calls a JNI implemented
function in order to update a label and one that calls Java code to update the same
label with different text. Also, in the native library we inserted a lot of vulnerable
code containing stack and buffer overflows and two different types of functions. Some
function are used only by other native components of the library and the others only
for being called by the Java code through JNI.

<p aligh="center"><img src="./assets/screenshot.png?raw=true" width="300"></p>