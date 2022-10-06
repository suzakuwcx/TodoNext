#include "todonextplugin.h"
#include "todonext.h"

void TodoNextPlugin::registerTypes(const char *uri){
    Q_ASSERT(QLatin1String(uri) == QLatin1String("com.suzakuwcx.todonextplugin"));
    qmlRegisterType<TodoNext>(uri, 1, 0, "TodoNext");
}

#include "todonextplugin.moc"