<h1 align="center">

<br>

<br>

<br>

</h1>

<h4 align="center">Pomiar refleksu</h4>

<p align="center">
  <a >
    <img src="https://i.imgur.com/8pm2Qxh.jpg"
         alt="Screenshot">
  </a>
</p>

## Project Overview 🎉
#Projekt został wykonany w celu pomiaru jak najdokładniejszego zmierzenia refleksu gracza i pokazanie 
#w ładnej formie kto ma najlepszy reflek.I wszystko to na platformie Arduino.
## Tech/framework used 🔧

| Tech                                                    | Description                              |
| ------------------------------------------------------- | ---------------------------------------- |
| C                                                       | Główny język                             |
| Python                                                  | Skrypt który przechwytuje dane z arudino i wyświetla na stronie html   |
| Arduino                                                 | Po prostu mikrosterownik jako platforma    |
| Linux                                                   | Wszystko było konfigurowane na debianie    |




## Installation 💾
#wersja dla 1 gracza
#led załączany stanem niskim                             czyli +5V - rezystor 330 Ohm - led - port Uno
#naciśnięcie przycisku podaje 0 czyli LOW (masę) na port Arduino   czyli +5V - rezystor 10 kOhm - port Uno i 1 styk przycisku 2 styk przycisku - masa
#do pomiaru czasu w milisekundach używamy millis(), a dla pomiaru w mikrosekundach możemy użyć micros()
#Po złożeniu zainstaluj na linuxa pakiet z pythonem i pakiet apache.
#Po instalcji nadaj uprawnienia pliki z roższerzeniem .py najlepiej (chmod 777)
#Ciesz się grą.


