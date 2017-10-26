#!/usr/bin/env python
# -*- coding: utf8 -*-
import MySQLdb #lib för att ansluta till mysql/mariadb
import time #lib för tid
import requests #lib för att hämta innehåll från hemsida
import datetime

conn = MySQLdb.connect(host="localhost", 
  user="root",
  passwd="",
  db="temp_db") #Ansluter till databas
curr = conn.cursor() #Variable för db cursor

nowTime = (time.strftime("%y-%m-%d ") + time.strftime("%H:%M:%S")) #vaiable för tid exempel format 17-20-3 11:24:20 

url = "http://192.168.10.112/arduino/digital/" #Arduino url för rest-server
getTemp = requests.get(url) #hämtar innehållet på en sida
sensorValue = getTemp.text #gör om det till text vilket kommer visa värdet för sensorn
a = sensorValue.replace("\n", "") #Tar bort newline och space för innehållet

sqlAdd = ("""INSERT INTO tempLog (datetime,temperature) VALUES (%s,%s)""", (nowTime,a)) #Variable för att lägga till temperatur och tid
curr.execute(*sqlAdd) #Kör variablen
conn.commit() #slutför sql insert
curr.close() #stänger cursor
conn.close() #stänger db anslutning
