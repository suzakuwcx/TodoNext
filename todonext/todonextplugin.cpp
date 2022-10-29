#include "todonextplugin.h"
#include "todonext.h"
#include "abstracttask.h"
#include <QLatin1String>

void TodoNextPlugin::registerTypes(const char *uri){
    Q_ASSERT(QLatin1String(uri) == QLatin1String("com.suzakuwcx.todonextplugin"));
    qmlRegisterType<TodoNext>(uri, 1, 0, "TodoNext");
    qmlRegisterUncreatableType<AbstractTask>(uri, 1, 0, "Task", "Create by TodoNext");
}

#include "todonextplugin.moc"