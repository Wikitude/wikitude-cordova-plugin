# Augmented Reality - Wikitude SDK Plugin
by Wikitude GmbH - [www.wikitude.com](http://www.wikitude.com)

Interested in advanced usage of the plugin and need assistance? 
[Register as a Wikitude developer](http://developer.wikitude.com) and get support in our forum.

For further questions visit us on www.wikitude.com or contact us via `phonegap <at> wikitude.com`

#### Important: This plugin runs on latest [PhoneGap 2.4](http://docs.phonegap.com/en/2.4.0/index.html) only


## DESCRIPTION 


The Wikitude PhoneGap Plugin enables web developers to embed an Augmented Reality view into their PhoneGap project. One can create a fully featured app with advanced Augmented Reality features, including Image Recognition, purely using HTML, CSS and Javascript.

###The Wikitude PhoneGap Plugin

* Available for iOS and Android
* Simple and seamless native PhoneGap integration
* Fully customizable Augmented Realty view
* Includes the full feature set of the Wikitude SDK
* AR content is purely written in HTML and JavaScript

![image](http://www.wikitude.com/wp-content/uploads/2012/09/Plugin_Phonegap.png)

###The Augmented Reality View
From a technical point of view the SDK adds a UI component, similar to a web view. In contrast to a standard web view this AR view can render Augmented Reality content.

Note: Content developed for this AR View is written in JavaScript and HTML. The .html and .js files for this view are different from the PhoneGap .js and .html files. The AR engine working in the background is called ARchitect Engine and is powering the SDK.

###Further developer resources
* [Full documentation and additional tutorials](http://forum.wikitude.com/documentation)
* [Developer Forum](http://forum.wikitude.com/home)
* [Wikitude SDK Download](http://forum.wikitude.com/download)
* [Google+ Page for News](https://plus.google.com/u/0/103004921345651739447/posts)
* [Developer Newsletter](http://www.wikitude.com/developer/newsletter)



## SETUP

* Create a new PhoneGap project with the command line tool provided by PhoneGap.
* Copy the WTWikitudePlugin and WTARViewController into your PhoneGap project folder ```Plugins/Wikitude``` and add them to your Xcode project.
* Add the following line to PhoneGap's config.xml file. ```<plugin name="WikitudePlugin" value="WTWikitudePlugin" />```
* Add the Wikitude SDK framework to your project. To add the framework, you can drag'n drop it into your projects ```Framework``` folder (Copy the framework into your project folder before to keep everything nice and tidy).
* Add the Following iOS Frameworks to your project:
	
	* libc++.dylib

	* libz.dylib

	* libsqlite3.dylib 

	* CoreMotion.framework

	* CoreVideo.framework

	* OpenGLES.framework

	* Security.framework
	
	
* Check if the ```'-all_load'``` linker flag is set in your projects linker settings. If so, please remove it and replace it with the following flag instead ```'-force_load $(BUILT_PRODUCTS_DIR)/libCordova.a'```.

	* if you want to use Image Recognition within your App, you need to copy the Vuforia SDK folder into a folder like ```[ProjectFolder/"AppName"/Vuforia]```. Also dont forget to add the files to your Xcode project. You can download the Vuforia SDK from [Qualcomm's](https://developer.vuforia.com/resources/sdk/ios) website.

* The last step is to edit the whitelist entries. Open the Cordova.plist and add a new entry to the 'ExternalHosts' Array: * (single Asterisk)

You can always have a look at the sample projects provided by Wikitude if you have problems setting up your own project.



## JAVASCRIPT INTERFACE
	
Its simple to use the Wikitude Plugin within your PhoneGap application.

We wrapped all ``` cordova.exec	 ``` calls into a separate JavaScript wrapper which handles location updates and some more functionality behind the scenes.

You will mainly work with the ``` WikitudePlugin ``` where all you have to do is to call ```Wikitude.isDeviceReady(successCallback, errorCallback)``` and in your successCallback, you can call ```WikitudePlugin.loadARchitectWorld(successCallback, errorCallback, "path/to/your/world")```.

If you want to communicate directly via the ```cordova.exec``` JavaScript calls, have a look at the ```Documentation``` folder which includes more information about that.
	

## Getting STARTED

To get started, we prepared two sample projects. You can read through these samples to understand how to use the JavaScript wrapper and how you add your ARchitect World to your project. There is also a ReadMe for both projects which explains what you have to do to get them running.

Note:
If you have purchased a Wikitude SDK license, you can enter you SDK Key in the ```WikitudePlugin.js``` file at line 9.


## LICENSE

   Copyright 2012 [Wikitude GmbH ](http://www.wikitude.com)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.