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
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Texas Instruments_By_element14_Batch_1">
<description>Developed by element14 :&lt;br&gt;
element14 CAD Library consolidation.ulp
at 30/07/2012 17:45:58</description>
<packages>
<package name="BGA64C80P8X8_800X800X145">
<smd name="A1" x="-2.794" y="2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="A2" x="-2.0066" y="2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="A3" x="-1.1938" y="2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="A4" x="-0.4064" y="2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="A5" x="0.4064" y="2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="A6" x="1.1938" y="2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="A7" x="2.0066" y="2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="A8" x="2.794" y="2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="B1" x="-2.794" y="2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="B2" x="-2.0066" y="2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="B3" x="-1.1938" y="2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="B4" x="-0.4064" y="2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="B5" x="0.4064" y="2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="B6" x="1.1938" y="2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="B7" x="2.0066" y="2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="B8" x="2.794" y="2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="C1" x="-2.794" y="1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="C2" x="-2.0066" y="1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="C3" x="-1.1938" y="1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="C4" x="-0.4064" y="1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="C5" x="0.4064" y="1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="C6" x="1.1938" y="1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="C7" x="2.0066" y="1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="C8" x="2.794" y="1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="D1" x="-2.794" y="0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="D2" x="-2.0066" y="0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="D3" x="-1.1938" y="0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="D4" x="-0.4064" y="0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="D5" x="0.4064" y="0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="D6" x="1.1938" y="0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="D7" x="2.0066" y="0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="D8" x="2.794" y="0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="E1" x="-2.794" y="-0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="E2" x="-2.0066" y="-0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="E3" x="-1.1938" y="-0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="E4" x="-0.4064" y="-0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="E5" x="0.4064" y="-0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="E6" x="1.1938" y="-0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="E7" x="2.0066" y="-0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="E8" x="2.794" y="-0.4064" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="F1" x="-2.794" y="-1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="F2" x="-2.0066" y="-1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="F3" x="-1.1938" y="-1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="F4" x="-0.4064" y="-1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="F5" x="0.4064" y="-1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="F6" x="1.1938" y="-1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="F7" x="2.0066" y="-1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="F8" x="2.794" y="-1.1938" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="G1" x="-2.794" y="-2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="G2" x="-2.0066" y="-2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="G3" x="-1.1938" y="-2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="G4" x="-0.4064" y="-2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="G5" x="0.4064" y="-2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="G6" x="1.1938" y="-2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="G7" x="2.0066" y="-2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="G8" x="2.794" y="-2.0066" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="H1" x="-2.794" y="-2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="H2" x="-2.0066" y="-2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="H3" x="-1.1938" y="-2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="H4" x="-0.4064" y="-2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="H5" x="0.4064" y="-2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="H6" x="1.1938" y="-2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="H7" x="2.0066" y="-2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<smd name="H8" x="2.794" y="-2.794" dx="0.3556" dy="0.3556" layer="1" roundness="100"/>
<wire x1="-4.0386" y1="-0.4064" x2="-4.2926" y2="-0.4064" width="0.1524" layer="21"/>
<wire x1="4.0386" y1="-0.4064" x2="4.2926" y2="-0.4064" width="0.1524" layer="21"/>
<wire x1="0.4064" y1="4.0386" x2="0.4064" y2="4.2926" width="0.1524" layer="21"/>
<wire x1="0.4064" y1="-4.0386" x2="0.4064" y2="-4.2926" width="0.1524" layer="21"/>
<wire x1="-3.6576" y1="4.0386" x2="-4.0386" y2="3.6576" width="0.1524" layer="21"/>
<wire x1="-4.0386" y1="-4.0386" x2="4.0386" y2="-4.0386" width="0.1524" layer="21"/>
<wire x1="4.0386" y1="-4.0386" x2="4.0386" y2="4.0386" width="0.1524" layer="21"/>
<wire x1="4.0386" y1="4.0386" x2="-4.0386" y2="4.0386" width="0.1524" layer="21"/>
<wire x1="-4.0386" y1="4.0386" x2="-4.0386" y2="-4.0386" width="0.1524" layer="21"/>
<text x="-5.842" y="2.159" size="1.27" layer="21" ratio="6" rot="SR0">A</text>
<text x="-5.842" y="-3.429" size="1.27" layer="21" ratio="6" rot="SR0">H</text>
<text x="-2.159" y="4.6736" size="1.27" layer="21" ratio="6" rot="SR90">1</text>
<text x="3.429" y="4.6736" size="1.27" layer="21" ratio="6" rot="SR90">8</text>
<wire x1="-3.6576" y1="4.0386" x2="-4.0386" y2="3.6576" width="0" layer="51"/>
<wire x1="-4.0386" y1="-4.0386" x2="4.0386" y2="-4.0386" width="0" layer="51"/>
<wire x1="4.0386" y1="-4.0386" x2="4.0386" y2="4.0386" width="0" layer="51"/>
<wire x1="4.0386" y1="4.0386" x2="-4.0386" y2="4.0386" width="0" layer="51"/>
<wire x1="-4.0386" y1="4.0386" x2="-4.0386" y2="-4.0386" width="0" layer="51"/>
<text x="-5.842" y="2.159" size="1.27" layer="51" ratio="6" rot="SR0">A</text>
<text x="-5.842" y="-3.429" size="1.27" layer="51" ratio="6" rot="SR0">H</text>
<text x="-2.159" y="4.6736" size="1.27" layer="51" ratio="6" rot="SR90">1</text>
<text x="3.429" y="4.6736" size="1.27" layer="51" ratio="6" rot="SR90">8</text>
<text x="-3.4544" y="7.62" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-3.4544" y="-7.62" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="ADS1298CZXGT">
<pin name="AVDD_2" x="-30.48" y="60.96" length="middle" direction="pwr"/>
<pin name="AVDD_3" x="-30.48" y="58.42" length="middle" direction="pwr"/>
<pin name="AVDD1" x="-30.48" y="55.88" length="middle" direction="pwr"/>
<pin name="AVDD_4" x="-30.48" y="53.34" length="middle" direction="pwr"/>
<pin name="AVDD_5" x="-30.48" y="50.8" length="middle" direction="pwr"/>
<pin name="AVDD" x="-30.48" y="48.26" length="middle" direction="pwr"/>
<pin name="DVDD_2" x="-30.48" y="45.72" length="middle" direction="pwr"/>
<pin name="DVDD" x="-30.48" y="43.18" length="middle" direction="pwr"/>
<pin name="DIN" x="-30.48" y="38.1" length="middle" direction="in"/>
<pin name="DAISY_IN" x="-30.48" y="35.56" length="middle" direction="in"/>
<pin name="RLDIN" x="-30.48" y="33.02" length="middle" direction="pas"/>
<pin name="~CS" x="-30.48" y="30.48" length="middle" direction="in"/>
<pin name="CLKSEL" x="-30.48" y="27.94" length="middle" direction="in"/>
<pin name="RESV1" x="-30.48" y="25.4" length="middle" direction="in"/>
<pin name="SCLK" x="-30.48" y="22.86" length="middle" direction="in"/>
<pin name="RLDREF" x="-30.48" y="20.32" length="middle" direction="in"/>
<pin name="~PWDN" x="-30.48" y="17.78" length="middle" direction="in"/>
<pin name="~RESET" x="-30.48" y="15.24" length="middle" direction="in"/>
<pin name="VCAP2" x="-30.48" y="12.7" length="middle" direction="pas"/>
<pin name="VCAP3" x="-30.48" y="10.16" length="middle" direction="pas"/>
<pin name="START" x="-30.48" y="7.62" length="middle" direction="in"/>
<pin name="CLK" x="-30.48" y="5.08" length="middle" direction="in"/>
<pin name="VREFN" x="-30.48" y="2.54" length="middle" direction="in"/>
<pin name="IN1P" x="-30.48" y="-2.54" length="middle" direction="in"/>
<pin name="IN2P" x="-30.48" y="-5.08" length="middle" direction="in"/>
<pin name="IN3P" x="-30.48" y="-7.62" length="middle" direction="in"/>
<pin name="IN4P" x="-30.48" y="-10.16" length="middle" direction="in"/>
<pin name="IN5P" x="-30.48" y="-12.7" length="middle" direction="in"/>
<pin name="IN6P" x="-30.48" y="-15.24" length="middle" direction="in"/>
<pin name="IN7P" x="-30.48" y="-17.78" length="middle" direction="in"/>
<pin name="IN8P" x="-30.48" y="-20.32" length="middle" direction="pas"/>
<pin name="IN1N" x="-30.48" y="-25.4" length="middle" direction="in"/>
<pin name="IN2N" x="-30.48" y="-27.94" length="middle" direction="in"/>
<pin name="IN3N" x="-30.48" y="-30.48" length="middle" direction="in"/>
<pin name="IN4N" x="-30.48" y="-33.02" length="middle" direction="in"/>
<pin name="IN5N" x="-30.48" y="-35.56" length="middle" direction="in"/>
<pin name="IN6N" x="-30.48" y="-38.1" length="middle" direction="in"/>
<pin name="IN7N" x="-30.48" y="-40.64" length="middle" direction="in"/>
<pin name="IN8N" x="-30.48" y="-43.18" length="middle" direction="pas"/>
<pin name="AVSS_2" x="-30.48" y="-48.26" length="middle" direction="pwr"/>
<pin name="AVSS1" x="-30.48" y="-50.8" length="middle" direction="pwr"/>
<pin name="AVSS_3" x="-30.48" y="-53.34" length="middle" direction="pwr"/>
<pin name="AVSS_4" x="-30.48" y="-55.88" length="middle" direction="pwr"/>
<pin name="AVSS_5" x="-30.48" y="-58.42" length="middle" direction="pwr"/>
<pin name="AVSS" x="-30.48" y="-60.96" length="middle" direction="pwr"/>
<pin name="DGND_2" x="-30.48" y="-63.5" length="middle" direction="pas"/>
<pin name="DGND_3" x="-30.48" y="-66.04" length="middle" direction="pas"/>
<pin name="DGND" x="-30.48" y="-68.58" length="middle" direction="pas"/>
<pin name="GPIO1" x="30.48" y="60.96" length="middle" rot="R180"/>
<pin name="GPIO2" x="30.48" y="58.42" length="middle" rot="R180"/>
<pin name="GPIO3" x="30.48" y="55.88" length="middle" rot="R180"/>
<pin name="GPIO4" x="30.48" y="53.34" length="middle" rot="R180"/>
<pin name="DOUT" x="30.48" y="48.26" length="middle" rot="R180"/>
<pin name="RLDOUT" x="30.48" y="45.72" length="middle" direction="out" rot="R180"/>
<pin name="RESV2" x="30.48" y="43.18" length="middle" direction="out" rot="R180"/>
<pin name="RLDINV" x="30.48" y="40.64" length="middle" rot="R180"/>
<pin name="RESV3" x="30.48" y="38.1" length="middle" direction="out" rot="R180"/>
<pin name="~DRDY" x="30.48" y="35.56" length="middle" direction="out" rot="R180"/>
<pin name="WCT" x="30.48" y="33.02" length="middle" direction="out" rot="R180"/>
<pin name="VREFP" x="30.48" y="30.48" length="middle" rot="R180"/>
<pin name="VCAP1" x="30.48" y="27.94" length="middle" rot="R180"/>
<pin name="VCAP4" x="30.48" y="25.4" length="middle" direction="out" rot="R180"/>
<pin name="TESTP_PACE_OUT1" x="30.48" y="20.32" length="middle" rot="R180"/>
<pin name="TESTN_PACE_OUT2" x="30.48" y="17.78" length="middle" rot="R180"/>
<wire x1="-25.4" y1="66.04" x2="-25.4" y2="-73.66" width="0.4064" layer="94"/>
<wire x1="-25.4" y1="-73.66" x2="25.4" y2="-73.66" width="0.4064" layer="94"/>
<wire x1="25.4" y1="-73.66" x2="25.4" y2="66.04" width="0.4064" layer="94"/>
<wire x1="25.4" y1="66.04" x2="-25.4" y2="66.04" width="0.4064" layer="94"/>
<text x="-5.3594" y="70.0786" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-5.2578" y="-82.1182" size="2.0828" layer="96" ratio="10" rot="SR0">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ADS1298CZXGT" prefix="U">
<description>Low-Power, 8-Channel, 24-Bit Analog Front-End for Biopotential Measurements</description>
<gates>
<gate name="A" symbol="ADS1298CZXGT" x="0" y="0"/>
</gates>
<devices>
<device name="" package="BGA64C80P8X8_800X800X145">
<connects>
<connect gate="A" pin="AVDD" pad="C6"/>
<connect gate="A" pin="AVDD1" pad="A7"/>
<connect gate="A" pin="AVDD_2" pad="A4"/>
<connect gate="A" pin="AVDD_3" pad="A6"/>
<connect gate="A" pin="AVDD_4" pad="B4"/>
<connect gate="A" pin="AVDD_5" pad="B6"/>
<connect gate="A" pin="AVSS" pad="D5"/>
<connect gate="A" pin="AVSS1" pad="A8"/>
<connect gate="A" pin="AVSS_2" pad="A5"/>
<connect gate="A" pin="AVSS_3" pad="B5"/>
<connect gate="A" pin="AVSS_4" pad="C5"/>
<connect gate="A" pin="AVSS_5" pad="D4"/>
<connect gate="A" pin="CLK" pad="G8"/>
<connect gate="A" pin="CLKSEL" pad="B8"/>
<connect gate="A" pin="DAISY_IN" pad="F6"/>
<connect gate="A" pin="DGND" pad="H7"/>
<connect gate="A" pin="DGND_2" pad="C7"/>
<connect gate="A" pin="DGND_3" pad="D7"/>
<connect gate="A" pin="DIN" pad="H8"/>
<connect gate="A" pin="DOUT" pad="E8"/>
<connect gate="A" pin="DVDD" pad="D8"/>
<connect gate="A" pin="DVDD_2" pad="C8"/>
<connect gate="A" pin="GPIO1" pad="F5"/>
<connect gate="A" pin="GPIO2" pad="E7"/>
<connect gate="A" pin="GPIO3" pad="E6"/>
<connect gate="A" pin="GPIO4" pad="E5"/>
<connect gate="A" pin="IN1N" pad="H2"/>
<connect gate="A" pin="IN1P" pad="H1"/>
<connect gate="A" pin="IN2N" pad="G2"/>
<connect gate="A" pin="IN2P" pad="G1"/>
<connect gate="A" pin="IN3N" pad="F2"/>
<connect gate="A" pin="IN3P" pad="F1"/>
<connect gate="A" pin="IN4N" pad="E2"/>
<connect gate="A" pin="IN4P" pad="E1"/>
<connect gate="A" pin="IN5N" pad="D2"/>
<connect gate="A" pin="IN5P" pad="D1"/>
<connect gate="A" pin="IN6N" pad="C2"/>
<connect gate="A" pin="IN6P" pad="C1"/>
<connect gate="A" pin="IN7N" pad="B2"/>
<connect gate="A" pin="IN7P" pad="B1"/>
<connect gate="A" pin="IN8N" pad="A2"/>
<connect gate="A" pin="IN8P" pad="A1"/>
<connect gate="A" pin="RESV1" pad="E4"/>
<connect gate="A" pin="RESV2" pad="F4"/>
<connect gate="A" pin="RESV3" pad="G4"/>
<connect gate="A" pin="RLDIN" pad="A3"/>
<connect gate="A" pin="RLDINV" pad="C3"/>
<connect gate="A" pin="RLDOUT" pad="B3"/>
<connect gate="A" pin="RLDREF" pad="C4"/>
<connect gate="A" pin="SCLK" pad="F8"/>
<connect gate="A" pin="START" pad="G7"/>
<connect gate="A" pin="TESTN_PACE_OUT2" pad="F3"/>
<connect gate="A" pin="TESTP_PACE_OUT1" pad="E3"/>
<connect gate="A" pin="VCAP1" pad="H5"/>
<connect gate="A" pin="VCAP2" pad="H6"/>
<connect gate="A" pin="VCAP3" pad="B7"/>
<connect gate="A" pin="VCAP4" pad="G3"/>
<connect gate="A" pin="VREFN" pad="H4"/>
<connect gate="A" pin="VREFP" pad="H3"/>
<connect gate="A" pin="WCT" pad="D3"/>
<connect gate="A" pin="~CS" pad="F7"/>
<connect gate="A" pin="~DRDY" pad="D6"/>
<connect gate="A" pin="~PWDN" pad="G5"/>
<connect gate="A" pin="~RESET" pad="G6"/>
</connects>
<technologies>
<technology name="">
<attribute name="MPN" value="ADS1298CZXGT" constant="no"/>
<attribute name="OC_FARNELL" value="1825746" constant="no"/>
<attribute name="OC_NEWARK" value="77R3938" constant="no"/>
<attribute name="PACKAGE" value="NFBGA-64" constant="no"/>
<attribute name="SUPPLIER" value="Texas Instruments" constant="no"/>
</technology>
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
<part name="U1" library="Texas Instruments_By_element14_Batch_1" deviceset="ADS1298CZXGT" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U1" gate="A" x="78.74" y="99.06"/>
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
