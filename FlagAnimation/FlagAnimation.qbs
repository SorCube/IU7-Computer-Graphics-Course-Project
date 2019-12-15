import qbs.FileInfo

QtApplication {
    Depends { name: "Qt.widgets" }
    
    // The following define makes your compiler emit warnings if you use
    // any Qt feature that has been marked deprecated (the exact warnings
    // depend on your compiler). Please consult the documentation of the
    // deprecated API in order to know how to port your code away from it.
    // You can also make your code fail to compile if it uses deprecated APIs.
    // In order to do so, uncomment the second entry in the list.
    // You can also select to disable deprecated APIs only up to a certain version of Qt.
    cpp.defines: [
        "QT_DEPRECATED_WARNINGS",
        /* "QT_DISABLE_DEPRECATED_BEFORE=0x060000" */ // disables all the APIs deprecated before Qt 6.0.0
    ]
    
    files: [
        "exceptions/baseexception.h",
        "exceptions/buildexception.h",
        "exceptions/drawexception.h",
        "exceptions/objectexception.h",
        "exceptions/transformexception.h",
        "exceptions/uploadexception.h",
        "facade/facade.cpp",
        "facade/facade.h",
        "gui/drawer.cpp",
        "gui/drawer.h",
        "main.cpp",
        "gui/mainwindow.cpp",
        "gui/mainwindow.h",
        "gui/mainwindow.ui",
        "gui/canvas.cpp",
        "gui/canvas.h",
        "filemanager/filemanager.cpp",
        "filemanager/filemanager.h",
        "managers/drawmanager.cpp",
        "managers/drawmanager.h",
        "managers/objectmanager.h",
        "managers/uploadmanager.h",
        "model/mathvector.cpp",
        "model/mathvector.h",
        "model/model.cpp",
        "model/model.h",
        "model/object.h",
        "model/triangle.cpp",
        "model/triangle.h",
        "model/vertex.cpp",
        "model/vertex.h",
        "scene/camera.cpp",
        "scene/camera.h",
        "scene/scene.cpp",
        "scene/scene.h",
        "transformation/transformation.h",
        "workers/modelbuilder.cpp",
        "workers/modelbuilder.h",
        "workers/modelcreator.cpp",
        "workers/modelcreator.h",
        "workers/modeluploader.cpp",
        "workers/modeluploader.h",
        "workers/objecttransformator.cpp",
        "workers/objecttransformator.h",
    ]
    
    install: true
    installDir: qbs.targetOS.contains("qnx") ? FileInfo.joinPaths("/tmp", name, "bin") : base
}
