ofxCanon
==============
The ofxCanon addon is an implementation of the Canon SDK. The Canon
SDK let you control a Canon camera. This addon has been tested with a 
Canon Eos 400D and 450D on a Mac and on Windows.

The CanonWrapper code which you can find on the forum is not properly 
implemented as it does not seem to take into account that the callback
is done asynchronously.  I've contacted the author and still waiting on a 
reply :-)  Though still you can use this CanonWrapper if you want to 
of course. With a couple of tweaks and custom constraints this wrapper works
perfectly.

The ofxCanon, is just another implementation, based on the same way
the examples canon delivers are implemented. This code is extremely clean and
makes use of design patterns which makes it easy to read.

This addon implements the most basic commands which were enough for me, though
it's very easy to add you own custom/new commands. 

By default the addon lets you take pictures which will be downloaded 
automatically to a folder of your choice.

Note: make sure to switch the camera to the "p" option. (hardware switch)

Windows + Mac Installation
===========================
Add this addon and the ofxCommanPattern addon to your project!


Installation Mac specific
=========================
1. 
Download the Canon SDK from: https://www.didp.canon-europa.com/developer/didp/didp_main.nsf

2. 
Make sure you've applied for a Canon Developers account, which you can do
on that website.

3. 
Login, click on download and find the EDSDK2800CD.dmg and downlaod it 

4. 
Extract this image and copy the files from the "EDSDK > Header" directory
to your project, ./src/lib/EDSK/

5. 
Add the "./" as last item to your search paths (Project > Get Info, search
for "search paths"

6. 
Add the framework to your project. Right click on your project > Add 
> Add existing framework and select the ESDK.Framework directory.
Repeat this for the "DPP.framework" directory.

7. 
Select the "DPP.framework" and "ESDK.framework" frameworks and drag and
drop them on the "Targets > [your project name ] > Copy Files (#) build
phase. This will copy the frameworks to their correct locations inside
your app directory.

8.
Also disable the "Connecting camera opens [appname]" to [no application] in
the iPhoto app. (From the menu > Preferences > General tab)


