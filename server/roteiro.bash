## Grafana
## https://blog.remontti.com.br/4014
## 10.1.75.1:3000
## 191.37.6.212:3000


## https://hugorezende.com.br/blog/tutorial-configurar-e-criar-uma-dashboard-no-grafana-usando-esp8266-e-mqtt/
## https://computingforgeeks.com/install-influxdb-on-debian-10-buster-linux/
## http://www.steves-internet-guide.com/client-connections-python-mqtt/
## https://www.ibm.com/support/knowledgecenter/pt-br/SSFKSJ_8.0.0/com.ibm.mq.dev.doc/q029090_.htm

##### Instalação Debian
# Debian 10.5.0 64 bits mínimo

##### Instalação Mosquitto
wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
apt-key add mosquitto-repo.gpg.key
cd /etc/apt/sources.list.d/
wget http://repo.mosquitto.org/debian/mosquitto-buster.list
apt-get update
apt-get install mosquitto mosquitto-clients
mosquitto_passwd -c /etc/mosquitto/passwd mqttadmin
# senha: senhamqtt

##### Instalação InfluxDB
wget -qO- https://repos.influxdata.com/influxdb.key | apt-key add -
echo "deb https://repos.influxdata.com/debian buster stable" | tee /etc/apt/sources.list.d/influxdb.list
apt update
apt install -y influxdb

influx -execute "CREATE USER "telegraf" WITH PASSWORD '99649ea3f29a4c9ebae2f51366db4d69' WITH ALL PRIVILEGES;"
influx -execute "CREATE USER "grafana" WITH PASSWORD '99649ea3f29a4c9ebae2f51366db4d69' WITH ALL PRIVILEGES;"

##### Instalação Telegraf

apt -y install telegraf


##### Instalação Grafana