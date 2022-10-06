#ifndef TODUNEXTPLUGIN_H
#define TODUNEXTPLUGIN_H

#include <QQmlExtensionPlugin>
#include <QQmlEngine>


class TodoNextPlugin : public QQmlExtensionPlugin {
	Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.suzakuwcx.todonextplugin")
public:
	void registerTypes(const char *uri) override;
};
#endif