# Implementacja wielowątkowości prosesów (mutex'y) w postaci automatycznej nastawni kolejowej (dolnośląskie)
Prowadzący: D.Ż. (Systemy Operacyjne 2 SO2)

*Migotanie wynika z wykorzystania SSH*
![ezgif com-video-to-gif](https://github.com/craksys/Tory_SO2P/assets/53128417/03b6f8a2-909b-4ae4-a8aa-ca46583511e8)

Pociągi są synchronizowane pomiędzy mapami i zarządzane przez globalny load balancer (mapa główna) oraz lokalny (pojedyńcza stacja).
Statystyki pokazują zapełnienie stacji przez pasażerów oraz pociągi.

Installation guide (Ubuntu 23.04):

`sudo apt update && sudo apt upgrade`

`sudo apt install git g++ libncurses-dev`

`git clone https://github.com/craksys/PWR-threads-traintraffic`

`cd PWR-threads-traintraffic`

Build and run:

`./run.sh`

> if don't work try chmod +x run.sh
