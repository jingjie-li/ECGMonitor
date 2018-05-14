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
<library name="AFE4400">
<packages>
<package name="RHA40_4P15X4P15">
<smd name="1" x="-2.975" y="2.250009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="2" x="-2.975" y="1.750009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="3" x="-2.975" y="1.250009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="4" x="-2.975" y="0.7500125" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="5" x="-2.975" y="0.2499875" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="6" x="-2.975" y="-0.2499875" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="7" x="-2.975" y="-0.7500125" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="8" x="-2.975" y="-1.250009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="9" x="-2.975" y="-1.750009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="10" x="-2.975" y="-2.250009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="11" x="-2.250565625" y="-2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="12" x="-1.750440625" y="-2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="13" x="-1.250315625" y="-2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="14" x="-0.7501875" y="-2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="15" x="-0.2500625" y="-2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="16" x="0.2500625" y="-2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="17" x="0.7501875" y="-2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="18" x="1.250315625" y="-2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="19" x="1.750440625" y="-2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="20" x="2.250565625" y="-2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="21" x="2.975" y="-2.250009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="22" x="2.975" y="-1.750009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="23" x="2.975" y="-1.250009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="24" x="2.975" y="-0.7500125" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="25" x="2.975" y="-0.2499875" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="26" x="2.975" y="0.2499875" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="27" x="2.975" y="0.7500125" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="28" x="2.975" y="1.250009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="29" x="2.975" y="1.750009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="30" x="2.975" y="2.250009375" dx="0.2794" dy="0.8382" layer="1" rot="R270"/>
<smd name="31" x="2.250565625" y="2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="32" x="1.750440625" y="2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="33" x="1.250315625" y="2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="34" x="0.7501875" y="2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="35" x="0.2500625" y="2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="36" x="-0.2500625" y="2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="37" x="-0.7501875" y="2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="38" x="-1.250315625" y="2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="39" x="-1.750440625" y="2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="40" x="-2.250565625" y="2.975" dx="0.2794" dy="0.8382" layer="1" rot="R180"/>
<smd name="41" x="0" y="0" dx="4.1402" dy="4.1402" layer="1"/>
<pad name="V" x="-1.5748" y="-1.5748" drill="0.254"/>
<pad name="V_1" x="-1.5748" y="-0.7874" drill="0.254"/>
<pad name="V_2" x="-1.5748" y="0" drill="0.254"/>
<pad name="V_3" x="-1.5748" y="0.7874" drill="0.254"/>
<pad name="V_4" x="-1.5748" y="1.5748" drill="0.254"/>
<pad name="V_5" x="-0.7874" y="-1.5748" drill="0.254"/>
<pad name="V_6" x="-0.7874" y="-0.7874" drill="0.254"/>
<pad name="V_7" x="-0.7874" y="0" drill="0.254"/>
<pad name="V_8" x="-0.7874" y="0.7874" drill="0.254"/>
<pad name="V_9" x="-0.7874" y="1.5748" drill="0.254"/>
<pad name="V_10" x="0" y="-1.5748" drill="0.254"/>
<pad name="V_11" x="0" y="-0.7874" drill="0.254"/>
<pad name="V_12" x="0" y="0" drill="0.254"/>
<pad name="V_13" x="0" y="0.7874" drill="0.254"/>
<pad name="V_14" x="0" y="1.5748" drill="0.254"/>
<pad name="V_15" x="0.7874" y="-1.5748" drill="0.254"/>
<pad name="V_16" x="0.7874" y="-0.7874" drill="0.254"/>
<pad name="V_17" x="0.7874" y="0" drill="0.254"/>
<pad name="V_18" x="0.7874" y="0.7874" drill="0.254"/>
<pad name="V_19" x="0.7874" y="1.5748" drill="0.254"/>
<pad name="V_20" x="1.5748" y="-1.5748" drill="0.254"/>
<pad name="V_21" x="1.5748" y="-0.7874" drill="0.254"/>
<pad name="V_22" x="1.5748" y="0" drill="0.254"/>
<pad name="V_23" x="1.5748" y="0.7874" drill="0.254"/>
<pad name="V_24" x="1.5748" y="1.5748" drill="0.254"/>
<wire x1="-2.4638" y1="3.3274" x2="-3.3274" y2="3.3274" width="0.1524" layer="51"/>
<wire x1="3.3274" y1="2.4638" x2="3.3274" y2="3.3274" width="0.1524" layer="51"/>
<wire x1="2.4638" y1="-3.3274" x2="3.3274" y2="-3.3274" width="0.1524" layer="51"/>
<wire x1="-3.3274" y1="-2.4638" x2="-3.3274" y2="-3.3274" width="0.1524" layer="51"/>
<wire x1="-3.3274" y1="-3.3274" x2="-2.4638" y2="-3.3274" width="0.1524" layer="51"/>
<wire x1="3.3274" y1="-3.3274" x2="3.3274" y2="-2.4638" width="0.1524" layer="51"/>
<wire x1="3.3274" y1="3.3274" x2="2.4638" y2="3.3274" width="0.1524" layer="51"/>
<wire x1="-3.3274" y1="3.3274" x2="-3.3274" y2="2.4638" width="0.1524" layer="51"/>
<polygon width="0" layer="51">
<vertex x="-3.9116" y="-2.0574"/>
<vertex x="-3.9116" y="-2.4384"/>
<vertex x="-3.6576" y="-2.4384"/>
<vertex x="-3.6576" y="-2.0574"/>
</polygon>
<polygon width="0" layer="51">
<vertex x="2.0574" y="-3.6576"/>
<vertex x="2.0574" y="-3.9116"/>
<vertex x="2.4384" y="-3.9116"/>
<vertex x="2.4384" y="-3.6576"/>
</polygon>
<polygon width="0" layer="51">
<vertex x="3.9116" y="2.4384"/>
<vertex x="3.9116" y="2.0574"/>
<vertex x="3.6576" y="2.0574"/>
<vertex x="3.6576" y="2.4384"/>
</polygon>
<polygon width="0" layer="51">
<vertex x="-2.4384" y="3.6576"/>
<vertex x="-2.4384" y="3.9116"/>
<vertex x="-2.0574" y="3.9116"/>
<vertex x="-2.0574" y="3.6576"/>
</polygon>
<text x="-4.6228" y="2.2352" size="1.27" layer="51" ratio="6" rot="SR0">*</text>
<polygon width="0" layer="31">
<vertex x="-3.3782" y="2.3622"/>
<vertex x="-3.3782" y="2.1336"/>
<vertex x="-2.5654" y="2.1336"/>
<vertex x="-2.5654" y="2.3622"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-3.3782" y="1.8542"/>
<vertex x="-3.3782" y="1.6256"/>
<vertex x="-2.5654" y="1.6256"/>
<vertex x="-2.5654" y="1.8542"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-3.3782" y="1.3716"/>
<vertex x="-3.3782" y="1.143"/>
<vertex x="-2.5654" y="1.143"/>
<vertex x="-2.5654" y="1.3716"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-3.3782" y="0.8636"/>
<vertex x="-3.3782" y="0.635"/>
<vertex x="-2.5654" y="0.635"/>
<vertex x="-2.5654" y="0.8636"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-3.3782" y="0.3556"/>
<vertex x="-3.3782" y="0.127"/>
<vertex x="-2.5654" y="0.127"/>
<vertex x="-2.5654" y="0.3556"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-3.3782" y="-0.127"/>
<vertex x="-3.3782" y="-0.3556"/>
<vertex x="-2.5654" y="-0.3556"/>
<vertex x="-2.5654" y="-0.127"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-3.3782" y="-0.635"/>
<vertex x="-3.3782" y="-0.8636"/>
<vertex x="-2.5654" y="-0.8636"/>
<vertex x="-2.5654" y="-0.635"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-3.3782" y="-1.143"/>
<vertex x="-3.3782" y="-1.3716"/>
<vertex x="-2.5654" y="-1.3716"/>
<vertex x="-2.5654" y="-1.143"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-3.3782" y="-1.6256"/>
<vertex x="-3.3782" y="-1.8542"/>
<vertex x="-2.5654" y="-1.8542"/>
<vertex x="-2.5654" y="-1.6256"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-3.3782" y="-2.1336"/>
<vertex x="-3.3782" y="-2.3622"/>
<vertex x="-2.5654" y="-2.3622"/>
<vertex x="-2.5654" y="-2.1336"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-2.3622" y="-2.5654"/>
<vertex x="-2.3622" y="-3.3782"/>
<vertex x="-2.1336" y="-3.3782"/>
<vertex x="-2.1336" y="-2.5654"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-1.8542" y="-2.5654"/>
<vertex x="-1.8542" y="-3.3782"/>
<vertex x="-1.6256" y="-3.3782"/>
<vertex x="-1.6256" y="-2.5654"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-1.3716" y="-2.5654"/>
<vertex x="-1.3716" y="-3.3782"/>
<vertex x="-1.143" y="-3.3782"/>
<vertex x="-1.143" y="-2.5654"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.8636" y="-2.5654"/>
<vertex x="-0.8636" y="-3.3782"/>
<vertex x="-0.635" y="-3.3782"/>
<vertex x="-0.635" y="-2.5654"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.3556" y="-2.5654"/>
<vertex x="-0.3556" y="-3.3782"/>
<vertex x="-0.127" y="-3.3782"/>
<vertex x="-0.127" y="-2.5654"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.127" y="-2.5654"/>
<vertex x="0.127" y="-3.3782"/>
<vertex x="0.3556" y="-3.3782"/>
<vertex x="0.3556" y="-2.5654"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.635" y="-2.5654"/>
<vertex x="0.635" y="-3.3782"/>
<vertex x="0.8636" y="-3.3782"/>
<vertex x="0.8636" y="-2.5654"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.143" y="-2.5654"/>
<vertex x="1.143" y="-3.3782"/>
<vertex x="1.3716" y="-3.3782"/>
<vertex x="1.3716" y="-2.5654"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.6256" y="-2.5654"/>
<vertex x="1.6256" y="-3.3782"/>
<vertex x="1.8542" y="-3.3782"/>
<vertex x="1.8542" y="-2.5654"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.1336" y="-2.5654"/>
<vertex x="2.1336" y="-3.3782"/>
<vertex x="2.3622" y="-3.3782"/>
<vertex x="2.3622" y="-2.5654"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.5654" y="-2.1336"/>
<vertex x="2.5654" y="-2.3622"/>
<vertex x="3.3782" y="-2.3622"/>
<vertex x="3.3782" y="-2.1336"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.5654" y="-1.6256"/>
<vertex x="2.5654" y="-1.8542"/>
<vertex x="3.3782" y="-1.8542"/>
<vertex x="3.3782" y="-1.6256"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.5654" y="-1.143"/>
<vertex x="2.5654" y="-1.3716"/>
<vertex x="3.3782" y="-1.3716"/>
<vertex x="3.3782" y="-1.143"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.5654" y="-0.635"/>
<vertex x="2.5654" y="-0.8636"/>
<vertex x="3.3782" y="-0.8636"/>
<vertex x="3.3782" y="-0.635"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.5654" y="-0.127"/>
<vertex x="2.5654" y="-0.3556"/>
<vertex x="3.3782" y="-0.3556"/>
<vertex x="3.3782" y="-0.127"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.5654" y="0.3556"/>
<vertex x="2.5654" y="0.127"/>
<vertex x="3.3782" y="0.127"/>
<vertex x="3.3782" y="0.3556"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.5654" y="0.8636"/>
<vertex x="2.5654" y="0.635"/>
<vertex x="3.3782" y="0.635"/>
<vertex x="3.3782" y="0.8636"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.5654" y="1.3716"/>
<vertex x="2.5654" y="1.143"/>
<vertex x="3.3782" y="1.143"/>
<vertex x="3.3782" y="1.3716"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.5654" y="1.8542"/>
<vertex x="2.5654" y="1.6256"/>
<vertex x="3.3782" y="1.6256"/>
<vertex x="3.3782" y="1.8542"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.5654" y="2.3622"/>
<vertex x="2.5654" y="2.1336"/>
<vertex x="3.3782" y="2.1336"/>
<vertex x="3.3782" y="2.3622"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="2.1336" y="3.3782"/>
<vertex x="2.1336" y="2.5654"/>
<vertex x="2.3622" y="2.5654"/>
<vertex x="2.3622" y="3.3782"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.6256" y="3.3782"/>
<vertex x="1.6256" y="2.5654"/>
<vertex x="1.8542" y="2.5654"/>
<vertex x="1.8542" y="3.3782"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.143" y="3.3782"/>
<vertex x="1.143" y="2.5654"/>
<vertex x="1.3716" y="2.5654"/>
<vertex x="1.3716" y="3.3782"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.635" y="3.3782"/>
<vertex x="0.635" y="2.5654"/>
<vertex x="0.8636" y="2.5654"/>
<vertex x="0.8636" y="3.3782"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.127" y="3.3782"/>
<vertex x="0.127" y="2.5654"/>
<vertex x="0.3556" y="2.5654"/>
<vertex x="0.3556" y="3.3782"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.3556" y="3.3782"/>
<vertex x="-0.3556" y="2.5654"/>
<vertex x="-0.127" y="2.5654"/>
<vertex x="-0.127" y="3.3782"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.8636" y="3.3782"/>
<vertex x="-0.8636" y="2.5654"/>
<vertex x="-0.635" y="2.5654"/>
<vertex x="-0.635" y="3.3782"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-1.3716" y="3.3782"/>
<vertex x="-1.3716" y="2.5654"/>
<vertex x="-1.143" y="2.5654"/>
<vertex x="-1.143" y="3.3782"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-1.8542" y="3.3782"/>
<vertex x="-1.8542" y="2.5654"/>
<vertex x="-1.6256" y="2.5654"/>
<vertex x="-1.6256" y="3.3782"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-2.3622" y="3.3782"/>
<vertex x="-2.3622" y="2.5654"/>
<vertex x="-2.1336" y="2.5654"/>
<vertex x="-2.1336" y="3.3782"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-2.0066" y="2.0066"/>
<vertex x="-2.0066" y="1.6764"/>
<vertex x="-1.8288" y="1.6764"/>
<vertex x="-1.6764" y="1.8288"/>
<vertex x="-1.6764" y="2.0066"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-2.0066" y="1.4732"/>
<vertex x="-2.0066" y="0.889"/>
<vertex x="-1.8288" y="0.889"/>
<vertex x="-1.6764" y="1.0414"/>
<vertex x="-1.6764" y="1.3208"/>
<vertex x="-1.8288" y="1.4732"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-2.0066" y="0.6858"/>
<vertex x="-2.0066" y="0.1016"/>
<vertex x="-1.8288" y="0.1016"/>
<vertex x="-1.6764" y="0.254"/>
<vertex x="-1.6764" y="0.5334"/>
<vertex x="-1.8288" y="0.6858"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-2.0066" y="-0.1016"/>
<vertex x="-2.0066" y="-0.6858"/>
<vertex x="-1.8288" y="-0.6858"/>
<vertex x="-1.6764" y="-0.5334"/>
<vertex x="-1.6764" y="-0.254"/>
<vertex x="-1.8288" y="-0.1016"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-2.0066" y="-0.889"/>
<vertex x="-2.0066" y="-1.4732"/>
<vertex x="-1.8288" y="-1.4732"/>
<vertex x="-1.6764" y="-1.3208"/>
<vertex x="-1.6764" y="-1.0414"/>
<vertex x="-1.8288" y="-0.889"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-2.0066" y="-1.6764"/>
<vertex x="-2.0066" y="-2.0066"/>
<vertex x="-1.6764" y="-2.0066"/>
<vertex x="-1.6764" y="-1.8288"/>
<vertex x="-1.8288" y="-1.6764"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-1.4732" y="2.0066"/>
<vertex x="-1.4732" y="1.8288"/>
<vertex x="-1.3208" y="1.6764"/>
<vertex x="-1.0414" y="1.6764"/>
<vertex x="-0.889" y="1.8288"/>
<vertex x="-0.889" y="2.0066"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-1.3208" y="1.4732"/>
<vertex x="-1.4732" y="1.3208"/>
<vertex x="-1.4732" y="1.0414"/>
<vertex x="-1.3208" y="0.889"/>
<vertex x="-1.0414" y="0.889"/>
<vertex x="-0.889" y="1.0414"/>
<vertex x="-0.889" y="1.3208"/>
<vertex x="-1.0414" y="1.4732"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-1.3208" y="0.6858"/>
<vertex x="-1.4732" y="0.5334"/>
<vertex x="-1.4732" y="0.254"/>
<vertex x="-1.3208" y="0.1016"/>
<vertex x="-1.0414" y="0.1016"/>
<vertex x="-0.889" y="0.254"/>
<vertex x="-0.889" y="0.5334"/>
<vertex x="-1.0414" y="0.6858"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-1.3208" y="-0.1016"/>
<vertex x="-1.4732" y="-0.254"/>
<vertex x="-1.4732" y="-0.5334"/>
<vertex x="-1.3208" y="-0.6858"/>
<vertex x="-1.0414" y="-0.6858"/>
<vertex x="-0.889" y="-0.5334"/>
<vertex x="-0.889" y="-0.254"/>
<vertex x="-1.0414" y="-0.1016"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-1.3208" y="-0.889"/>
<vertex x="-1.4732" y="-1.0414"/>
<vertex x="-1.4732" y="-1.3208"/>
<vertex x="-1.3208" y="-1.4732"/>
<vertex x="-1.0414" y="-1.4732"/>
<vertex x="-0.889" y="-1.3208"/>
<vertex x="-0.889" y="-1.0414"/>
<vertex x="-1.0414" y="-0.889"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-1.3208" y="-1.6764"/>
<vertex x="-1.4732" y="-1.8288"/>
<vertex x="-1.4732" y="-2.0066"/>
<vertex x="-0.889" y="-2.0066"/>
<vertex x="-0.889" y="-1.8288"/>
<vertex x="-1.0414" y="-1.6764"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.6858" y="2.0066"/>
<vertex x="-0.6858" y="1.8288"/>
<vertex x="-0.5334" y="1.6764"/>
<vertex x="-0.254" y="1.6764"/>
<vertex x="-0.1016" y="1.8288"/>
<vertex x="-0.1016" y="2.0066"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.5334" y="1.4732"/>
<vertex x="-0.6858" y="1.3208"/>
<vertex x="-0.6858" y="1.0414"/>
<vertex x="-0.5334" y="0.889"/>
<vertex x="-0.254" y="0.889"/>
<vertex x="-0.1016" y="1.0414"/>
<vertex x="-0.1016" y="1.3208"/>
<vertex x="-0.254" y="1.4732"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.5334" y="0.6858"/>
<vertex x="-0.6858" y="0.5334"/>
<vertex x="-0.6858" y="0.254"/>
<vertex x="-0.5334" y="0.1016"/>
<vertex x="-0.254" y="0.1016"/>
<vertex x="-0.1016" y="0.254"/>
<vertex x="-0.1016" y="0.5334"/>
<vertex x="-0.254" y="0.6858"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.5334" y="-0.1016"/>
<vertex x="-0.6858" y="-0.254"/>
<vertex x="-0.6858" y="-0.5334"/>
<vertex x="-0.5334" y="-0.6858"/>
<vertex x="-0.254" y="-0.6858"/>
<vertex x="-0.1016" y="-0.5334"/>
<vertex x="-0.1016" y="-0.254"/>
<vertex x="-0.254" y="-0.1016"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.5334" y="-0.889"/>
<vertex x="-0.6858" y="-1.0414"/>
<vertex x="-0.6858" y="-1.3208"/>
<vertex x="-0.5334" y="-1.4732"/>
<vertex x="-0.254" y="-1.4732"/>
<vertex x="-0.1016" y="-1.3208"/>
<vertex x="-0.1016" y="-1.0414"/>
<vertex x="-0.254" y="-0.889"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="-0.5334" y="-1.6764"/>
<vertex x="-0.6858" y="-1.8288"/>
<vertex x="-0.6858" y="-2.0066"/>
<vertex x="-0.1016" y="-2.0066"/>
<vertex x="-0.1016" y="-1.8288"/>
<vertex x="-0.254" y="-1.6764"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.1016" y="2.0066"/>
<vertex x="0.1016" y="1.8288"/>
<vertex x="0.254" y="1.6764"/>
<vertex x="0.5334" y="1.6764"/>
<vertex x="0.6858" y="1.8288"/>
<vertex x="0.6858" y="2.0066"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.254" y="1.4732"/>
<vertex x="0.1016" y="1.3208"/>
<vertex x="0.1016" y="1.0414"/>
<vertex x="0.254" y="0.889"/>
<vertex x="0.5334" y="0.889"/>
<vertex x="0.6858" y="1.0414"/>
<vertex x="0.6858" y="1.3208"/>
<vertex x="0.5334" y="1.4732"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.254" y="0.6858"/>
<vertex x="0.1016" y="0.5334"/>
<vertex x="0.1016" y="0.254"/>
<vertex x="0.254" y="0.1016"/>
<vertex x="0.5334" y="0.1016"/>
<vertex x="0.6858" y="0.254"/>
<vertex x="0.6858" y="0.5334"/>
<vertex x="0.5334" y="0.6858"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.254" y="-0.1016"/>
<vertex x="0.1016" y="-0.254"/>
<vertex x="0.1016" y="-0.5334"/>
<vertex x="0.254" y="-0.6858"/>
<vertex x="0.5334" y="-0.6858"/>
<vertex x="0.6858" y="-0.5334"/>
<vertex x="0.6858" y="-0.254"/>
<vertex x="0.5334" y="-0.1016"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.254" y="-0.889"/>
<vertex x="0.1016" y="-1.0414"/>
<vertex x="0.1016" y="-1.3208"/>
<vertex x="0.254" y="-1.4732"/>
<vertex x="0.5334" y="-1.4732"/>
<vertex x="0.6858" y="-1.3208"/>
<vertex x="0.6858" y="-1.0414"/>
<vertex x="0.5334" y="-0.889"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.254" y="-1.6764"/>
<vertex x="0.1016" y="-1.8288"/>
<vertex x="0.1016" y="-2.0066"/>
<vertex x="0.6858" y="-2.0066"/>
<vertex x="0.6858" y="-1.8288"/>
<vertex x="0.5334" y="-1.6764"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="0.889" y="2.0066"/>
<vertex x="0.889" y="1.8288"/>
<vertex x="1.0414" y="1.6764"/>
<vertex x="1.3208" y="1.6764"/>
<vertex x="1.4732" y="1.8288"/>
<vertex x="1.4732" y="2.0066"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.0414" y="1.4732"/>
<vertex x="0.889" y="1.3208"/>
<vertex x="0.889" y="1.0414"/>
<vertex x="1.0414" y="0.889"/>
<vertex x="1.3208" y="0.889"/>
<vertex x="1.4732" y="1.0414"/>
<vertex x="1.4732" y="1.3208"/>
<vertex x="1.3208" y="1.4732"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.0414" y="0.6858"/>
<vertex x="0.889" y="0.5334"/>
<vertex x="0.889" y="0.254"/>
<vertex x="1.0414" y="0.1016"/>
<vertex x="1.3208" y="0.1016"/>
<vertex x="1.4732" y="0.254"/>
<vertex x="1.4732" y="0.5334"/>
<vertex x="1.3208" y="0.6858"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.0414" y="-0.1016"/>
<vertex x="0.889" y="-0.254"/>
<vertex x="0.889" y="-0.5334"/>
<vertex x="1.0414" y="-0.6858"/>
<vertex x="1.3208" y="-0.6858"/>
<vertex x="1.4732" y="-0.5334"/>
<vertex x="1.4732" y="-0.254"/>
<vertex x="1.3208" y="-0.1016"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.0414" y="-0.889"/>
<vertex x="0.889" y="-1.0414"/>
<vertex x="0.889" y="-1.3208"/>
<vertex x="1.0414" y="-1.4732"/>
<vertex x="1.3208" y="-1.4732"/>
<vertex x="1.4732" y="-1.3208"/>
<vertex x="1.4732" y="-1.0414"/>
<vertex x="1.3208" y="-0.889"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.0414" y="-1.6764"/>
<vertex x="0.889" y="-1.8288"/>
<vertex x="0.889" y="-2.0066"/>
<vertex x="1.4732" y="-2.0066"/>
<vertex x="1.4732" y="-1.8288"/>
<vertex x="1.3208" y="-1.6764"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.6764" y="2.0066"/>
<vertex x="1.6764" y="1.8288"/>
<vertex x="1.8288" y="1.6764"/>
<vertex x="2.0066" y="1.6764"/>
<vertex x="2.0066" y="2.0066"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.8288" y="1.4732"/>
<vertex x="1.6764" y="1.3208"/>
<vertex x="1.6764" y="1.0414"/>
<vertex x="1.8288" y="0.889"/>
<vertex x="2.0066" y="0.889"/>
<vertex x="2.0066" y="1.4732"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.8288" y="0.6858"/>
<vertex x="1.6764" y="0.5334"/>
<vertex x="1.6764" y="0.254"/>
<vertex x="1.8288" y="0.1016"/>
<vertex x="2.0066" y="0.1016"/>
<vertex x="2.0066" y="0.6858"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.8288" y="-0.1016"/>
<vertex x="1.6764" y="-0.254"/>
<vertex x="1.6764" y="-0.5334"/>
<vertex x="1.8288" y="-0.6858"/>
<vertex x="2.0066" y="-0.6858"/>
<vertex x="2.0066" y="-0.1016"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.8288" y="-0.889"/>
<vertex x="1.6764" y="-1.0414"/>
<vertex x="1.6764" y="-1.3208"/>
<vertex x="1.8288" y="-1.4732"/>
<vertex x="2.0066" y="-1.4732"/>
<vertex x="2.0066" y="-0.889"/>
</polygon>
<polygon width="0" layer="31">
<vertex x="1.8288" y="-1.6764"/>
<vertex x="1.6764" y="-1.8288"/>
<vertex x="1.6764" y="-2.0066"/>
<vertex x="2.0066" y="-2.0066"/>
<vertex x="2.0066" y="-1.6764"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-3.4798" y="2.4638"/>
<vertex x="-3.4798" y="2.032"/>
<vertex x="-2.4892" y="2.032"/>
<vertex x="-2.4892" y="2.4638"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-3.4798" y="1.9558"/>
<vertex x="-3.4798" y="1.5494"/>
<vertex x="-2.4892" y="1.5494"/>
<vertex x="-2.4892" y="1.9558"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-3.4798" y="1.4478"/>
<vertex x="-3.4798" y="1.0414"/>
<vertex x="-2.4892" y="1.0414"/>
<vertex x="-2.4892" y="1.4478"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-3.4798" y="0.9652"/>
<vertex x="-3.4798" y="0.5334"/>
<vertex x="-2.4892" y="0.5334"/>
<vertex x="-2.4892" y="0.9652"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-3.4798" y="0.4572"/>
<vertex x="-3.4798" y="0.0508"/>
<vertex x="-2.4892" y="0.0508"/>
<vertex x="-2.4892" y="0.4572"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-3.4798" y="-0.0508"/>
<vertex x="-3.4798" y="-0.4572"/>
<vertex x="-2.4892" y="-0.4572"/>
<vertex x="-2.4892" y="-0.0508"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-3.4798" y="-0.5334"/>
<vertex x="-3.4798" y="-0.9652"/>
<vertex x="-2.4892" y="-0.9652"/>
<vertex x="-2.4892" y="-0.5334"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-3.4798" y="-1.0414"/>
<vertex x="-3.4798" y="-1.4478"/>
<vertex x="-2.4892" y="-1.4478"/>
<vertex x="-2.4892" y="-1.0414"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-3.4798" y="-1.5494"/>
<vertex x="-3.4798" y="-1.9558"/>
<vertex x="-2.4892" y="-1.9558"/>
<vertex x="-2.4892" y="-1.5494"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-3.4798" y="-2.032"/>
<vertex x="-3.4798" y="-2.4638"/>
<vertex x="-2.4892" y="-2.4638"/>
<vertex x="-2.4892" y="-2.032"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-2.4638" y="-2.4892"/>
<vertex x="-2.4638" y="-3.4798"/>
<vertex x="-2.032" y="-3.4798"/>
<vertex x="-2.032" y="-2.4892"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-1.9558" y="-2.4892"/>
<vertex x="-1.9558" y="-3.4798"/>
<vertex x="-1.5494" y="-3.4798"/>
<vertex x="-1.5494" y="-2.4892"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-1.4478" y="-2.4892"/>
<vertex x="-1.4478" y="-3.4798"/>
<vertex x="-1.0414" y="-3.4798"/>
<vertex x="-1.0414" y="-2.4892"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-0.9652" y="-2.4892"/>
<vertex x="-0.9652" y="-3.4798"/>
<vertex x="-0.5334" y="-3.4798"/>
<vertex x="-0.5334" y="-2.4892"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-0.4572" y="-2.4892"/>
<vertex x="-0.4572" y="-3.4798"/>
<vertex x="-0.0508" y="-3.4798"/>
<vertex x="-0.0508" y="-2.4892"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="0.0508" y="-2.4892"/>
<vertex x="0.0508" y="-3.4798"/>
<vertex x="0.4572" y="-3.4798"/>
<vertex x="0.4572" y="-2.4892"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="0.5334" y="-2.4892"/>
<vertex x="0.5334" y="-3.4798"/>
<vertex x="0.9652" y="-3.4798"/>
<vertex x="0.9652" y="-2.4892"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="1.0414" y="-2.4892"/>
<vertex x="1.0414" y="-3.4798"/>
<vertex x="1.4478" y="-3.4798"/>
<vertex x="1.4478" y="-2.4892"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="1.5494" y="-2.4892"/>
<vertex x="1.5494" y="-3.4798"/>
<vertex x="1.9558" y="-3.4798"/>
<vertex x="1.9558" y="-2.4892"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.032" y="-2.4892"/>
<vertex x="2.032" y="-3.4798"/>
<vertex x="2.4638" y="-3.4798"/>
<vertex x="2.4638" y="-2.4892"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.4892" y="-2.032"/>
<vertex x="2.4892" y="-2.4638"/>
<vertex x="3.4798" y="-2.4638"/>
<vertex x="3.4798" y="-2.032"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.4892" y="-1.5494"/>
<vertex x="2.4892" y="-1.9558"/>
<vertex x="3.4798" y="-1.9558"/>
<vertex x="3.4798" y="-1.5494"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.4892" y="-1.0414"/>
<vertex x="2.4892" y="-1.4478"/>
<vertex x="3.4798" y="-1.4478"/>
<vertex x="3.4798" y="-1.0414"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.4892" y="-0.5334"/>
<vertex x="2.4892" y="-0.9652"/>
<vertex x="3.4798" y="-0.9652"/>
<vertex x="3.4798" y="-0.5334"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.4892" y="-0.0508"/>
<vertex x="2.4892" y="-0.4572"/>
<vertex x="3.4798" y="-0.4572"/>
<vertex x="3.4798" y="-0.0508"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.4892" y="0.4572"/>
<vertex x="2.4892" y="0.0508"/>
<vertex x="3.4798" y="0.0508"/>
<vertex x="3.4798" y="0.4572"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.4892" y="0.9652"/>
<vertex x="2.4892" y="0.5334"/>
<vertex x="3.4798" y="0.5334"/>
<vertex x="3.4798" y="0.9652"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.4892" y="1.4478"/>
<vertex x="2.4892" y="1.0414"/>
<vertex x="3.4798" y="1.0414"/>
<vertex x="3.4798" y="1.4478"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.4892" y="1.9558"/>
<vertex x="2.4892" y="1.5494"/>
<vertex x="3.4798" y="1.5494"/>
<vertex x="3.4798" y="1.9558"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.4892" y="2.4638"/>
<vertex x="2.4892" y="2.032"/>
<vertex x="3.4798" y="2.032"/>
<vertex x="3.4798" y="2.4638"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="2.032" y="3.4798"/>
<vertex x="2.032" y="2.4892"/>
<vertex x="2.4638" y="2.4892"/>
<vertex x="2.4638" y="3.4798"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="1.5494" y="3.4798"/>
<vertex x="1.5494" y="2.4892"/>
<vertex x="1.9558" y="2.4892"/>
<vertex x="1.9558" y="3.4798"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="1.0414" y="3.4798"/>
<vertex x="1.0414" y="2.4892"/>
<vertex x="1.4478" y="2.4892"/>
<vertex x="1.4478" y="3.4798"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="0.5334" y="3.4798"/>
<vertex x="0.5334" y="2.4892"/>
<vertex x="0.9652" y="2.4892"/>
<vertex x="0.9652" y="3.4798"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="0.0508" y="3.4798"/>
<vertex x="0.0508" y="2.4892"/>
<vertex x="0.4572" y="2.4892"/>
<vertex x="0.4572" y="3.4798"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-0.4572" y="3.4798"/>
<vertex x="-0.4572" y="2.4892"/>
<vertex x="-0.0508" y="2.4892"/>
<vertex x="-0.0508" y="3.4798"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-0.9652" y="3.4798"/>
<vertex x="-0.9652" y="2.4892"/>
<vertex x="-0.5334" y="2.4892"/>
<vertex x="-0.5334" y="3.4798"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-1.4478" y="3.4798"/>
<vertex x="-1.4478" y="2.4892"/>
<vertex x="-1.0414" y="2.4892"/>
<vertex x="-1.0414" y="3.4798"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-1.9558" y="3.4798"/>
<vertex x="-1.9558" y="2.4892"/>
<vertex x="-1.5494" y="2.4892"/>
<vertex x="-1.5494" y="3.4798"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-2.4638" y="3.4798"/>
<vertex x="-2.4638" y="2.4892"/>
<vertex x="-2.032" y="2.4892"/>
<vertex x="-2.032" y="3.4798"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-2.1336" y="2.1336"/>
<vertex x="2.1336" y="2.1336"/>
<vertex x="2.1336" y="1.778"/>
<vertex x="-2.1336" y="1.778"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-2.1336" y="1.3716"/>
<vertex x="2.1336" y="1.3716"/>
<vertex x="2.1336" y="0.9906"/>
<vertex x="-2.1336" y="0.9906"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-2.1336" y="0.5842"/>
<vertex x="2.1336" y="0.5842"/>
<vertex x="2.1336" y="0.2032"/>
<vertex x="-2.1336" y="0.2032"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-2.1336" y="-0.2032"/>
<vertex x="2.1336" y="-0.2032"/>
<vertex x="2.1336" y="-0.5842"/>
<vertex x="-2.1336" y="-0.5842"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-2.1336" y="-0.9906"/>
<vertex x="2.1336" y="-0.9906"/>
<vertex x="2.1336" y="-1.3716"/>
<vertex x="-2.1336" y="-1.3716"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-2.1336" y="-1.778"/>
<vertex x="2.1336" y="-1.778"/>
<vertex x="2.1336" y="-2.1336"/>
<vertex x="-2.1336" y="-2.1336"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-2.1336" y="2.1336"/>
<vertex x="-1.778" y="2.1336"/>
<vertex x="-1.778" y="-2.1336"/>
<vertex x="-2.1336" y="-2.1336"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-0.9906" y="2.1336"/>
<vertex x="-1.3716" y="2.1336"/>
<vertex x="-1.3716" y="-2.1336"/>
<vertex x="-0.9906" y="-2.1336"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="-0.2032" y="2.1336"/>
<vertex x="-0.5842" y="2.1336"/>
<vertex x="-0.5842" y="-2.1336"/>
<vertex x="-0.2032" y="-2.1336"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="0.5842" y="2.1336"/>
<vertex x="0.2032" y="2.1336"/>
<vertex x="0.2032" y="-2.1336"/>
<vertex x="0.5842" y="-2.1336"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="1.3716" y="2.1336"/>
<vertex x="0.9906" y="2.1336"/>
<vertex x="0.9906" y="-2.1336"/>
<vertex x="1.3716" y="-2.1336"/>
</polygon>
<polygon width="0" layer="29">
<vertex x="1.778" y="2.1336"/>
<vertex x="2.1336" y="2.1336"/>
<vertex x="2.1336" y="-2.1336"/>
<vertex x="1.778" y="-2.1336"/>
</polygon>
<wire x1="-3.0734" y1="1.8034" x2="-1.8034" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="2.3622" y1="3.0734" x2="2.1336" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="1.8542" y1="3.0734" x2="1.6256" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="1.3716" y1="3.0734" x2="1.143" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="0.8636" y1="3.0734" x2="0.635" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="0.3556" y1="3.0734" x2="0.127" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="-0.127" y1="3.0734" x2="-0.3556" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="3.0734" x2="-0.8636" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="-1.143" y1="3.0734" x2="-1.3716" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="-1.6256" y1="3.0734" x2="-1.8542" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="-2.1336" y1="3.0734" x2="-2.3622" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="2.3622" x2="-3.0734" y2="2.1336" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="1.8542" x2="-3.0734" y2="1.6256" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="1.3716" x2="-3.0734" y2="1.143" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="0.8636" x2="-3.0734" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="0.3556" x2="-3.0734" y2="0.127" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="-0.127" x2="-3.0734" y2="-0.3556" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="-0.635" x2="-3.0734" y2="-0.8636" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="-1.143" x2="-3.0734" y2="-1.3716" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="-1.6256" x2="-3.0734" y2="-1.8542" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="-2.1336" x2="-3.0734" y2="-2.3622" width="0.1524" layer="21"/>
<wire x1="-2.3622" y1="-3.0734" x2="-2.1336" y2="-3.0734" width="0.1524" layer="21"/>
<wire x1="-1.8542" y1="-3.0734" x2="-1.6256" y2="-3.0734" width="0.1524" layer="21"/>
<wire x1="-1.3716" y1="-3.0734" x2="-1.143" y2="-3.0734" width="0.1524" layer="21"/>
<wire x1="-0.8636" y1="-3.0734" x2="-0.635" y2="-3.0734" width="0.1524" layer="21"/>
<wire x1="-0.3556" y1="-3.0734" x2="-0.127" y2="-3.0734" width="0.1524" layer="21"/>
<wire x1="0.127" y1="-3.0734" x2="0.3556" y2="-3.0734" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-3.0734" x2="0.8636" y2="-3.0734" width="0.1524" layer="21"/>
<wire x1="1.143" y1="-3.0734" x2="1.3716" y2="-3.0734" width="0.1524" layer="21"/>
<wire x1="1.6256" y1="-3.0734" x2="1.8542" y2="-3.0734" width="0.1524" layer="21"/>
<wire x1="2.1336" y1="-3.0734" x2="2.3622" y2="-3.0734" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="-2.3622" x2="3.0734" y2="-2.1336" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="-1.8542" x2="3.0734" y2="-1.6256" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="-1.3716" x2="3.0734" y2="-1.143" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="-0.8636" x2="3.0734" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="-0.3556" x2="3.0734" y2="-0.127" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="0.127" x2="3.0734" y2="0.3556" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="0.635" x2="3.0734" y2="0.8636" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="1.143" x2="3.0734" y2="1.3716" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="1.6256" x2="3.0734" y2="1.8542" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="2.1336" x2="3.0734" y2="2.3622" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="-3.0734" x2="3.0734" y2="-3.0734" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="-3.0734" x2="3.0734" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="3.0734" y1="3.0734" x2="-3.0734" y2="3.0734" width="0.1524" layer="21"/>
<wire x1="-3.0734" y1="3.0734" x2="-3.0734" y2="-3.0734" width="0.1524" layer="21"/>
<text x="-4.6228" y="2.2352" size="1.27" layer="21" ratio="6" rot="SR0">*</text>
<text x="-2.8702" y="-0.635" size="1.27" layer="25" ratio="6" rot="SR0">&gt;NAME</text>
<text x="-3.4544" y="-0.635" size="1.27" layer="27" ratio="6" rot="SR0">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="AFE4400_RHA_40">
<pin name="BG" x="0" y="0" direction="pas"/>
<pin name="VCM" x="0" y="-2.54" direction="in"/>
<pin name="TXN" x="0" y="-5.08" direction="out"/>
<pin name="TXP" x="0" y="-7.62" direction="out"/>
<pin name="SCLK" x="0" y="-10.16" direction="pas"/>
<pin name="PD_ALM" x="0" y="-12.7" direction="out"/>
<pin name="SPISTE" x="0" y="-15.24" direction="pas"/>
<pin name="TX_REF" x="0" y="-17.78" direction="pas"/>
<pin name="*RESET" x="0" y="-20.32" direction="in"/>
<pin name="ADC_RDY" x="0" y="-22.86" direction="out"/>
<pin name="LED_ALM" x="0" y="-25.4" direction="out"/>
<pin name="DIAG_END" x="0" y="-27.94" direction="out"/>
<pin name="AFE_*PDN" x="0" y="-30.48" direction="in"/>
<pin name="INN" x="0" y="-35.56" direction="in"/>
<pin name="XIN" x="0" y="-38.1" direction="in"/>
<pin name="SPISOMI" x="0" y="-40.64" direction="in"/>
<pin name="RX_ANA_GND_2" x="0" y="-45.72" direction="pwr"/>
<pin name="RX_ANA_GND_3" x="0" y="-48.26" direction="pas"/>
<pin name="RX_ANA_GND" x="0" y="-50.8" direction="pas"/>
<pin name="RX_DIG_GND_2" x="0" y="-53.34" direction="pas"/>
<pin name="RX_DIG_GND" x="0" y="-55.88" direction="pas"/>
<pin name="LED_DRV_GND_2" x="0" y="-58.42" direction="pas"/>
<pin name="LED_DRV_GND_3" x="0" y="-60.96" direction="pas"/>
<pin name="LED_DRV_GND" x="0" y="-63.5" direction="pas"/>
<pin name="INP" x="91.44" y="-48.26" direction="in" rot="R180"/>
<pin name="XOUT" x="91.44" y="-45.72" direction="out" rot="R180"/>
<pin name="CLKOUT" x="91.44" y="-43.18" direction="out" rot="R180"/>
<pin name="SPISIMO" x="91.44" y="-40.64" direction="out" rot="R180"/>
<pin name="RX_ANA_SUP_2" x="91.44" y="-35.56" direction="pas" rot="R180"/>
<pin name="RX_ANA_SUP" x="91.44" y="-33.02" direction="pas" rot="R180"/>
<pin name="RX_DIG_SUP" x="91.44" y="-30.48" direction="pas" rot="R180"/>
<pin name="TX_CTRL_SUP" x="91.44" y="-27.94" direction="pas" rot="R180"/>
<pin name="LED_DRV_SUP_2" x="91.44" y="-25.4" direction="pas" rot="R180"/>
<pin name="LED_DRV_SUP" x="91.44" y="-22.86" direction="pas" rot="R180"/>
<pin name="DNC_2" x="91.44" y="-17.78" direction="nc" rot="R180"/>
<pin name="DNC_3" x="91.44" y="-15.24" direction="nc" rot="R180"/>
<pin name="DNC_4" x="91.44" y="-12.7" direction="nc" rot="R180"/>
<pin name="DNC_5" x="91.44" y="-10.16" direction="nc" rot="R180"/>
<pin name="DNC" x="91.44" y="-7.62" direction="nc" rot="R180"/>
<pin name="VSS" x="91.44" y="-2.54" direction="pwr" rot="R180"/>
<pin name="EPAD" x="91.44" y="0" direction="pas" rot="R180"/>
<wire x1="7.62" y1="5.08" x2="7.62" y2="-68.58" width="0.1524" layer="94"/>
<wire x1="7.62" y1="-68.58" x2="83.82" y2="-68.58" width="0.1524" layer="94"/>
<wire x1="83.82" y1="-68.58" x2="83.82" y2="5.08" width="0.1524" layer="94"/>
<wire x1="83.82" y1="5.08" x2="7.62" y2="5.08" width="0.1524" layer="94"/>
<text x="40.9956" y="9.1186" size="2.0828" layer="95" ratio="6" rot="SR0">&gt;NAME</text>
<text x="40.0558" y="6.5786" size="2.0828" layer="96" ratio="6" rot="SR0">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="AFE4400_RHA_40" prefix="U">
<gates>
<gate name="A" symbol="AFE4400_RHA_40" x="0" y="0"/>
</gates>
<devices>
<device name="" package="RHA40_4P15X4P15">
<connects>
<connect gate="A" pin="*RESET" pad="29"/>
<connect gate="A" pin="ADC_RDY" pad="28"/>
<connect gate="A" pin="AFE_*PDN" pad="20"/>
<connect gate="A" pin="BG" pad="7"/>
<connect gate="A" pin="CLKOUT" pad="30"/>
<connect gate="A" pin="DIAG_END" pad="21"/>
<connect gate="A" pin="DNC" pad="35"/>
<connect gate="A" pin="DNC_2" pad="5"/>
<connect gate="A" pin="DNC_3" pad="6"/>
<connect gate="A" pin="DNC_4" pad="10"/>
<connect gate="A" pin="DNC_5" pad="34"/>
<connect gate="A" pin="EPAD" pad="41"/>
<connect gate="A" pin="INN" pad="1"/>
<connect gate="A" pin="INP" pad="2"/>
<connect gate="A" pin="LED_ALM" pad="22"/>
<connect gate="A" pin="LED_DRV_GND" pad="16"/>
<connect gate="A" pin="LED_DRV_GND_2" pad="12"/>
<connect gate="A" pin="LED_DRV_GND_3" pad="13"/>
<connect gate="A" pin="LED_DRV_SUP" pad="18"/>
<connect gate="A" pin="LED_DRV_SUP_2" pad="17"/>
<connect gate="A" pin="PD_ALM" pad="23"/>
<connect gate="A" pin="RX_ANA_GND" pad="40"/>
<connect gate="A" pin="RX_ANA_GND_2" pad="3"/>
<connect gate="A" pin="RX_ANA_GND_3" pad="36"/>
<connect gate="A" pin="RX_ANA_SUP" pad="39"/>
<connect gate="A" pin="RX_ANA_SUP_2" pad="33"/>
<connect gate="A" pin="RX_DIG_GND" pad="32"/>
<connect gate="A" pin="RX_DIG_GND_2" pad="19"/>
<connect gate="A" pin="RX_DIG_SUP" pad="31"/>
<connect gate="A" pin="SCLK" pad="24"/>
<connect gate="A" pin="SPISIMO" pad="26"/>
<connect gate="A" pin="SPISOMI" pad="25"/>
<connect gate="A" pin="SPISTE" pad="27"/>
<connect gate="A" pin="TXN" pad="14"/>
<connect gate="A" pin="TXP" pad="15"/>
<connect gate="A" pin="TX_CTRL_SUP" pad="11"/>
<connect gate="A" pin="TX_REF" pad="9"/>
<connect gate="A" pin="VCM" pad="4"/>
<connect gate="A" pin="VSS" pad="8"/>
<connect gate="A" pin="XIN" pad="38"/>
<connect gate="A" pin="XOUT" pad="37"/>
</connects>
<technologies>
<technology name="">
<attribute name="MANUFACTURER_PART_NUMBER" value="afe4400_rha_40" constant="no"/>
<attribute name="VENDOR" value="Texas Instruments" constant="no"/>
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
<part name="U1" library="AFE4400" deviceset="AFE4400_RHA_40" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U1" gate="A" x="48.26" y="86.36"/>
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
