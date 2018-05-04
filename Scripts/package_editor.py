#!/usr/bin/python

# Packages the editor by copying all relevant files to the Builds directory.
# This will not execute the editor build, and is implied the editor has been
# been built before executing this script.

# Usage: "package_editor $Configuration"
# Where: $Configuration - e.g. Debug, OptimizedDebug

import os
import sys
import shutil

configuration = 'OptimizedDebug' #sys.argv[1]
dataEntriesToIgnore = ['Raw', 'Settings.asset']
binEntriesToIgnore = ['Game.exe', 'Game.pdb']

dataFolder = 'Data'
bsfDataFolder = 'Source\\bsf\\Data'
assembliesFolder = 'Assemblies'
monoFolder = 'Mono'
libFolder = 'x64\\' + configuration + '\\'

inputDataFolder = '..\\' + dataFolder
inputBsfDataFolder = '..\\' + bsfDataFolder
inputBinFolder = '..\\bin\\'
inputAssembliesFolder = inputBinFolder + assembliesFolder
inputMonoFolder = inputBinFolder + monoFolder
inputLibFolder = inputBinFolder + libFolder

outputBaseFolder = '..\\Builds\Banshee3D\\'
outputEditorDataFolder = outputBaseFolder + 'EditorData'
outputDataFolder = outputBaseFolder + dataFolder
outputBinFolder = outputBaseFolder + '\\bin\\'
outputAssembliesFolder = outputBinFolder + assembliesFolder
outputMonoFolder = outputBinFolder + monoFolder
outputLibFolder = outputBaseFolder

def copytree(src, dst):
    if not os.path.exists(dst):
        os.makedirs(dst)
    
    for item in os.listdir(src):
        if item in dataEntriesToIgnore:
            print("Ignoring " + item)
            continue
        
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        print(s)
        if os.path.isdir(s):
            copytree(s, d)
        else:
            shutil.copy2(s, d)	
	
def package_editor():
    if os.path.exists(outputBaseFolder):
        shutil.rmtree(outputBaseFolder)

    copytree(inputDataFolder, outputEditorDataFolder)
    copytree(inputBsfDataFolder, outputDataFolder)
    copytree(inputAssembliesFolder, outputAssembliesFolder)
    copytree(inputMonoFolder, outputMonoFolder)

    for root, dirs, files in os.walk(inputLibFolder):
        for file in files:
            if(file.lower().endswith(('.dll', '.exe', '.pdb', '.so', '.dylib'))):
                if(not file in binEntriesToIgnore):
                    filePath = os.path.join(root, file)
                    shutil.copy(filePath, outputLibFolder)

package_editor()
