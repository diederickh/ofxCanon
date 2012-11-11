ofxCanon
==============
The ofxCanon is a wrapper around the EDSDK from Canon to control most of the 
Canon cameras. This addon has been tested with a Canon EOS 400D and 450D on 
Mac only. This simple branch needs to be updated for Windows.
This branch has been updated to openFrameoworks 007.

Installation on Mac 
=====================
1.
Download the Canon SDK from: https://www.didp.canon-europa.com/developer/didp/didp_main.nsf

2.
Make sure you've applied for a Canon Developers account, which you can do
on that website.

3.
Login, click on download and find the EDSDK21000CD.dmg and downlaod it


================================================================================
See the openFrameworks_ofxCanon.pdf file for a step by step installation guide
================================================================================


Installation on Windows
=========================

1. Download ofxCanon files from https://github.com/roxlu/ofxCanon. Optional: unzip the files in <oF directory>/addons/ofxCanon

2. Apply for a Canon Developers account and download the SDK (e.g. EDSDKv2.8.zip)

3. Create a new openFrameworks project by duplicating apps/myApps/emptyExample

4. Open the project in CodeBlocks (v. 10.05)

5. Click on Project > Build Options...

6. Make sure to select your project name on the left, not release or debug, then click on the tab Search directories

7. Click on Add and search for the ofxCanon/src folder (e.g. ..\..\..\addons\ofxCanon\src)

8. Click on Add again and search for the EDSDK/Header folder (e.g. ..\..\..\..\..\canon\EDSDKv2.8\EDSDK\Header)

9. Move to the Linker settings tab, click on Add and search for the EDSDK.lib file (e.g. ..\..\..\..\..\canon\EDSDKv2.8\EDSDK\Library\EDSDK.lib)

10. Click on Project > Add files recursively... and add both ofxCanon/src and EDSDK/Header. More info: http://forum.openframeworks.cc/index.php/topic,3090.0.html

11. Copy the files from EDSDK/Dll to myApps/<your project>/bin

12. Refer to ofxCanon/example to test your project.
