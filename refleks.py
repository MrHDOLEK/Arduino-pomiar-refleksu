#!/usr/bin/python
# -*- coding: utf-8 -*-
import serial

top10=[-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0]  #11 element jest tempem

#strona wyświetlająca wynik
def Strona2(co):
        strona = "<html><head>\n\
        <meta http-equiv=\"Expires\" content=\"0\">\n\
        <meta http-equiv=\"Content-Type\" content=\"text"+'/'+"html; charset=utf-8\" />\n\
        <meta http-equiv=\"Cache-Control\" content=\"no-store, no-cache, must-revalidate\">\n\
        <meta http-equiv=\"Pragma\" content=\"no-cache\">\n\
        </head>\n\
        <script LANGUAGE=\"JavaScript\">\n\
         var clock= 2000;\n\
         function clock2()\n\
         {\n\
          clock=clock-1000;\n\
          dis_clock=clock/1000;\n\
          document.getElementById('clock').innerHTML = dis_clock;\n\
          document.getElementById('clock_2').innerHTML = dis_clock;\n\
          if(clock==0)\n\
           document.zegar.submit();\n\
          window.setTimeout(\"clock2()\", 1000);\n\
         }\n\
        </script>\n\
        <body onLoad=\"clock2();\">\n\
        <form name=\"zegar\" action=\"autorefresh.html\" method=\"post\">\n\
        </form>\n\
        <table cellspacing=\"20\" width=\"100%\"><tr>\n\
        <td align=\"center\">\n\
        Strona się odświeży za :<br><b><span id=\"clock\"></span> sek.</b>\n\
        </td>\n\
        <td><div align=\"center\"><h1>"+co+"</h1></div></td>\n\
        <td align=\"center\">\n\
        Strona się odświeży za :<br><b><span id=\"clock_2\"></span> sek.</b>\n\
        </td></tr></table>\n\
        </body>\n\
        </html>\n"

        #print strona
        plik = open('./autorefresh.html', 'w')
        plik.write(strona)
        plik.close()
        
try:
#---------------uruchomienie portu szeregowego ----------------------------------
        ser = serial.Serial(port='/dev/ttyUSB0',baudrate = 9600,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS,timeout=1)
        x=""
        
        while 1:
                x=ser.readline()        #odbieramy potwierdzenie
                x=x.rstrip()
                if x=="-1":                             Strona2("<font color=\"red\">Falstart - naciśnij przycisk.</font>")
                if x=="Czekam":                         Strona2("Czekam - naciśnij przycisk.")
                if x.find("Wynik")>-1:
                        wyn=x.split(':')
                        s=float(wyn[1])/1000000
                        #aktualizacja TOP10
                        top10[0]=s
                        top10.sort()
                        top10[0]=-1.0
                        k=1
                        while k<=10:
                                #if top10[k]!=-1.0: print top10[k]
                                k+=1
                        #wyświetlenie strony
                        Strona2("Wynik <font color=\"blue\">"+str(s)+"</font> sek.<br><h4>Naciśnij przycisk.</h4>")
                if x=="Uwaga!":                         Strona2("Pomiar w toku ...")
                
except KeyboardInterrupt:
        print "Przerwano dzialanie programu\n"

finally:
        print "Bye..."
