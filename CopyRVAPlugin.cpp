#include "CopyRVAPlugin.h"

#include <MainWindow.h>

#include <qapplication.h>
#include <qclipboard.h>

// Adapted from "SamplePlugin" examples from the Cutter repo (GPLv3)

void CopyRVAPlugin::setupPlugin() {}


static void CopyRVAToClipboard(uintptr_t address)
{
    CutterCore* core = Core();
    
    QClipboard* clipboard = QApplication::clipboard();
    size_t fileOffset = address - rz_bin_get_baddr(core->core()->bin);
    if (fileOffset > rz_bin_get_size(core->core()->bin))
    {
        // out of bounds - usually means we're trying to get the RVA of a function that hasn't been analysed
        QMessageBox error;
        error.setText("RVA out of bounds.");
        error.setInformativeText("Target function probably hasn't been analysed.");
        error.exec();
        return;
    }
    // leading '+' to make it obvious it's an offset
    // TODO setting to remove '+'
    // TODO setting to add module name
    clipboard->setText("+0x" + QString::number(fileOffset, 16));
}

void CopyRVAPlugin::setupInterface(MainWindow *main)
{
    // TODO are Adressables always functions?
    addressableAction = main->getContextMenuExtensions(MainWindow::ContextMenuType::Addressable)->addAction("Copy function RVA");
    QMetaObject::Connection con1 = connect(addressableAction, &QAction::triggered, this, [this]() 
    {
        // get address
        uintptr_t address = addressableAction->data().toULongLong();
        CopyRVAToClipboard(address);
    });

    disassemblyMenu = main->getContextMenuExtensions(MainWindow::ContextMenuType::Disassembly)->addMenu("Copy RVA");
    disassemblyInstAction = disassemblyMenu->addAction("Copy instruction RVA");
    QMetaObject::Connection con2 = connect(disassemblyInstAction, &QAction::triggered, this, [this]()
    {
        // get address
        uintptr_t address = disassemblyMenu->menuAction()->data().toULongLong();
        CopyRVAToClipboard(address);
    });

    disassemblyFuncAction = disassemblyMenu->addAction("Copy function RVA");
    QMetaObject::Connection con3 = connect(disassemblyFuncAction, &QAction::triggered, this, [this]()
    {
        // get address
        uintptr_t address = disassemblyMenu->menuAction()->data().toULongLong();
        CutterCore* core = Core();
        RVA functionStart = core->getFunctionStart(address);
        CopyRVAToClipboard(functionStart);
    });

    if(!con1 || !con2 || !con3)
        Core()->message("CopyRVAPlugin: Connection failed");

    Core()->message("CopyRVAPlugin: loaded");
}
