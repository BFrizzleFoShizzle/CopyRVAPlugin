#ifndef CUTTERCOPYRVAPLUGIN_H
#define CUTTERCOPYRVAPLUGIN_H

#include <CutterPlugin.h>
#include <qmenu.h>

// Adapted from "SamplePlugin" examples from the Cutter repo (GPLv3)

class CopyRVAPlugin : public QObject, CutterPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "re.rizin.cutter.plugins.CutterPlugin")
    Q_INTERFACES(CutterPlugin)

public:
    void setupPlugin() override;
    void setupInterface(MainWindow *main) override;

    QString getName() const override { return "Copy RVA Plugin"; }
    QString getAuthor() const override { return "Bryden Frizzell"; }
    QString getDescription() const override { return "A plugin for copying Relative Virtual Addresses."; }
    QString getVersion() const override { return "1.0"; }

private:
    QAction* addressableAction;
    QMenu* disassemblyMenu;
    QAction* disassemblyFuncAction;
    QAction* disassemblyInstAction;
};

#endif // CUTTERCOPYRVAPLUGIN_H
