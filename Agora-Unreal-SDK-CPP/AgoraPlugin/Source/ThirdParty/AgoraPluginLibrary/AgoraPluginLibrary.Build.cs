//  Copyright (c) 2023 Agora.io. All rights reserved.

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using UnrealBuildTool;

public class AgoraPluginLibrary : ModuleRules
{

    private string soFormatStr = "		<copyFile src=\"$S(PluginDir)/$S(Architecture)/{0}\" dst=\"$S(BuildDir)/libs/$S(Architecture)/{0}\"/>";

    // bool bUE427OrLater = false;

    public AgoraPluginLibrary(ReadOnlyTargetRules Target) : base(Target)
    {
        // if(Target.Version.MajorVersion >= 4 && Target.Version.MinorVersion >= 27)
        // {
        //     bUE427OrLater = true;
        // }
        // else
        // {
        //     bUE427OrLater = false;
        // }


        Type = ModuleType.External;
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LoadWindowsLibrary(Path.Combine(ModuleDirectory, "Win", "Release", "x86_64"));
        }
        //else if(Target.Platform == UnrealTargetPlatform.Win32)
        //{
        //  LoadWindowsLibrary(Path.Combine(ModuleDirectory, "Win", "Release", "x86"));
        //}
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            LoadAndroidLibrary(Path.Combine(ModuleDirectory, "Android", "Release"));
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            LoadIOSLibrary(Path.Combine(ModuleDirectory, "IOS", "Release"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            LoadMacLibrary(Path.Combine(ModuleDirectory, "Mac", "Release"));
        }
    }

    public void LoadMacLibrary(string librarypath)
    {
        string[] dirstr = Directory.GetDirectories(librarypath);
        for (int i = 0; i < dirstr.Length; i++)
        {
            string frameworkName = Path.GetFileName(dirstr[i]);
            if (frameworkName.Contains(".framework"))
            {
                PublicFrameworks.Add(Path.Combine(librarypath, frameworkName));
            }
            Console.WriteLine("PublicFrameworks Add " + frameworkName);
        }
    }

    public void LoadIOSLibrary(string librarypath)
    {
        List<string> fileNames = GetAllFileNames(librarypath);
        for (int i = 0; i < fileNames.Count; i++)
        {
            string extension = Path.GetExtension(fileNames[i]);
            if (extension == ".zip")
            {
                string filenamWithoutExtension = Path.GetFileNameWithoutExtension(fileNames[i]);
                string filenamWithoutFrameWork = Path.GetFileNameWithoutExtension(filenamWithoutExtension);

#if UE_4_27_OR_LATER
    PublicAdditionalFrameworks.Add(new Framework(filenamWithoutFrameWork, Path.Combine(librarypath, fileNames[i]), "", true));
#else
    PublicAdditionalFrameworks.Add(new Framework(filenamWithoutFrameWork, Path.Combine(librarypath, fileNames[i]), ""));
#endif

                Console.WriteLine("PublicAdditionalFrameworks Add" + fileNames[i]);
            }
        }
        PublicFrameworks.AddRange(new string[] { "CoreML", "VideoToolbox", "Accelerate", "CFNetwork", "OpenGLES", "CoreTelephony" });
    }


    public void LoadAndroidLibrary(string librarypath)
    {
        string xmlTemplateData = File.ReadAllText(Path.Combine(librarypath, "APL_Template.xml"));
        string[] Architectures = { "armeabi-v7a", "arm64-v8a" };
        string sopathwrite = "";
        for (int i = 0; i < Architectures.Length; i++)
        {
            string architecturespath = Path.Combine(librarypath, Architectures[i]);
            List<string> fileNames = GetAllFileNames(architecturespath);
            for (int j = 0; j < fileNames.Count; j++)
            {
                string filename = fileNames[j];
                string extension = Path.GetExtension(filename);
                if (extension == ".so")
                {
                    string sopath = string.Format(soFormatStr, filename);
                    if (!sopathwrite.Contains(sopath))
                    {
                        sopathwrite += sopath + "\r\n";
                    }
                    PublicAdditionalLibraries.Add(Path.Combine(architecturespath, filename));
                    Console.WriteLine("PublicAdditionalLibraries " + filename);
                }
            }
        }
        sopathwrite += "		<copyFile src=\"$S(PluginDir)/agora-rtc-sdk.jar\" dst=\"$S(BuildDir)/libs/agora-rtc-sdk.jar\" />" + "\r\n";
        sopathwrite += "		<copyFile src=\"$S(PluginDir)/agora-rtc-sdk-javadoc.jar\" dst=\"$S(BuildDir)/libs/agora-rtc-sdk-javadoc.jar\" />" + "\r\n";
        sopathwrite += "		<copyFile src=\"$S(PluginDir)/AgoraScreenShareExtension.aar\" dst=\"$S(BuildDir)/libs/AgoraScreenShareExtension.aar\" />";
        xmlTemplateData = xmlTemplateData.Replace("<!-- AgoraInsert -->", sopathwrite);
        File.WriteAllText(Path.Combine(librarypath, "APL_Generated.xml"), xmlTemplateData);
        AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(librarypath, "APL_Generated.xml"));
    }

    public void LoadWindowsLibrary(string librarypath)
    {
        List<string> fileNames = GetAllFileNames(librarypath);
        for (int i = 0; i < fileNames.Count; i++)
        {
            string filename = fileNames[i];

            string extension = Path.GetExtension(filename);
            if (extension == ".lib")
            {
                PublicAdditionalLibraries.Add(Path.Combine(librarypath, filename));
                Console.WriteLine("AdditionalLibraries Add" + filename);
            }
            else if (extension == ".dll")
            {
                PublicDelayLoadDLLs.Add(Path.Combine(librarypath, filename));
                Console.WriteLine("DelayLoadDLL Add" + filename);
            }

            RuntimeDependencies.Add(Path.Combine("$(ProjectDir)/Binaries/", Target.Platform + "", filename), Path.Combine(librarypath, filename));

            Console.WriteLine("RuntimeDependencies Add" + filename);
        }
    }

    List<string> GetAllFileNames(string path, string pattern = "*")
    {
        List<FileInfo> folder = new DirectoryInfo(path).GetFiles(pattern).ToList();

        return folder.Select(x => x.Name).ToList();
    }
}
