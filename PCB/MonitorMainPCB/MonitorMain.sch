<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="8.6.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="5" fill="1" visible="no" active="no"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="texas-ads1293">
<description>ADS1293 Low-Power, 3-Channel, 24-Bit Analog Front-End for Biopotential Measurements</description>
<packages>
<package name="QFN28-5X5">
<description>Pads size: 0.25x0.6, thermal pad: 3.6x3.6</description>
<smd name="GND" x="0" y="0" dx="3.6" dy="3.6" layer="1"/>
<smd name="25" x="-2.4" y="0" dx="0.6" dy="0.25" layer="1"/>
<smd name="24" x="-2.4" y="0.5" dx="0.6" dy="0.25" layer="1"/>
<smd name="23" x="-2.4" y="1" dx="0.6" dy="0.25" layer="1"/>
<smd name="22" x="-2.4" y="1.5" dx="0.6" dy="0.25" layer="1"/>
<smd name="26" x="-2.4" y="-0.5" dx="0.6" dy="0.25" layer="1"/>
<smd name="27" x="-2.4" y="-1" dx="0.6" dy="0.25" layer="1"/>
<smd name="28" x="-2.4" y="-1.5" dx="0.6" dy="0.25" layer="1"/>
<smd name="11" x="2.4" y="0" dx="0.6" dy="0.25" layer="1"/>
<smd name="12" x="2.4" y="0.5" dx="0.6" dy="0.25" layer="1"/>
<smd name="13" x="2.4" y="1" dx="0.6" dy="0.25" layer="1"/>
<smd name="14" x="2.4" y="1.5" dx="0.6" dy="0.25" layer="1"/>
<smd name="18" x="0" y="2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="17" x="0.5" y="2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="16" x="1" y="2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="15" x="1.5" y="2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="19" x="-0.5" y="2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="20" x="-1" y="2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="21" x="-1.5" y="2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="4" x="0" y="-2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="5" x="0.5" y="-2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="6" x="1" y="-2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="7" x="1.5" y="-2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="3" x="-0.5" y="-2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="2" x="-1" y="-2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="1" x="-1.5" y="-2.4" dx="0.6" dy="0.25" layer="1" rot="R90"/>
<smd name="10" x="2.4" y="-0.5" dx="0.6" dy="0.25" layer="1"/>
<smd name="9" x="2.4" y="-1" dx="0.6" dy="0.25" layer="1"/>
<smd name="8" x="2.4" y="-1.5" dx="0.6" dy="0.25" layer="1"/>
<circle x="-2.1" y="-2.1" radius="0.25495" width="0.1" layer="21"/>
<text x="-2.575" y="2.825" size="0.6096" layer="25" font="vector">&gt;NAME</text>
<text x="-2.575" y="-3.45" size="0.6096" layer="27" font="vector">&gt;VALUE</text>
<wire x1="-2.55" y1="1.8" x2="-2.55" y2="2.55" width="0.1" layer="21"/>
<wire x1="-2.55" y1="2.55" x2="-1.8" y2="2.55" width="0.1" layer="21"/>
<wire x1="1.8" y1="2.55" x2="2.55" y2="2.55" width="0.1" layer="21"/>
<wire x1="2.55" y1="2.55" x2="2.55" y2="1.8" width="0.1" layer="21"/>
<wire x1="-2.55" y1="-1.8" x2="-2.55" y2="-2.55" width="0.1" layer="21"/>
<wire x1="-2.55" y1="-2.55" x2="-1.8" y2="-2.55" width="0.1" layer="21"/>
<wire x1="1.8" y1="-2.55" x2="2.55" y2="-2.55" width="0.1" layer="21"/>
<wire x1="2.55" y1="-2.55" x2="2.55" y2="-1.8" width="0.1" layer="21"/>
<wire x1="-2.7" y1="-2.7" x2="2.7" y2="-2.7" width="0.01" layer="39"/>
<wire x1="2.7" y1="-2.7" x2="2.7" y2="2.7" width="0.01" layer="39"/>
<wire x1="2.7" y1="2.7" x2="-2.7" y2="2.7" width="0.01" layer="39"/>
<wire x1="-2.7" y1="2.7" x2="-2.7" y2="-2.7" width="0.01" layer="39"/>
</package>
</packages>
<symbols>
<symbol name="ADS1293">
<pin name="IN1" x="-20.32" y="17.78" length="middle" direction="in"/>
<pin name="IN2" x="-20.32" y="15.24" length="middle" direction="in"/>
<pin name="IN3" x="-20.32" y="12.7" length="middle" direction="in"/>
<pin name="IN4" x="-20.32" y="10.16" length="middle" direction="in"/>
<pin name="IN5" x="-20.32" y="7.62" length="middle" direction="in"/>
<pin name="IN6" x="-20.32" y="5.08" length="middle" direction="in"/>
<pin name="WCT" x="-20.32" y="0" length="middle" direction="out"/>
<pin name="CMOUT" x="-20.32" y="-5.08" length="middle" direction="out"/>
<pin name="RLDOUT" x="-20.32" y="-7.62" length="middle" direction="out"/>
<pin name="RLDINV" x="-20.32" y="-10.16" length="middle" direction="in"/>
<pin name="RLDIN" x="-20.32" y="-12.7" length="middle"/>
<pin name="RLDREF" x="-20.32" y="-15.24" length="middle" direction="out"/>
<pin name="SYNCB" x="20.32" y="-10.16" length="middle" rot="R180"/>
<pin name="VSSIO" x="2.54" y="-25.4" length="middle" direction="pwr" rot="R90"/>
<pin name="ALARMB" x="20.32" y="-7.62" length="middle" direction="out" rot="R180"/>
<pin name="CSB" x="20.32" y="5.08" length="middle" direction="in" rot="R180"/>
<pin name="SCLK" x="20.32" y="10.16" length="middle" direction="in" rot="R180"/>
<pin name="SDI" x="20.32" y="12.7" length="middle" direction="in" rot="R180"/>
<pin name="SDO" x="20.32" y="15.24" length="middle" direction="out" rot="R180"/>
<pin name="DRDYB" x="20.32" y="7.62" length="middle" direction="out" rot="R180"/>
<pin name="CLK" x="20.32" y="17.78" length="middle" rot="R180"/>
<pin name="VDDIO" x="5.08" y="25.4" length="middle" direction="pwr" rot="R270"/>
<pin name="XTAL1" x="20.32" y="0" length="middle" direction="in" rot="R180"/>
<pin name="XTAL2" x="20.32" y="-2.54" length="middle" direction="in" rot="R180"/>
<pin name="RSTB" x="-2.54" y="25.4" length="middle" direction="in" rot="R270"/>
<pin name="CVREF" x="2.54" y="25.4" length="middle" rot="R270"/>
<pin name="VSS" x="-2.54" y="-25.4" length="middle" direction="pwr" rot="R90"/>
<pin name="VDD" x="-5.08" y="25.4" length="middle" direction="pwr" rot="R270"/>
<wire x1="-15.24" y1="-20.32" x2="15.24" y2="-20.32" width="0.254" layer="94"/>
<wire x1="15.24" y1="-20.32" x2="15.24" y2="20.32" width="0.254" layer="94"/>
<wire x1="15.24" y1="20.32" x2="-15.24" y2="20.32" width="0.254" layer="94"/>
<wire x1="-15.24" y1="20.32" x2="-15.24" y2="-20.32" width="0.254" layer="94"/>
<text x="-15.24" y="21.59" size="1.778" layer="95">&gt;NAME</text>
<text x="2.54" y="-22.86" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ADS1293" prefix="IC">
<description>The ADS1293 incorporates all features commonly required in portable, low-power medical, sports, and fitness electrocardiogram (ECG) applications. With high levels of integration and exceptional performance, the ADS1293 enables the creation of scalable medical instrumentation systems at significantly reduced size, power, and overall cost.&lt;br&gt;&lt;br&gt;


