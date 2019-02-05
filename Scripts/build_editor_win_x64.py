#!/usr/bin/python

# Builds and packages the editor. Make sure you have MSBuild
# installed and the path is valid.

# Usage: "build_editor_win_x64 $Configuration"
# Where: $Configuration - e.g. OptimizedDebug, Release

import os

msbuildPath = "C:\\Program Files (x86)\\MSBuild\\14.0\\Bin\\amd64"
configuration = 'Release' #sys.argv[1]
buildPath = "..\\build\\"
solutionPath = buildPath + "Banshee.sln"

if not os.path.exists(msbuildPath):
    print("MSBuild path is not valid. Used path {0}: ".format(msbuildPath))
    exit;

os.environ["PATH"] += os.pathsep + msbuildPath

# Build the engine
os.system("msbuild {0} /p:Configuration={1};Platform=x64 /m".format(solutionPath, configuration))

# Build Win32 game executable
os.system("msbuild {0} /p:Configuration={1};Platform=x64 /m".format(solutionPath, configuration))

os.system("package_editor.py " + configuration)
