@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\WKavr\ex001\labels.tmp" -fI -W+ie -C V2E -o "C:\WKavr\ex001\ex001.hex" -d "C:\WKavr\ex001\ex001.obj" -e "C:\WKavr\ex001\ex001.eep" -m "C:\WKavr\ex001\ex001.map" "C:\WKavr\ex001\ex001.asm"