The library has been designed by&lt;a href="https://www.facebook.com/groups/eaglecadsoftUK"&gt; Richard Magdycz&lt;/a&gt;</description>
<gates>
<gate name="G$1" symbol="ADS1293" x="0" y="0"/>
</gates>
<devices>
<device name="" package="QFN28-5X5">
<connects>
<connect gate="G$1" pin="ALARMB" pad="15"/>
<connect gate="G$1" pin="CLK" pad="21"/>
<connect gate="G$1" pin="CMOUT" pad="8"/>
<connect gate="G$1" pin="CSB" pad="16"/>
<connect gate="G$1" pin="CVREF" pad="26"/>
<connect gate="G$1" pin="DRDYB" pad="20"/>
<connect gate="G$1" pin="IN1" pad="1"/>
<connect gate="G$1" pin="IN2" pad="2"/>
<connect gate="G$1" pin="IN3" pad="3"/>
<connect gate="G$1" pin="IN4" pad="4"/>
<connect gate="G$1" pin="IN5" pad="5"/>
<connect gate="G$1" pin="IN6" pad="6"/>
<connect gate="G$1" pin="RLDIN" pad="11"/>
<connect gate="G$1" pin="RLDINV" pad="10"/>
<connect gate="G$1" pin="RLDOUT" pad="9"/>
<connect gate="G$1" pin="RLDREF" pad="12"/>
<connect gate="G$1" pin="RSTB" pad="25"/>
<connect gate="G$1" pin="SCLK" pad="17"/>
<connect gate="G$1" pin="SDI" pad="18"/>
<connect gate="G$1" pin="SDO" pad="19"/>
<connect gate="G$1" pin="SYNCB" pad="13"/>
<connect gate="G$1" pin="VDD" pad="28"/>
<connect gate="G$1" pin="VDDIO" pad="22"/>
<connect gate="G$1" pin="VSS" pad="27"/>
<connect gate="G$1" pin="VSSIO" pad="14"/>
<connect gate="G$1" pin="WCT" pad="7"/>
<connect gate="G$1" pin="XTAL1" pad="23"/>
<connect gate="G$1" pin="XTAL2" pad="24"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="IC1" library="texas-ads1293" deviceset="ADS1293" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="IC1" gate="G$1" x="182.88" y="127"/>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
