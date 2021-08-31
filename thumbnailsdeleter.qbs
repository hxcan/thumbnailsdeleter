import qbs

CppApplication
{
    files:
    [
        "GeneralCleaner.cpp",
        "GeneralCleaner.h",
        "main.cpp",
        "TrashCleaner.ui",
        "RpmbuildCleaner.ui",
        "ManageWindow.ui",
        "MainLogic.cpp",
        "MainLogic.h",
        "ThumbnailsDeleter.cpp",
        "ThumbnailsDeleter.h",
        "ThumbnailsDeleter.ui",
        "TrashCleaner.cpp",
        "TrashCleaner.h",
        "ManageWindow.cpp",
        "ManageWindow.h",
        "GeneralCleaner.ui",
        "TdPreCompile.h",
        "RpmbuildCleaner.cpp",
        "RpmbuildCleaner.h",
        "mapReduceFunctions.cpp",
        "mapReduceFunctions.h",
    ]
 
    Depends
    {
        name: "Qt"
        submodules: 
            [
            "core",
            "gui",
            "widgets",
            "concurrent",
        ]
    }
    
    cpp.dynamicLibraries:
        [
        "ParallizedAlgorithms",
        "Qt5Gui",
        "Qt5Concurrent",
        "Qt5Core",
        "Qt5Widgets",
    ]
    
    Group 
    {
        name: "The app itself"
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
        
//        qbs -f /root/SoftwareDevelop/thumbnailsdeleter/thumbnailsdeleter/thumbnailsdeleter.qbs  profile:qt-5-11-3 qbs.installRoot:/usr
//        qbs-setup-qt --detect
    }
}
        
    
    
