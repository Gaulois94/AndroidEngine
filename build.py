#!/usr/bin/python3

import re 
import subprocess
import xml.etree.ElementTree as ET
import os

err = False
if os.path.exists("build.xml"):
	err = subprocess.call("ant debug -Dcompression.disable=set", shell=True)

proc = subprocess.Popen("adb devices -l", shell=True, stdout=subprocess.PIPE)
(output, errors) = proc.communicate()
name = None
activityName = None

if not err and output.find(b"usb") != -1 and os.path.exists("AndroidManifest.xml"):
	tree = ET.parse("AndroidManifest.xml")
	root = tree.getroot()
	if "package" in root.attrib:
			name = root.attrib["package"]
	for activity in root.iter("activity"):
		print(activity.attrib)
		if "{http://schemas.android.com/apk/res/android}name" in activity.attrib:
			activityName = activity.attrib["{http://schemas.android.com/apk/res/android}name"]
	if not (name and activityName):
		exit()
	subprocess.call("ant installd", shell=True)
	subprocess.call("adb shell am start -n " + name + "/." + activityName, shell=True)
