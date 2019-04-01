<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.2" tiledversion="1.2.0" name="Objects" tilewidth="75" tileheight="75" tilecount="6" columns="0">
 <grid orientation="orthogonal" width="1" height="1"/>
 <properties>
  <property name="AreObjects" type="bool" value="true"/>
 </properties>
 <tile id="0" type="Enemy">
  <properties>
   <property name="HP" type="int" value="20"/>
   <property name="SpeedPerSecond" type="float" value="100"/>
  </properties>
  <image width="75" height="75" source="graphics/bloater.png"/>
 </tile>
 <tile id="1" type="Enemy">
  <properties>
   <property name="HP" type="int" value="5"/>
   <property name="SpeedPerSecond" type="float" value="400"/>
  </properties>
  <image width="55" height="55" source="graphics/chaser.png"/>
 </tile>
 <tile id="2" type="Enemy">
  <properties>
   <property name="HP" type="int" value="2"/>
   <property name="SpeedPerSecond" type="float" value="50"/>
  </properties>
  <image width="50" height="50" source="graphics/crawler.png"/>
 </tile>
 <tile id="3" type="Player">
  <properties>
   <property name="BulletSpeedPerSecond" type="float" value="300"/>
   <property name="MaxBulletSpawnCooldown" type="float" value="0.2"/>
   <property name="SpeedPerSecond" type="float" value="1200"/>
   <property name="StartAmmo" type="int" value="10"/>
   <property name="StartHP" type="int" value="3"/>
  </properties>
  <image width="50" height="50" source="graphics/player.png"/>
 </tile>
 <tile id="4" type="Item">
  <properties>
   <property name="Ammo" type="int" value="10"/>
  </properties>
  <image width="50" height="59" source="graphics/ammo_pickup.png"/>
 </tile>
 <tile id="5" type="Item">
  <properties>
   <property name="HP" type="int" value="1"/>
  </properties>
  <image width="55" height="55" source="graphics/health_pickup.png"/>
 </tile>
</tileset>
