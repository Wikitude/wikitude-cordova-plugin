
# Augmented Reality - Wikitude SDK Plugin
by Wikitude GmbH - [www.wikitude.com](http://www.wikitude.com)

##The Wikitude PhoneGap Plugin

The Wikitude PhoneGap Plugin enables web developers to embed an augmented reality view into their PhoneGap project. You can create a fully featured app with advanced augmented reality features, including image recognition, purely using HTML, CSS and JavaScript.

* Available for iOS and Android
* Simple and seamless native PhoneGap integration
* Fully customizable augmented reality (AR) view
* Full feature set of the Wikitude SDK
* AR content is purely written in HTML and JavaScript

![image](http://www.wikitude.com/wp-content/uploads/2012/12/Plugin_Phonegap.png)

For detailed documentation including a setup and getting started guide please see the official documentation under: [http://developer.wikitude.com/documentation/phonegap](http://developer.wikitude.com/documentation/phonegap)

### Supported mobile operating systems
* Android 
* iOS

### Installation via plugman

#### Android 
execute 

	sudo plugman --platform android --project {PROJECT/PATH}/platforms/android --plugin https://github.com/Wikitude/wikitude-phonegap.git
	
This will install all required components and even copy an index_samples.html file so you can test ImageRecognition and POI-Loading right away.

Find details on how to set-up project with latest PhoneGap version and command-line at the [phoneGap website]([Follow phoneGap install instructions](http://docs.phonegap.com/en/3.0.0rc1/guide_cli_index.md.html#The%20Command-line%20Interface)

### Manual installation
#### Android 
* Create a folder called com/wikitude/phonegap within your project's src- folder and copy `WikitudePlugin.java` into it
* Add following line to your `res/xml/config.xml`

		<feature name="WikitudePlugin">
        	<param name="android-package" value="com.wikitude.phonegap.WikitudePlugin"/>
        </feature>
* Copy `WikitudePlugin.js` in assets/www-folder and ensure to include it in the related HTMLs.
* Download the Wikitude SDK, copy the `wikitudesdk.jar` in the Android-folder to your projects libs-folder and add it to your project's build path
* Visit [Wikitude Developer Site
 ](http://developer.wikitude.com/) to find samples and how to license your app to remove the watermark in the camera

### Samples
A Sample project per supported platform is in the `samples` folder, you solely need to download `wikitudesdk.jar` for Android and the Wikitude-Framework for iOS upfront via [Wikitude's website](http://www.wikitude.com) and copy the files to the right folder.


### Tested PhoneGap versions
* PhoneGap 3.0.0 (26.07.2013), Wikitude SDK 3.0.1
* PhoneGap 2.8.1 (04.07.2013), Wikitude SDK 3.0
* PhoneGap 2.5.0 (28.02.2013), Wikitude SDK 2.0
* PhoneGap 2.4.0 (24.02.2013), Wikitude SDK 2.0
* PhoneGap 2.2.0 (18.01.2013), Wikitude SDK 2.0


###The Augmented Reality View
From a technical point of view the Wikitude SDK adds a UI component called **AR View**, similar to a web view. In contrast to a standard web view the `AR View` can render augmented reality content.

Content developed for the AR View is written in JavaScript and HTML. The HTML and JavaScript files for the AR view are different from the PhoneGap `.js` and `.html` files.


###Further developer resources
* [Full documentation and additional tutorials](http://developer.wikitude.com/documentation)
* [Developer Forum](http://developer.wikitude.com/developer-forum)
* [Wikitude SDK Download](http://developer.wikitude.com/download)
* [Google+ Page for News](https://plus.google.com/u/0/103004921345651739447/posts)
* [Developer Newsletter](http://www.wikitude.com/developer/newsletter)


## WATERMARK

The free trial version of the Wikitude SDK shows a start-up animation and a trial watermark in the camera-view. To get rid of this please have a look at the store and [pricing plan](http://www.wikitude.com/products/wikitude-sdk/pricing/) and consider a commercial or educational license.

## LICENSE

``` 
   Copyright 2012-2013 [Wikitude GmbH](http://www.wikitude.com)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
``` 
